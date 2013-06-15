#ifndef NYX_CORE_INCLUDED_SOUND_READER_H_
#define NYX_CORE_INCLUDED_SOUND_READER_H_
#include "Object/NonCopyable.h"

namespace Nyx {

	struct WaveFileHeader;
	///�T�E���h���[�_
	class SoundReader : NonCopyable {
	public:
		/**
		* �f�X�g���N�^
		*/
		virtual ~SoundReader() {}
		/**
		* WAV�t�@�C�����J��
		* @param const std::wstring& �t�@�C����
		*/
		virtual void Open(const std::wstring& fileName) =0 ;
		

		/**
		* �ǂݍ��݃J�[�\�����w�肵���ʒu�ɃZ�b�g����
		* @param ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual void SetCursor(ulong cursor) =0 ;


		/**
		* �ǂݍ��݃J�[�\�����擾����
		* @return ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual ulong GetCursor() const = 0;
		
		
		/**
		* Wave�t�@�C���w�b�_�̎擾���܂�
		* @return const WaveFileHeader& WAVE�t�@�C���w�b�_
		*/
		virtual const WaveFileHeader& ReadHeader() =0 ;


		/**
		* Wave�f�[�^���擾���܂�
		* @param size_t  �ǂݍ��݃o�C�g��
		* @param size_t�@���ۂɓǂݎ�����T�C�Y
		* @return std::shared_ptr<char> WAVE�f�[�^
		*/
		virtual std::shared_ptr<char> Read(size_t bufferSize, ulong* readSize=nullptr) =0 ;
	};
}
#endif