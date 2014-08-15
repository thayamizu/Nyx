#pragma once
#include "PCH/PCH.h"

using namespace nyx;

BEGIN_TEST(MATRIX44001)
{
	matrix mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(mat.mat_[i][j] == 0);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44002)
{
	matrix mat(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

	int value = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			++value;
			WIN_ASSERT_TRUE(mat.mat_[i][j] == value);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44003)
{
	matrix mat;
	mat.set(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

	int value = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			++value;
			WIN_ASSERT_TRUE(mat.mat_[i][j] == value);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44004)
{
	matrix exp(1,0,0,0,
				 0,1,0,0,
				 0,0,1,0,
				 0,0,0,1);
	matrix mat;
	mat.identity();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(mat.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44005)
{
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const matrix mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const matrix exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	matrix value = mat1 + mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44006)
{
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const matrix mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const matrix exp;
	matrix value = mat1 - mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44007)
{
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 
	const matrix exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	matrix value = mat1 * s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44008)
{
	const matrix mat( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 

	matrix value = mat / s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44009)
{
	const matrix A( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix B( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);

	matrix value = A * B;
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
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const matrix mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const matrix exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	matrix value = mat1 + mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44011)
{
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const matrix mat2(1, 2, 3, 4, 
				  5 ,6, 7, 8, 
				  9, 10, 11, 12,
				  13,14,15,16);
	const matrix exp;
	matrix value = mat1 - mat2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44012)
{
	const matrix mat1(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 
	const matrix exp ( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	matrix value = mat1 * s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44013)
{
	const matrix mat( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);
	const auto s = 2.f; 

	matrix value = mat / s;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			WIN_ASSERT_TRUE(value.mat_[i][j] == exp.mat_[i][j]);
		}
	}
}
END_TEST

BEGIN_TEST(MATRIX44014)
{
	const matrix A( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix B( 2,  4,  6, 8,
					10, 12, 14, 16,
					18, 20, 22, 24,
					26, 28, 30, 32);
	const matrix exp(1  ,2,3,4,
				 5,  6,7,8,
				 9,  10,11,12,
				 13, 14,15,16);

	matrix value = A * B;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//WIN_ASSERT_TRUE(value.Mat[i][j] == exp.Mat[i][j]);
		}
	}
}
END_TEST



