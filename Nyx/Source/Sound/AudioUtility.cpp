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
#include "PCH/PCH.h"
#include "AudioUtility.h"
#include "WaveFileHeader.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	const double AudioUtility::DefaultBitRate      = 16;

	const double AudioUtility::DefaultSamplingRate = 44100;

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::VolumeToDecibel(long volume) {
		volume  = Math::Clamp(volume, 1L, 100L);
		return static_cast<long>(33.2f * Math::Log10((float)volume/100) * 100);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	long AudioUtility::DecibelToVolume(long decibel) {
		decibel = Math::Clamp(decibel, -10000L, 0L);
		if (decibel <= -10000L) {
			return 0;
		}
		if (decibel >= 0 ) {
			return 100;
		}

		return static_cast<long>(Math::Pow(10, (decibel / 33.2/100)) * 100);
	}

	
	//-------------------------------------------------------------------------------------------------------
	//
	void AudioUtility::BuildWaveFormatEx(WAVEFORMATEX* wfx, const WaveFileHeader& waveHeader){
		//Wave�t�H�[�}�b�g�̃Z�b�g�A�b�v
		ZeroMemory(wfx, sizeof(WAVEFORMATEX));
		wfx->wFormatTag      = waveHeader.formatChunk.formatTag;
		wfx->nChannels       = waveHeader.formatChunk.channelNum;
		wfx->wBitsPerSample  = waveHeader.formatChunk.bitsRate;
		wfx->nSamplesPerSec  = waveHeader.formatChunk.samplingRate;
		wfx->nBlockAlign     = waveHeader.formatChunk.blockSize;
		wfx->nAvgBytesPerSec = waveHeader.formatChunk.bytesPerSec;
		wfx->cbSize          = sizeof(WAVEFORMATEX);
	}
}