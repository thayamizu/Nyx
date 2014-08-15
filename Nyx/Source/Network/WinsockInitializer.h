#ifndef NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#define NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#include "Utility/Exception.h"
#pragma comment( lib, "ws2_32.lib" )

namespace nyx {

	template<int Major= 2, int Minor = 0>
	class winsock_initializer {
	public:
		/**
		* �R���X�g���N�^
		*/
		winsock_initializer() {
			startup();
		}


		/**
		* �f�X�g���N�^
		*/
		~winsock_initializer() {
			cleanup();
		}


		/**
		* Winsock�����������܂�
		*/
		void startup() {
			int result = WSAStartup(MAKEWORD(Major, Minor), &wsaData_);
			if (result != 0) {
				throw nyx::win32_exception("Winsock�̏������Ɏ��s���܂���", result);
			}
		}


		/**
		* Winsock�̏I�����������܂��D
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