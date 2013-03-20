
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

namespace Nyx {
	using std::unique_ptr;
	using std::shared_ptr;

	///RIFF�`�����N�\����
	struct RIFFChunk
	{
		ulong fileSize;///< �t�@�C���T�C�Y
	};

	///Format�`�����N�\����
	struct FmtChunk
	{
		long chunkSize; ///<�`�����N�T�C�Y
		short formatTag; ///<�t�H�[�}�b�gID
		ushort channelNum;///<�`�����l����
		ulong  samplingRate; ///<�T���v�����O���[�g
		ulong  bytesPerSec;//<�f�[�^���x
		ushort blockSize; ///<�u���b�N�T�C�Y
		ushort bitsRate;///< �T���v��������̃r�b�g��
	};

	///�f�[�^�`�����N�\����
	struct DataChunk
	{
		long           chunkSize;///< �`�����N�T�C�Y 
		uchar* waveData;///< �g�`�f�[�^
	};

	///wav�t�@�C�����[�_
	class WaveReader {
	public:
		/**
		* �R���X�g���N�^
		*/
		WaveReader();

		/**
		* �f�X�g���N�^
		*/
		~WaveReader();

		/**
		* �t�@�C������Wave�t�@�C����ǂݍ��݂܂�
		* @param std::wstring wav�t�@�C����
		*/
		void ReadFromFile(std::wstring fileName);

		/**
		* ��������̃f�[�^����Wave�t�@�C����ǂݍ��݂܂�
		* @param shared_ptr<char> Wave�t�@�C���f�[�^
		*/
		void ReadFromMem(shared_ptr<char> waveData);

		/**
		* Wave�t�@�C���̃w�b�_�����o��
		* @note 
		* ������ŕԂ������������Ȃ��[
		*/
		void PrintHeaderInfo();

		/**
		* RIFF�`�����N���擾���܂��B
		* @param RIFFChunk* Riff�`�����N�\���̂ւ̃|�C���^
		*/
		void GetRiffChunk(RIFFChunk* riff);

		/**
		* �t�H�[�}�b�g�`�����N���擾
		* @param FmtChunk* Fmt�`�����N�\���̂ւ̃|�C���^
		*/
		void GetFmtChunk(FmtChunk* fmt);

		/**
		*�@�f�[�^�`�����N���擾
		* @param DataChunk* �f�[�^�`�����N�\���̂ւ̃|�C���^
		*/
		void GetDataChunk(DataChunk* data);

	private:
		RIFFChunk riffChunk_; ///< RIFF�`�����N
		FmtChunk fmtChunk_;///< fmt�`�����N
		DataChunk dataChunk_; ///< data�`�����N
	};
}
#endif
