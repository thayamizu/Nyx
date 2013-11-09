#ifndef NYX_CORE_INCLUDED_IRENDERABLE_H_
#define NYX_CORE_INCLUDED_IRENDERABLE_H_
#include "Primitive/Matrix44.h"

namespace Nyx {

	///�����_�����O�\�ȃ��\�[�X
	class IRenderable {
	public:
		/**
		*
		*/
		virtual ~IRenderable() {}
		
		
		/**
		*
		*/
		virtual void Render(const Matrix44& matrix) const = 0;
	};
};

#endif