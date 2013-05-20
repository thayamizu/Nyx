#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "AudioUtility.h"
#include "WaveReader.h"
#include "DirectSoundStatic3DAudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStatic3DAudioBuffer::DirectSoundStatic3DAudioBuffer(
		const AudioBufferDesc& bufferDesc, 
		const DirectSoundPtr dsound, const std::wstring& fileName)
		: DirectSound3DAudioBuffer(), waveReader_(new WaveReader(fileName)), bufferDesc_(bufferDesc){

			bufferDesc_.waveFormat = waveReader_->ReadHeader();

			Load(bufferDesc_, dsound, fileName);
			Create3DBuffer();
			WriteWaveData(bufferDesc_.waveFormat.dataChunk.chunkSize);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStatic3DAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_Static3DAudioBuffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStatic3DAudioBuffer::WriteWaveData(size_t bufferSize){
		//�o�b�t�@�ɔg�`�f�[�^�̏�������
		void* waveData  = nullptr;
		ulong waveSize  = 0;
		HRESULT hr = GetHandle()->Lock(0, 0, &waveData, &waveSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}
		
		ulong readBytes;
		auto buffer= waveReader_->Read(waveSize, &readBytes);
		CopyMemory(waveData, buffer.get(), readBytes);

		hr = GetHandle()->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStatic3DAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		Assert(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->ReadHeader();

		//�t���O�̐ݒ�
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY;

		//�t�H�[�J�X���[�h�̐ݒ�
		if ( bufferDesc_.focusType == AudioUtility::FocusType_GlobalFocus) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDesc�̃Z�b�g�A�b�v
		ZeroMemory(dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc->lpwfxFormat     = &wfx;
		dsBufferDesc->dwBufferBytes   = waveHeader.dataChunk.chunkSize;
		dsBufferDesc->dwFlags         = flag;
		dsBufferDesc->dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc->guid3DAlgorithm = bufferDesc_.algorithm;
	}
}