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
#ifndef NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#define NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "Sound/IAudioBuffer.h"

namespace Nyx {
	///オーディオバッファのDirectSoundによる実装
	class DirectSoundAudioBuffer : public IAudioBuffer{
	public:
		/**
		* コンストラクタ
		*/
		explicit DirectSoundAudioBuffer();

		/**
		* コンストラクタ
		* @param const AudioBufferDesc オーディオバッファ記述子
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		virtual void Load(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds);


		/**
		* 再生
		*/
		virtual void Play(bool isLoop);


		/**
		* 停止
		*/
		virtual void Stop();


		/**
		* レジューム
		*/
		virtual void Resume();


		/**
		* リセット
		*/
		virtual void Reset();


		/**
		* ボリュームの設定
		* @param long ボリューム
		*/
		virtual void SetVolume(long volume);


		/**
		* ボリュームの取得
		* @return long
		*/
		virtual long GetVolume() const;


		/**
		* ステータスコードの取得
		* @return ulong
		*/
		virtual ulong GetStatus() const;


		/**
		*　オーディオバッファにエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		virtual void SetEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファのエフェクトをリセットします
		*/
		virtual void ResetEffect();


		/**
		* DirectSoundBufferのポインタを返します
		* @return const DirectSoundBufferPtr& DirectSoundBufferのポインタ
		*/
		virtual const DirectSoundBufferPtr& GetHandle() const;


		/**
		* オーディオバッファの状態の取得
		* @return AudioState
		*/
		virtual AudioState GetState() const;


	protected:
		/**
		* AudioBufferDescからDSBUFFERDESCを構築します
		* @param [out] DSBUFFERDESC
		* @param const AudioBufferDesc&
		*/
		virtual void BuildDirectSoundBufferDesc(DSBUFFERDESC* bufferDesc, WAVEFORMATEX& wfx) = 0;


		/**
		* バッファにWaveデータを書き込みます
		* @param size_t バッファサイズ
		*/
		virtual void WriteWaveData() = 0;
	private:	
		/**
		*　オーディオバッファにコーラスエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetChorusEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにディストーションエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetDistortionEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにエコーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetEchoEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにフランジャーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetFlangerEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにガーグルエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetGargleEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにパラメトリックイコライザーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetParametricEqualizerEffect(const AudioEffectDesc& effectDesc);


		/**
		*　オーディオバッファにリバーブエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void SetReverbEffect(const AudioEffectDesc& effectDesc);
	private:
		DirectSoundBufferPtr soundBuffer_;
	};
}
#endif