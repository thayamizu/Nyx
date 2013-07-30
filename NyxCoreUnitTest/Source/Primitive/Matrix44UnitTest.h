#pragma once
#include "PCH/PCH.h"

using namespace Nyx;

BEGIN_TEST(MATRIX44001)
{
	Matrix44 mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(mat.Mat[i][j] == 0);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44002)
{
	Matrix44 mat(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

	int value = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			++value;
			WIN_ASSERT_TRUE(mat.Mat[i][j] == value);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44003)
{
	Matrix44 mat;
	mat.Set(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

	int value = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			++value;
			WIN_ASSERT_TRUE(mat.Mat[i][j] == value);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44004)
{
	Matrix44 exp(1,0,0,0,
				 0,1,0,0,
				 0,0,1,0,
				 0,0,0,1);
	Matrix44 mat;
	mat.Identity();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(mat.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44005)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const Matrix44 mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const Matrix44 exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	Matrix44 value = mat1 + mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44006)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const Matrix44 mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const Matrix44 exp;
	Matrix44 value = mat1 - mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44007)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 
	const Matrix44 exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	Matrix44 value = mat1 * s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44008)
{
	const Matrix44 mat( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 

	Matrix44 value = mat / s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44009)
{
	const Matrix44 A( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 B( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);

	Matrix44 value = A * B;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST


BEGIN_TEST(MATRIX44010)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const Matrix44 mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const Matrix44 exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	Matrix44 value = mat1 + mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44011)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const Matrix44 mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const Matrix44 exp;
	Matrix44 value = mat1 - mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44012)
{
	const Matrix44 mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 
	const Matrix44 exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	Matrix44 value = mat1 * s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44013)
{
	const Matrix44 mat( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 

	Matrix44 value = mat / s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44014)
{
	const Matrix44 A( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 B( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const Matrix44 exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);

	Matrix44 value = A * B;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST



