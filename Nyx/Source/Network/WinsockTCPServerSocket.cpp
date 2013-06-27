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
	WinsockTCPServerSocket::WinsockTCPServerSocket() 
		: port_(0), maxConnect_(1) {
			// �\�P�b�g�̍쐬
			source_ = socket(AF_INET, SOCK_STREAM, 0);
			if(source_ != 0){
				int status = ::WSAGetLastError();
				throw Win32Exception("�\�P�b�g�̍쐬�Ɏ��s���܂���", status);
			}
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::WinsockTCPServerSocket(ushort port) 
		: port_(port), maxConnect_(1) {
			// �\�P�b�g�̍쐬
			source_ = socket(AF_INET, SOCK_STREAM, 0);
			if(source_ != 0){
				int status = ::WSAGetLastError();
				throw Win32Exception("�\�P�b�g�̍쐬�Ɏ��s���܂���", status);
			}

			//�\�P�b�g�ƃA�h���X���Ƀo�C���h
			Bind();

			//�ڑ��v�����󂯕t����
			Listen();
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::~WinsockTCPServerSocket() {
		Disconnect();
	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPServerSocket::Accept() {
		int destinationAddressSize = sizeof(sockaddr_in);
		sockaddr_in destinationAddress;
		destination_ = accept(source_, (struct sockaddr *)&destinationAddress, &destinationAddressSize);

		return destination_ != INVALID_SOCKET;
	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPServerSocket::Listen() {
		int result = listen(source_, maxConnect_);
		return result == INVALID_SOCKET;
	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPServerSocket::Bind() {
		address_.sin_family           = AF_INET;
		address_.sin_port             = htons(port_);
		address_.sin_addr.S_un.S_addr = INADDR_ANY;
		int result = bind(source_, (sockaddr *)&address_, sizeof(address_));

		return result != INVALID_SOCKET;
	}


	//-----------------------------------------------------------------------------------------
	//
	void WinsockTCPServerSocket::Disconnect() {
		if (destination_ != NULL) {
			closesocket(destination_);
		}

		if (source_ != NULL) {
			closesocket(source_);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	void WinsockTCPServerSocket::SetPort(ushort port) {
		port_ = port;
	}


	//-----------------------------------------------------------------------------------------
	//
	ushort WinsockTCPServerSocket::GetPort() const {
		return port_;
	}


	//-----------------------------------------------------------------------------------------
	//
	void WinsockTCPServerSocket::SetMaxConnect(size_t maxConnect) {
		maxConnect_ = maxConnect;
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t WinsockTCPServerSocket::GetMaxConnect() const {
		return maxConnect_;
	}


	//-----------------------------------------------------------------------------------------
	//
	int WinsockTCPServerSocket::Send(char *buffer, const size_t bufferSize) const {
		return send(destination_, buffer, bufferSize, 0);
	}


	//-----------------------------------------------------------------------------------------
	//
	int WinsockTCPServerSocket::Recieve(char *buffer, const size_t bufferSize) const  {
		return recv(destination_, buffer, bufferSize, 0);
	}
}