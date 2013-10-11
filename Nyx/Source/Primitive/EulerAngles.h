#ifndef NYX_CORE_INCLUDED_EULER_ANGLES_H_
#define NYX_CORE_INCLUDED_EULER_ANGLES_H_
#include "Primitive/Matrix44.h"
#include "Primitive/Quaternion.h"

namespace Nyx {

	template <typename T = float>
	class EulerAngles {
		static_assert(std::is_floating_point<T>::value, "T required floating_point.");
	public:
		T heading;		///ヘディング
		T pitch;		///ピッチ
		T bank;			///バンク


		static const EulerAngles<T> Zero;///ゼロ定数
		
		/**
		* コンストラクタ
		*/
		EulerAngles()  {
			Set(0, 0, 0);
		}


		/**
		* コンストラクタ
		* @param T ヘディング
		* @param T ピッチ
		* @param T バンク
		*/
		EulerAngles(T heading, T pitch, T bank) {
			Set(heading, pitch, bank);
		}


		/**
		* オイラー角の値をセットします
		* @param T ヘディング
		* @param T ピッチ
		* @param T バンク
		*/
		void Set(T heading, T pitch, T bank) {
			this->heading = heading;
			this->pitch   = pitch;
			this->bank    = bank;
		}


		/**
		* オイラー角を恒等化します
		*/
		void SetupIdentity() {
			Set(0, 0, 0);
		}


		/**
		* オイラー角を正準化します
		*/
		void Canonize() {
			//-π～πの範囲にラップするラムダ式
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
	// 定数定義
	//--------------------------------------------------------------------------------------
	// ゼロ四元数
	template<typename T>
	const EulerAngles<T> EulerAngles<T>::Zero = EulerAngles<T>(0, 0, 0, 0);
}
#endif