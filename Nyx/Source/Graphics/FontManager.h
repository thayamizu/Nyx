#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace Nyx {

	class FontManager {
	public:

		/**
		* �e�N�X�`���ɂ�镶���𐶐����܂�
		* @param wchar_t ����
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<TextureFont> CreateChar(wchar_t chara, const FontInfo& fontInfo);
		

		/**
		* �e�N�X�`���ɂ�镶���𐶐����܂�
		* @param wchar_t ����
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<TextureText> CreateText(const std::wstring& text,  const FontInfo& fontInfo);


		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static void Delete(const std::wstring& key);


		/**
		*
		*/
		static std::shared_ptr<TextureFont> GetItem(wchar_t chara);
	private:
		/**
		* �R���X�g���N�^
		*/
		FontManager() {}
		std::wstring txtFileName_;
	};
}
#endif