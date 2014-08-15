#ifndef NYX_CORE_RESOURCE_CACHE_H_
#define NYX_CORE_RESOURCE_CACHE_H_
#include "Utility/NonCopyable.h"
#include "ResourceHandle.h"
#include <string>
namespace nyx
{
	typedef std::unordered_map<std::wstring, std::shared_ptr<resource_handle>> cache_map;
	class resource_cache {
	public:

		/*
		* �R���X�g���N�^
		*/
		resource_cache();

		/*
		*�@�f�X�g���N�^
		*/
		~resource_cache();
		
		/*
		*�L���b�V���Ƀ��\�[�X��ǉ����܂�
		* @param  const std::shared_ptr<ResourceHandle>& handle
		*/
		static void add(const std::shared_ptr<resource_handle>& handle);

		/*
		*�@�L���b�V�����烊�\�[�X���폜���܂�
		* @param const std::wstring& �L�[
		*/
		static void remove(const std::wstring& key);

		/*
		*�@�L���b�V�����N���A���܂�
		*/
		static void clear();

		/*
		*�@�L���b�V�����烊�\�[�X���J�����܂�
		*/
		static void release();
		
		/*
		*�@�L���b�V�����烊�\�[�X�𕜌����܂�
		*/
		static void recover();
		
		/*
		*�@�L���b�V�����烊�\�[�X�𕜌����܂�
		*/
		static bool find(const std::wstring& resourceName);
		
		/*
		* �L���b�V������L�[�ɑΉ����郊�\�[�X�̃n���h�����擾���܂�
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		static std::shared_ptr<resource_handle> get_handle(const std::wstring& key);
	private:
		static cache_map  cacheMap_;
	};
}

#endif
