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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_3D_STREAMING_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_3D_STREAMING_AUDIO_BUFFER_H_
#include "Sound/IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {

	///3DオーディオバッファのDirectSoundによる実装
	class DirectSound3DStreamingAudioBuffer : public IAudioBuffer {
	public:
		/**
		* コンストラクタ
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		DirectSound3DStreamingAudioBuffer(const DirectSound ds, const std::wstring fileName);

		/**
		* コンストラクタ
		* @param const DirectSound DirectSoundオブジェクト
		* @param  shared_ptr<char> waveData
		*/
		DirectSound3DStreamingAudioBuffer(const DirectSound ds, std::shared_ptr<char> wave);

		/**
		* デストラクタ
		*/
		virtual ~DirectSound3DStreamingAudioBuffer();

		/**
		*　再生
		*/
		void Play();
		/**
		*　停止
		*/
		void Stop();

		/**
		*　レジューム
		*/
		void Resume();

		/**
		*　リセット
		*/
		void Reset();

		/**
		*　パンを設定
		*/
		void SetPan(long pan);

		/**
		*　ボリュームを設定
		*/
		void SetVolume(long v);

		/**
		*　ボリュームの取得
		*/
		long GetVolume() const ;

		/**
		*　パンの取得
		*/
		long GetPan() const;
		
		/**
		* 音源位置を設定
		* @param float x座標
		* @param float y座標
		* @param float z座標
		*/
		void SetPos(float x, float y, float z);

		/**
		* サウンドソースの最小距離を設定
		* @param float 最小距離
		*/
		void SetMinDistance(float min);

		/**
		* サウンドソースの最大距離を設定
		* @param float 最大距離
		*/
		void SetMaxDistance(float max);

	private:
		long volume;///< ボリューム
		long pan;///< パン
		DirectSoundBuffer soundBuffer; ///< サウンドバッファ
		DirectSound3DBuffer sound3DBuffer;///< 3Dバッファ
		DirectSound3DListener listener; ///<　リスナー

	};
}
#endif
