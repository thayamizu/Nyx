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
#ifndef NYX_CORE_INCLUDED_IRESOURCE_H_
#define NYX_CORE_INCLUDED_IRESOURCE_H_
#include "Utility/Common.h"

namespace Nyx {
	///���\�[�X�C���^�t�F�[�X
	class IResource {
	public:
		/**
		*�@�R���X�g���N�^
		*/
		IResource():bufferSize(0), bufferData(NULL), resourceName() {}

		/**
		* �f�X�g���N�^
		*/virtual IResource::~IResource() 
		{
			if (bufferData != NULL) {
				SafeDelete(bufferData);
			}
		}

		/**
		* ���\�[�X�f�[�^���o�b�N�A�b�v����
		* @param std::wstring�@���\�[�X��
		* @param uint ���\�[�X�T�C�Y
		* @param uchar* ���\�[�X�f�[�^
		*/
		virtual void SetResourceData(std::wstring name, uint size, uchar* data) 
		{
			resourceName = name;
			bufferSize   = size;
			bufferData   = new uchar[bufferSize];

			memcpy(bufferData, data, size);
		}

		/**
		* ���\�[�X�̑傫�����擾
		* @param int ���\�[�X�T�C�Y
		*/
		virtual int GetResourceSize() {
			return bufferSize;
		}

		/**
		* ���\�[�X�f�[�^���擾
		* @param uchar** ���\�[�X�f�[�^
		*/
		virtual void GetResourceData(uchar** data) 
		{
			*data = bufferData;
		}

		/**
		* ���\�[�X�����擾
		* @return std::wstring ���\�[�X��
		*/
		virtual std::wstring GerResourceName() {
			return resourceName;
		}

		/**
		* ���X�g�A
		*/
		virtual void Restore() = 0;
	private:
		uint bufferSize;
		uchar* bufferData;
		std::wstring resourceName;
	};
}
#endif