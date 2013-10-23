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
#ifndef NYX_CORE_INCLUDED_FONT_H_
#define NYX_CORE_INCLUDED_FONT_H_

namespace Nyx {
	namespace GDI {

		/// �t�H���g
		class Font {
		public:
			//------------------------------------------------------------------------------
			//�\�z�E�j��
			//------------------------------------------------------------------------------
			/**
			*
			*/
			Font(const int height_, const int angle_, const std::wstring face_);
			/**
			*
			*/
			Font(const int height_, const int angle_, const int weight_, const bool isItalic_, const bool isUnderLine_, const bool isStrike_, const int charset_, const std::wstring face_);
			/**
			*
			*/
			Font(const Font& font_);

			/**
			*
			*/
			~Font();

			//------------------------------------------------------------------------------
			//�t�H���g�̃Z�b�g
			//------------------------------------------------------------------------------
			/**
			*
			*/
			void Set(const int h, const int angle, const std::wstring face);
			/**
			*
			*/
			void Set(const int height_, const int angle_, const int weight_, const bool isItalic_, const bool isUnderLine_, const bool isStrike_, const int charset_, const std::wstring face);


			//------------------------------------------------------------------------------
			//�`��
			//------------------------------------------------------------------------------
			/**
			*
			*/
			void Draw(HDC hdc, const wchar_t* text_, RECT rect_);
			/**
			*
			*/
			void Draw(HDC hdc, const std::wstring text_, RECT rect_);

			//------------------------------------------------------------------------------
			//�擾
			//------------------------------------------------------------------------------
			/**
			*
			*/
			int GetAngle();
			/**
			*
			*/
			int GetHeight();
			/**
			*

			*/int GetWeight();
			/**
			*
			*/
			bool IsItalic();
			/**
			*
			*/
			bool IsUnderLine();
			/**
			*
			*/
			HFONT GetFont();
		private:
			Font(); 
			int angle; 
			int height;
			int weight;
			int charset;
			bool isItalic;
			bool isStrike;
			bool isUnderLine;
			std::wstring face;
			HFONT font;
		};
	}
}
#endif