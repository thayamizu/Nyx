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
		static void Add(const std::shared_ptr<ResourceHandle>& handle);

		/*
		*　キャッシュからリソースを削除します
		* @param const std::wstring& キー
		*/
		static void Delete(const std::wstring& key);

		/*
		*　キャッシュをクリアします
		*/
		static void Clear();

		/*
		*　キャッシュからリソースを開放します
		*/
		static void Release();
		
		/*
		*　キャッシュからリソースを復元します
		*/
		static void Recovery();
		
		/*
		*　キャッシュからリソースを復元します
		*/
		static bool Find(const std::wstring& resourceName);
		
		/*
		* キャッシュからキーに対応するリソースのハンドルを取得します
		* @param std::wstring key
		* @return std::shared_ptr<ResourceHandle> 
		*/
		static std::shared_ptr<ResourceHandle> GetHandle(const std::wstring& key);
	private:
		static CacheMap  cacheMap_;
	};
}

#endif
