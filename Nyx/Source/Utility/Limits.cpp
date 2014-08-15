#include "PCH/PCH.h"
#include "Utility/Limits.h"

namespace nyx {
	
	// float �ő�l
	const float limits::FLOAT_MINIMUM =  (1.17549435e-38F);

	// float �ő�l
	const float limits::FLOAT_MAXIMUM = (3.402823466e+38F);

	// float �ő�l�̕�����
	const float limits::FLOAT_MAX_SQRT = sqrt(FLOAT_MAXIMUM);

	// double �ŏ��l
	const double limits::DOUBLE_MINIMUM = (2.2250738585072014e-308);

	// double �ő�l
	const double limits::DOUBLE_MAXIMUM = (1.7976931348623158e+308);
}