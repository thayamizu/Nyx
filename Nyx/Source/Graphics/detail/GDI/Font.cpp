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
#include "Graphics/detail/GDI/Font.h"

namespace nyx {
	namespace win32 {

		//------------------------------------------------------------------------------
		//
		font::font(const int height_, const int angle_, const std::wstring face_) 
		:fontHandle_(NULL){
			set(height_, angle_, face_);   


		}

		//------------------------------------------------------------------------------
		//
		font::font(const int height_, const int angle_, const int weight_,
			const bool isItalic_, const bool isUnderLine_, const bool isStrike_,
			const int charset_, const std::wstring face_)
			:fontHandle_(NULL)
		{
			set(height_, angle_, weight_, isItalic_, isUnderLine_,isStrike_, charset_ ,face_);
		}

		//------------------------------------------------------------------------------
		//
		font::font(const font &font_) {
			height_ = font_.height_;                     
			angle_  = font_.angle_;                 
			weight_ = font_.weight_;FW_REGULAR;             
			isItalic_   = font_.isItalic_;                    
			isUnderLine_= font_.isUnderLine_;                  
			isStrike_   = font_.isStrike_;                 
			charset_ = font_.charset_;      
			fontFace_    = font_.fontFace_.c_str();           



		}

		//------------------------------------------------------------------------------
		//
		font::~font() {

		}

		//------------------------------------------------------------------------------
		//
		void font::set(const int height,const int angle, const std::wstring face) {
			height_ = height;                      //�������i�����Ɠ����j
			angle_  = angle;                  //�e�L�X�g�̊p�x
			weight_ = FW_REGULAR;             //�t�H���g�̏d���i�����j
			isItalic_    = false;
			isUnderLine_ = false;                  //�A���_�[���C��
			isStrike_   = false;                  //�ł�������
			charset_ = SHIFTJIS_CHARSET;       //�����Z�b�g
			fontFace_    = face;                  //���̖�

			fontHandle_=  CreateFont(
				height_,       //�t�H���g����
				0,                      //�������i�����Ɠ����j
				angle_,                  //�e�L�X�g�̊p�x
				0,                      //�x�[�X���C���Ƃ����Ƃ̊p�x
				weight_,             //�t�H���g�̏d���i�����j
				isItalic_,                  //�C�^���b�N��
				isUnderLine_,                  //�A���_�[���C��
				isStrike_,                  //�ł�������
				charset_,       //�����Z�b�g
				OUT_TT_ONLY_PRECIS,     //�o�͐��x
				CLIP_DEFAULT_PRECIS,    //�N���b�s���O���x
				PROOF_QUALITY,          //�o�͕i��
				FIXED_PITCH|FF_MODERN,  //�s�b�`�ƃt�@�~���[
				fontFace_.c_str());                  //���̖�

			NYX_ASSERT(fontHandle_ != NULL);
		}

		//------------------------------------------------------------------------------
		//
		void font::set(const int height, const int angle, const int weight,
			const bool isItalic, const bool isUnderLine, const bool isStrike, 
			const int charset, const std::wstring face) {
				height_ = height;                      //�������i�����Ɠ����j
				angle_  = angle;                  //�e�L�X�g�̊p�x
				weight_ = weight;             //�t�H���g�̏d���i�����j
				isItalic_    = isItalic;
				isUnderLine_ = isUnderLine;                  //�A���_�[���C��
				isStrike_    = isStrike;                  //�ł�������
				charset_ = charset;       //�����Z�b�g
				fontFace_    = face;                  //���̖�

				fontHandle_=  CreateFont(
					height_,       //�t�H���g����
					0,                      //�������i�����Ɠ����j
					angle_,                  //�e�L�X�g�̊p�x
					0,                      //�x�[�X���C���Ƃ����Ƃ̊p�x
					weight_,             //�t�H���g�̏d���i�����j
					isItalic_,                  //�C�^���b�N��
					isUnderLine_,                  //�A���_�[���C��
					isStrike_,                  //�ł�������
					charset_,       //�����Z�b�g
					OUT_TT_ONLY_PRECIS,     //�o�͐��x
					CLIP_DEFAULT_PRECIS,    //�N���b�s���O���x
					PROOF_QUALITY,          //�o�͕i��
					FIXED_PITCH|FF_MODERN,  //�s�b�`�ƃt�@�~���[
					fontFace_.c_str());                  //���̖�

				NYX_ASSERT(fontHandle_ != NULL);
		} 

		//------------------------------------------------------------------------------
		//
		void font::draw(HDC hdc, const wchar_t* text_, RECT rect) {
			SelectObject(hdc, fontHandle_);
			DrawText(hdc, text_, -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		void font::draw(HDC hdc, const std::wstring text_,RECT rect) {
			SelectObject(hdc, fontHandle_);
			DrawText(hdc, text_.c_str(), -1, &rect, DT_WORDBREAK | DT_LEFT);
			DeleteObject(hdc);
		}

		//------------------------------------------------------------------------------
		//
		int font::get_angle() {
			return angle_;
		}

		//------------------------------------------------------------------------------
		//
		int font::get_height() {
			return height_;
		}

		//------------------------------------------------------------------------------
		//  
		int font::get_font_weight() {
			return weight_;
		}

		//------------------------------------------------------------------------------
		//  
		bool font::is_italic() {
			return isItalic_;
		}

		//------------------------------------------------------------------------------
		//
		bool font::is_underline() {
			return isUnderLine_;
		}

		//------------------------------------------------------------------------------
		//            
		font_handle font::get_font_handle() {
			return fontHandle_;    
		}
	}
}