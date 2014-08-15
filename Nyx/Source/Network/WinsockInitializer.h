#ifndef NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#define NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#include "Utility/Exception.h"
#pragma comment( lib, "ws2_32.lib" )

namespace nyx {

	template<int Major= 2, int Minor = 0>
	class winsock_initializer {
	public:
		/**
		* コンストラクタ
		*/
		winsock_initializer() {
			startup();
		}


		/**
		* デストラクタ
		*/
		~winsock_initializer() {
			cleanup();
		}


		/**
		* Winsockを初期化します
		*/
		void startup() {
			int result = WSAStartup(MAKEWORD(Major, Minor), &wsaData_);
			if (result != 0) {
				throw nyx::win32_exception("Winsockの初期化に失敗しました", result);
			}
		}


		/**
		* Winsockの終了処理をします．
		*/
		void cleanup() {
			WSACleanup();
		}
	private:
		WSADATA wsaData_;///< 
	};

	static const nyx::winsock_initializer<> g_winsock_init = nyx::winsock_initializer<>();
}
#endif