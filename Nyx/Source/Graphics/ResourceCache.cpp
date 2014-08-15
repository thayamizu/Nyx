#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceCache.h"
#include "Graphics/ResourceHandle.h"

namespace nyx {
	cache_map  resource_cache::cacheMap_ = cache_map();

	//----------------------------------------------------------------------------------------
	//
	resource_cache::resource_cache()
	{
	}

	//----------------------------------------------------------------------------------------
	//
	resource_cache::~resource_cache() {
		clear();
	}

	//----------------------------------------------------------------------------------------
	//
	void resource_cache::add(const std::shared_ptr<resource_handle>& handle)  {
		NYX_ASSERT(handle != nullptr);
		cacheMap_[handle->get_name()] = handle;
	}


	//----------------------------------------------------------------------------------------
	//
	void resource_cache::remove(const std::wstring& key) {
		auto it = cacheMap_.find(key);
		if (it != cacheMap_.end()) {
			cacheMap_.erase(it);
		} 
	}

	//----------------------------------------------------------------------------------------
	//
	void resource_cache::clear() {
		cacheMap_.clear();
	}

	//----------------------------------------------------------------------------------------
	//
	bool resource_cache::find(const std::wstring& resourceName) {
		auto it = cacheMap_.find(resourceName);
		return it != cacheMap_.end();
	}

	//----------------------------------------------------------------------------------------
	//
	std::shared_ptr<resource_handle> resource_cache::get_handle(const std::wstring& key) {
		auto it = cacheMap_.find(key);
		if (it != cacheMap_.end()) {
			return it->second;
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	//
	void resource_cache::release() {
		for (auto it : cacheMap_) {
			auto item = it.second->get_resource();
			item->release();
		}
	}


	//----------------------------------------------------------------------------------------
	//
	void resource_cache::recover() {
		for (auto it : cacheMap_) {
			auto item = it.second->get_resource();
			item->recovery();
		}
	}
}