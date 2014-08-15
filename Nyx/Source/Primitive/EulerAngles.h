#ifndef NYX_CORE_INCLUDED_EULER_ANGLES_H_
#define NYX_CORE_INCLUDED_EULER_ANGLES_H_
#include "Primitive/Matrix44.h"
#include "Primitive/Quaternion.h"

namespace nyx {

	template <typename T = float>
	class euler_angles {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T heading;		///�w�f�B���O
		T pitch;		///�s�b�`
		T bank;			///�o���N


		static const euler_angles<T> ZERO;///�[���萔
		
		/**
		* �R���X�g���N�^
		*/
		euler_angles()  {
			set(0, 0, 0);
		}


		/**
		* �R���X�g���N�^
		* @param T �w�f�B���O
		* @param T �s�b�`
		* @param T �o���N
		*/
		euler_angles(T heading, T pitch, T bank) {
			set(heading, pitch, bank);
		}


		/**
		* �I�C���[�p�̒l���Z�b�g���܂�
		* @param T �w�f�B���O
		* @param T �s�b�`
		* @param T �o���N
		*/
		void set(T heading, T pitch, T bank) {
			this->heading = heading;
			this->pitch   = pitch;
			this->bank    = bank;
		}


		/**
		* �I�C���[�p���P�������܂�
		*/
		void identity() {
			set(0, 0, 0);
		}


		/**
		* �I�C���[�p�𐳏������܂�
		*/
		void canonize() {
			//-�΁`�΂͈̔͂Ƀ��b�v���郉���_��
			auto wrapPI = [](T radian){
				const float k = 1.0f / math::PI;
				radian = radian - math::DOUBLE_PI *math::floor((radian +math::PI)/math::DOUBLE_PI);
				return radian;
			};
			pitch = wrapPI(pitch);

			if (pitch < -math::HALF_PI) {
				heading += math::PI;
				pitch    = - math::PI - pitch;
				bank    += math::PI;
			}
			else if (pitch > math::HALF_PI) {
				heading += math::PI;
				pitch    = math::PI - pitch;
				bank    += math::PI;
			}

			if (math::abs(pitch) > math::HALF_PI - 1e-4) {
				heading += bank;
				bank = 0.0;
			}
			else {
				bank = wrapPI(bank);
			}

			heading = wrapPI(heading);
		}
	};

	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------
	// �[���l����
	template<typename T>
	const euler_angles<T> euler_angles<T>::ZERO = euler_angles<T>(0, 0, 0, 0);
}
#endif