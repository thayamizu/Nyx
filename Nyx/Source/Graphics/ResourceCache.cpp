#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceCache.h"
#include "Graphics/ResourceHandle.h"

namespace Nyx {

	ResourceCache::ResourceCache()
		:cache_() {
	}

	void ResourceCache::Add(std::shared_ptr<ResourceHandle> handle)  {
		Assert(handle != nullptr);
		auto key = handle->GetId();
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

}