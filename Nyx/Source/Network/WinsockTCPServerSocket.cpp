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
#include "Network/WinsockTCPServerSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	const int WinsockTCPServerSocket::MaxConnectNum = 5;


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::WinsockTCPServerSocket(int port) {
		dstAddrSize = sizeof(dstAddr);

		// �\�P�b�g�̍쐬
		srcSock = socket(AF_INET, SOCK_STREAM, 0);
		if(srcSock < 0){
			exit(-1);
		}

		// �\�P�b�g�̐ݒ�
		srcAddr.sin_family = AF_INET;
		srcAddr.sin_port = htons(static_cast<ushort>(port));
		srcAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		if(bind(srcSock, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) != 0){
			exit(-1);
		}

		// TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
		if(listen(srcSock, MaxConnectNum)){
			exit(-1);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::~WinsockTCPServerSocket() {
		// TCP�Z�b�V�����̏I��
		closesocket(srcSock);
		closesocket(dstSock);

	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPServerSocket::Accept() {
		// TCP�N���C�A���g����̐ڑ��v�����󂯕t����
		dstSock = accept(srcSock, (struct sockaddr *)&dstAddr, &dstAddrSize);

		return dstSock != INVALID_SOCKET;
	}


	//-----------------------------------------------------------------------------------------
	//
	int WinsockTCPServerSocket::Send(char *buf, int buf_len) {
		return send(dstSock, buf, buf_len, 0);
	}


	//-----------------------------------------------------------------------------------------
	//
	int WinsockTCPServerSocket::Recieve(char *buf, int buf_len) {
		return recv(dstSock, buf, buf_len, 0);
	}
}