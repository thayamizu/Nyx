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
#ifndef NYX_CORE_INCLUDED_DIRECT_GRAPHICS_TEXTURE_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_DIRECT_GRAPHICS_TEXTURE_FONT_MANAGER_H_

namespace Nyx {
	namespace DX9 {
		///������`�悷��Ƃ��ɕK�v�ȏ��
		struct CharInfo {
			bool isDrawed;///<�`�悳��Ă���
			uchar transparency;///< �����x(0~255)
		};

		//�O���錾
		///�e�N�X�`���t�H���g�̊Ǘ��N���X
		class DXTextureFontManager {
			typedef std::vector<CharInfo> CharInfoContainer;
			typedef std::vector<DXTextureFont*> DXTextureFontContainer;
		public:
			//--------------------------------------------------------------------------------------
			// �\�z�E�j��
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			DXTextureFontManager();

			/**
			*
			*/
			DXTextureFontManager(int capacity, std::wstring font, int size, Color4c color, int speed);

			/**
			*
			*/
			~DXTextureFontManager();

			//--------------------------------------------------------------------------------------
			// �e�N�X�`���̃��[�h�E���
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			int Load(DirectGraphicsDevice&);

			/**
			*
			*/
			void Release();

			/**
			*
			*/
			bool OnResetDevice();

			/**
			*
			*/
			bool OnLostDevice();

			//--------------------------------------------------------------------------------------
			// �`��
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void RenderAll(float x, float y, float z,  float sx=1, float sy=1, float angle=0);

			/**
			*
			*/
			void Render(int index, float x, float y, float z,  float sx=1, float sy=1, float angle=0);

			//--------------------------------------------------------------------------------------
			// ������̐ݒ�
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void SetText(std::wstring text);

			/**
			*
			*/
			std::wstring GetText() const;

			/**
			*
			*/
			void SetTextLength(int len);

			/**
			*
			*/
			int GetTextLength() const;

			//--------------------------------------------------------------------------------------
			// �t�H���g���̎擾�E�ݒ�
			//--------------------------------------------------------------------------------------
			/**
			*
			*/
			void AdjustRowAndColumn(int width, int height);
			/**
			*
			*/
			void SetFontSize(int size);
			/**
			*
			*/
			int GetFontSize() const;

			/**
			*
			*/
			void SetFontColor(Color4c color);

			/**
			*
			*/
			Color4c GetFontColor()const;

			/**
			*
			*/
			void SetRow(int n);
			/**
			*
			*/
			int GetRow() const;

			/**
			*
			*/
			void SetColumn(int n);

			/**
			*
			*/
			int GetColumn() const;

			/**
			*
			*/
			void SetSpeed(int s);
			/**
			*
			*/
			int GetSpeed() const;


			/**
			*
			*/
			void SetTransparent(int s);
			/**
			*
			*/
			int GetTransparent() const;
		private:
			static const int defaultTransparent;

		private:

			Color4c fontColor;///<�t�H���g�J���[
			int transparent;///< ���ߗ�
			int fontSize;///< �t�H���g�T�C�Y
			int textSpeed;///< ��������̑���
			size_t textLength;///< ��x�ɕ`�悷��e�L�X�g�̒���
			int rowNum;   ///< �P�s�ŕ\�����镶����
			int columnNum;///< 1��ɕ\�����镶����
			uint cursorRead;///< ���łɍ쐬�������̂܂ł�;
			std::wstring fontName;///�g�p����t�H���g�̖��O
			std::wstring textstring;///<���[�h���Ă��镶����
			CharInfoContainer charInfo;
			DXTextureFontContainer container;///< �X�̕����e�N�X�`�����i�[���Ă�R���e�i
		};
	}
}
#endif