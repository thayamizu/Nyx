#ifndef NYX_CORE_RESOURCE_CACHE_H_
#define NYX_CORE_RESOURCE_CACHE_H_
#include "Utility/NonCopyable.h"

namespace Nyx
{
	class ResourceHandle;
	class ResourceCache {
	public:
		typedef std::unordered_map<std::wstring, std::shared_ptr<ResourceHandle>> Cache;

		ResourceCache();
		~ResourceCache();
		void Add(std::wstring key, const std::shared_ptr<ResourceHandle>& handle);

		void Delete(std::wstring key);

		void Clear();

		std::shared_ptr<ResourceHandle> GetCacheItem(std::wstring key);
	private:
		Cache cache_;
	};
}

#endif
