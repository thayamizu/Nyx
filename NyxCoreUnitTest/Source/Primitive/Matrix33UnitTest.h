#pragma once
#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(Matrix33_0001)
{
	Matrix33 mat;

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
	Matrix33 mat = Matrix33(1,2,3,4,5,6,7,8,9);

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
	Matrix33 mat;
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
			WIN_ASSERT_TRUE(Matrix33::Zero.Mat[i][j] == 0);
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
				WIN_ASSERT_TRUE(Matrix33::Unit.Mat[i][j] == 1);
			}
			else {
				WIN_ASSERT_TRUE(Matrix33::Unit.Mat[i][j] == 0);
			}
		}
	}
}
END_TEST

BEGIN_TEST(Matrix33_0006)
{
	Matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	Matrix33 mat2(1, 2, 2,
				  2, 1, 2,
				  2, 2, 1);
	Matrix33 m = mat1 + mat2;

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
	Matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	Matrix33 mat2(3, 2, 2,
				  2, 3, 2,
				  2, 2, 3);
	Matrix33 m = mat1 - mat2;

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
	Matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);
	const float s = 0;
	Matrix33 m = mat1 * s;

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
	Matrix33 mat1(1, 2, 3,
				  4, 5, 6,
				  7, 8, 9);
	Vector3f v(3,4,5);
	Vector3f exp(26, 62,98);
	Vector3f value = mat1* v;
	WIN_TRACE("value=(%f, %f, %f)\n", value.x, value.y, value.z);
	WIN_ASSERT_TRUE(exp.x == value.x);
	WIN_ASSERT_TRUE(exp.y == value.y);
	WIN_ASSERT_TRUE(exp.z == value.z);
}
END_TEST
BEGIN_TEST(Matrix33_0010)
{
	Matrix33 mat1(1, 2, 3,
				  2, 4, 5,
				  3, 4, 1);
	Matrix33 mat2(3, 4, 5,
				  5, 4, 3,
				  1, 2, 3);
	Matrix33 exp(16, 18, 20,
				 31, 34, 37,
				 30, 30, 30);	
	Matrix33 m = mat1 * mat2;

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
	Matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	Matrix33 mat2(1, 2, 2,
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
	Matrix33 mat1(1, 0, 0,
				  0, 1, 0,
				  0, 0, 1);

	Matrix33 mat2(3, 2, 2,
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
	Matrix33 mat1(1, 0, 0,
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
	Matrix33 mat1(1, 2, 3,
				  2, 4, 5,
				  3, 4, 1);
	Matrix33 mat2(3, 4, 5,
				  5, 4, 3,
				  1, 2, 3);
	Matrix33 exp(16, 18, 20,
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
	Matrix33 mat(1,2,3,4,5,6,7,8,9);
	const auto value = mat.Determinant();
	const auto exp = 0.f;

	WIN_TRACE("value = %f", value);
	WIN_ASSERT_TRUE(value == exp);
}
END_TEST

BEGIN_TEST(Matrix33_0016)
{
	Matrix33 mat(1, 2, 3, 
		         4, 5, 6,
				 7, 8, 9);
	const Matrix33 value = mat.Transpose();
	const Matrix33 exp(1, 4, 7,
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
	Matrix33 mat;
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
	Matrix33 mat(1, 2, 3, 
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
	Matrix33 mat(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const auto d = mat.Determinant();
	WIN_TRACE("%f", d);
	WIN_ASSERT_TRUE(d == 12);
	const auto value = mat.Inverse();
	const auto exp = Matrix33( -1,  1,  5,
		-7, -5, -1, 
		-4, -8, -4) / d; 

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				const auto a = Math::Abs(exp.Mat[i][j]);
				const auto b = Math::Abs(exp.Mat[i][j]);
				WIN_ASSERT_TRUE(Math::Abs(a - b) <= Math::Epsilon);
			}
		}

}
END_TEST


BEGIN_TEST(Matrix_0020)
{
	const Matrix33 mat1(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const Matrix33 mat2(1, 2, 3,
		3, 2, 1,
		2, 3, 1);
	const Matrix33 mat3(1, 2, 3,
		3, 2, 1,
		2, -1, 1);
	
	WIN_ASSERT_TRUE(mat1 == mat2);
	WIN_ASSERT_FALSE(mat1 == mat3);
}
END_TEST


BEGIN_TEST(Matrix_0021)
{
	const Matrix33 mat1(1, 2, 3, 
		3, 2, 1, 
		2, 3, 1);
	const Matrix33 mat2(1, 2, 3,
		3, 2, 1,
		2, 3, 1);
	const Matrix33 mat3(1, 2, 3,
		3, 2, 1,
		2, -1, 1);
	
	WIN_ASSERT_FALSE(mat1 != mat2);
	WIN_ASSERT_TRUE(mat1 != mat3);
}
END_TEST

