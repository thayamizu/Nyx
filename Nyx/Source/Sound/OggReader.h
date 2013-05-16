#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_

namespace Nyx {
	///ogg�t�@�C�����[�_
	class OggReader {
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
		* ogg�t�@�C�����J��
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
		* �t�@�C������ogg�t�@�C����ǂݍ��݂܂�
		* @param std::wstring wav�t�@�C����
		*/
		//void ReadFromFile(const std::wstring& fileName);


		/**
		* ogg�t�@�C���w�b�_�̎擾���܂�
		* @return const WaveFileHeader& WAVE�t�@�C���w�b�_
		*/
		const WaveFileHeader& ReadHeader();


		/**
		* ogg�f�[�^���擾���܂�
		* @return std::shared_ptr<char> WAVE�f�[�^
		*/
		std::shared_ptr<char> Read(size_t bufferSize);
	private:
	};
}

#endif