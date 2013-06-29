#ifndef NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#define NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#include "PCH/PCH.h"

namespace Nyx {

	template<int Major= 2, int Minor = 0>
	class WinsockInitializer {
	public:
		/**
		* コンストラクタ
		*/
		WinsockInitializer() {
			Startup();
		}


		/**
		* デストラクタ
		*/
		~WinsockInitializer() {
			Cleanup();
		}


		/**
		* Winsockを初期化します
		*/
		void Startup() {
			int result = WSAStartup(MAKEWORD(Major, Minor), &wsaData_);
			if (result != 0) {
				throw Nyx::Win32Exception("Winsockの初期化に失敗しました", result);
			}
		}


		/**
		* Winsockの終了処理をします．
		*/
		void Cleanup() {
			WSACleanup();
		}
	private:
		WSADATA wsaData_;///< 
	};

	///
	static const WinsockInitializer<>& winsock_initializer = WinsockInitializer<>();
}
#endif