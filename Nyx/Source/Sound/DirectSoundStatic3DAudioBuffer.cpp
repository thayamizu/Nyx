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
#include "Debug/DebugOutput.h"
#include "AudioUtility.h"
#include "WaveReader.h"
#include "SoundReader.h"
#include "DirectSoundStatic3DAudioBuffer.h"

namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	dsound_static_3d_audio_buffer::dsound_static_3d_audio_buffer(
		const audio_buffer_desc& bufferDesc, 
		const dsound_ptr dsound, const std::shared_ptr<sound_reader> reader)
		: dsound_3d_audio_buffer(), waveReader_(reader), bufferDesc_(bufferDesc){

			bufferDesc_.waveFormat = waveReader_->read_header();

			load(bufferDesc_, dsound);
			create_3d_buffer();
			write_wave_data();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AUDIO_BUFFER_TYPE dsound_static_3d_audio_buffer::get_buffer_type() const {
		return AUDIO_BUFFER_TYPE_STATIC_3D;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_static_3d_audio_buffer::write_wave_data(){
		//�o�b�t�@�ɔg�`�f�[�^�̏�������
		void* waveData  = nullptr;
		uint64_t waveSize  = 0;
		HRESULT hr = get_handle()->Lock(0, 0, &waveData, &waveSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}
		
		uint64_t readBytes;
		auto buffer= waveReader_->read(waveSize, &readBytes);
		CopyMemory(waveData, buffer.get(), readBytes);

		hr = get_handle()->Unlock(waveData, waveSize, NULL, NULL);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_static_3d_audio_buffer::build_dsound_buffer_desc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		NYX_ASSERT(waveReader_ != nullptr);
		const auto waveHeader = waveReader_->read_header();

		//�t���O�̐ݒ�
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY;

		//�t�H�[�J�X���[�h�̐ݒ�
		if ( bufferDesc_.focusType == FOCUS_TYPE_GLOBAL) {
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