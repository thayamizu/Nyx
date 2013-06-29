#ifndef NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#define NYX_CORE_INCLUDED_WINSOCK_INITIALIZER_H_
#include "PCH/PCH.h"

namespace Nyx {

	template<int Major= 2, int Minor = 0>
	class WinsockInitializer {
	public:
		/**
		* �R���X�g���N�^
		*/
		WinsockInitializer() {
			Startup();
		}


		/**
		* �f�X�g���N�^
		*/
		~WinsockInitializer() {
			Cleanup();
		}


		/**
		* Winsock�����������܂�
		*/
		void Startup() {
			int result = WSAStartup(MAKEWORD(Major, Minor), &wsaData_);
			if (result != 0) {
				throw Nyx::Win32Exception("Winsock�̏������Ɏ��s���܂���", result);
			}
		}


		/**
		* Winsock�̏I�����������܂��D
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