/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "AudioUtility.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundStaticAudioBuffer.h"
#include "WaveReader.h"
namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStaticAudioBuffer::DirectSoundStaticAudioBuffer(
		const AudioBufferDesc& bufferDesc, 
		const DirectSoundPtr dsound, const std::wstring& fileName)
		: DirectSoundStereoAudioBuffer(), waveReader_(new WaveReader(fileName)), bufferDesc_(bufferDesc){

			bufferDesc_.waveFormat = waveReader_->ReadHeader();

			Load(bufferDesc_, dsound);

			WriteWaveData();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::BufferType DirectSoundStaticAudioBuffer::GetBufferType() const {
		return AudioUtility::BufferType_StaticAudioBuffer;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStaticAudioBuffer::WriteWaveData(){
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
	void DirectSoundStaticAudioBuffer::BuildDirectSoundBufferDesc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		Assert(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->ReadHeader();

		//�t���O�̐ݒ�
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;

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