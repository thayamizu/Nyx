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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_

namespace Nyx {
	using std::shared_ptr;
	class AudioBuffer;
	///�X�g���[�~���u�I�[�f�B�I�o�b�t�@��DirectSound�ɂ�����
	class DirectSoundStreamingAudioBuffer : public AudioBuffer
	{
	public:
		//---------------------------------------------------------------------------
		//�\�z�E�j��
		//---------------------------------------------------------------------------
		/**
		* �R���X�g���N�^
		* @param DirectSound DirectSound�I�u�W�F�N�g
		* @param tstring �t�@�C����
		*/
		DirectSoundStreamingAudioBuffer(DirectSound, tstring fileName);

		/**
		* �R���X�g���N�^
		* @param DirectSound DirectSound�I�u�W�F�N�g
		* @param shared_ptr<char> wave�f�[�^
		*/
		DirectSoundStreamingAudioBuffer(DirectSound, shared_ptr<char> waveData);

		/**
		* �f�X�g���N�^
		*/
		~DirectSoundStreamingAudioBuffer();

		//---------------------------------------------------------------------------
		//�Đ��E��~
		//---------------------------------------------------------------------------
		/**
		* �Đ� 
		*/
		void Play();

		/**
		* ��~
		*/
		void Stop();

		/**
		* ���W���[��
		*/
		void Resume();

		/**
		* ���Z�b�g
		*/
		void Reset();

		//---------------------------------------------------------------------------
		//���̎擾
		//---------------------------------------------------------------------------
		/**
		* �p���̎擾
		* @return long �p��
		*/
		long GetPan() const ;

		/**
		* �p���̐ݒ�
		* @param int �p��
		*/
		void SetPan(int pan_);

		/**
		* �{�����[���̎擾
		* @return long �{�����[��
		*/
		long GetVolume() const ;

		/**
		* �{�����[���̐ݒ�
		* @param �{�����[��
		*/
		void SetVolume(int v);

		/*
		* �ʒm�X���b�h�̋N���֐�
		* @param void* �p�����[�^
		* @return ulong
		*/
		friend ulong __stdcall NotifyThreadProc(void*);

	private:
		/**
		* �ʒm�X���b�h
		*/
		void NotifyThread();

		/**
		* �o�b�t�@��������
		* @param �I�t�Z�b�g�ʒu
		* @return HRESULT �������݌���
		*/
		HRESULT WriteToBuffer(ulong offset);

		static const int NotifyEventNums = 4; ///< �ʒm�C�x���g�̐�

	private:
		long pan;	///< �p��
		long volume;///< �{�����[��
		bool isEOF; ///< Wave�f�[�^�̏I�[
		ulong cursorPlay;///< �Đ��J�[�\��
		ulong cursorRead;///< �ǂݍ��݃J�[�\��
		ulong waveSize;  ///< WAVE�f�[�^�̃T�C�Y
		ulong bufferSize;///< �o�b�t�@�T�C�Y
		ulong notifySize;///< �ʒm�C�x���g����������T�C�Y
		ulong nextOffset;///< ���ɏ������ރI�t�Z�b�g�ʒu
		shared_ptr<uchar> waveData;///<WAVE�f�[�^
		HANDLE notifyEvent[NotifyEventNums]; ///< �ʒm�C�x���g�̃n���h��
		HANDLE notifyThreadHandle;///< �ʒm�X���b�h�̃n���h��
		DirectSoundBuffer soundBuffer;///<DirectSound�Z�J���_���o�b�t�@
	};
}
#endif