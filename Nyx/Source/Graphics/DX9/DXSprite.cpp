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
#include "IO/File.h"
#include "Graphics/ISprite.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXSprite.h"

namespace Nyx {
	namespace DX9 {
		using std::shared_ptr;
		using Nyx::File;

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, int w, int h) 
			:ISprite()
		{
			//デバイスの取得
			Direct3DDevice d3dDevice = device.GetDevice();

			// スプライトの作成
			HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
			Assert(hr == S_OK);

			//「テクスチャオブジェクト」の作成
			hr = D3DXCreateTexture(d3dDevice, w, h, 0, 0,	D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, &texture);
			Assert(hr == S_OK);

			//テクスチャの幅と高さを保存
			SetWidth(w);
			SetHeight(h);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw, int ch)
			: ISprite(w, h, 0, 0, cw, ch)  {
				//チップサイズ
				SetChipSize(cw, ch);

				//デバイスの取得
				Direct3DDevice d3dDevice = device.GetDevice();

				// スプライトの作成
				HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
				Assert(hr == S_OK);

				//「テクスチャオブジェクト」の作成
				hr = D3DXCreateTextureFromFileEx(d3dDevice, fileName.c_str(), w, h, 0, 0,	D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,
					0xFF,NULL,NULL,&texture);
				Assert(hr == S_OK);

				//ファイルからリソースデータをキャッシュする
				std::unique_ptr<File> file = std::unique_ptr<File>(new File(fileName, Nyx::ReadMode));
				ulong size = file->GetSize();
				uchar *buffer = NULL;
				buffer = new uchar [size];
				file->Read(buffer, size);
				SetResourceData(fileName, size, buffer);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, shared_ptr<char> data, uint size, int w, int h, int cw, int ch)
			: ISprite(w, h, 0, 0, cw, ch) {
				//チップサイズの設定
				SetChipSize(cw, ch);

				///デバイスの取得
				Direct3DDevice d3dDevice = device.GetDevice();

				// スプライトの作成
				HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
				Assert(hr == S_OK);

				//「テクスチャオブジェクト」の作成
				hr = D3DXCreateTextureFromFileInMemoryEx(d3dDevice, &*data, size, w,h, 0, 0, D3DFMT_UNKNOWN, 
					D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xFF, NULL, NULL, &texture);
				//hr =D3DXCreateTextureFromFileInMemory(d3dDevice, (void*)&*data, size, &texture);
				Assert(hr == S_OK);

				//リソースデータをキャッシュする
				SetResourceData(L"スプライト", size, (uchar*)(&*data));
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Restore() 
		{
			//リソースがキャッシュされていない
			if (GetResourceSize() == 0) {return;}

			//キャッシュしてあるリソースデータを読み込む
			uchar* buffer;
			uint size = GetResourceSize();
			buffer = new uchar[size];
			GetResourceData(&buffer);

			Direct3DDevice d3dDevice;
			HRESULT hr = sprite->GetDevice(&d3dDevice);
			Assert(SUCCEEDED(hr));
			int w = this->GetWidth();
			int h = this->GetHeight();

			//「テクスチャオブジェクト」の作成
			hr = D3DXCreateTextureFromFileInMemoryEx(d3dDevice, buffer, size, w,h, 0, 0, D3DFMT_UNKNOWN, 
				D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,0xff000000, NULL, NULL, &texture);
			Assert(hr == S_OK);
			SafeDelete(buffer);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Release() 
		{
			SafeRelease(sprite);
			SafeRelease(texture);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::~DXSprite() 
		{
			Release();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Fill(Rect2i rect, Color4c color) {
			Assert(sprite  != NULL);
			Assert(texture != NULL);

			RECT r = {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
			D3DLOCKED_RECT lr;
			HRESULT hr = texture->LockRect(0, &lr, &r, 0);
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				return;
			}
			FillMemory(lr.pBits , lr.Pitch * GetHeight(), 
				D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			hr = texture->UnlockRect(0);
			Assert(hr == S_OK);

		}
		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, Color4c color) {	
			RECT rect= {0,0, GetWidth(), GetHeight()};
			D3DXVECTOR3 pos(0, 0, 0);
			D3DXVECTOR3 center(GetWidth()/2.f, GetHeight()/2.f, 0);

			//
			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;	
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, int cx, int cy, Color4c color) {
			int height, width;
			GetChipSize(width, height);

			RECT rect= {cx*width, cy*height, cx*width+width, cy*height+height};
			D3DXVECTOR3 center(cx*width+width/2.f, cy*height+height/2.f, 0);
			D3DXVECTOR3 pos(0, 0, 0);

			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture,&rect, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, Rect2i rect, Color4c color) {
			RECT r = {rect.x, rect.y, rect.x + rect.width, rect.y+rect.height};
			D3DXVECTOR3 center(rect.width/2.f, rect.height/2.f, 0.f);
			D3DXVECTOR3 pos(0, 0, 0);

			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture,&r, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &r, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::OnLostDevice() {
			return sprite->OnLostDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::OnResetDevice() {
			return sprite->OnResetDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::CreateSprite(DirectGraphicsDevice& device) {
			return D3DXCreateSprite(device.GetDevice(),&sprite);
		}
	}
}