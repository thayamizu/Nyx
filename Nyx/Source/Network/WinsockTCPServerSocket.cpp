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
#include "Debug/DebugOutput.h"
#include "Network/WinsockTCPServerSocket.h"

namespace nyx {
	//-----------------------------------------------------------------------------------------
	//
	winsock_tcp_server_socket::winsock_tcp_server_socket(size_t port) 
		: port_(port), maxConnect_(1) {
			// ソケットの作成
			source_ = socket(AF_INET, SOCK_STREAM, 0);
			if(source_ == INVALID_SOCKET){
				int status = ::WSAGetLastError();
				debug_out::trace("ソケットの作成に失敗しました。");
				throw win32_exception("ソケットの作成に失敗しました。", status);
			}

			//ソケットとアドレス情報にバインド
			if (!this->bind()) {
				LRESULT status = ::WSAGetLastError();
				debug_out::trace("Bindに失敗しました。");
				throw win32_exception("Bindに失敗しました。", status);
			}

			//接続要求を受け付ける
			if(!this->listen()) {
				LRESULT status = ::WSAGetLastError();
				debug_out::trace("Listenに失敗しました。");
				throw win32_exception("Listenに失敗しました。", status);
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
		// ソケットの設定
		address_.sin_family           = AF_INET;
		address_.sin_port = htons(static_cast<u_short>(port_));
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