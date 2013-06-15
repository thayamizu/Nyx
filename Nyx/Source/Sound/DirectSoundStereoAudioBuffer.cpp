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
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "DirectSoundStereoAudioBuffer.h"

namespace Nyx {
	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStereoAudioBuffer::DirectSoundStereoAudioBuffer() 
		: DirectSoundAudioBuffer(), IStereoAudioBuffer() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	DirectSoundStereoAudioBuffer::~DirectSoundStereoAudioBuffer() {

	}


	//-------------------------------------------------------------------------------------------------------
	//
	long DirectSoundStereoAudioBuffer::GetPan() const {
		auto soundBuffer = GetHandle();
		long pan;
		HRESULT hr = soundBuffer->GetPan(&pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̎擾�Ɏ��s���܂����B", hr);
		}
		auto volume = AudioUtility::DecibelToVolume((pan > 0) ? - pan : pan);
		return (pan > 0)? 100L - volume : volume - 100L;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void DirectSoundStereoAudioBuffer::SetPan(long volume) {
		auto soundBuffer = GetHandle();
		Assert(soundBuffer != nullptr);
		const auto ref = 100L;
		volume = Math::Clamp(volume, -100L, 100L);
		auto pan = AudioUtility::VolumeToDecibel(ref - Math::Abs(volume));
		pan = (volume > 0)? pan : -pan;
		HRESULT hr = soundBuffer->SetPan(pan);
		if (FAILED(hr)) {
			DebugOutput::Trace("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B[%s:%d]", __FILE__, __LINE__);
			throw COMException("DirectSound�I�[�f�B�I�o�b�t�@�̃p���l�̐ݒ�Ɏ��s���܂����B", hr);
		}
	}
}