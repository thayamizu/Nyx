#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_
#include "IResource.h"

namespace Nyx
{
	///���\�[�X�n���h��
	class ResourceHandle {
	public:
		/**
		* �R���X�g���N�^
		*/
		ResourceHandle(std::wstring name, const std::shared_ptr<IResource>& resource)
			: name_(name), resource_(resource) {
		}

		/**
		* ���\�[�X�����擾���܂�
		* @return std::wstring ���\�[�X��
		*/
		std::wstring GetId() const {
			return name_;
		}

		/**
		* ���\�[�X�ւ̃|�C���^���擾���܂�
		* @return ���\�[�X
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
