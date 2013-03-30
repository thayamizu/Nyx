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
#ifndef NYX_CORE_INCLUDED_RANDOM_H_
#define NYX_CORE_INCLUDED_RANDOM_H_

namespace Nyx {
	/// Mersenne Twister�@�ɂ�闐������
	DEPRECATED class Random {
	public:
		/* Period parameters */  
		static const uint N = (624);
		static const uint M = (397);
		static const ulong MatrixA   = (0x9908b0dfUL);   /* constant vector a */
		static const ulong UpperMask = (0x80000000UL);  /* most significant w-r bits */
		static const ulong LowerMask = (0x7fffffffUL);  /* least significant r bits */

		//------------------------------------------------------------------------
		//�@�\�z�E�j��
		//------------------------------------------------------------------------
		/**
		*�R���X�g���N�^
		*/
		Random() : mti(624+1) {}

		//------------------------------------------------------------------------
		//�@������
		//------------------------------------------------------------------------
		/**
		* �����ɂ�闐���̏�����
		* @param ulong ����
		*/
		void Init(ulong s);

		/**
		* �����̗�ɂ�闐���̏�����
		* @param ulong ������
		* @param int ������̒���
		*/
		void Init(ulong init_key[], int key_length);

		/**
		* ������ɂ�闐���̏�����
		* @param std::wstring ������������
		*/
		void Init(std::wstring s);

		//------------------------------------------------------------------------
		//�@��������
		//------------------------------------------------------------------------
		/**
		* [0,0xffffffff]�͈̔͂ŗ����𐶐�
		* @return ulong ����
		*/
		ulong Int32(void);

		/**
		* [0,0x7fffffff]�͈̔͂ŗ����𐶐�
		* @return long ����
		*/
		long Int31(void);

		/**
		* [0,1]�܂ł͈̔͂ŗ����𐶐�
		* @return double ����
		*/
		double Real1(void);

		/**
		* [0,1)�܂ł͈̔͂ŗ����𐶐�
		* @return double ����
		*/
		double Real2(void);


		/**
		* (0,1)�͈̔͂ŗ����𐶐�
		* @return ����
		*/double Real3(void);

		/**
		* [0,1) 53�r�b�g���x
		*/double Res53(void);
	private:
		ulong mt[N];///< ������
		int mti;    ///< �V�[�h 
	};
}
#endif
