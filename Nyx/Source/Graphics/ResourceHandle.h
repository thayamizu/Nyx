#ifndef NYX_CORE_RESOURCE_HANDLE_H_
#define NYX_CORE_RESOURCE_HANDLE_H_
#include "IResource.h"

namespace nyx
{
	///���\�[�X�n���h��
	class resource_handle {
	public:
		/**
		* �R���X�g���N�^
		*/
		resource_handle(std::wstring name, const std::shared_ptr<iresource>& resource)
			: name_(name), resource_(resource) {
		}

		/**
		* ���\�[�X�����擾���܂�
		* @return std::wstring ���\�[�X��
		*/
		std::wstring get_name() const {
			return name_;
		}

		/**
		* ���\�[�X�ւ̃|�C���^���擾���܂�
		* @return ���\�[�X
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
