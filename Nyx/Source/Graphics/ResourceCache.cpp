#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceCache.h"
#include "Graphics/ResourceHandle.h"

namespace Nyx {

	ResourceCache::ResourceCache()
		:cache_()
	{
	}
	ResourceCache::~ResourceCache() {
		Clear();
	}
	void ResourceCache::Add(std::wstring key, const std::shared_ptr<ResourceHandle>& handle)  {
		Assert(handle != nullptr);
		cache_[key] = handle;
	}

	void ResourceCache::Delete(std::wstring key) {
		auto it = cache_.find(key);
		if (it != cache_.end()) {
			cache_.erase(it);
		} 
	}

	void ResourceCache::Clear() {
		cache_.clear();
	}

	std::shared_ptr<ResourceHandle> ResourceCache::GetCacheItem(std::wstring key) {
		auto it = cache_.find(key);
		if (it != cache_.end()) {
			return it->second;
		}
		return nullptr;
	}
}