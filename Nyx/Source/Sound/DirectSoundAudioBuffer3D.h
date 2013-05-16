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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_3D_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_3D_AUDIO_BUFFER_H_
#include "IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class Vector3f;

	///DirectSound3DAuioBufferのラッパ
	//class DirectSound3DAudioBuffer {
	//public:
	//	/**
	//	* コンストラクタ
	//	*/
	//	DirectSound3DAudioBuffer();
	//	
	//	/**
	//	* 
	//	DirectSound3DAudioBuffer();
	//	/**
	//	* リスナーの位置を取得します
	//	* @return Vecto3f リスナーの位置ベクトル
	//	*/
	//	Vector3f GetPosition() const ;


	//	/**
	//	*　リスナーの位置を設定します
	//	* @param const Vector3f&　リスナーの位置ベクトル
	//	*/
	//	void SetPosition(const Vector3f& pos) ;


	//	/**
	//	* 速度ベクトルを取得します
	//	* @return Vector3f　リスナーの速度ベクトル
	//	*/
	//	Vector3f GetVelocity() const ;


	//	/**
	//	*　速度ベクトルを設定します
	//	* @param const Vector3f& リスナーの速度ベクトル
	//	*/
	//	void SetVelocity(const Vector3f& velocity) ;


	//	/**
	//	* ドップラー係数を取得します
	//	* @return float ドップラー係数
	//	*/
	//	float GetDopplerFactor() const ;


	//	/**
	//	* ドップラー係数を設定します
	//	* @param float ドップラー係数
	//	*/
	//	void SetDopplerFactor(float dopplerFactor) ;


	//	/**
	//	* ロールオフ係数を取得します
	//	* @return ロールオフ係数
	//	*/
	//	float GetRolloffFactor() const ;


	//	/**
	//	* ロールオフ係数を設定します
	//	* @param float ロールオフ係数
	//	*/
	//	void SetRolloffFactor(float rolloffFactor) ;

	//private:
	//	DirectSoundBufferPtr soundBuffer; ///< 3Dサウンドバッファ
	//};
}
#endif
