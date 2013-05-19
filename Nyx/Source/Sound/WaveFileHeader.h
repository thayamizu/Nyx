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
#ifndef NYX_CORE_INCLUDED_WAVE_FILE_HEADER_H_
#define NYX_CORE_INCLUDED_WAVE_FILE_HEADER_H_

namespace Nyx {

	///Format�`�����N�\����
	struct FormatChunk
	{
		char	formatChunkID[4]; ///FMT�`�����NID
		uint	chunkSize;        ///<�`�����N�T�C�Y
		ushort	formatTag;        ///<�t�H�[�}�b�gID
		ushort	channelNum;       ///<�`�����l����
		uint	samplingRate;     ///<�T���v�����O���[�g
		uint	bytesPerSec;      ///<�f�[�^���x
		ushort	blockSize;        ///<�u���b�N�T�C�Y
		ushort	bitsRate;         ///< �T���v��������̃r�b�g��
	};

	///�f�[�^�`�����N�\����
	struct DataChunk
	{
		char dataChunkID[4]; ///< �f�[�^�`�����NID
		uint  chunkSize;      ///< �`�����N�T�C�Y 
	};

	///Wave�t�@�C���w�b�_�\����
	struct WaveFileHeader
	{
		char        riffID[4];  ///< RIFF�t�H�[�}�b�gID
		uint         fileSize;   ///< �t�@�C���T�C�Y
		char        waveID[4];  ///< Wave�t�@�C��ID
		FormatChunk  formatChunk;///<�t�H�[�}�b�g�`�����N
		DataChunk    dataChunk;  ///<�f�[�^�`�����N
	};
}

#endif