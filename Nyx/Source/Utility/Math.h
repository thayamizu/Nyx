#ifndef NYX_CORE_INCLUDED_MATH_H_
#define NYX_CORE_INCLUDED_MATH_H_
#include <cmath>

namespace Nyx
{
	class Math  {
	public:
		//--------------------------------------------------------------------------------------
		//���w�萔��`
		//--------------------------------------------------------------------------------------
		/**
		* �p�C
		*/
		static const float PI;       

		/**
		* �l�C�s�A��
		*/
		static const float E;

		/**
		* �p�C/2
		*/
		static const float HalfPI;

		/**
		* �p�C/4
		*/
		static const float QuadraplePI;

		/**
		* �p�C * 2
		*/
		static const float DoublePI;

		/**
		* �p�C * 4
		*/
		static const float QuadrantPI;

		/**
		* �C�v�V����
		*/
		static const float Epsilon;



		//--------------------------------------------------------------------------------------
		// �P�ʕϊ��֐�
		//--------------------------------------------------------------------------------------
		/**
		* �ʓx�@�֕ϊ�
		* @param deg �x���@�̊p�x
		* @return  float �x���@���ʓx�@�ɕϊ������l
		*/
		static float ToRadian(float deg) {
			return deg * PI / 180.0F ; 
		}

		/**
		* �x���@�֕ϊ�
		* @param rad �ʓx�@
		* @return  float �ʓx�@��x���@�ɕϊ������l
		*/
		static float ToDegree(float rad) {
			return rad * 180.0F / PI;
		}

		//--------------------------------------------------------------------------------------
		// ��Βl
		//--------------------------------------------------------------------------------------
		/**
		* ��Βl���v�Z����
		* @param  x    ��Βl�ɂ���������
		* @return ��Βl
		*/
		static int Abs(int x) {
			return ::abs(x);

		}

		/**
		* ��Βl���v�Z����
		* @param  x�@��Βl�ɂ���������
		* @return ��Βl
		*/
		static float Abs(float x) {
			return ::fabs(x);
		}

		//--------------------------------------------------------------------------------------
		// �ő�l�E�ŏ��l
		//--------------------------------------------------------------------------------------
		/**
		* �ő�l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return �傫������Ԃ�
		*/
		static int Max(int x, int y) {
			return (x > y) ? x : y;
		}

		/**
		* �ő�l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return �傫������Ԃ�
		*/
		static float Max(float x, float y) {
			return (x > y) ? x : y;
		}

		/**
		* �ŏ��l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return�@����������Ԃ�
		*/
		static int Min(int x, int y) {
			return  (x > y) ? y : x;
		}

		/**
		* �ŏ��l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return�@����������Ԃ�
		*/
		static float Min(float x, float y) {
			return (x > y) ? y : x;
		}

		//--------------------------------------------------------------------------------------
		// �؂�グ�E�؂�̂�
		//--------------------------------------------------------------------------------------
		/**
		* �؂�̂�
		* @param x �؂�̂Ă�����
		* @return �؂�̂Ă��l
		*/
		static float Floor(float x) {
			return ::floorf(x);
		}

		/**
		* �؂�グ
		* @param x �؂�グ�����l
		* @return �؂�グ���l
		*/  
		static float Ceil(float x) {
			return ::ceilf(x);
		}

		//--------------------------------------------------------------------------------------
		//�w���E�ΐ��֐�
		//--------------------------------------------------------------------------------------
		/**
		* ���������v�Z����
		* @param
		* @return 
		*/
		static float Sqrt(float x) {
			return ::sqrtf(x);
		}

		/**
		* �ׂ���
		* @param x ��
		* @param y �w��
		* @return x��y��
		*/
		static float Pow(float x, float y) {
			return ::powf(x, y);
		}
		/**
		* 2�ׂ̂���
		* @param x �w��
		* @return 2��x��
		*/
		static float Pow2(float x) {
			return ::powf(2.0f, x);
		}

		/**
		* �w��
		* @param x �搔
		* @return ���R�ΐ��̒��x��
		*/
		static float Exp(float x) {
			return ::expf(x);
		}

		/**
		* ���R�ΐ�
		* @param x ���R�ΐ������Ώےl
		* @return ���R�ΐ�
		*/ 
		static float Log(float x) {
			return ::logf(x);
		}

		/**
		* ��p�ΐ�
		* @param x ��p�ΐ������Ώےl
		* @return ��p�ΐ�
		*/ 
		static float Log10(float x) {
			return ::log10f(x);
		}

		/**
		* 2�ׂ̂��悩���`�F�b�N
		* @param x 
		* @return 2�̗ݏ�Ȃ�true
		*/
		static bool IsPow2(int x) {
			return (x & (x-1)) == 0;
		}


		//--------------------------------------------------------------------------------------
		//�O�p�֐�
		//--------------------------------------------------------------------------------------
		/**
		* ����
		* @param x �������v�Z����l
		* @return x�̐���
		*/
		static float Sin(float x) {
			return ::sinf(x);
		}

		/**
		* �]��
		* @param x �]�����v�Z����l
		* @return x�̗]��
		*/
		static float Cos(float x) {
			return ::cosf(x);
		}

		/**
		* ����
		* @param x ���ڂ��v�Z����l
		* @return x�̐���
		*/
		static float Tan(float x) {
			return ::tanf(x);
		}

		/**
		* �o�Ȑ���
		* @param x �o�Ȑ������v�Z����l
		* @return x�̑o�Ȑ���
		*/
		static float Sinh(float x) {
			return ::sinhf(x);  
		}

		/**
		* �o�ȗ]��
		* @param x �o�ȗ]�����v�Z����l
		* @return x�̑o�ȗ]��
		*/
		static float Cosh(float x) {
			return ::coshf(x);
		}
		/**
		* �o�Ȑ���
		* @param x �o�Ȑ��ڂ��v�Z����l
		* @return x�̑o�Ȑ���
		*/
		static float Tanh(float x) {
			return ::tanhf(x);
		}

		/**
		* �t����
		* @param x �t�������v�Z����l  -1 �` 1
		* @return x�̋t����   -��/2�`��/2
		*/
		static float Asin(float x) {
			return ::asinf(x);
		}

		/**
		* �t�]��
		* @param x �t�]�����v�Z����l -1 �` 1
		* @return x�̋t�]��-��/2�`��/2
		*/
		static float Acos(float x) {
			return ::acosf(x);
		}

		/**
		* �t����
		* @param x �t���ڂ��v�Z����l
		* @return x�̋t����  -��/2�`��/2
		*/
		static float Atan(float x) {
			return ::atanf(x);
		}

		/**
		* �t����
		* @param y �t���ڂ��v�Z����y�l
		* @param x �t���ڂ��v�Z����x�l     
		* @return (x,y)�̋t���� -�΁`��
		*/                         
		static float Atan2(float y, float x) {
			return ::atan2f(y, x);
		}
	};
}
#endif