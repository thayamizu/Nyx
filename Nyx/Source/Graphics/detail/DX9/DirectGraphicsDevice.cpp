/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Primitive/Vector3.h"

#include "Primitive/Matrix44.h"

#include "Graphics/IGraphicsDevice.h"
#include "Graphics/detail/DX9/DirectXDefinition.h"
#include "Graphics/detail/DX9/DirectGraphicsDevice.h"

namespace Nyx {
	namespace DX9 {

		DirectGraphicsDevice::DirectGraphicsDevice(HWND hWnd, int w, int h, bool mode)
			:hwnd(hWnd), backBufferWidth(w), backBufferHeight(h), hMenu(NULL), isWindowed(mode), isShowCursor(false), isLostDevice(false)
		{
			//ウインドウサイズの記憶
			GetWindowRect(hwnd, &windowSize);

			// Direct3Dオブジェクトの作成
			LPDIRECT3D9  d3d = Direct3DCreate9(D3D_SDK_VERSION);
			Assert(d3d != NULL);

			//プライマリディスプレイのアダプタディスプレイモードを取得
			D3DDISPLAYMODE display;
			d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);

			// D3DPresentParametersの設定
			ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

			//(ウインドウ・モード用)
			presentParameter.BackBufferWidth			= backBufferWidth;
			presentParameter.BackBufferHeight			= backBufferHeight;
			presentParameter.BackBufferFormat			= /*isWindowed?D3DFMT_UNKNOWN:*/display.Format;
			presentParameter.BackBufferCount			= 1;
			presentParameter.MultiSampleType			= D3DMULTISAMPLE_NONE;
			presentParameter.MultiSampleQuality			= 0;
			presentParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
			presentParameter.hDeviceWindow				= hWnd;
			presentParameter.Windowed					= isWindowed? true: false;
			presentParameter.EnableAutoDepthStencil		= true;
			presentParameter.AutoDepthStencilFormat		= D3DFMT_D16;
			presentParameter.Flags						= 0;
			presentParameter.FullScreen_RefreshRateInHz = 0;
			presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

