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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_3D_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_3D_AUDIO_BUFFER_H_
#include "IAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class Vector3f;

	///DirectSound3DAuioBuffer�̃��b�p
	//class DirectSound3DAudioBuffer {
	//public:
	//	/**
	//	* �R���X�g���N�^
	//	*/
	//	DirectSound3DAudioBuffer();
	//	
	//	/**
	//	* 
	//	DirectSound3DAudioBuffer();
	//	/**
	//	* ���X�i�[�̈ʒu���擾���܂�
	//	* @return Vecto3f ���X�i�[�̈ʒu�x�N�g��
	//	*/
	//	Vector3f GetPosition() const ;


	//	/**
	//	*�@���X�i�[�̈ʒu��ݒ肵�܂�
	//	* @param const Vector3f&�@���X�i�[�̈ʒu�x�N�g��
	//	*/
	//	void SetPosition(const Vector3f& pos) ;


	//	/**
	//	* ���x�x�N�g�����擾���܂�
	//	* @return Vector3f�@���X�i�[�̑��x�x�N�g��
	//	*/
	//	Vector3f GetVelocity() const ;


	//	/**
	//	*�@���x�x�N�g����ݒ肵�܂�
	//	* @param const Vector3f& ���X�i�[�̑��x�x�N�g��
	//	*/
	//	void SetVelocity(const Vector3f& velocity) ;


	//	/**
	//	* �h�b�v���[�W�����擾���܂�
	//	* @return float �h�b�v���[�W��
	//	*/
	//	float GetDopplerFactor() const ;


	//	/**
	//	* �h�b�v���[�W����ݒ肵�܂�
	//	* @param float �h�b�v���[�W��
	//	*/
	//	void SetDopplerFactor(float dopplerFactor) ;


	//	/**
	//	* ���[���I�t�W�����擾���܂�
	//	* @return ���[���I�t�W��
	//	*/
	//	float GetRolloffFactor() const ;


	//	/**
	//	* ���[���I�t�W����ݒ肵�܂�
	//	* @param float ���[���I�t�W��
	//	*/
	//	void SetRolloffFactor(float rolloffFactor) ;

	//private:
	//	DirectSoundBufferPtr soundBuffer; ///< 3D�T�E���h�o�b�t�@
	//};
}
#endif
