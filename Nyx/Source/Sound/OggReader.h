#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_
#include "SoundReader.h"

namespace Nyx {
	struct WaveFileHeader;
	///ogg�t�@�C�����[�_
	class OggReader : public SoundReader {
	public:
		/**
		* �R���X�g���N�^
		*/
		OggReader();


		/**
		* �R���X�g���N�^
		* @param const std::wstring& �t�@�C����
		*/
		OggReader(const std::wstring& fileName);


		/**
		* WAV�t�@�C�����J��
		* @param const std::wstring& �t�@�C����
		*/
		void Open(const std::wstring& fileName);
		

		/**
		* �ǂݍ��݃J�[�\�����w�肵���ʒu�ɃZ�b�g����
		* @param ulong �ǂݍ��݃J�[�\���ʒu
		*/
		void SetCursor(ulong cursor);


		/**
		* �ǂݍ��݃J�[�\�����擾����
		* @return ulong �ǂݍ��݃J�[�\���ʒu
		*/
		ulong GetCursor() const;
		
		
		/**
		* Wave�t�@�C���w�b�_�̎擾���܂�
		* @return const WaveFileHeader& WAVE�t�@�C���w�b�_
		*/
		const WaveFileHeader& ReadHeader();


		/**
		* Wave�f�[�^���擾���܂�
		* @param size_t  �ǂݍ��݃o�C�g��
		* @param size_t�@���ۂɓǂݎ�����T�C�Y
		* @return std::shared_ptr<char> WAVE�f�[�^
		*/
		std::shared_ptr<char> Read(size_t bufferSize, ulong* readSize=nullptr);
	private:
		WaveFileHeader header;
	};
}

#endif