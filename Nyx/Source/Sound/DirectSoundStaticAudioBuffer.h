#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSoundAudioBuffer.h"

namespace Nyx {
	class AudioBuffer;
	struct AudioBufferDesc;
	
	class DirectSoundStaticAudioBuffer : public IAudioBuffer {
	public:
		/**
		* コンストラクタ
		*/
		explicit DirectSoundStaticAudioBuffer();

		/**
		* コンストラクタ
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		explicit DirectSoundStaticAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr ds, const std::wstring& fileName);

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
		virtual AudioUtility::BufferType GetBufferType() const;


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