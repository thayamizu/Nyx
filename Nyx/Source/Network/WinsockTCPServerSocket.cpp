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
#include "Network/WinsockTCPServerSocket.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//
	const int WinsockTCPServerSocket::MaxConnectNum = 5;


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::WinsockTCPServerSocket(int port) {
		dstAddrSize = sizeof(dstAddr);

		// ソケットの作成
		srcSock = socket(AF_INET, SOCK_STREAM, 0);
		if(srcSock < 0){
			exit(-1);
		}

		// ソケットの設定
		srcAddr.sin_family = AF_INET;
		srcAddr.sin_port = htons(static_cast<ushort>(port));
		srcAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		if(bind(srcSock, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) != 0){
			exit(-1);
		}

		// TCPクライアントからの接続要求を待てる状態にする
		if(listen(srcSock, MaxConnectNum)){
			exit(-1);
		}
	}


	//-----------------------------------------------------------------------------------------
	//
	WinsockTCPServerSocket::~WinsockTCPServerSocket() {
		// TCPセッションの終了
		closesocket(srcSock);
		closesocket(dstSock);

	}


	//-----------------------------------------------------------------------------------------
	//
	bool WinsockTCPServerSocket::Accept() {
		// TCPクライアントからの接続要求を受け付ける
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