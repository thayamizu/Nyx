#ifndef NYX_CORE_INCLUDED_IRENDERABLE_H_
#define NYX_CORE_INCLUDED_IRENDERABLE_H_
#include "Primitive/Matrix44.h"

namespace nyx {

	///�����_�����O�\�ȃ��\�[�X
	class irenderable {
	public:
		/**
		*
		*/
		virtual ~irenderable() {}
		
		
		/**
		*
		*/
		virtual void render(const matrix& matrix) const = 0;
	};
};

#endif