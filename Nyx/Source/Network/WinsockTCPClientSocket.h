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
#ifndef NYX_CORE_WINSOCK_TCP_CLIENT_SOCKET_H_
#define NYX_CORE_WINSOCK_TCP_CLIENT_SOCKET_H_
#include "WinsockInitializer.h"

namespace Nyx {
	///TCP�N���C�A���g�\�P�b�g
	class WinsockTCPClientSocket {
	public:
		/*
		* �R���X�g���N�^
		*/
		WinsockTCPClientSocket();


		/**
		* �f�X�g���N�^
		*/
		~WinsockTCPClientSocket();


		/**
		* �T�[�o�[�֐ڑ�����
		* @param const char* �A�h���X
		* @param const int �|�[�g�ԍ�
		*/
		bool Connect(const char* address, size_t port);
		
		
		/**
		* �T�[�o�[�֐ڑ�����
		* @param const std::string& �A�h���X
		* @param int �|�[�g�ԍ�
		*/
		bool Connect(const std::string&  address, size_t port);
		
		
		/**
		* �T�[�o�[�ւ̐ڑ���ؒf����
		*/
		void Disconnect();


		/**
		* �T�[�o�[�Ƀf�[�^�𑗐M����
		* @param ���M�o�b�t�@
		* @param ���M�o�b�t�@�̒���
		* @return ���M�o�C�g��
		*/
		size_t Send(char* buffer, size_t bufferSize) const;


		/**
		* �T�[�o�[����f�[�^����M����
		* @param ��M�o�b�t�@
		* @param ��M�o�b�t�@�̒���
		* @return ��M�o�C�g��
		*/
		size_t Recieve(char* buffer, size_t bufferSize) const;
	private:
		SOCKET  destination_;///< �ڑ���̃\�P�b�g
		sockaddr_in address_;///< �T�[�o�̃A�h���X���
	};

}
#endif