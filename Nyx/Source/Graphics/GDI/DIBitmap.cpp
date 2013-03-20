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
#include "Graphics/GDI/DIBitmap.h"
#include "Primitive/Color3c.h"
#include "Debug/Assert.h"

namespace Nyx {
	namespace GDI {

		//-------------------------------------------------------------------------------------------------------
		//
		DIBitmap::DIBitmap(const std::wstring fileName_){
			hMemDC = ::CreateCompatibleDC(NULL);
			hbitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), 
				fileName_.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			Assert(hbitmap != NULL);
			::GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		DIBitmap::~DIBitmap() {
			Release();
		}

		//-------------------------------------------------------------------------------------------------------
		//
		//bool DIBitmap::LoadFromFile(const std::wstring fileName_) {
		//	//一度開放する
		//	Release();
		//
		//	hMemDC = ::CreateCompatibleDC(NULL);
		//	hbitmap = (HBITMAP)LoadImage(::GetModuleHandle(NULL), 
		//		fileName_.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//
		//
		//	::GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		//
		//	return true;
		//}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y,ulong op) {
			//画像を選択
			SelectObject(hMemDC, hbitmap);
			//指定した座標にそのまま描画
			::BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int sx, int sy, ulong op) {
			//画像を選択
			SelectObject(hMemDC, hbitmap);
			//伸縮して描画
			::StretchBlt(hdc, x, y, bitmap.bmWidth*sx, bitmap.bmHeight*sy, hMemDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, ulong op) {
			//画像を選択
			SelectObject(hMemDC, hbitmap);
			::StretchBlt(hdc, x, y, width, height, hMemDC, width*tx, height*ty, width, height, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int colorKey) {
			//画像を選択
			SelectObject(hMemDC, hbitmap);
			//抜き色を指定して描画
			::TransparentBlt(
				hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, 
				hMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, 
				colorKey);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey) {
			//画像を選択
			SelectObject(hMemDC, hbitmap);
			//抜き色を指定して描画(チップ対応)
			::TransparentBlt(
				hdc, x, y, width, height, hMemDC,
				width*tx, height*ty, width, height, colorKey);
		}


		//-------------------------------------------------------------------------------------------------------
		//アルファブレンディング
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey, uchar alpha) {
			//アルファブレンドの設定
			BLENDFUNCTION blend;
			blend.BlendOp    = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = alpha;
			blend.AlphaFormat = 0;

			//一時領域の作成
			HDC tmp = ::CreateCompatibleDC(hdc);
			HBITMAP work=::CreateCompatibleBitmap(hdc, bitmap.bmWidth, bitmap.bmHeight);
			SelectObject(tmp, work);

			//一時領域へチップ画像を描画(抜き色指定）
			SelectObject(hMemDC, hbitmap);
			::TransparentBlt(
				tmp, 0, 0, width, height, 
				hMemDC, width*tx, height*ty, width, height, colorKey);

			//一時領域へ描画したものを、アルファブレンディングしてプライマリに転送
			AlphaBlend(
				hdc, x, y, width, height, 
				tmp, 0, 0, width, height, blend);

			//一時領域の解放
			DeleteObject(work);
			DeleteObject(tmp);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		long DIBitmap::GetWidth() {
			return bitmap.bmWidth;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		long DIBitmap::GetHeight() {
			return bitmap.bmHeight;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		long* DIBitmap::GetPixel() {
			return reinterpret_cast<long*>(bitmap.bmBits);
		}

		//---------------------------------------------------------------
		//解放処理
		//---------------------------------------------------------------
		void DIBitmap::Release() {
			DeleteDC(hMemDC);
			DeleteObject(hbitmap);
		}
	}
}