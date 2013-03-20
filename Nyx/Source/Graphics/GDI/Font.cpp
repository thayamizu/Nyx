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
#include "Utility/Common.h"
#include "Debug/Assert.h"
#include "Graphics/GDI/Font.h"

namespace Nyx {
	namespace GDI {

		//------------------------------------------------------------------------------
		//
		Font::Font(const int height_, const int angle_, const std::wstring face_) {
			Set(height_, angle_, face_);   


		}

		//------------------------------------------------------------------------------
		//
		Font::Font(const int height_, const int angle_, const int weight_, 
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_, 
			const int charset_, const std::wstring face_) 
		{
			Set(height_, angle_, weight_, isItalic_, isUnderLine_,isStrike_, charset_ ,face_);
		}

		//------------------------------------------------------------------------------
		//
		Font::Font(const Font &font_) {
			height = font_.height;                     
			angle  = font_.angle;                 
			weight = font_.weight;FW_REGULAR;             
			isItalic   = font_.isItalic;                    
			isUnderLine= font_.isUnderLine;                  
			isStrike   = font_.isStrike;                 
			charset = font_.charset;      
			face    = font_.face.c_str();           



		}

		//------------------------------------------------------------------------------
		//
		Font::~Font() {

		}

		//------------------------------------------------------------------------------
		//
		void Font::Set(const int height_,const int angle_, const std::wstring face_) {
			height = height_;                      //�������i�����Ɠ����j
			angle  = angle_;                  //�e�L�X�g�̊p�x
			weight = FW_REGULAR;             //�t�H���g�̏d���i�����j
			isItalic    = false;
			isUnderLine = false;                  //�A���_�[���C��
			isStrike   = false;                  //�ł�������
			charset = SHIFTJIS_CHARSET;       //�����Z�b�g
			face    = face_;                  //���̖�

			font=  CreateFont(
				height,       //�t�H���g����
				0,                      //�������i�����Ɠ����j
				angle,                  //�e�L�X�g�̊p�x
				0,                      //�x�[�X���C���Ƃ����Ƃ̊p�x
				weight,             //�t�H���g�̏d���i�����j
				isItalic,                  //�C�^���b�N��
				isUnderLine,                  //�A���_�[���C��
				isStrike,                  //�ł�������
				charset,       //�����Z�b�g
				OUT_TT_ONLY_PRECIS,     //�o�͐��x
				CLIP_DEFAULT_PRECIS,    //�N���b�s���O���x
				PROOF_QUALITY,          //�o�͕i��
				FIXED_PITCH|FF_MODERN,  //�s�b�`�ƃt�@�~���[
				face.c_str());                  //���̖�

			Assert(font != NULL);
		}

		//------------------------------------------------------------------------------
		//
		void Font::Set(const int height_, const int angle_, const int weight_,
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_, 
			const int charset_, const std::wstring face_) {
				height = height_;                      //�������i�����Ɠ����j
				angle  = angle_;                  //�e�L�X�g�̊p�x
				weight = weight_;             //�t�H���g�̏d���i�����j
				isItalic    = isItalic_;
				isUnderLine = isUnderLine_;                  //�A���_�[���C��
				isStrike    = isStrike_;                  //�ł�������
				charset = charset_;       //�����Z�b�g
				face    = face_;                  //���̖�

				font=  CreateFont(
					height,       //�t�H���g����
					0,                      //�������i�����Ɠ����j
					angle,                  //�e�L�X�g�̊p�x
					0,                      //�x�[�X���C���Ƃ����Ƃ̊p�x
					weight,             //�t�H���g�̏d���i�����j
					isItalic,                  //�C�^���b�N��
					isUnderLine,                  //�A���_�[���C��
					isStrike,                  //�ł�������
					charset,       //�����Z�b�g
					OUT_TT_ONLY_PRECIS,     //�o�͐��x
					CLIP_DEFAULT_PRECIS,    //�N���b�s���O���x
					PROOF_QUALITY,          //�o�͕i��
					FIXED_PITCH|FF_MODERN,  //�s�b�`�ƃt�@�~���[
					face.c_str());                  //���̖�

				Assert(font != NULL);
		} 

		//------------------------------------------------------------------------------
		//
		void Font::Draw(HDC hdc, const wchar_t* text_, RECT rect) {
			SelectObject(hdc, font);
			DrawText(hdc, text_, -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		void Font::Draw(HDC hdc, const std::wstring text_,RECT rect) {
			SelectObject(hdc, font);
			DrawText(hdc, text_.c_str(), -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		int Font::GetAngle() {
			return angle;
		}

		//------------------------------------------------------------------------------
		//
		int Font::GetHeight() {
			return height;
		}

		//------------------------------------------------------------------------------
		//  
		int Font::GetWeight() {
			return weight;
		}

		//------------------------------------------------------------------------------
		//  
		bool Font::IsItalic() {
			return isItalic;
		}

		//------------------------------------------------------------------------------
		//
		bool Font::IsUnderLine() {
			return isUnderLine;
		}

		//------------------------------------------------------------------------------
		//            
		HFONT Font::GetFont() {
			return font;    
		}
	}
}