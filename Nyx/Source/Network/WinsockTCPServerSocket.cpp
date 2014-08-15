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
#include "Debug/DebugOutput.h"
#include "Network/WinsockTCPServerSocket.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	//
	winsock_tcp_server_socket::winsock_tcp_server_socket(size_t port) 
		: port_(port), maxConnect_(1) {
			// �\�P�b�g�̍쐬
			source_ = socket(AF_INET, SOCK_STREAM, 0);
			if(source_ == INVALID_SOCKET){
				int status = ::WSAGetLastError();
				debug_out::trace("�\�P�b�g�̍쐬�Ɏ��s���܂����B");
				throw win32_exception("�\�P�b�g�̍쐬�Ɏ��s���܂����B", status);
			}

			//�\�P�b�g�ƃA�h���X���Ƀo�C���h
			if (!this->bind()) {
				LRESULT status = ::WSAGetLastError();
				debug_out::trace("Bind�Ɏ��s���܂����B");
				throw win32_exception("Bind�Ɏ��s���܂����B", status);
			}

			//�ڑ��v�����󂯕t����
			if(!this->listen()) {
				LRESULT status = ::WSAGetLastError();
				debug_out::trace("Listen�Ɏ��s���܂����B");
				throw win32_exception("Listen�Ɏ��s���܂����B", status);
			}

	}


	//-----------------------------------------------------------------------------------------
	//
	winsock_tcp_server_socket::~winsock_tcp_server_socket() {
		disconnect();
	}


	//-----------------------------------------------------------------------------------------
	//
	bool winsock_tcp_server_socket::accept() {
		int destinationAddressSize = sizeof(sockaddr_in);
		sockaddr_in destinationAddress;
		destination_ = ::accept(source_, (struct sockaddr *)&destinationAddress, &destinationAddressSize);

		return destination_ != INVALID_SOCKET;
	}


	//-----------------------------------------------------------------------------------------
	//
	bool winsock_tcp_server_socket::listen() {
		int result = ::listen(source_, maxConnect_);
		return result == 0;
	}


	//-----------------------------------------------------------------------------------------
	//
	bool winsock_tcp_server_socket::bind() {
		// �\�P�b�g�̐ݒ�
		address_.sin_family           = AF_INET;
		address_.sin_port             = htons(port_);
		address_.sin_addr.S_un.S_addr = INADDR_ANY;
		int result = ::bind(source_, (sockaddr *)&address_, sizeof(address_));

		return result != SOCKET_ERROR;
	}


	//-----------------------------------------------------------------------------------------
	//
	void winsock_tcp_server_socket::disconnect() {
		if (destination_ != NULL) {
			closesocket(destination_);
		}

		if (source_ != NULL) {
			closesocket(source_);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	void winsock_tcp_server_socket::set_connection_size(size_t maxConnect) {
		maxConnect_ = maxConnect;
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t winsock_tcp_server_socket::get_connection_size() const {
		return maxConnect_;
	}


	//-----------------------------------------------------------------------------------------
	//
	int winsock_tcp_server_socket::send(char *buffer, const size_t bufferSize) const {
		return ::send(destination_, buffer, bufferSize, 0);
	}


	//-----------------------------------------------------------------------------------------
	//
	int winsock_tcp_server_socket::recieve(char *buffer, const size_t bufferSize) const  {
		return recv(destination_, buffer, bufferSize, 0);
	}
}