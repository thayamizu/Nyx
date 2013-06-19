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
/*@file
*@brief �l�����̉��Z
*�e�X�g�����Ȃ̂ŁA�ł���Ύg��Ȃ��ł��������B
*Todo�F�P�̃e�X�g�̎��{
*@author t.hayamizu
*/
#ifndef NYX_CORE_INCLUDED_QUATERNION_H_
#define NYX_CORE_INCLUDED_QUATERNION_H_


namespace Nyx {
	class Quaternion 
	{
	public:
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float element[4];
		};
		static const Quaternion Zero;
		static const Quaternion Unit;

	public: 
		//!�f�t�H���g�R���X�g���N�^
		//�e�v�f���O����������
		Quaternion();

		/*!�R���X�g���N�^
		*@param Vector3f v
		*@param float n
		*/
		Quaternion(Vector3f v, float n);

		/*!�R���X�g���N�^
		*@param float x
		*@param float y
		*@param float z
		*@param float n
		*/
		Quaternion (float x, float y, float z, float n);

		//!�f�X�g���N�^
		~Quaternion();

		/*!�l�����̑傫��
		*@return float �l�����̑傫��
		*/
		float Length();

		/*!�l�����̑傫��
		*@return float �l�����̑傫��
		*/
		float SquaredLength();

		/*!�l�������m�̉��Z
		*@param const Quaternion q
		*@return Quaternion
		*/
		inline Quaternion operator + (const Quaternion& q) const ;

		/*!�l�������m�̌��Z
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator - (const Quaternion& q) const ;

		/*!�l�������m�̏�Z
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator * (const Quaternion& q) const ;

		/*!�l�����̃X�J����Z
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator * (const float s) const ;

		/*!�l�����̃X�J�����Z
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator / (const float  s) const ;

		/*!�l�����̉��Z
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion& operator += (const Quaternion& q);

		/*!�l�����̌��Z
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion& operator -= (const Quaternion& q);

		/*!�l�������m�̏�Z
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator *= (const Quaternion& q);

		/*!�l�����̃X�J����Z
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator *= (const float s);

		/*!�l�����̃X�J�����Z
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator /= (const float s);

		/*!����
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion operator ~ () const;

		/**
		* �t��
		* @return Quaternion&
		*/
		Quaternion& Inverse();

		/**
		* �l�����̐��K��
		*/
		void Normalize();

	};

}
#endif