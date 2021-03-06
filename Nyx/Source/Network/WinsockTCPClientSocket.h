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
#ifndef NYX_CORE_WINSOCK_TCP_CLIENT_SOCKET_H_
#define NYX_CORE_WINSOCK_TCP_CLIENT_SOCKET_H_
#include "WinsockInitializer.h"

namespace nyx {
	///TCPクライアントソケット
	class winsock_tcp_client_socket {
	public:
		/*
		* コンストラクタ
		*/
		winsock_tcp_client_socket();


		/**
		* デストラクタ
		*/
		~winsock_tcp_client_socket();


		/**
		* サーバーへ接続する
		* @param const char* アドレス
		* @param const int ポート番号
		*/
		bool connect(const char* address, size_t port);
		
		
		/**
		* サーバーへ接続する
		* @param const std::string& アドレス
		* @param int ポート番号
		*/
		bool connect(const std::string&  address, size_t port);
		
		
		/**
		* サーバーへの接続を切断する
		*/
		void disconnect();


		/**
		* サーバーにデータを送信する
		* @param 送信バッファ
		* @param 送信バッファの長さ
		* @return 送信バイト数
		*/
		size_t send(char* buffer, size_t bufferSize) const;


		/**
		* サーバーからデータを受信する
		* @param 受信バッファ
		* @param 受信バッファの長さ
		* @return 受信バイト数
		*/
		size_t recieve(char* buffer, size_t bufferSize) const;
	private:
		SOCKET  destination_;///< 接続先のソケット
		sockaddr_in address_;///< サーバのアドレス情報
	};

}
#endif