/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F*�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/

#ifndef NYX_CORE_INCLUDED_MEMORY_CHECKER_H_
#define NYX_CORE_INCLUDED_MEMORY_CHECKER_H_

#ifdef _DEBUG
// crtdbg.h ���C���N���[�h�������Ƃ� _CRTDBG_MAP_ALLOC ���`���Ă��
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new  ::new(_CLIENT_BLOCK, __FILE__, __LINE__)

namespace nyx {
	///�������̏��
	typedef ::_CrtMemState memory_state;

	///�������`�F�b�J�[
	class memory_checker {
	public:
		/**
		* �������`�F�b�J�[�̏�����
		* @return �����Ȃ�true
		*/
		static bool initialize();

		/**
		* ��������Ԃ��擾����
		* @return MemoryState
		*/
		static memory_state get_memory_state();

		/**
		*�@�������̏ڍ׃_���v�����s����
		*/
		static void dump_detail();

		/*
		*�@�������̍����ڍ׃_���v�����s����
		* @param MemoryState& ���������
		*/
		static void dump_detail(const memory_state& old);


		/*
		*�@�������̓��v�_���v�����s����
		*/
		static void dump_statics();

		/*
		*�@�������̍������v�_���v�����s����
		* @param const MemoryState ���������
		*/
		static void dump_statics(const memory_state& old);


		/*
		*�@���������[�N���`�F�b�N����
		* @param const MemoryState& ���������
		*/
		static bool leak_check(const memory_state& state );

	private:
		memory_checker(){}//�����֎~
		static bool initialized;///< �����ς݂��ǂ���
	};
}
#else 
//�����[�X���́A�������`�F�b�J�[��؂�
namespace nyx {
	typedef ::_CrtMemState memory_state;

	class memory_checker {
	public:

		static bool initialize();

		static memory_state get_memory_state();

		static void dump_detail();
		static void dump_detail(const memory_state& old);

		static void dump_statics();
		static void dump_statics(const memory_state& old);

		static bool leak_check(const memory_state& state );

	private:
		memory_checker(){}//�����֎~
		static bool initialized;
	};

}
#endif

#endif
