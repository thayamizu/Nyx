#include "PCH/PCH.h"
#include "Utility/Limits.h"

namespace nyx {
	
	// float 最大値
	const float limits::FLOAT_MINIMUM =  (1.17549435e-38F);

	// float 最大値
	const float limits::FLOAT_MAXIMUM = (3.402823466e+38F);

	// float 最大値の平方根
	const float limits::FLOAT_MAX_SQRT = sqrt(FLOAT_MAXIMUM);

	// double 最小値
	const double limits::DOUBLE_MINIMUM = (2.2250738585072014e-308);

	// double 最大値
	const double limits::DOUBLE_MAXIMUM = (1.7976931348623158e+308);
}