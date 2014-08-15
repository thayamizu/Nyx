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
#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_3D_H
#include "Primitive/Vector3.h"

namespace nyx {
	///3D�T�E���h�̋@�\�����I�[�f�B�I�o�b�t�@�C���^�t�F�[�X
	class i3d_audio_buffer{
	public:
		virtual vector3f get_position() const = 0;
		virtual void set_position(const vector3f& velocity) = 0;
		virtual vector3f get_velocity() const = 0;
		virtual void set_velocity(const vector3f& velocity) = 0;

		/**
		* ��������̍ő勗�����擾���܂�
		* @return float ��������̍ő勗��
		*/
		virtual float get_max_distance() const = 0;


		/**
		* ��������̍ő勗����ݒ肵�܂�
		* @param float  �ő勗��
		*/
		virtual void set_max_distance(float maxDistance) = 0;
		

		/**
		* ��������̍ŏ�������ݒ肵�܂�
		* @param float  �ŏ�����
		*/
		virtual float get_min_distance() const = 0;


		/**
		* ��������̍ŏ��������擾���܂�
		* @return float ��������̍ŏ�����
		*/
		virtual void set_min_distance(float minDistance) = 0;
	};
}
#endif