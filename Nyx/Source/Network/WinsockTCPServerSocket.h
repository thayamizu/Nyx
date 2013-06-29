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
#ifndef NYX_CORE_WINSOCK_TCP_SERVER_SOCKET_H_
#define NYX_CORE_WINSOCK_TCP_SERVER_SOCKET_H_
#include "WinsockInitializer.h"

namespace Nyx {

	///TCP�T�[�o�\�P�b�g
	class WinsockTCPServerSocket {
	public:
		/**
		* �R���X�g���N�^
		* @param ushort �|�[�g�ԍ�
		*/
		WinsockTCPServerSocket(ushort port=8080) ;


		/**
		* �f�X�g���N�^
		*/
		~WinsockTCPServerSocket();


		/**
		* �N���C�A���g����̐ڑ��v�����󂯓���
		* @return bool �N���C�A���g�Ɛڑ������Ȃ�true
		*/
		bool Accept();


		/**
		*
		*/
		bool Listen();


		/**
		*
		*/
		bool Bind();
		/**
		* 
		*/
		void Disconnect();


		/**
		* 
		*/
		void SetMaxConnect(size_t maxConnect);


		/**
		* 
		*/
		size_t GetMaxConnect() const;


		/**
		* @param char* ���M�o�b�t�@
		* @param int ���M�o�b�t�@�̒���
		* @return int ���M�o�C�g��
		*/
		int Send(char *buffer, size_t bufferSize) const ;


		/**
		* @param char* ��M�o�b�t�@
		* @param int ��M�o�b�t�@�̒���
		* @return int ��M�o�C�g��
		*/
		int Recieve(char *buffer, size_t bufferSize) const;
	private:
		ushort port_;
		size_t maxConnect_;
		SOCKET source_, destination_;
		sockaddr_in address_;
	};
}
#endif

