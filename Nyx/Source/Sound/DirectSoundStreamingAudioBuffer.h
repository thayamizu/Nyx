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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#include "Sound/IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class AudioBuffer;
	struct AudioBufferDesc;
	class DirectSoundAudioBuffer;

	class DirectSoundStreamingAudioBuffer : public IAudioBuffer {
	public:
		/**
		* コンストラクタ
		*/
		explicit DirectSoundStreamingAudioBuffer();

		/**
		* コンストラクタ
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		explicit DirectSoundStreamingAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);

		/**
		* コンストラクタ
		* @param const AudioBufferDesc オーディオバッファ記述子
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		virtual void Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);


		/**
		* オーディオバッファを再生します
		*/
		virtual void Play(bool isLoop);


		/**
		* オーディオバッファを停止します
		*/
		virtual void Stop();


		/**
		* オーディオバッファをレジュームします
		*/
		virtual void Resume();


		/**
		* オーディオバッファをリセットします
		*/
		virtual void Reset();


		/**
		* パンの値を設定します
		* @param long パン
		*/
		virtual void SetPan(long pan);


		/**
		* ボリュームの値を設定します
		* @param long ボリューム
		*/
		virtual void SetVolume(long volume);


		/**
		* ボリュームの値を取得します
		* @return long
		*/
		virtual long GetVolume() const;


		/**
		* パンの値を取得します
		* @return long
		*/
		virtual long GetPan() const;


		/**
		* オーディオバッファの状態の取得
		* @return AudioState
		*/
		virtual AudioState GetState() const;


		/**
		* オーディオバッファの状態の取得します
		* @return AudioUtility::BufferType
		*/
		virtual AudioUtility::BufferType GetBufferType() const = 0;


		/**
		*　オーディオバッファにエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		virtual void SetEffect(const AudioEffectDesc& effectDesc);
		
		
		/**
		*　オーディオバッファのエフェクトをリセットします
		*/
		virtual void ResetEffect();
	private:
		std::shared_ptr<DirectSoundAudioBuffer> audio_;
	};
}
#endif