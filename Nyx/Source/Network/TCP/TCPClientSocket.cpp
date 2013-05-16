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
#include "Network/ISocket.h"
#include "Network/TCP/TCPClientSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	TCPClientSocket::TCPClientSocket(char *addr, int port) {
		//WinSock ������
		WSAStartup(MAKEWORD(2,0), &wsaData);

		// �\�P�b�g�̍쐬
		dstSock = socket(AF_INET, SOCK_STREAM, 0);
		if(dstSock < 0){
			exit(-1);
		}

		// �ڑ���w��p�\���̂̏���
		dstAddr.sin_family = AF_INET;
		dstAddr.sin_port = htons(port);
		dstAddr.sin_addr.S_un.S_addr = inet_addr(addr);

		// �T�[�o�ɐڑ�
		if(connect(dstSock, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) != 0){
			exit(-1);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	TCPClientSocket::~TCPClientSocket() {
		// tcP�Z�b�V�����̏I��
		closesocket(dstSock);

		// winsock2�̏I������
		WSACleanup();
	}


	//-----------------------------------------------------------------------------------------
	//
	int TCPClientSocket::Send(char *buf, int buf_len) {
		return send(dstSock, buf, buf_len, 0);
	}


	//-----------------------------------------------------------------------------------------
	//��M
	int TCPClientSocket::Recieve(char *buf, int buf_len) {
		return recv(dstSock, buf, buf_len, 0);
	}
}
