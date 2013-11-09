#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_
#include "IResource.h"

namespace Nyx
{
	///リソースハンドル
	class ResourceHandle {
	public:
		/**
		* コンストラクタ
		*/
		ResourceHandle(std::wstring name, const std::shared_ptr<IResource>& resource)
			: name_(name), resource_(resource) {
		}

		/**
		* リソース名を取得します
		* @return std::wstring リソース名
		*/
		std::wstring GetId() const {
			return name_;
		}

		/**
		* リソースへのポインタを取得します
		* @return リソース
		*/
		std::shared_ptr<IResource> GetResource() const {
			return resource_;
		}
	private:
		std::wstring name_;
		std::shared_ptr<IResource> resource_;
	};

}

#endif
