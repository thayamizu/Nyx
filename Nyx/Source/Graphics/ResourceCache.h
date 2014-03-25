#ifndef NYX_CORE_RESOURCE_CACHE_H_
#define NYX_CORE_RESOURCE_CACHE_H_
#include "Utility/NonCopyable.h"
#include "ResourceHandle.h"
#include <string>
namespace Nyx
{
	typedef std::unordered_map<std::wstring, std::shared_ptr<ResourceHandle>> CacheMap;
	class ResourceCache {
	public:

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
		static void Add(const std::shared_ptr<ResourceHandle>& handle);

		/*
		*�@�L���b�V�����烊�\�[�X���폜���܂�
		* @param const std::wstring& �L�[
		*/
		static void Delete(const std::wstring& key);

		/*
		*�@�L���b�V�����N���A���܂�
		*/
		static void Clear();

		/*
		*�@�L���b�V�����烊�\�[�X���J�����܂�
		*/
		static void Release();
		
		/*
		*�@�L���b�V�����烊�\�[�X�𕜌����܂�
		*/
		static void Recovery();
		
		/*
		*�@�L���b�V�����烊�\�[�X�𕜌����܂�
		*/
		static bool Find(const std::wstring& resourceName);
		
		/*
		* �L���b�V������L�[�ɑΉ����郊�\�[�X�̃n���h�����擾���܂�
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		static std::shared_ptr<ResourceHandle> GetHandle(const std::wstring& key);
	private:
		static CacheMap  cacheMap_;
	};
}

#endif
