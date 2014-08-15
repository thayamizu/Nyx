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
		* コンストラクタ
		*/
		resource_cache();

		/*
		*　デストラクタ
		*/
		~resource_cache();
		
		/*
		*キャッシュにリソースを追加します
		* @param  const std::shared_ptr<ResourceHandle>& handle
		*/
		static void add(const std::shared_ptr<resource_handle>& handle);

		/*
		*　キャッシュからリソースを削除します
		* @param const std::wstring& キー
		*/
		static void remove(const std::wstring& key);

		/*
		*　キャッシュをクリアします
		*/
		static void clear();

		/*
		*　キャッシュからリソースを開放します
		*/
		static void release();
		
		/*
		*　キャッシュからリソースを復元します
		*/
		static void recover();
		
		/*
		*　キャッシュからリソースを復元します
		*/
		static bool find(const std::wstring& resourceName);
		
		/*
		* キャッシュからキーに対応するリソースのハンドルを取得します
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		static std::shared_ptr<resource_handle> get_handle(const std::wstring& key);
	private:
		static cache_map  cacheMap_;
	};
}

#endif
