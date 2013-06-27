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
#include "Network/WinsockTCPClientSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPClientSocket::WinsockTCPClientSocket()
	:destination_(NULL), address_() {
		// �\�P�b�g�̍쐬
		destination_ = socket(AF_INET, SOCK_STREAM, 0);
		if(destination_ < 0){
			int result = ::WSAGetLastError();
			throw Nyx::Win32Exception("Winsock�\�P�b�g�̍쐬�Ɏ��s���܂���", result);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPClientSocket::~WinsockTCPClientSocket() {
		Disconnect();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPClientSocket::Connect(const char* address, const ushort port) {
		// �ڑ���w��p�\���̂̏���
		address_.sin_family           = AF_INET;
		address_.sin_port             = htons(port);
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

		//�T�[�o�[�֐ڑ�
		int result = connect(destination_, (sockaddr *)&address_, sizeof(address_));

		return (result == 0) ? true : false;
	}
	
	
	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPClientSocket::Connect(const std::string& address, const ushort port) {
		return Connect(address.c_str(), port);
	}


	//-----------------------------------------------------------------------------------------
	//
	void WinsockTCPClientSocket::Disconnect() {
		if (destination_ != NULL) {
			closesocket(destination_);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	int WinsockTCPClientSocket::Send(char *buffer, const size_t bufferSize) const {
		return send(destination_, buffer, bufferSize, 0);
	}


	//-----------------------------------------------------------------------------------------
	//��M
	int WinsockTCPClientSocket::Recieve(char *buffer, const size_t bufferSize) const {
		return recv(destination_, buffer, bufferSize, 0);
	}
}
