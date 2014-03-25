#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"
#include "Utility/NonCopyable.h"

namespace Nyx {

	///�X�v���C�g�}�l�[�W��
	class SpriteManager : NonCopyable {
	public:
		/**
		* �X�v���C�g�𐶐����܂�
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param std::wstring �t�@�C����
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<Sprite> CreateSprite(int width, int height, const Color4c& color);
		
		/**
		* �X�v���C�g�𐶐����܂�
		* @return std::shared_ptr<Sprite>
		*/
		static std::shared_ptr<Sprite> CreateSprite(const std::wstring& fileName);
		
		/**
		* �e�L�X�g�t�@�C������܂Ƃ߂ăL���b�V���Ƀ��[�h���܂�
		* @param const std::wstring& �e�L�X�g�t�@�C����
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		static void Load(const std::wstring& txtFileName);

		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static void Delete(const std::wstring& resourceName);

		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		static std::shared_ptr<Sprite> GetItem(const std::wstring& resourceName);
	private:
		/**
		* �R���X�g���N�^
		*/
		SpriteManager() {}
	};
}
#endif