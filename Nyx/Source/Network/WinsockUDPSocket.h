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
#ifndef NYX_CORE_INCLUDED_WINSOCK_UDP_SERVER_SOCKET_H_
#define NYX_CORE_INCLUDED_WINSOCK_UDP_SERVER_SOCKET_H_
#include "WinsockInitializer.h"

namespace nyx {
	///UDP�\�P�b�g
	class winsock_udp_socket {
	public:
		/**
		*�@�R���X�g���N�^
		*/
		winsock_udp_socket(const char* address, size_t port, size_t blockingMode = 1);


		/**
		*�@�f�X�g���N�^
		*/
		~winsock_udp_socket();


		/**
		* �\�P�b�g�ƃA�h���X�����o�C���h���܂�
		* @param const char* �A�h���X
		* @param ushort �|�[�g�ԍ�
		*/
		bool bind(const char* address, size_t port);


		/**
		* �T�[�o�[�Ƀf�[�^�𑗐M���܂�
		* @param char*   ���M�o�b�t�@
		* @param size_t  ���M�o�b�t�@�̒���
		* @return size_t ���M�o�C�g��
		*/
		size_t send(const char *buffer, size_t bufferSize, const winsock_udp_socket& socket) const;


		/**
		* �T�[�o�[����f�[�^����M���܂�
		* @param char*  ��M�o�b�t�@
		* @param size_t ��M�o�b�t�@�̒���
		* @return size_ ��M�o�C�g��
		*/
		size_t recieve(char *buffer, size_t bufferSize, winsock_udp_socket& socket) const;
	private:
		SOCKET      socket_;  ///< �ڑ���̃\�P�b�g
		sockaddr_in address_; ///< �ڑ����̃A�h���X���
	};
}
#endif
