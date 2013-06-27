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
#include "Network/WinsockTCPClientSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPClientSocket::WinsockTCPClientSocket()
	:destination_(NULL), address_() {
		// ソケットの作成
		destination_ = socket(AF_INET, SOCK_STREAM, 0);
		if(destination_ < 0){
			int result = ::WSAGetLastError();
			throw Nyx::Win32Exception("Winsockソケットの作成に失敗しました", result);
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
		// 接続先指定用構造体の準備
		address_.sin_family           = AF_INET;
		address_.sin_port             = htons(port);
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

		//サーバーへ接続
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
	//受信
	int WinsockTCPClientSocket::Recieve(char *buffer, const size_t bufferSize) const {
		return recv(destination_, buffer, bufferSize, 0);
	}
}
