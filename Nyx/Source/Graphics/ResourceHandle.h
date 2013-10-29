#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_

namespace Nyx
{
	class ResourceHandle {
	public:
		ResourceHandle(size_t bufferSize, std::wstring guid, std::shared_ptr<void> resource);

		size_t GetBufferSize() {
			return bufferSize_;
		}

		std::wstring GetId() const {
			return uuid_;
		}

		std::shared_ptr<void> GetResource() const {
			return resource_;
		}
	private:
		size_t bufferSize_;
		std::wstring uuid_;
		std::shared_ptr<void> resource_;
	};
}

#endif
