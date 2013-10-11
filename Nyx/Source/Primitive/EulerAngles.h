#ifndef NYX_CORE_INCLUDED_EULER_ANGLES_H_
#define NYX_CORE_INCLUDED_EULER_ANGLES_H_
#include "Primitive/Matrix44.h"
#include "Primitive/Quaternion.h"

namespace Nyx {

	template <typename T = float>
	class EulerAngles {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T heading;		///�w�f�B���O
		T pitch;		///�s�b�`
		T bank;			///�o���N


		static const EulerAngles<T> Zero;///�[���萔
		
		/**
		* �R���X�g���N�^
		*/
		EulerAngles()  {
			Set(0, 0, 0);
		}


		/**
		* �R���X�g���N�^
		* @param T �w�f�B���O
		* @param T �s�b�`
		* @param T �o���N
		*/
		EulerAngles(T heading, T pitch, T bank) {
			Set(heading, pitch, bank);
		}


		/**
		* �I�C���[�p�̒l���Z�b�g���܂�
		* @param T �w�f�B���O
		* @param T �s�b�`
		* @param T �o���N
		*/
		void Set(T heading, T pitch, T bank) {
			this->heading = heading;
			this->pitch   = pitch;
			this->bank    = bank;
		}


		/**
		* �I�C���[�p���P�������܂�
		*/
		void SetupIdentity() {
			Set(0, 0, 0);
		}


		/**
		* �I�C���[�p�𐳏������܂�
		*/
		void Canonize() {
			//-�΁`�΂͈̔͂Ƀ��b�v���郉���_��
			auto wrapPI = [](T radian){
				const float k = 1.0f / Math::PI;
				radian = radian - Math::DoublePI *Math::Floor((radian +Math::PI)/Math::DoublePI);
				return radian;
			};
			pitch = wrapPI(pitch);

			if (pitch < -Math::HalfPI) {
				heading += Math::PI;
				pitch    = - Math::PI - pitch;
				bank    += Math::PI;
			}
			else if (pitch > Math::HalfPI) {
				heading += Math::PI;
				pitch    = Math::PI - pitch;
				bank    += Math::PI;
			}

			if (Math::Abs(pitch) > Math::HalfPI - 1e-4) {
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
	const EulerAngles<T> EulerAngles<T>::Zero = EulerAngles<T>(0, 0, 0, 0);
}
#endif