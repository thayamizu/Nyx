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
#ifndef NYX_CORE_DIRECT_GRAPHICS_DEVICE_H_
#define NYX_CORE_DIRECT_GRAPHICS_DEVICE_H_

#include "Primitive/Color3.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "DirectXDefinition.h"

namespace Nyx {
	namespace DX9 {

		///DirectGraphicsデバイス
		class DirectGraphicsDevice 
		{
		public:
			/**
			* コンストラクタ
			* @param HWND ウインドウハンドルインスタンス
			* @param int ウインドウの幅(ウインドウの幅・高さ＝バックバッファの幅・高さとなります)
			* @param int ウインドウの高さ
			* @param bool ウインドウモード
			*/
			DirectGraphicsDevice(HWND hwnd, int w, int h, bool mode=true);

			/**
			* デストラクタ
			*/
			~DirectGraphicsDevice();

			/**
			* デバイスロスト時の処理
			* @return bool デバイスリセットに成功すればtrueを返します
			*/
			bool OnLostDevice();

			/**
			* Direct3Dデバイスを返します。
			* @return Direct3DDevice  
			*/
			D3dDevice9Ptr GetDevice();

			/**
			*　カーソルの表示・非表示を切り替えます
			* @param bool trueであればカーソル表示
			*/
			void ShowCursor(bool);

			/**
			* ディスプレイ―モ度を切り替えます。
			* @return bool ウインドウモードであればtrueを返します
			*/
			bool ChangeDisplayMode();

			/**
			* ウインドウモードかどうかを判定
			* @return bool ウインドウモードであるならばtrue
			*/
			bool IsWindowed();

			/**
			* フルスクリーンモードかどうかを判定
			* @return bool フルスクリーンモードであるならばtrue
			*/
			bool IsFullScreen();
			
			
			
			//---------------------------------------------------------------------------
			//サンプラーステート
			//---------------------------------------------------------------------------
			/**
			*　現在のサンプラーステートの取得
			* @param DWORD サンプラーステートインデックス
			* @param D3DSAMPLERSTATETYPE サンプラーステートの種類
			* @param DWORD 取得するサアンプラーステートの値
			*/
			void GetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD* value);


			/**
			* サンプラーステートの設定
			* @param DWORD サンプラーステートインデックス
			* @param D3DSAMPLERSTATETYPE サンプラーステートの種類
			* @param DWORD 設定するステート値
			*/
			void SetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD value);
			
			
			//---------------------------------------------------------------------------
			//ライト
			//---------------------------------------------------------------------------
			/**
			*ライトを取得
			*/
			void GetLight(D3DLIGHT9 *);

			/**
			* ライトを設定
			* @param Vector3f ライト位置
			* @param Vector3f 方向ベクトル
			* @param Color3f 拡散反射光の値(RGB)
			* @param Color3f 鏡面反射光の値(RGB)
			* @param float ライトの範囲
			* @param D3DLIGHTTYPE ライトの種類(ポイントライトディレクショナルライトなど)
			*/
			void SetLight(Vector3f pos, Vector3f dir, Color3f diffuse, Color3f specular, float range, D3DLIGHTTYPE type);

			//---------------------------------------------------------------------------
			//トランスフォーム
			//---------------------------------------------------------------------------
			/**
			* デバイスのトランスフォーム関連ステートを設定する
			* @param D3DTRANSFORMSTATETYPE トランスフォームステートの値
			* @param const Matrix44トランスフォーム行列
			*/
			void SetTransform(D3DTRANSFORMSTATETYPE state, const Matrix44 * matrix);


			/**
			*デバイスのトランスフォーム関連ステートを取得する
			* @param D3DTRANSFORMSTATETYPE トランスフォームステートの値
			* @param Matrix44トランスフォーム行列
			*/
			void GetTransform(D3DTRANSFORMSTATETYPE state, Matrix44 * matrix);

			//---------------------------------------------------------------------------
			//ビューポート
			//---------------------------------------------------------------------------
			/**
			* ビューポートを取得
			* @param D3DVeiwPort ビューポート
			*/
			void GetViewPort(D3DVIEWPORT9* viewport);

			/**
			*　ビューポートの設定
			* @param int x値
			* @param int y値
			* @param int　幅
			* @param int　高さ
			* @param float z-near
			* @param float z-far
			*/
			void SetViewPort(int x, int y, int width, int height, float near, float far);

			//---------------------------------------------------------------------------
			//描画
			//---------------------------------------------------------------------------
			/**
			* 画面をクリア
			*/
			void Clear();
			/**
			* シーンの開始
			* @return bool シーンの開始に失敗した場合にはfalseが返ります
			*/
			bool BeginScene();

			/**
			* シーンの終了
			*/
			void EndScene();

			void RenderPrimitive();

			//---------------------------------------------------------------------------
			//ステートブロック
			//---------------------------------------------------------------------------
			void BeginStateBlock();
			void EndStateBlock();


			//---------------------------------------------------------------------------
			//頂点記述
			//---------------------------------------------------------------------------
			void CreateVertexDeclaration();
			
			//---------------------------------------------------------------------------
			//頂点バッファの生成
			//---------------------------------------------------------------------------
			void CreateVertexBuffer();
			
			//---------------------------------------------------------------------------
			//フォグ
			//---------------------------------------------------------------------------
			void SetFog();

			//---------------------------------------------------------------------------
			//Zテスト
			//---------------------------------------------------------------------------
			void SetZTest();

			//---------------------------------------------------------------------------
			//修復
			//---------------------------------------------------------------------------
			/**
			* デバイスのリセット
			* @param　D3DPRESETN_PARAMETERS デバイスパラメータ
			* @return デバイスリセットに成功すればtrue
			*/
			bool ResetDevice(D3DPRESENT_PARAMETERS& d3dpp);
		private:
			RECT windowSize;
			int backBufferWidth;
			int backBufferHeight;

			bool isWindowed;
			bool isLostDevice;
			bool isShowCursor;

			HWND hwnd;
			D3d9Ptr d3d_;
			HMENU hMenu;
			D3dDevice9Ptr d3dDevice_;
			D3DPRESENT_PARAMETERS presentParameter;
		};
	}
}

#endif