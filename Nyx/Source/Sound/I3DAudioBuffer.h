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
#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H
#include "Primitive/Vector3.h"

namespace nyx {
	///3Dサウンドの機能を持つオーディオバッファインタフェース
	class i3d_audio_buffer{
	public:
		virtual vector3f get_position() const = 0;
		virtual void set_position(const vector3f& velocity) = 0;
		virtual vector3f get_velocity() const = 0;
		virtual void set_velocity(const vector3f& velocity) = 0;

		/**
		* 音源からの最大距離を取得します
		* @return float 音源からの最大距離
		*/
		virtual float get_max_distance() const = 0;


		/**
		* 音源からの最大距離を設定します
		* @param float  最大距離
		*/
		virtual void set_max_distance(float maxDistance) = 0;
		

		/**
		* 音源からの最小距離を設定します
		* @param float  最小距離
		*/
		virtual float get_min_distance() const = 0;


		/**
		* 音源からの最小距離を取得します
		* @return float 音源からの最小距離
		*/
		virtual void set_min_distance(float minDistance) = 0;
	};
}
#endif