#ifndef NYX_CORE_RESOURCE_CACHE_H_
#define NYX_CORE_RESOURCE_CACHE_H_

namespace Nyx
{
	class ResourceHandle;
	class ResourceCache {
		typedef std::unordered_map<std::wstring, std::shared_ptr<ResourceHandle>> Cache;
	public:
		ResourceCache();

		void Add(const std::shared_ptr<ResourceHandle> handle);

		void Delete(std::wstring key);

		void Clear();

	private:
		Cache cache_;
	};
}

#endif
