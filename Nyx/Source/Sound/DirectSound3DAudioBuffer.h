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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_3D_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_3D_AUDIO_BUFFER_H_
#include "I3DAudioBuffer.h"
#include "DirectSoundAudioBuffer.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class DirectSound3DAudioBuffer : public DirectSoundAudioBuffer, public I3DAudioBuffer {
	public:
		/**
		* �R���X�g���N�^
		*/
		DirectSound3DAudioBuffer();
		
		
		/**
		* �f�X�g���N�^
		*/
		~DirectSound3DAudioBuffer();


		/**
		* �����̈ʒu���擾���܂�
		* @return Vector3f
		*/
		Vector3f GetPosition() const;
		
		
		/**
		* �����̈ʒu��ݒ肵�܂�
		* @param const Vector3f&
		*/
		void SetPosition(const Vector3f& pos);

		
		/**
		* �����̑��x���擾���܂�
		* @return Vector3f 
		*/
		Vector3f GetVelocity() const ;
		
		/**
		* �����̑��x��ݒ肵�܂�
		* @param const Vector3f & veclocity
		*/
		void SetVelocity(const Vector3f& velocity);


		/**
		* ��������̍ő勗�����擾���܂�
		* @return float ��������̍ő勗��
		*/
		float GetMaxDistance() const;


		/**
		* ��������̍ő勗����ݒ肵�܂�
		* @param float  �ő勗��
		*/
		void SetMaxDistance(float maxDistance);


		/**
		* ��������̍ŏ�������ݒ肵�܂�
		* @param float  �ŏ�����
		*/
		float GetMinDistance() const;


		/**
		* ��������̍ŏ��������擾���܂�
		* @return float ��������̍ŏ�����
		*/
		void SetMinDistance(float minDistance);
	protected:
		/**
		* 3D�o�b�t�@���쐬���܂��D
		*/
		void Create3DBuffer();

	private:
		DirectSound3DBufferPtr buffer_;
	};
}
#endif
