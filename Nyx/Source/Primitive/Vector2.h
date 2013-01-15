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
#ifndef NYX_CORE_INCLUDED_VECTOR2_H_
#define NYX_CORE_INCLUDED_VECTOR2_H_


namespace Nyx
{
	class Vector2 {
	public:
		//--------------------------------------------------------------------------------------
		// �����o�ϐ�
		//--------------------------------------------------------------------------------------
		union {
			struct {
				float x; ///< X����
				float y; ///< Y����
			};

			float element[2];
		};

		//--------------------------------------------------------------------------------------
		// �����o�萔
		//--------------------------------------------------------------------------------------
		static const Vector2 Zero;  ///< �[���x�N�g��

		static const Vector2 UnitX; ///< X���P�ʃx�N�g��

		static const Vector2 UnitY; ///< Y���P�ʃx�N�g��

		static const Vector2 ScaleUnit; ///< �X�P�[���P�ʃx�N�g��


		//--------------------------------------------------------------------------------------
		// �R���X�g���N�^�E�f�X�g���N�^
		//--------------------------------------------------------------------------------------

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vector2();

		/**
		* �R���X�g���N�^
		* @param x
		* @param y
		*/
		Vector2(float x, float y);

		/**
		* �R�s�[�R���X�g���N�^
		* @param Vector2
		*/
		Vector2(const Vector2 & u);

		/** 
		* �f�X�g���N�^
		*/
		~Vector2();
		//--------------------------------------------------------------------------------------
		// �l�̐ݒ�
		//--------------------------------------------------------------------------------------
		/**
		* �l�̐ݒ�
		*/
		void Set(float x_, float y_);

		//--------------------------------------------------------------------------------------
		// ���Z
		//--------------------------------------------------------------------------------------
		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2 operator +(const Vector2& rhs) const ;

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/ 
		Vector2 operator -(const Vector2& rhs) const;

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2 operator *(const float rhs) const;

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2 operator *(const Vector2& rhs) const;

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2 operator /(const float rhs) const;

		//--------------------------------------------------------------------------------------
		// ������Z
		//--------------------------------------------------------------------------------------
		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2 & operator +=(const Vector2& rhs);
		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/                                                                             
		Vector2 & operator -=(const Vector2& rhs);

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2 &  operator *=(const float rhs);

		/** 
		* �x�N�g����Z
		* @param �E�Ӓl 
		* @return ��Z����
		*/
		Vector2 &  operator *=(const Vector2& rhs);

		/** 
		* �x�N�g�����Z
		* @param �E�Ӓl 
		* @return ���Z����
		*/
		Vector2 & operator /=(const float rhs);

		/** 
		* �x�N�g�����]
		* @param �E�Ӓl 
		* @return ���]���ꂽ�x�N�g��
		*/
		Vector2 operator ~();

		/** 
		* �x�N�g�����
		* @param �E�Ӓl 
		* @return ������ꂽ�x�N�g��
		*/
		Vector2& operator =(const Vector2 &rhs);


		//--------------------------------------------------------------------------------------
		// �x�N�g�����Z
		//--------------------------------------------------------------------------------------
		/**
		* �h�b�g�ρi���ρj
		* @param �E�Ӓl
		* @return ����
		*/
		float Dot(const Vector2& rhs);

		/**
		* �x�N�g���̒���
		* @return �x�N�g���̒����̕�����
		*/
		float Length();

		/**
		* �x�N�g���̒����̕�����
		* @return �x�N�g���̒����̕�����
		*/
		float SquaredLength();

		/**
		* �x�N�g���𐳋K��
		*/
		inline void Normalize();

		/**
		* �x�N�g���𔽓]
		*/
		inline void Inverse();

		inline Vector2 Lerp(const Vector2& v1, const Vector2& v2, float s); 
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
		bool operator ==(const Vector2& rhs) const;

		/** 
		* �x�N�g���̓������Z
		* �ۂߌ덷�΍�
		* @param �E�Ӓl 
		* @return ��r���ʂ��������Ȃ��true
		*/
		bool Equal(const Vector2& rhs) const;    
		/** 
		* �x�N�g���������Z
		* @param �E�Ӓl 
		* @return�@��r���ʂ��������Ȃ��Ȃ��true
		*/
		bool operator !=(const Vector2& rhs) const;
	};

}
#endif
//VECTOR_H
