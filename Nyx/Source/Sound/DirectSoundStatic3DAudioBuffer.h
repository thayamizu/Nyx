#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_3DAUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STATIC_3DAUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "DirectSound3DAudioBuffer.h"

namespace Nyx {
	struct AudioBuffeDesc;
	class WaveReader;

	///静的3Dバッファ
	class DirectSoundStatic3DAudioBuffer : public DirectSound3DAudioBuffer {
	public:
		/**
		* コンストラクタ
		* @param const AudioBufferDesc& bufferDesc
		* @param const DirectSoundPtr 
		* @param const std::wstring& fileName
		*/
		DirectSoundStatic3DAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName);


		/**
		* オーディオバッファの状態の取得します
		* @return AudioUtility::BufferType
		*/
		AudioUtility::BufferType GetBufferType() const;
	private:
		/**
		* DirectSoundのセカンダリバッファにwaveデータを書き込みます
		* @param size_t バッファサイズ
		*/
		void WriteWaveData();


		/**
		* 静的なDirectSoundセカンダリバッファ記述子を作成します
		* @param DSBUFFERDESC*
		* @param WAVEFORMATEX& wfx
		*/
		void BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx);
	private:
		AudioBufferDesc bufferDesc_;
		std::shared_ptr<WaveReader> waveReader_;
	};
}
#endif