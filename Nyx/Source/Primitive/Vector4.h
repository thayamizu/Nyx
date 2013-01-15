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
#ifndef NYX_CORE_INCLUDED_VECTOR4_H_
#define NYX_CORE_INCLUDED_VECTOR4_H_

namespace Nyx
{
	class Vector4 {
	public:
		//--------------------------------------------------------------------------------------
		// �����o�ϐ�
		//--------------------------------------------------------------------------------------
		union {
			struct {
				/// x�l
				float  x;
				/// y�l
				float  y;
				/// z�l
				float z;
				/// w
				float w;
			};
			/// �z��
			float elements[4];
		};

		//--------------------------------------------------------------------------------------
		// �����o�萔
		//--------------------------------------------------------------------------------------
		static const Vector4 Zero;  ///< �[���x�N�g��

		static const Vector4 UnitX; ///< X���P�ʃx�N�g��

		static const Vector4 UnitY; ///< Y���P�ʃx�N�g��

		static const Vector4 UnitZ; ///< Z���P�ʃx�N�g��

		static const Vector4 ScaleUnit; ///< �X�P�[���P�ʃx�N�g�� 

		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^�E�f�X�g���N�^
		//--------------------------------------------------------------------------------------
		/**
		*�f�t�H���g�R���X�g���N�^
		*/
		Vector4();

		/**
		* �������R���X�g���N�^
		* @param x
		* @param y
		* @param z
		*/
		Vector4(float x_, float y_, float z_, float w_);

		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector4
		*/
		Vector4(const Vector4 & u);

		/**
		* �f�X�g���N�^
		*/
		~Vector4();
		//--------------------------------------------------------------------------------------
		// �l�̐ݒ�
		//--------------------------------------------------------------------------------------
		/**
		* �l�̐ݒ�
		*/
		void Set(float x_, float y_, float z_, float w_);

		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		/**
		* ���Z
		* @param �E�Ӓl  
		* @return�@���Z���� 
		*/
		Vector4 operator +(const Vector4& u) const;

		/**
		* ���Z
		* @param�@�E�Ӓl  
		* @return ���Z����
		*/
		Vector4 operator -(const Vector4& u) const;

		/**
		* ��Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector4 operator *(const float u) const;

		/**
		* ��Z
		* @param  �E�Ӓl
		* @return ��Z���� 
		*/
		Vector4 operator *(const Vector4& u) const;

		/**
		* ���Z
		* @param �E�Ӓl  
		* @return ���Z����
		*/
		Vector4 operator /(const float u) const;

		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4& operator +=(const Vector4& u);

		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4& operator -=(const Vector4& u);

		/**
		* ��Z���
		* @param  �E�Ӓl
		* @return ��Z����
		*/
		Vector4& operator *=(const float u);

		/**
		* ��Z���
		* @param  �E�Ӓl
		* @return ��Z����
		*/
		Vector4& operator *=(const Vector4& u);

		/**
		* ���Z���
		* @param  �E�Ӓl
		* @return ���Z����
		*/
		Vector4& operator /=(const float u);

		/**
		* ���
		* @param �E�Ӓl
		* @return �������
		*/
		Vector4& operator =(Vector4& u);

		/**
		* ���] 
		* @param ���]����
		*/
		Vector4& operator ~();

		//--------------------------------------------------------------------------------------
		// �x�N�g�����Z
		//--------------------------------------------------------------------------------------
		/**
		* �h�b�g��
		* @param �E�Ӓl
		* @return ����
		*/
		float Dot(Vector4& u);

		//�l�����ł͊O�ς͒�`�ł��Ȃ�
		//**
		//* �N���X��
		//* @param   �E�Ӓl
		//* @return�@�N���X�� 
		//*/
		//Vector4 Cross(Vector4& u);

		/**
		* �x�N�g���̒���
		* @return  ����
		*/
		float Length();

		/**
		* �x�N�g���̒����̓��l
		* @return  ����
		*/
		float SquaredLength();

		/**
		* �x�N�g���̐��K��
		*/
		void Normalize();

		/**
		* �x�N�g���̔��]
		*/
		void Inverse();

		/**
		* ���`���
		*/
		Vector4 Lerp(const Vector4& v1, const Vector4& v2, float s);
		//--------------------------------------------------------------------------------------
		// �_�����Z
		//--------------------------------------------------------------------------------------
		/** 
		* @return �[���x�N�g���Ȃ�true
		*/
		bool IsZero() const;

		/** 
		* @return �P�ʃx�N�g���Ȃ�true
		*/
		bool IsUnit() const;

		/** 
		* �x�N�g���̓������Z
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool operator ==(const Vector4& u) const;

		/** 
		* �x�N�g���̓������Z
		* �ۂߌ덷�΍�
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool Equal(const Vector4& u) const;    
		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const Vector4& u) const;
	};
}


#endif