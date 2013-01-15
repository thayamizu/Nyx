#include "PCH/PCH.h"
#include "Utility/Limits.h"

namespace Nyx {
	
	// float 最大値
	const float Limits::FloatMin =  (1.17549435e-38F);

	// float 最大値
	const float Limits::FloatMax = (3.402823466e+38F);

	// float 最大値の平方根
	const float Limits::FloatMaxSqrt = sqrt(FloatMax);

	// double 最小値
	const double Limits::DoubleMin = (2.2250738585072014e-308);

	// double 最大値
	const double Limits::DoubleMax = (1.7976931348623158e+308);
}