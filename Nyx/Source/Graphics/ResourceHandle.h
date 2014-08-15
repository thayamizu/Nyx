#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_
#include "IResource.h"

namespace nyx
{
	///リソースハンドル
	class resource_handle {
	public:
		/**
		* コンストラクタ
		*/
		resource_handle(std::wstring name, const std::shared_ptr<iresource>& resource)
			: name_(name), resource_(resource) {
		}

		/**
		* リソース名を取得します
		* @return std::wstring リソース名
		*/
		std::wstring get_name() const {
			return name_;
		}

		/**
		* リソースへのポインタを取得します
		* @return リソース
		*/
		std::shared_ptr<iresource> get_resource() const {
			return resource_;
		}

	private:
		std::wstring name_;
	    std::shared_ptr<iresource> resource_;
	};

}

#endif
