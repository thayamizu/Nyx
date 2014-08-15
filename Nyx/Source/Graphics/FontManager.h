#ifndef NYX_CORE_INCLUDED_FONT_MANAGER_H_
#define NYX_CORE_INCLUDED_FONT_MANAGER_H_
#include "FontInfo.h"
#include "TextureFont.h"
#include "TextureText.h"

namespace nyx {

	class font_factory {
	public:

		/**
		* �e�N�X�`���ɂ�镶���𐶐����܂�
		* @param wchar_t ����
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<texture_font> make_texture_char(wchar_t chara, const font_info& fontInfo);
		

		/**
		* �e�N�X�`���ɂ�镶���𐶐����܂�
		* @param wchar_t ����
		* @param const FontInfo& �t�H���g���
		* @return std::shared_ptr<TextureFont>
		*/
		static std::shared_ptr<texture_text> make_texture_text(const std::wstring& text,  const font_info& fontInfo);


		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static void remove(const std::wstring& key);


		/**
		*
		*/
		static std::shared_ptr<texture_font> get_item(wchar_t chara);
	private:
		/**
		* �R���X�g���N�^
		*/
		font_factory() {}
		std::wstring txtFileName_;
	};
}
#endif