#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace Nyx {

	class FontManager {
		/**
		* �R���X�g���N�^
		*/
		FontManager();

		/**
		* �e�N�X�`���ɂ�镶���𐶐����܂�
		* @param wchar_t ����
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureFont>
		*/
		std::shared_ptr<TextureFont> CreateChar(wchar_t chara, const FontInfo& fontInfo);

		/**
		* �e�N�X�`���ɂ��e�L�X�g�𐶐����܂�
		* @param const wstring& �e�L�X�g
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureText>
		*/
		std::shared_ptr<TextureText> CreateText(const std::wstring& text, const FontInfo& fontInfo);

		/**
		* �e�L�X�g�t�@�C������܂Ƃ߂ăL���b�V���Ƀ��[�h���܂�
		* @param const std::wstring& �e�L�X�g�t�@�C����
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		std::shared_ptr<TextureText> Load(const std::wstring& txtFileName, const FontInfo& fontInfo);


		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void Delete(const std::wstring& key);
	};
}
#endif