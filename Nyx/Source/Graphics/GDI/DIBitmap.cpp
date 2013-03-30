/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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
		//	//��x�J������
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
			//�摜��I��
			SelectObject(hMemDC, hbitmap);
			//�w�肵�����W�ɂ��̂܂ܕ`��
			::BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int sx, int sy, ulong op) {
			//�摜��I��
			SelectObject(hMemDC, hbitmap);
			//�L�k���ĕ`��
			::StretchBlt(hdc, x, y, bitmap.bmWidth*sx, bitmap.bmHeight*sy, hMemDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, ulong op) {
			//�摜��I��
			SelectObject(hMemDC, hbitmap);
			::StretchBlt(hdc, x, y, width, height, hMemDC, width*tx, height*ty, width, height, op);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int colorKey) {
			//�摜��I��
			SelectObject(hMemDC, hbitmap);
			//�����F���w�肵�ĕ`��
			::TransparentBlt(
				hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, 
				hMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, 
				colorKey);
		}

		//-------------------------------------------------------------------------------------------------------
		//
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey) {
			//�摜��I��
			SelectObject(hMemDC, hbitmap);
			//�����F���w�肵�ĕ`��(�`�b�v�Ή�)
			::TransparentBlt(
				hdc, x, y, width, height, hMemDC,
				width*tx, height*ty, width, height, colorKey);
		}


		//-------------------------------------------------------------------------------------------------------
		//�A���t�@�u�����f�B���O
		void DIBitmap::Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey, uchar alpha) {
			//�A���t�@�u�����h�̐ݒ�
			BLENDFUNCTION blend;
			blend.BlendOp    = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = alpha;
			blend.AlphaFormat = 0;

			//�ꎞ�̈�̍쐬
			HDC tmp = ::CreateCompatibleDC(hdc);
			HBITMAP work=::CreateCompatibleBitmap(hdc, bitmap.bmWidth, bitmap.bmHeight);
			SelectObject(tmp, work);

			//�ꎞ�̈�փ`�b�v�摜��`��(�����F�w��j
			SelectObject(hMemDC, hbitmap);
			::TransparentBlt(
				tmp, 0, 0, width, height, 
				hMemDC, width*tx, height*ty, width, height, colorKey);

			//�ꎞ�̈�֕`�悵�����̂��A�A���t�@�u�����f�B���O���ăv���C�}���ɓ]��
			AlphaBlend(
				hdc, x, y, width, height, 
				tmp, 0, 0, width, height, blend);

			//�ꎞ�̈�̉��
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
		//�������
		//---------------------------------------------------------------
		void DIBitmap::Release() {
			DeleteDC(hMemDC);
			DeleteObject(hbitmap);
		}
	}
}