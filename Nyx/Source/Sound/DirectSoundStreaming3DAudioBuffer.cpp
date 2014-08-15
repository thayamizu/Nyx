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
#include "IO/File.h"
#include "Sound/WaveReader.h"
#include "Sound/SoundReader.h"
#include "DirectSoundStreaming3DAudioBuffer.h"
namespace nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	dsound_streaming_3d_audio_buffer::dsound_streaming_3d_audio_buffer(
		const audio_buffer_desc& bufferDesc, 
		const dsound_ptr dsound, const std::shared_ptr<sound_reader> reader)
		: dsound_3d_audio_buffer(), waveReader_(reader), bufferDesc_(bufferDesc), offset_(0){

			//�o�b�t�@���쐬

			bufferDesc_.waveFormat = waveReader_->read_header();

			//�o�b�t�@�ɍĐ��f�[�^����������
			const uint64_t samplingRate = bufferDesc_.waveFormat.formatChunk.samplingRate;   
			const uint64_t blockAlign   = bufferDesc_.waveFormat.formatChunk.blockSize;  
			const uint64_t size         = samplingRate * 2 * blockAlign / NotifyEventNum;   
			notifySize_  = size;

			load(bufferDesc_, dsound);
			create_3d_buffer();
			write_wave_data();

			//�ʒm�X���b�h�̐���
			notifyThreadHandle_ = CreateThread( NULL,0, notify_3d_buffer_proc, (void*)this, 0, 0);

			//�ʒm�C�x���g�̐ݒ�
			LPDIRECTSOUNDNOTIFY notify;
			DSBPOSITIONNOTIFY  positionNotify[NotifyEventNum] = {};
			HRESULT hr = get_handle()->QueryInterface(IID_IDirectSoundNotify, reinterpret_cast<void**>(&notify));
			if ( FAILED(hr)) {
				debug_out::trace("IDirectSoundNotify�̎擾�Ɏ��s���܂����B", hr);
				throw com_exception("IDirectSoundNotify�̎擾�Ɏ��s���܂����B", hr);
			}

			// �C�x���g�ƃV�O�i���ɂȂ�ʒu���擾
			for( int i = 0 ; i < NotifyEventNum ; i++ ) {
				notifyEventList_[i] = CreateEvent(NULL, false, false, NULL);
				positionNotify[i].dwOffset     = (notifySize_ * i) + notifySize_-1; 
				positionNotify[i].hEventNotify = notifyEventList_[i];
			}

			// �C�x���g���Z�b�g
			hr = notify->SetNotificationPositions(NotifyEventNum, positionNotify);
			if( FAILED(hr)) {
				debug_out::trace("IDirectSoundNotify�ʒm�C�x���g�̐ݒ肪���s���܂����B", hr);
				throw com_exception("IDirectSoundNotify�ʒm�C�x���g�̐ݒ肪���s���܂����B", hr);
			}

			SafeRelease(notify);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	dsound_streaming_3d_audio_buffer::~dsound_streaming_3d_audio_buffer() {
		for (auto var : notifyEventList_) {
			CloseHandle(var);
		}

		if (notifyThreadHandle_ != nullptr) {
			CloseHandle(notifyThreadHandle_);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioUtility::AUDIO_BUFFER_TYPE dsound_streaming_3d_audio_buffer::get_buffer_type() const {
		return AudioUtility::AUDIO_BUFFER_TYPE_STREAMING_3D;
	}

	void dsound_streaming_3d_audio_buffer::reset() {
		offset_ = 0;
		waveReader_->set_cursor(0);
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_streaming_3d_audio_buffer::write_wave_data(){
		const auto handle = get_handle();
		const auto size   = bufferDesc_.waveFormat.dataChunk.chunkSize;
		
		if (size <= offset_ + notifySize_) {
			offset_ = 0;
			waveReader_->set_cursor(0);
		}
		//�o�b�t�@�����b�N
		void* readData1 = nullptr;
		void* readData2 = nullptr;
		uint64_t readSize1  = 0;
		uint64_t readSize2  = 0;
		HRESULT hr = handle->Lock(0, notifySize_, &readData1, &readSize1, &readData2, &readSize2, DSBLOCK_FROMWRITECURSOR);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃��b�N�Ɏ��s���܂����B", hr);
		}

		//�o�b�t�@�ɏ�������
		uint64_t readBytes;
		const auto buffer = waveReader_->read(readSize1, &readBytes);
		CopyMemory(readData1, buffer.get(), readBytes);
		offset_ += readSize1;
		if (readData2 != nullptr) {
			const auto buffer = waveReader_->read(readSize2, &readBytes);
			CopyMemory(readData2, buffer.get(), readBytes);
			offset_ += readSize2;
		}
		
		//�o�b�t�@���A�����b�N
		hr = handle->Unlock(readData1, readSize1, readData2, readSize2);
		if (FAILED(hr)) {
			debug_out::trace("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw com_exception("DirectSound�I�[�f�B�I�o�b�t�@�̃A�����b�N�Ɏ��s���܂����B", hr);
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_streaming_3d_audio_buffer::build_dsound_buffer_desc(DSBUFFERDESC* dsBufferDesc, WAVEFORMATEX& wfx){
		//�t���O�̐ݒ�
		DWORD flag = DSBCAPS_CTRLFX | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D |  DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;

		//�t�H�[�J�X���[�h�̐ݒ�
		if ( bufferDesc_.focusType == AudioUtility::FOCUS_TYPE_GLOBAL) {
			flag |= DSBCAPS_GLOBALFOCUS;
		}
		else {
			flag |= DSBCAPS_STICKYFOCUS;

		}

		//DSBufferDesc�̃Z�b�g�A�b�v
		ZeroMemory(dsBufferDesc, sizeof(DSBUFFERDESC));
		dsBufferDesc->lpwfxFormat     = &wfx;
		dsBufferDesc->dwBufferBytes   = notifySize_ * NotifyEventNum;
		dsBufferDesc->dwFlags         = flag;
		dsBufferDesc->dwSize          = sizeof(DSBUFFERDESC);
		dsBufferDesc->guid3DAlgorithm = bufferDesc_.algorithm;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	uint64_t _stdcall notify_3d_buffer_proc(void* parameter) {
		NYX_ASSERT(parameter != nullptr)
		auto audio = reinterpret_cast<dsound_streaming_3d_audio_buffer*>(parameter);
		audio->notify_thread();
		return 0L;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void dsound_streaming_3d_audio_buffer::notify_thread() {
		bool isDone = false;
		while( !isDone ) { 
			uint64_t signal = MsgWaitForMultipleObjects(NotifyEventNum, notifyEventList_, 
				FALSE, INFINITE, QS_ALLEVENTS );

			switch( signal ) {
			case WAIT_OBJECT_0: 
			case WAIT_OBJECT_0+1:
			case WAIT_OBJECT_0+2:
			case WAIT_OBJECT_0+3:
				write_wave_data();
				break;
			case WAIT_OBJECT_0+NotifyEventNum:
				std::cout <<"�o�b�t�@��������5" << std::endl;

				MSG msg;
				while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
					if( msg.message == WM_QUIT ){
				std::cout <<"�o�b�t�@��������6" << std::endl;
						isDone=true;
					}
				}
				break;
			}
		}
	}
}