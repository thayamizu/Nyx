#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_
#include "SoundReader.h"
#include "vorbis/vorbisfile.h"

namespace nyx {
	struct wav_file_header;
	///ogg�t�@�C�����[�_
	class ogg_reader : public sound_reader {
	public:
		/**
		* �R���X�g���N�^
		*/
		ogg_reader();


		/**
		* �R���X�g���N�^
		* @param const std::wstring& �t�@�C����
		*/
		ogg_reader(const std::wstring& fileName);

		/**
		* �f�X�g���N�^
		*/
		~ogg_reader();

		/**
		* WAV�t�@�C�����J��
		* @param const std::wstring& �t�@�C����
		*/
		void open(const std::wstring& fileName);
		
		/**
		* WAV�t�@�C������܂�
		*/
		void close();
		
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
		wav_file_header header_;
		OggVorbis_File* vorbisFile_;
		vorbis_info *  vorbisInfo_;

	};
}

#endif