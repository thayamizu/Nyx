#ifndef NYX_CORE_INCLUDED_MATH_H_
#define NYX_CORE_INCLUDED_MATH_H_
#include <cmath>

namespace nyx
{
	class math  {
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
		static const float HALF_PI;

		/**
		* �p�C/4
		*/
		static const float QUADRAPLE_PI;

		/**
		* �p�C * 2
		*/
		static const float DOUBLE_PI;

		/**
		* �p�C * 4
		*/
		static const float QUADRANT_PI;

		/**
		* �C�v�V����
		*/
		static const float EPSILON;


		//--------------------------------------------------------------------------------------
		//�N�����v
		//--------------------------------------------------------------------------------------
		/**
		* ����N�����v
		* @note �e���v���[�g�p�����[�^�ɂ́A�Z�p�^���w�肵�Ă��������B
		* @param  �N�����v�Ώ�
		* @param  ���
		*/
		template <typename T>
		static T upper_clamp(T value, T upper) {
			static_assert(std::is_arithmetic<T>::value, "T requires arithmetic type.");
			return (value >= upper)? upper: value; 
		}

		/**
		* �����N�����v
		* @note �e���v���[�g�p�����[�^�ɂ́A�Z�p�^���w�肵�Ă��������B
		* @param T value �N�����v�Ώ�
		* @param T lower ����
		*/
		template <typename T>
		static T lower_clamp(T value, T lower) {
			static_assert(std::is_arithmetic<T>::value, "T requires arithmetic type.");
			return (value <= lower)? lower: value; 
		}

		/**
		* �N�����v
		* @note �e���v���[�g�p�����[�^�ɂ́A�Z�p�^���w�肵�Ă��������B
		* @param T value �N�����v�Ώ�
		* @param T upper ���
		* @param T lower ����
		*/
		template <typename T>
		static T clamp(T value, T lower, T upper) {
			static_assert(std::is_arithmetic<T>::value, "T requires arithmetic type.");
			value = lower_clamp(value, lower);
			value = upper_clamp(value, upper);
			return value;
		}

		//--------------------------------------------------------------------------------------
		// �P�ʕϊ��֐�
		//--------------------------------------------------------------------------------------
		/**
		* �ʓx�@�֕ϊ�
		* @param deg �x���@�̊p�x
		* @return  float �x���@���ʓx�@�ɕϊ������l
		*/
		static float to_radian(float deg) {
			return deg * PI / 180.0F ; 
		}

		/**
		* �x���@�֕ϊ�
		* @param rad �ʓx�@
		* @return  float �ʓx�@��x���@�ɕϊ������l
		*/
		static float to_degree(float rad) {
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
		static int abs(int x) {
			return ::abs(x);

		}

		/**
		* ��Βl���v�Z����
		* @param  x�@��Βl�ɂ���������
		* @return ��Βl
		*/
		static float abs(float x) {
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
		static int max_of(int x, int y) {
			return (x > y) ? x : y;
		}

		/**
		* �ő�l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return �傫������Ԃ�
		*/
		static float max_of(float x, float y) {
			return (x > y) ? x : y;
		}

		/**
		* �ŏ��l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return�@����������Ԃ�
		*/
		static int min_of(int x, int y) {
			return  (x > y) ? y : x;
		}

		/**
		* �ŏ��l
		* @param x �E�Ӓl
		* @param y ���Ӓl
		* @return�@����������Ԃ�
		*/
		static float min_of(float x, float y) {
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
		static float floor(float x) {
			return ::floorf(x);
		}

		/**
		* �؂�グ
		* @param x �؂�グ�����l
		* @return �؂�グ���l
		*/  
		static float ceil(float x) {
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
		static float sqrt(float x) {
			return ::sqrtf(x);
		}

		/**
		* �ׂ���
		* @param x ��
		* @param y �w��
		* @return x��y��
		*/
		static float power(float x, float y) {
			return ::powf(x, y);
		}
		/**
		* 2�ׂ̂���
		* @param x �w��
		* @return 2��x��
		*/
		static float power2(float x) {
			return ::powf(2.0f, x);
		}

		/**
		* �w��
		* @param x �搔
		* @return ���R�ΐ��̒��x��
		*/
		static float exponent(float x) {
			return ::expf(x);
		}

		/**
		* ���R�ΐ�
		* @param x ���R�ΐ������Ώےl
		* @return ���R�ΐ�
		*/ 
		static float log(float x) {
			return ::logf(x);
		}

		/**
		* ��p�ΐ�
		* @param x ��p�ΐ������Ώےl
		* @return ��p�ΐ�
		*/ 
		static float log10(float x) {
			return ::log10f(x);
		}

		/**
		* 2�ׂ̂��悩���`�F�b�N
		* @param x 
		* @return 2�̗ݏ�Ȃ�true
		*/
		static bool is_power2(int x) {
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
		static float sin(float x) {
			return ::sinf(x);
		}

		/**
		* �]��
		* @param x �]�����v�Z����l
		* @return x�̗]��
		*/
		static float cos(float x) {
			return ::cosf(x);
		}

		/**
		* ����
		* @param x ���ڂ��v�Z����l
		* @return x�̐���
		*/
		static float tan(float x) {
			return ::tanf(x);
		}

		/**
		* �o�Ȑ���
		* @param x �o�Ȑ������v�Z����l
		* @return x�̑o�Ȑ���
		*/
		static float sinh(float x) {
			return ::sinhf(x);  
		}

		/**
		* �o�ȗ]��
		* @param x �o�ȗ]�����v�Z����l
		* @return x�̑o�ȗ]��
		*/
		static float cosh(float x) {
			return ::coshf(x);
		}
		/**
		* �o�Ȑ���
		* @param x �o�Ȑ��ڂ��v�Z����l
		* @return x�̑o�Ȑ���
		*/
		static float tanh(float x) {
			return ::tanhf(x);
		}

		/**
		* �t����
		* @param x �t�������v�Z����l  -1 �` 1
		* @return x�̋t����   -��/2�`��/2
		*/
		static float asin(float x) {
			return ::asinf(x);
		}

		/**
		* �t�]��
		* @param x �t�]�����v�Z����l -1 �` 1
		* @return x�̋t�]��-��/2�`��/2
		*/
		static float acos(float x) {
			return ::acosf(x);
		}

		/**
		* �t����
		* @param x �t���ڂ��v�Z����l
		* @return x�̋t����  -��/2�`��/2
		*/
		static float atan(float x) {
			return ::atanf(x);
		}

		/**
		* �t����
		* @param y �t���ڂ��v�Z����y�l
		* @param x �t���ڂ��v�Z����x�l     
		* @return (x,y)�̋t���� -�΁`��
		*/                         
		static float atan2(float y, float x) {
			return ::atan2f(y, x);
		}
	};
}
#endif