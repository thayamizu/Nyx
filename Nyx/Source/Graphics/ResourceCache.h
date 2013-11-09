#ifndef NYX_CORE_RESOURCE_CACHE_H_
#define NYX_CORE_RESOURCE_CACHE_H_
#include "Utility/NonCopyable.h"

namespace Nyx
{
	class ResourceHandle;
	class ResourceCache {
	public:
		typedef std::unordered_map<std::wstring, std::shared_ptr<ResourceHandle>> Cache;

		/*
		* �R���X�g���N�^
		*/
		ResourceCache();

		/*
		*�@�f�X�g���N�^
		*/
		~ResourceCache();
		
		/*
		*�L���b�V���Ƀ��\�[�X��ǉ����܂�
		* @param  const std::shared_ptr<ResourceHandle>& handle
		*/
		void Add(const std::shared_ptr<ResourceHandle>& handle);

		/*
		*�@�L���b�V�����烊�\�[�X���폜���܂�
		* @param const std::wstring& �L�[
		*/
		void Delete(const std::wstring& key);

		/*
		*�@�L���b�V�����N���A���܂�
		*/
		void Clear();

		/*
		*�@�L���b�V�����烊�\�[�X���J�����܂�
		*/
		void Release();
		
		/*
		*�@�L���b�V�����烊�\�[�X�𕜌����܂�
		*/
		void Recovery();
		
		/*
		* �L���b�V������L�[�ɑΉ����郊�\�[�X�̃n���h�����擾���܂�
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		std::shared_ptr<ResourceHandle> GetCacheItem(const std::wstring& key);
	private:
		Cache cache_;
	};
}

#endif
