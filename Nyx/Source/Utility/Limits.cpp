#include "PCH/PCH.h"
#include "Utility/Limits.h"

namespace Nyx {
	
	// float �ő�l
	const float Limits::FloatMin =  (1.17549435e-38F);

	// float �ő�l
	const float Limits::FloatMax = (3.402823466e+38F);

	// float �ő�l�̕�����
	const float Limits::FloatMaxSqrt = sqrt(FloatMax);

	// double �ŏ��l
	const double Limits::DoubleMin = (2.2250738585072014e-308);

	// double �ő�l
	const double Limits::DoubleMax = (1.7976931348623158e+308);
}