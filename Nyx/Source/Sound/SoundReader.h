#ifndef NYX_CORE_INCLUDED_SOUND_READER_H_
#define NYX_CORE_INCLUDED_SOUND_READER_H_
#include "Utility/NonCopyable.h"
#include "WaveFileHeader.h"

namespace nyx {

	struct wav_file_header;
	///�T�E���h���[�_
	class sound_reader : noncopyable {
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~sound_reader() {}
		/**
		* WAV�t�@�C�����J��
		* @param const std::wstring& �t�@�C����
		*/
		virtual void open(const std::wstring& fileName) =0 ;
		

		/**
		* �ǂݍ��݃J�[�\�����w�肵���ʒu�ɃZ�b�g����
		* @param ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual void set_cursor(uint64_t cursor) =0 ;


		/**
		* �ǂݍ��݃J�[�\�����擾����
		* @return ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual uint64_t get_cursor() const = 0;
		
		
		/**
		* Wave�t�@�C���w�b�_�̎擾���܂�
		* @return const WaveFileHeader& WAVE�t�@�C���w�b�_
		*/
		virtual const wav_file_header& read_header() =0 ;


		/**
		* Wave�f�[�^���擾���܂�
		* @param size_t  �ǂݍ��݃o�C�g��
		* @param size_t�@���ۂɓǂݎ�����T�C�Y
		* @return std::shared_ptr<char> WAVE�f�[�^
		*/
		virtual std::shared_ptr<char> read(size_t bufferSize, uint64_t* readSize=nullptr) =0 ;
	};
}
#endif