/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "WinsockUDPSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	WinsockUDPSocket::WinsockUDPSocket(const char* address, const unsigned short port, const ulong blockingMode)
		: socket_(NULL), address_() {
			socket_ = socket(AF_INET, SOCK_DGRAM, 0);
			if (socket_ == INVALID_SOCKET) {
				LRESULT status = ::WSAGetLastError();
				throw Win32Exception("UDPソケットの作成に失敗しました", status);
			}


			//アドレス情報とソケットをバインディング
			Bind(address, port);


			//ブロッキングモード
			ulong blocking = blockingMode;
			::ioctlsocket(socket_, FIONBIO, &blocking);
	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockUDPSocket::Bind(const char* address, unsigned short port) {
		// ローカルサーバのアドレスを指定
		address_.sin_family           = AF_INET;
		address_.sin_port			  = htons(port);

		address_.sin_addr.S_un.S_addr = inet_addr(address);

		// 無効だったので, DomainName から検索する
		if (address_.sin_addr.S_un.S_addr == 0xffffffff) {
			auto host = gethostbyname(address);
			if (host == NULL) {
				return false;
			}

			auto hostname = reinterpret_cast<unsigned int *>(host->h_addr_list[0]);
			address_.sin_addr.S_un.S_addr = *hostname;

		}
		int status = bind(socket_, (sockaddr*)&address_, sizeof(address_));
		if (status == INVALID_SOCKET) {
			return false;
		}

		return true;
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockUDPSocket::~WinsockUDPSocket() {
		if (socket_ != NULL) {
			closesocket(socket_);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t WinsockUDPSocket::Send(const char *buffer, const size_t bufferSize, const WinsockUDPSocket& destination) const {
		return sendto(socket_, buffer, bufferSize, 0, (sockaddr*)&destination.address_, sizeof(destination.address_));
	}


	//-----------------------------------------------------------------------------------------
	//
	size_t WinsockUDPSocket::Recieve( char *buffer, const size_t bufferSize, WinsockUDPSocket& source) const {
		int length = sizeof(source.address_);
		return recvfrom(socket_, buffer, bufferSize, 0,  (sockaddr*)&source.address_, &length);
	}
}
