#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceCache.h"
#include "Graphics/ResourceHandle.h"

namespace Nyx {
	CacheMap  ResourceCache::cacheMap_ = CacheMap();

	//----------------------------------------------------------------------------------------
	//
	ResourceCache::ResourceCache()
	{
	}

	//----------------------------------------------------------------------------------------
	//
	ResourceCache::~ResourceCache() {
		Clear();
	}

	//----------------------------------------------------------------------------------------
	//
	void ResourceCache::Add(const std::shared_ptr<ResourceHandle>& handle)  {
		Assert(handle != nullptr);
		cacheMap_[handle->GetId()] = handle;
	}


	//----------------------------------------------------------------------------------------
	//
	void ResourceCache::Delete(const std::wstring& key) {
		auto it = cacheMap_.find(key);
		if (it != cacheMap_.end()) {
			cacheMap_.erase(it);
		} 
	}

	//----------------------------------------------------------------------------------------
	//
	void ResourceCache::Clear() {
		cacheMap_.clear();
	}

	//----------------------------------------------------------------------------------------
	//
	bool ResourceCache::Find(const std::wstring& resourceName) {
		auto it = cacheMap_.find(resourceName);
		return it != cacheMap_.end();
	}

	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<ResourceHandle> ResourceCache::GetHandle(const std::wstring& key) {
		auto it = cacheMap_.find(key);
		if (it != cacheMap_.end()) {
			return it->second;
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	//
	void ResourceCache::Release() {
		for (auto it : cacheMap_) {
			auto item = it.second->GetResource();
			item->Release();
		}
	}


	//----------------------------------------------------------------------------------------
	//
	void ResourceCache::Recovery() {
		for (auto it : cacheMap_) {
			auto item = it.second->GetResource();
			item->Recovery();
		}
	}
}