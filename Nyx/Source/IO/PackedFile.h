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
#ifndef NYX_CORE_PACKED_FILE_H_
#define NYX_CORE_PACKED_FILE_H_
#include "Utility/NonCopyable.h"

namespace nyx
{
	using std::unique_ptr;
	using std::shared_ptr;
	///�p�b�N���ꂽ�t�@�C��
	NYX_DEPRECATED class packed_file :  private noncopyable
	{
	public:
		//-------------------------------------------------------
		//�\�z�E�j��
		//-------------------------------------------------------
		packed_file(const wchar_t*  name, FILE_ACCESS_ATTRIBUTE attr=FILE_ACCESS_ATTRIBUTE_READ);
		~packed_file();

		//-----------------------------------------------------
		//�l�̎擾
		//-----------------------------------------------------
		/**
		* �w�b�_�T�C�Y�̎擾
		* @return ulong
		*/
		uint64_t get_header_size();
		/**
		* �w�b�_�T�C�Y�̎擾
		* @return �w�b�_�T�C�Y
		*/
		uint32_t get_file_num();

		/**
		* �w�b�_�T�C�Y�̎擾
		* @return �w�b�_�T�C�Y
		*/
		uint64_t get_file_size(uint32_t index);
		/**
		* index�ԖڂɃp�b�N���ꂽ�f�[�^�̎擾
		*@param index
		*@return shared_ptr<char> 
		*/
		shared_ptr<char> get_file_data(uint32_t index);

		//-----------------------------------------------------
		//�t�@�C������
		//-----------------------------------------------------
		/**
		*
		*/
		bool open(const std::wstring&  name, FILE_ACCESS_ATTRIBUTE attr=FILE_ACCESS_ATTRIBUTE_READ);
		bool close();
		bool flush();

		/**
		*
		*/
		uint64_t get_current_position() const;

		/**
		*
		*/uint64_t get_size() const;

		/**
		*
		*/
		std::wstring get_file_name() const;


		/**
		*
		*/
		uint64_t read(void* buffer, uint64_t size);
		
		/**
		*
		*/
		uint64_t write(void* buffer, uint64_t size);
		/**
		*
		*/
		uint64_t seek(long offSet);

		/**
		*
		*/
		uint64_t seek_begin(long offSet);

		/**
		*
		*/
		uint64_t seek_end(long offSet);

		/**
		*
		*/
		bool is_opened();

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}

#endif