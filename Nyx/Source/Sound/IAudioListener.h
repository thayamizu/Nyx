/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#define NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#include "Primitive/Vector3.h"

namespace nyx {
	///オーディオリスナー
	class iaudio_listener {
	public:
		virtual ~iaudio_listener() {}
	
		/**
		* リスナーの位置を取得します
		* @return Vecto3f リスナーの位置ベクトル
		*/
		virtual vector3f get_position() const = 0;
	

		/**
		*　リスナーの位置を設定します
		* @param const Vector3f&　リスナーの位置ベクトル
		*/
		virtual void set_position(const vector3f& pos) = 0;
		
		
		/**
		* 速度ベクトルを取得します
		* @return Vector3f　リスナーの速度ベクトル
		*/
		virtual vector3f get_velocity() const = 0;
		
		
		/**
		*　速度ベクトルを設定します
		* @param const Vector3f& リスナーの速度ベクトル
		*/
		virtual void set_velocity(const vector3f& velocity) = 0;


		/**
		* ドップラー係数を取得します
		* @return float ドップラー係数
		*/
		virtual float get_doppler_factor() const = 0;
		

		/**
		* ドップラー係数を設定します
		* @param float ドップラー係数
		*/
		virtual void set_doppler_factor(float dopplerFactor) = 0;
		

		/**
		* ロールオフ係数を取得します
		* @return ロールオフ係数
		*/
		virtual float get_rolloff_factor() const = 0;
		
		
		/**
		* ロールオフ係数を設定します
		* @param float ロールオフ係数
		*/
		virtual void set_rolloff_factor(float rolloffFactor) = 0;
	};
}
#endif