#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_

namespace Nyx
{
	class ResourceHandle {
	public:
		ResourceHandle(std::wstring uuid, const std::shared_ptr<void>& resource);

		std::wstring GetId() const {
			return uuid_;
		}

		std::shared_ptr<void> GetResource() const {
			return resource_;
		}
	private:
		std::wstring uuid_;
		std::shared_ptr<void> resource_;
	};
}

#endif
