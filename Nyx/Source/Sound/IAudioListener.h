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
#ifndef NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#define NYX_CORE_INCLUDED_IAUDIO_LISTENER_
#include "Primitive/Vector3.h"

namespace nyx {
	///�I�[�f�B�I���X�i�[
	class iaudio_listener {
	public:
		virtual ~iaudio_listener() {}
	
		/**
		* ���X�i�[�̈ʒu���擾���܂�
		* @return Vecto3f ���X�i�[�̈ʒu�x�N�g��
		*/
		virtual vector3f get_position() const = 0;
	

		/**
		*�@���X�i�[�̈ʒu��ݒ肵�܂�
		* @param const Vector3f&�@���X�i�[�̈ʒu�x�N�g��
		*/
		virtual void set_position(const vector3f& pos) = 0;
		
		
		/**
		* ���x�x�N�g�����擾���܂�
		* @return Vector3f�@���X�i�[�̑��x�x�N�g��
		*/
		virtual vector3f get_velocity() const = 0;
		
		
		/**
		*�@���x�x�N�g����ݒ肵�܂�
		* @param const Vector3f& ���X�i�[�̑��x�x�N�g��
		*/
		virtual void set_velocity(const vector3f& velocity) = 0;


		/**
		* �h�b�v���[�W�����擾���܂�
		* @return float �h�b�v���[�W��
		*/
		virtual float get_doppler_factor() const = 0;
		

		/**
		* �h�b�v���[�W����ݒ肵�܂�
		* @param float �h�b�v���[�W��
		*/
		virtual void set_doppler_factor(float dopplerFactor) = 0;
		

		/**
		* ���[���I�t�W�����擾���܂�
		* @return ���[���I�t�W��
		*/
		virtual float get_rolloff_factor() const = 0;
		
		
		/**
		* ���[���I�t�W����ݒ肵�܂�
		* @param float ���[���I�t�W��
		*/
		virtual void set_rolloff_factor(float rolloffFactor) = 0;
	};
}
#endif