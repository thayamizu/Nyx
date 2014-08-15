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
#include "WinsockUDPSocket.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	//
	winsock_udp_socket::winsock_udp_socket(const char* address, const size_t port, const size_t blockingMode)
		: socket_(NULL), address_() {
			socket_ = socket(AF_INET, SOCK_DGRAM, 0);
			if (socket_ == INVALID_SOCKET) {
				LRESULT status = ::WSAGetLastError();
				throw win32_exception("UDP�\�P�b�g�̍쐬�Ɏ��s���܂���", status);
			}


			//�A�h���X���ƃ\�P�b�g���o�C���f�B���O
			bind(address, port);


			//�u���b�L���O���[�h
			uint64_t blocking = blockingMode;
			::ioctlsocket(socket_, FIONBIO, &blocking);
	}


	//-----------------------------------------------------------------------------------------
	//
	bool winsock_udp_socket::bind(const char* address, size_t port) {
		// ���[�J���T�[�o�̃A�h���X���w��
		address_.sin_family           = AF_INET;
		address_.sin_port			  = htons(port);
		address_.sin_addr.S_un.S_addr = inet_addr(address);

		// �����������̂�, DomainName ���猟������
		if (address_.sin_addr.S_un.S_addr == 0xffffffff) {
			auto host = gethostbyname(address);
			if (host == NULL) {
				return false;
			}

			auto hostname = reinterpret_cast<unsigned int *>(host->h_addr_list[0]);
			address_.sin_addr.S_un.S_addr = *hostname;

		}

		int status = ::bind(socket_, (sockaddr*)&address_, sizeof(address_));
		if (status == INVALID_SOCKET) {
			return false;
		}

		return true;
	}


	//-----------------------------------------------------------------------------------------
	//
	winsock_udp_socket::~winsock_udp_socket() {
		if (socket_ != NULL) {
			closesocket(socket_);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t winsock_udp_socket::send(const char *buffer, const size_t bufferSize, const winsock_udp_socket& destination) const {
		return sendto(socket_, buffer, bufferSize, 0, (sockaddr*)&destination.address_, sizeof(destination.address_));
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t winsock_udp_socket::recieve( char *buffer, const size_t bufferSize, winsock_udp_socket& source) const {
		int length = sizeof(source.address_);
		return recvfrom(socket_, buffer, bufferSize, 0,  (sockaddr*)&source.address_, &length);
	}
}