			//Direct3DDeviceオブジェクトの生成
			LPDIRECT3DDEVICE9 d3dDevice = nullptr;
			HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&presentParameter, &d3dDevice );
			if( FAILED(hr)) {  
				hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&presentParameter, &d3dDevice);
				if( FAILED(hr)) {	  
					hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&presentParameter, &d3dDevice);
					if( FAILED(hr)){
						hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&presentParameter, &d3dDevice);
						Assert(hr == S_OK);
					}
				}
			}

			ResetDevice(presentParameter);

			d3d_ = D3d9Ptr(d3d, true);
			d3dDevice_ = D3dDevice9Ptr(d3dDevice, true);
		}

		//-----------------------------------------------------------------------------------------
		// ウインドウモードかどうかの判定
		DirectGraphicsDevice::~DirectGraphicsDevice() {
		}

		//-----------------------------------------------------------------------------------------
		// ウインドウモードかどうかの判定
		void DirectGraphicsDevice::ShowCursor(bool showCursor) {
			isShowCursor = showCursor;
			d3dDevice_->ShowCursor(showCursor);
		}

		//-----------------------------------------------------------------------------------------
		// ウインドウモードかどうかの判定
		bool DirectGraphicsDevice::IsWindowed() {
			return isWindowed;
		}

		//-----------------------------------------------------------------------------------------
		// フルスクリーンかどうかの判定
		bool DirectGraphicsDevice::IsFullScreen() {
			return !isWindowed;
		}

		//-----------------------------------------------------------------------------------------
		// フルスクリーン<->ウインドウの切り替え
		bool DirectGraphicsDevice::ChangeDisplayMode() {

			//ウインドウモードを入れ替え
			isWindowed= !isWindowed;
			presentParameter.Windowed = isWindowed;
			if (isWindowed) {
				/*presentParameter.BackBufferWidth=backBufferWidth;
				presentParameter.BackBufferHeight=0;
				presentParameter.BackBufferFormat = D3DFMT_UNKNOWN;*/
			}
			else {
				//プライマリディスプレイのアダプタディスプレイモードを取得
				/*D3DDISPLAYMODE display;
				d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);
				presentParameter.BackBufferWidth = backBufferWidth;
				presentParameter.BackBufferHeight = backBufferHeight;
				presentParameter.BackBufferFormat = display.Format;
				*/
			}

			//デバイスリセット
			ResetDevice(presentParameter);

			return isWindowed;
		}
	
		//-----------------------------------------------------------------------------------------
		// サンプラーステートの取得
		void DirectGraphicsDevice::GetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD* value) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetSamplerState(sampler, type, value);

		}

		//-----------------------------------------------------------------------------------------
		// サンプラーステートの設定
		void DirectGraphicsDevice::SetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD value) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->SetSamplerState(sampler, type, value);
		}

		//-----------------------------------------------------------------------------------------
		// ライティングの取得
		void DirectGraphicsDevice::GetLight(D3DLIGHT9* light) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetLight(0, light);
		}

		//-----------------------------------------------------------------------------------------
		// ライティングの設定
		void DirectGraphicsDevice::SetLight(Vector3f pos, Vector3f dir, Color3f diffuse, Color3f specular, float range, D3DLIGHTTYPE type) {
			Assert(d3dDevice_ != nullptr);
			D3DLIGHT9 light;
			ZeroMemory( &light, sizeof(D3DLIGHT9) );
			
			light.Type       = type;
			light.Range      = range;

			light.Position.x = pos.x;
			light.Position.y = pos.y;
			light.Position.z = pos.z;

			light.Diffuse.r  = diffuse.r;
			light.Diffuse.g  = diffuse.g;
			light.Diffuse.b  = diffuse.b;

			light.Specular.r = specular.r;
			light.Specular.g = specular.g;
			light.Specular.b = specular.b;

			D3DXVec3Normalize( 
				reinterpret_cast<D3DXVECTOR3*>(&light.Direction), reinterpret_cast<D3DXVECTOR3*>(&dir) );

			HRESULT hr = d3dDevice_->SetLight( 0, &light );
			d3dDevice_->LightEnable( 0, true );
			Assert(hr == S_OK);

		}

		//-----------------------------------------------------------------------------------------
		// ビューポートの取得
		void DirectGraphicsDevice::GetViewPort(D3DVIEWPORT9* vp) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetViewport(vp);
		}

		//-----------------------------------------------------------------------------------------
		// ビューポートの設定
		void DirectGraphicsDevice::SetViewPort(int x, int y, int width, int height, float front, float back) {
			Assert(d3dDevice_ != nullptr);
			D3DVIEWPORT9 vp;
			vp.X  = x;
			vp.Y  = y;
			vp.Width  = width;
			vp.Height = height;
			vp.MinZ=front;
			vp.MaxZ=back;
			d3dDevice_->SetViewport(&vp);
		}

		//-----------------------------------------------------------------------------------------
		// トランスフォーム行列の設定
		void DirectGraphicsDevice::SetTransform(  D3DTRANSFORMSTATETYPE state, const Matrix44 * matrix)
		{
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->SetTransform(state, reinterpret_cast<const D3DXMATRIX*>(matrix));
		}

		//-----------------------------------------------------------------------------------------
		// トランスフォーム行列の取得
		void DirectGraphicsDevice::GetTransform(  D3DTRANSFORMSTATETYPE state, Matrix44 * matrix) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->SetTransform(state, reinterpret_cast<D3DXMATRIX*>(matrix));
		}

		//-----------------------------------------------------------------------------------------
		// デバイスの取得
		D3dDevice9Ptr DirectGraphicsDevice::GetDevice() {
			Assert(d3dDevice_ != nullptr);
			return d3dDevice_;
		}


		//-----------------------------------------------------------------------------------------
		//デバイスのリセット
		bool DirectGraphicsDevice::ResetDevice(D3DPRESENT_PARAMETERS& d3dpp) {

			HRESULT hr = d3dDevice_->Reset(&d3dpp);
			switch(hr) {
			case D3DERR_INVALIDCALL: 
				DebugOutput::DebugMessage("無効な呼び出しです");
				return false;
			case D3DERR_DEVICELOST:
				DebugOutput::DebugMessage("デバイスロスト");
				isLostDevice=true;
				return false;
			case D3DERR_DRIVERINTERNALERROR: 
				DebugOutput::DebugMessage("ドライバー内部エラー");
				PostQuitMessage(0);//強制終了
				return false;
			}
			//ビューポートの設定
			SetViewPort(0, 0, backBufferWidth, backBufferHeight, 0.f, 1.f);

			// Zバッファー処理を有効にする
			d3dDevice_->SetRenderState( D3DRS_ZENABLE, true );  
			//ソリッド
			d3dDevice_->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
			// カリング
			d3dDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			// ライトを有効にする
			d3dDevice_->SetRenderState( D3DRS_LIGHTING, true );
			// アンビエントライト（環境光）を設定する
			d3dDevice_->SetRenderState( D3DRS_AMBIENT, 0x00111111 );
			// スペキュラ（鏡面反射）を有効にする
			d3dDevice_->SetRenderState(D3DRS_SPECULARENABLE,true);
			//シェーディングモード(グーロー)
			d3dDevice_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
			//アルファブレンディングを設定する
			d3dDevice_->SetRenderState ( D3DRS_ALPHABLENDENABLE, true );	
			d3dDevice_->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			d3dDevice_->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			d3dDevice_->SetRenderState( D3DRS_ALPHATESTENABLE, true );	
			

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//クリア
		void DirectGraphicsDevice::Clear() {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(125, 125, 125, 0), 1.f, 0);
		}

		//-----------------------------------------------------------------------------------------
		//描画の開始
		bool DirectGraphicsDevice::BeginScene() {
			if (isLostDevice) {
				return false;
			}
			Assert(d3dDevice_ != nullptr);
			// 画面を青でクリアする
			d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 128), 1.f, 0);
			// 描画開始
			if (SUCCEEDED(d3dDevice_->BeginScene())) {
				return true;
			}
			return false;
		}

		//-----------------------------------------------------------------------------------------
		//描画の終了
		void DirectGraphicsDevice::EndScene() {
			Assert(d3dDevice_ != nullptr);
			// 描画終了
			d3dDevice_->EndScene();
			// 実際に画面に描画結果を表示する
			switch (d3dDevice_->Present(NULL, NULL, NULL, NULL)) {

				// デバイスが落っこちていた場合
			case D3DERR_DEVICELOST:
				isLostDevice = true;
				break;
				// ドライバエラーが起きた場合
			case D3DERR_DRIVERINTERNALERROR:
				throw std::runtime_error("内部ドライバエラーが発生");
				break;
			default:
				break;
			}
		}

		//-----------------------------------------------------------------------------------------
		//デバイスロスト時の処理
		bool DirectGraphicsDevice::OnLostDevice() {
			// デバイスのリセットが出来るかを調べる
			if (d3dDevice_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
				// デバイスをリセットする
				if (!ResetDevice(presentParameter)) {
					return false;	
				}
				else {
					isLostDevice=false;
				}
			}
			else {
				return false;
			}
			return true;;
		}
	}
}