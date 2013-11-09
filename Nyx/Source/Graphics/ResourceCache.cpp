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
	void ResourceCache::Add(const std::shared_ptr<ResourceHandle>& handle)  {
		Assert(handle != nullptr);
		cache_[handle->GetId()] = handle;
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


	void ResourceCache::Release() {
		for (auto it : cache_) {
			auto item = it.second->GetResource();
			item->Release();
		}
	}
	void ResourceCache::Recovery() {
		for (auto it : cache_) {
			auto item = it.second->GetResource();
			item->Recovery();
		}
	}
}