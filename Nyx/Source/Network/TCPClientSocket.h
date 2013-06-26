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
#ifndef NYX_CORE_TCP_CLIENT_SOCKET_H_
#define NYX_CORE_TCP_CLIENT_SOCKET_H_

namespace Nyx {
	///TCP�N���C�A���g�\�P�b�g
	class TCPClientSocket {
	public:
		/**
		* @param char* �A�h���X
		* @param int �|�[�g�ԍ�
		*/
		TCPClientSocket(char *addr, int port);

		
		/**
		* �f�X�g���N�^
		*/
		~TCPClientSocket();


		/**
		* @param ���M�o�b�t�@
		* @param ���M�o�b�t�@�̒���
		* @return ���M�o�C�g��
		*/
		int Send(char *buf, int buf_len);


		/**
		* @param ��M�o�b�t�@
		* @param ��M�o�b�t�@�̒���
		* @return ��M�o�C�g��
		*/
		int Recieve(char *buf, int buf_len);
	private:
		WSADATA wsaData;///< 
		SOCKET dstSock;///< �ڑ���̃\�P�b�g
		struct sockaddr_in dstAddr;///<�@�T�[�o�̃A�h���X���
	};

}
#endif