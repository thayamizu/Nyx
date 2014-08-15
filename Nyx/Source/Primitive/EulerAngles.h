#ifndef NYX_CORE_INCLUDED_EULER_ANGLES_H_
#define NYX_CORE_INCLUDED_EULER_ANGLES_H_
#include "Primitive/Matrix44.h"
#include "Primitive/Quaternion.h"

namespace nyx {

	template <typename T = float>
	class euler_angles {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T heading;		///ヘディング
		T pitch;		///ピッチ
		T bank;			///バンク


		static const euler_angles<T> ZERO;///ゼロ定数
		
		/**
		* コンストラクタ
		*/
		euler_angles()  {
			set(0, 0, 0);
		}


		/**
		* コンストラクタ
		* @param T ヘディング
		* @param T ピッチ
		* @param T バンク
		*/
		euler_angles(T heading, T pitch, T bank) {
			set(heading, pitch, bank);
		}


		/**
		* オイラー角の値をセットします
		* @param T ヘディング
		* @param T ピッチ
		* @param T バンク
		*/
		void set(T heading, T pitch, T bank) {
			this->heading = heading;
			this->pitch   = pitch;
			this->bank    = bank;
		}


		/**
		* オイラー角を恒等化します
		*/
		void identity() {
			set(0, 0, 0);
		}


		/**
		* オイラー角を正準化します
		*/
		void canonize() {
			//-π～πの範囲にラップするラムダ式
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
	// 定数定義
	//--------------------------------------------------------------------------------------
	// ゼロ四元数
	template<typename T>
	const euler_angles<T> euler_angles<T>::ZERO = euler_angles<T>(0, 0, 0, 0);
}
#endif