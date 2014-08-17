#pragma once
#include "PCH/PCH.h"

using namespace nyx;

BEGIN_TEST(Matrix33_0001)
{
	matrix33 mat;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat.Mat[i][j] == 0);
		}
	}
}
END_TEST

BEGIN_TEST(Matrix33_0002)
{
	matrix33 mat = matrix33(1,2,3,4,5,6,7,8,9);

	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat.Mat[i][j] == index);
			++index;
		}
	}
}
END_TEST

BEGIN_TEST(Matrix33_0003)
{
	matrix33 mat;
	mat.Set(1,2,3,4,5,6,7,8,9);

	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat.Mat[i][j] == index);
			++index;
		}
	}
}
END_TEST
BEGIN_TEST(Matrix33_0004)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(matrix33::Zero.Mat[i][j] == 0);
		}
	}
}
END_TEST

BEGIN_TEST(Matrix33_0005)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j ) {
				WIN_ASSERT_TRUE(matrix33::Unit.Mat[i][j] == 1);
			}
			else {
				WIN_ASSERT_TRUE(matrix33::Unit.Mat[i][j] == 0);
			}
		}
	}
}
END_TEST

BEGIN_TEST(Matrix33_0006)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	matrix33 mat2(1, 2, 2,
				  2, 1, 2,
				  2, 2, 1);
	matrix33 m = mat1 + mat2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(m.Mat[i][j] == 2);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0007)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	matrix33 mat2(3, 2, 2,
				  2, 3, 2,
				  2, 2, 3);
	matrix33 m = mat1 - mat2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(m.Mat[i][j] == -2);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0008)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);
	const float s = 0;
	matrix33 m = mat1 * s;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(m.Mat[i][j] == 0);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0009)
{
	matrix33 mat1(1, 2, 3,
				  4, 5, 6,
				  7, 8, 9);
	vector3f v(3,4,5);
	vector3f exp(26, 62,98);
	vector3f value = mat1* v;
	WIN_TRACE("value=(%f, %f, %f)\n", value.x, value.y, value.z);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST
BEGIN_TEST(Matrix33_0010)
{
	matrix33 mat1(1, 2, 3,
				  2, 4, 5,
				  3, 4, 1);
	matrix33 mat2(3, 4, 5,
				  5, 4, 3,
				  1, 2, 3);
	matrix33 exp(16, 18, 20,
				 31, 34, 37,
				 30, 30, 30);	
	matrix33 m = mat1 * mat2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(m.Mat[i][j] == exp.Mat[i][j]);
		}

	}

}
END_TEST



BEGIN_TEST(Matrix33_0011)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	matrix33 mat2(1, 2, 2,
				  2, 1, 2,
				  2, 2, 1);
	mat1 += mat2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat1.Mat[i][j] == 2);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0012)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	matrix33 mat2(3, 2, 2,
				  2, 3, 2,
				  2, 2, 3);
	mat1 -= mat2;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat1.Mat[i][j] == -2);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0013)
{
	matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);
	const float s = 0;
	mat1 *= s;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat1.Mat[i][j] == 0);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0014)
{
	matrix33 mat1(1, 2, 3,
				  2, 4, 5,
				  3, 4, 1);
	matrix33 mat2(3, 4, 5,
				  5, 4, 3,
				  1, 2, 3);
	matrix33 exp(16, 18, 20,
				 31, 34, 37,
				 30, 30, 30);	
	mat1 *= mat2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(mat1.Mat[i][j] == exp.Mat[i][j]);
		}

	}

}
END_TEST

BEGIN_TEST(Matrix33_0015)
{
	matrix33 mat(1,2,3,4,5,6,7,8,9);
	const auto value = mat.Determinant();
	const auto exp = 0.f;

	WIN_TRACE("value = %f", value);
	WIN_ASSERT_TRUE(value == exp);
}
END_TEST

BEGIN_TEST(Matrix33_0016)
{
	matrix33 mat(1, 2, 3, 
		         4, 5, 6,
				 7, 8, 9);
	const matrix33 value = mat.Transpose();
	const matrix33 exp(1, 4, 7,
					   2, 5, 8,
					   3, 6, 9);
		for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}

	}
}
END_TEST

BEGIN_TEST(Matrix33_0017)
{
	matrix33 mat;
	mat.SetupIdentity();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j ) {
				WIN_ASSERT_TRUE(mat.Mat[i][j] == 1);
			}
			else {
				WIN_ASSERT_TRUE(mat.Mat[i][j] == 0);
			}
		}
	}
}
END_TEST

BEGIN_TEST(Matrix_0018)
{
	matrix33 mat(1, 2, 3, 
		4, 5, 6,
		7, 8, 9);
	const auto value = mat.Inverse();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == 0);
		}
	}

}
END_TEST


BEGIN_TEST(Matrix_0019)
{
	matrix33 mat(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const auto d = mat.Determinant();
	WIN_TRACE("%f", d);
	WIN_ASSERT_TRUE(d == 12);
	const auto value = mat.Inverse();
	const auto exp = matrix33( -1,  1,  5,
		-7, -5, -1, 
		-4, -8, -4) / d; 

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				const auto a = math::abs(exp.Mat[i][j]);
				const auto b = math::abs(exp.Mat[i][j]);
				WIN_ASSERT_TRUE(math::abs(a - b) <= math::EPSILON);
			}
		}

}
END_TEST


BEGIN_TEST(Matrix_0020)
{
	const matrix33 mat1(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const matrix33 mat2(1, 2, 3,
		3, 2, 1,
		2, 3, 1);
	const matrix33 mat3(1, 2, 3,
		3, 2, 1,
		2, -1, 1);
	
	WIN_ASSERT_TRUE(mat1 == mat2);
	WIN_ASSERT_FALSE(mat1 == mat3);
}
END_TEST


BEGIN_TEST(Matrix_0021)
{
	const matrix33 mat1(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const matrix33 mat2(1, 2, 3,
		3, 2, 1,
		2, 3, 1);
	const matrix33 mat3(1, 2, 3,
		3, 2, 1,
		2, -1, 1);
	
	WIN_ASSERT_FALSE(mat1 != mat2);
	WIN_ASSERT_TRUE(mat1 != mat3);
}
END_TEST

