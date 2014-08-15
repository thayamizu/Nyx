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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STEREO_AUDIO_BUFFER
#include "DirectSoundAudioBuffer.h"
#include "Primitive/Vector3.h"

namespace nyx {

	///ステレオサウンド
	class dsound_stereo_audio_buffer : public dsound_audio_buffer{
	public:
		/**
		* コンストラクタ
		*/
		dsound_stereo_audio_buffer();


		/**
		* デストラクタ
		*/
		virtual ~dsound_stereo_audio_buffer();


		/**
		* パンの設定
		* @param long パン
		*/
		void set_pan(long pan);


		/**
		* パンの取得
		* @return long
		*/
		long get_pan() const;
	protected:
		virtual vector3f get_position() const ;
		virtual void set_position(const vector3f& velocity) ;
		virtual vector3f get_velocity() const ;
		virtual void set_velocity(const vector3f& velocity) ;

		/**
		* 音源からの最大距離を取得します
		* @return float 音源からの最大距離
		*/
		virtual float get_max_distance() const ;


		/**
		* 音源からの最大距離を設定します
		* @param float  最大距離
		*/
		virtual void set_max_distance(float maxDistance) ;


		/**
		* 音源からの最小距離を設定します
		* @param float  最小距離
		*/
		virtual float get_min_distance() const ;


		/**
		* 音源からの最小距離を取得します
		* @return float 音源からの最小距離
		*/
		virtual void set_min_distance(float minDistance) ;
	};
}
#endif