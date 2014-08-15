#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"
#include "Utility/NonCopyable.h"

namespace nyx {

	///�X�v���C�g�}�l�[�W��
	class sprite_factory : noncopyable {
	public:
		/**
		* �X�v���C�g�𐶐����܂�
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param std::wstring �t�@�C����
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<sprite> make_sprite(int width, int height, const color4c& color);
		
		/**
		* �X�v���C�g�𐶐����܂�
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<sprite> make_sprite(const std::wstring& fileName);
		
		/**
		* �e�L�X�g�t�@�C������܂Ƃ߂ăL���b�V���Ƀ��[�h���܂�
		* @param const std::wstring& �e�L�X�g�t�@�C����
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		static void load_sprite(const std::wstring& txtFileName);

		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static void remove(const std::wstring& resourceName);

		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static std::shared_ptr<sprite> get_item(const std::wstring& resourceName);
	private:
		/**
		* �R���X�g���N�^
		*/
		sprite_factory() {}
	};
}
#endif