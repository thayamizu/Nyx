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
		* ���y�t�@�C�����I�[�v�����܂�
		* @param const std::wstring& �t�@�C����
		*/
		virtual void Open(const std::wstring& fileName) = 0;
		
		
		/**
		* �ǂݍ��݃J�[�\�����w�肵���ʒu�ɃZ�b�g����
		* @param ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual void SetCursor(ulong cursor) = 0;


		/**
		* �ǂݍ��݃J�[�\�����擾����
		* @return ulong �ǂݍ��݃J�[�\���ʒu
		*/
		virtual ulong GetCursor() const = 0;


		/**
		* ���y�t�@�C������w�肵���o�b�t�@�T�C�Y�������ǂݍ���
		* @param size_t �o�b�t�@�T�C�Y
		*/
		virtual std::shared_ptr<char> Read(size_t size) = 0;
		

		/**
		* �w�b�_�����擾����
		* @return WaveHeader Wave�t�@�C���̃w�b�_
		*/
		virtual const WaveFileHeader& ReadHeader() = 0;
	};
}
#endif