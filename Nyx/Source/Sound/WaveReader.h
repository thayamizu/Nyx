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
#ifndef NYX_CORE_INCLUDED_WAVE_READER_H_
#define NYX_CORE_INCLUDED_WAVE_READER_H_
#include "SoundReader.h"

namespace nyx {
	class file;

	///wav�t�@�C�����[�_
	class wave_reader : public sound_reader {
	public:
		/**
		* �R���X�g���N�^
		*/
		wave_reader();


		/**
		* �R���X�g���N�^
		* @param const std::wstring& �t�@�C����
		*/
		wave_reader(const std::wstring& fileName);


		/**
		* WAV�t�@�C�����J��
		* @param const std::wstring& �t�@�C����
		*/
		void open(const std::wstring& fileName);
		

		/**
		* �ǂݍ��݃J�[�\�����w�肵���ʒu�ɃZ�b�g����
		* @param ulong �ǂݍ��݃J�[�\���ʒu
		*/
		void set_cursor(uint64_t cursor);


		/**
		* �ǂݍ��݃J�[�\�����擾����
		* @return ulong �ǂݍ��݃J�[�\���ʒu
		*/
		uint64_t get_cursor() const;
		
		
		/**
		* Wave�t�@�C���w�b�_�̎擾���܂�
		* @return const WaveFileHeader& WAVE�t�@�C���w�b�_
		*/
		const wav_file_header& read_header();


		/**
		* Wave�f�[�^���擾���܂�
		* @param size_t  �ǂݍ��݃o�C�g��
		* @param size_t�@���ۂɓǂݎ�����T�C�Y
		* @return std::shared_ptr<char> WAVE�f�[�^
		*/
		std::shared_ptr<char> read(size_t bufferSize, uint64_t* readSize=nullptr);
	private:
		bool isReadHeader_;             ///< �w�b�_��ǂݍ���ł��邩
		char align_[3];                 ///< �A���C�����g����
		uint64_t cursor_;                  ///< �J�[�\��
		std::wstring   fileName_;       ///< �t�@�C����
		std::shared_ptr<file> waveFile_;///< Wave�t�@�C��
		wav_file_header waveHeader_;     ///< Wave�t�@�C���w�b�_
	};
}
#endif
