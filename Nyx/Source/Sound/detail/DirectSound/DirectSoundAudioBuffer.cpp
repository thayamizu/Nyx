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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Sound/AudioUtility.h"
#include "Sound/WaveReader.h"
#include "DirectSoundAudioBuffer.h"

namespace Nyx {
	DirectSoundAudioBuffer::DirectSoundAudioBuffer() 
		: soundBuffer_(nullptr), bufferDesc_(), waveReader_(nullptr) {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundAudioBuffer::DirectSoundAudioBuffer(const AudioBufferDesc& bufferDesc, const DirectSoundPtr dsound, const std::wstring& fileName)
		: soundBuffer_(nullptr), bufferDesc_(bufferDesc), waveReader_(new WaveReader(fileName)){
			
			Load(bufferDesc, dsound, fileName);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Load(const AudioBufferDesc& desc, const DirectSoundPtr ds, const std::wstring& fileName) {
		WAVEFORMATEX wfx;
		BuildWaveFormatEx(wfx);

		DSBUFFERDESC bufferDesc;
		BuildDirectSoundBufferDesc(bufferDesc, wfx);

		//フォーカスモード
		//サウンドバッファの生成
		LPDIRECTSOUNDBUFFER primaryBuffer;
		HRESULT hr = ds->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオのプライマリバッファの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオのプライマリバッファの作成に失敗しました。", hr);
		}

		LPDIRECTSOUNDBUFFER8 soundBuffer;
		hr = primaryBuffer->QueryInterface(IID_IDirectSoundBuffer8 , (void**)&soundBuffer);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオのセカンダリバッファの作成に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオのセカンダリバッファの作成に失敗しました。", hr);
		}

		//スマートポインタの管理下に置く
		soundBuffer_ = DirectSoundBufferPtr(soundBuffer);

		//バッファに書き込み
		WriteWaveData();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Play(bool isLoop) {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Play(0, 0, isLoop);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファを再生出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファを再生出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Stop() {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->Stop();
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファを停止出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファを停止出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Resume() {
		Assert(soundBuffer_ != nullptr);
		//再生中なら処理しない
		ulong status = GetStatus();
		if ((status & DSBSTATUS_PLAYING)) {
			return;
		} 

		//レジュームする
		HRESULT hr = soundBuffer_->Play(0, 0, status & DSBPLAY_LOOPING);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファをレジューム出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファをレジューム出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::Reset() {
		Assert(soundBuffer_ != nullptr);
		//再生中なら停止する
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		} 

		HRESULT hr = soundBuffer_->SetCurrentPosition(0);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファの再生位置をリセット出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファの再生位置をリセット出来ませんでした。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetPan(long pan) {
		Assert(soundBuffer_ != nullptr);
		HRESULT hr = soundBuffer_->SetPan(pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのパン値の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのパン値の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetVolume(long volume) {
		Assert(soundBuffer_ != nullptr);
		long decibel = AudioUtility::VolumeToDecibel(volume);
		HRESULT hr = soundBuffer_->SetVolume(decibel);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのデシベル値の設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのデシベル値の設定に失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundAudioBuffer::GetPan() const {
		Assert(soundBuffer_ != nullptr);
		long pan;
		HRESULT hr = soundBuffer_->GetPan(&pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのパン値の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのパン値の取得に失敗しました。", hr);
		}

		return pan;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundAudioBuffer::GetVolume() const {
		Assert(soundBuffer_ != nullptr);
		long decibel;
		HRESULT hr = soundBuffer_->GetVolume(&decibel);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのデシベル値の取得に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのデシベル値の取得に失敗しました。", hr);
		}

		return AudioUtility::DecibelToVolume(decibel);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioState DirectSoundAudioBuffer::GetState() const {
		Assert(soundBuffer_ != nullptr);
		ulong status = GetStatus();

		AudioState state;
		state.isBufferLost = static_cast<bool>(status & DSBSTATUS_BUFFERLOST);
		state.isLooping    = static_cast<bool>(status & DSBSTATUS_LOOPING);
		state.isPlaying    = static_cast<bool>(status & DSBSTATUS_PLAYING);

		return state;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::ResetEffect() {
		HRESULT hr = soundBuffer_->SetFX(0, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("エフェクトのリセットに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("エフェクトのリセットに失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetEffect(const AudioEffectDesc& effectDesc) {
		switch(effectDesc.effectType) {
		case AudioUtility::EffectType_Chorus:
			SetChorusEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Distortion:
			SetDistortionEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Echo:
			SetEchoEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Flanger:
			SetFlangerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Gargle:
			SetFlangerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_ParametricEqualizer:
			SetParametricEqualizerEffect(effectDesc);
			break;
		case AudioUtility::EffectType_Reverb:
			SetReverbEffect(effectDesc);
			break;
		default:
			DebugOutput::Trace("EffectTypeの値が違います。");
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::BuildWaveFormatEx(WAVEFORMATEX& wfx) {
		//ヘッダ情報
		const auto waveHeader = waveReader_->GetFileHeader();

		//Waveフォーマットのセットアップ
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx.nChannels       = waveHeader.formatChunk.channelNum;
		wfx.wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx.nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx.nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx.nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx.cbSize          = sizeof(WAVEFORMATEX);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC& dsBufferDesc, WAVEFORMATEX& wfx) {
		//ヘッダ情報
		const auto waveHeader = waveReader_->GetFileHeader();

		//フラグの設定
		DWORD flag;
		switch(bufferDesc_.bufferType)
		{
		case AudioUtility::BufferType_StaticAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
			break;
		case AudioUtility::BufferType_Static3DAudioBufer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRL3D  | DSBCAPS_CTRLVOLUME;
			break;
		case AudioUtility::BufferType_StreamingAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY;
			break;
		case AudioUtility::BufferType_Streaming3DAudioBuffer:
			flag = DSBCAPS_CTRLFX | DSBCAPS_CTRL3D  | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY;
			break;
		}

		//フォーカスモードの設定
		if ( bufferDesc_.focusType == AudioUtility::FocusType_GlobalFocus) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDescのセットアップ
		ZeroMemory(&dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc.lpwfxFormat     = &wfx;
		dsBufferDesc.dwBufferBytes   = bufferDesc_.bufferSize;
		dsBufferDesc.dwFlags         = flag;
		dsBufferDesc.dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc.guid3DAlgorithm = bufferDesc_.algorithm;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::WriteWaveData() {
		Assert(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->GetFileHeader();

		//バッファに波形データの書き込み
		void* waveData  = nullptr;
		ulong waveSize  = 0;
		ulong chunkSize = waveHeader.dataChunk.chunkSize; 
		HRESULT hr = soundBuffer_->Lock(0, chunkSize, &waveData, &waveSize, NULL, NULL, 0);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのロックに失敗しました。", hr);
		}

		auto waveDataSource = waveReader_->GetWaveData();
		memcpy(waveData, waveDataSource.get(), chunkSize);

		hr = soundBuffer_->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのアンロックに失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのアンロックに失敗しました。", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetChorusEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_CHORUS;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("コーラスエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("コーラスエフェクトの設定に失敗しました。", hr);
		}

		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetDistortionEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_DISTORTION;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("ディストーションエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("ディストーションエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetEchoEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("エコーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("エコーエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}
	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetFlangerEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_FLANGER;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("フランジャーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("フランジャーエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetGargleEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_GARGLE;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("ガーグルエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("ガーグルエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetParametricEqualizerEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_STANDARD_PARAMEQ;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("パラメトリックイコライザーエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("パラメトリックイコライザースエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundAudioBuffer::SetReverbEffect(const AudioEffectDesc& effectDesc) {
		ulong status = GetStatus();
		if (status & DSBSTATUS_PLAYING) {
			Stop();
		}

		ulong result;
		DSEFFECTDESC desc;
		ZeroMemory(&desc, sizeof(DSEFFECTDESC));
		desc.dwSize  = sizeof(DSEFFECTDESC);
		desc.dwFlags = NULL;
		desc.guidDSFXClass = GUID_DSFX_WAVES_REVERB;

		HRESULT hr = soundBuffer_->SetFX(1, &desc, &result);
		if (FAILED(hr)) {
			DebugOutput::Trace("リバーブエフェクトの設定に失敗しました。[%s:%d]", __FILE__, __LINE__);
			throw COMException("リバーブスエフェクトの設定に失敗しました。", hr);
		}
		Resume();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	ulong DirectSoundAudioBuffer::GetStatus() const {
		Assert(soundBuffer_ != nullptr);
		ulong status;
		HRESULT hr = soundBuffer_->GetStatus(&status);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSoundオーディオバッファのステータスコードを取得出来ませんでした。[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSoundオーディオバッファのステータスコードを取得出来ませんでした。", hr);
		}
		return status;
	}
}