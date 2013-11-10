#ifndef NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#define NYX_CORE_INCLUDED_CORE_SPRITE_MANAGER_H_
#include "ResourceCache.h"

namespace Nyx {

	typedef std::vector <std::shared_ptr<Sprite>> SpriteCache;

	///�X�v���C�g�}�l�[�W��
	class SpriteManager {
	public:
		/**
		* �R���X�g���N�^
		*/
		SpriteManager();

		/**
		* �X�v���C�g�𐶐����܂�
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param std::wstring �t�@�C����
		* @return std::shared_ptr<Sprite>
		*/
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const Color4c& color);
		
		/**
		* �X�v���C�g�𐶐����܂�
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param const Color4c& �F
		* @return std::shared_ptr<Sprite>
		*/
		std::shared_ptr<Sprite> CreateSprite(int width, int height, const std::wstring& fileName);
		
		/**
		* �e�L�X�g�t�@�C������܂Ƃ߂ăL���b�V���Ƀ��[�h���܂�
		* @param const std::wstring& �e�L�X�g�t�@�C����
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @return std::vector<std::shared_ptr<Sprite>>
		*/
		SpriteCache Load(const std::wstring& txtFileName, int width, int height);

		/**
		* �L���b�V������w�肵�����\�[�X���폜���܂�
		* @param const std::wstring& �t�@�C����
		*/
		void Delete(const std::wstring& fileName);
	};
}
#endif