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
		* コンストラクタ
		*/
		ResourceCache();

		/*
		*　デストラクタ
		*/
		~ResourceCache();
		
		/*
		*キャッシュにリソースを追加します
		* @param  const std::shared_ptr<ResourceHandle>& handle
		*/
		void Add(const std::shared_ptr<ResourceHandle>& handle);

		/*
		*　キャッシュからリソースを削除します
		* @param const std::wstring& キー
		*/
		void Delete(const std::wstring& key);

		/*
		*　キャッシュをクリアします
		*/
		void Clear();

		/*
		*　キャッシュからリソースを開放します
		*/
		void Release();
		
		/*
		*　キャッシュからリソースを復元します
		*/
		void Recovery();
		
		/*
		* キャッシュからキーに対応するリソースのハンドルを取得します
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		std::shared_ptr<ResourceHandle> GetCacheItem(const std::wstring& key);
	private:
		Cache cache_;
	};
}

#endif
