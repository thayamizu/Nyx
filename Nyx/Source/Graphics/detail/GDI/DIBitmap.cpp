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
#include "Graphics/detail/GDI/DIBitmap.h"
#include "Primitive/Color3.h"
#include "Debug/Assert.h"

namespace nyx {
	namespace win32 {

		//-------------------------------------------------------------------------------------------------------
		//
		bitmap::bitmap(const std::wstring fileName_){
			hMemDC_ = ::CreateCompatibleDC(NULL);
			hBitmap_ = (HBITMAP)LoadImage(GetModuleHandle(NULL), 
				fileName_.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			NYX_ASSERT(hBitmap_ != NULL);
			::GetObject(hBitmap_, sizeof(BITMAP), &bmpData_);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		bitmap::~bitmap() {
			release();
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
		void bitmap::draw(HDC hdc, int x, int y,uint64_t op) {
			//画像を選択
			SelectObject(hMemDC_, hBitmap_);
			//指定した座標にそのまま描画
			::BitBlt(hdc, x, y, bmpData_.bmWidth, bmpData_.bmHeight, hMemDC_, 0, 0, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void bitmap::draw(HDC hdc, int x, int y, int sx, int sy, uint64_t op) {
			//画像を選択
			SelectObject(hMemDC_, hBitmap_);
			//伸縮して描画
			::StretchBlt(hdc, x, y, bmpData_.bmWidth*sx, bmpData_.bmHeight*sy, hMemDC_, 0, 0,bmpData_.bmWidth, bmpData_.bmHeight, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void bitmap::draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, uint64_t op) {
			//画像を選択
			SelectObject(hMemDC_, hBitmap_);
			::StretchBlt(hdc, x, y, width, height, hMemDC_, width*tx, height*ty, width, height, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void bitmap::draw(HDC hdc, int x, int y, int colorKey) {
			//画像を選択
			SelectObject(hMemDC_, hBitmap_);
			//抜き色を指定して描画
			::TransparentBlt(
				hdc, x, y, bmpData_.bmWidth, bmpData_.bmHeight, 
				hMemDC_, 0, 0, bmpData_.bmWidth, bmpData_.bmHeight, 
				colorKey);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void bitmap::draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey) {
			//画像を選択
			SelectObject(hMemDC_, hBitmap_);
			//抜き色を指定して描画(チップ対応)
			::TransparentBlt(
				hdc, x, y, width, height, hMemDC_,
				width*tx, height*ty, width, height, colorKey);
		}


		//-------------------------------------------------------------------------------------------------------
		//アルファブレンディング
		void bitmap::draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey, uint8_t alpha) {
			//アルファブレンドの設定
			BLENDFUNCTION blend;
			blend.BlendOp    = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = alpha;
			blend.AlphaFormat = 0;

			//一時領域の作成
			HDC tmp = ::CreateCompatibleDC(hdc);
			HBITMAP work=::CreateCompatibleBitmap(hdc, bmpData_.bmWidth, bmpData_.bmHeight);
			SelectObject(tmp, work);

			//一時領域へチップ画像を描画(抜き色指定）
			SelectObject(hMemDC_, hBitmap_);
			::TransparentBlt(
				tmp, 0, 0, width, height, 
				hMemDC_, width*tx, height*ty, width, height, colorKey);

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
		long bitmap::get_width() {
			return bmpData_.bmWidth;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		long bitmap::get_height() {
			return bmpData_.bmHeight;
		}

		//-------------------------------------------------------------------------------------------------------
		//
		long* bitmap::get_pixel() {
			return reinterpret_cast<long*>(bmpData_.bmBits);
		}

		//---------------------------------------------------------------
		//解放処理
		//---------------------------------------------------------------
		void bitmap::release() {
			DeleteDC(hMemDC_);
			DeleteObject(hBitmap_);
		}
	}
}