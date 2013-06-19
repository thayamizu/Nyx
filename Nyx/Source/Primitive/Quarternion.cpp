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
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�
*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
********************************************************************************/
#include "PCH/PCH.h"
#include "Primitive/Vector3.h"
#include "Primitive/Quaternion.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//�[��
	const Quaternion Quaternion::Zero=Quaternion(0, 0, 0, 0);

	//-----------------------------------------------------------------------------------------
	//�P�ʎl��
	const Quaternion Quaternion::Unit=Quaternion(1, 1, 1, 1);

	//-----------------------------------------------------------------------------------------
	//�f�t�H���g�R���X�g���N�^
	Quaternion::Quaternion ()
		:x(0), y(0), z(0), w(0)
	{
	}

	//-----------------------------------------------------------------------------------------
	//�R���X�g���N�^
	Quaternion::Quaternion(Vector3f v, float n)
		:x(v.x), y(v.y), z(v.z), w(n)
	{

	}

	//-----------------------------------------------------------------------------------------
	//�R���X�g���N�^
	Quaternion::Quaternion (float x_, float y_, float z_, float n_)
		:x(x_), y(y_), z(z_), w(n_)
	{

	}

	//-----------------------------------------------------------------------------------------
	// �f�X�g���N�^
	Quaternion::~Quaternion()
	{
	}
	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̑傫��
	float Quaternion::Length()
	{
		return Math::Sqrt(x*x + y*y + z*z + w*w);
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̑傫��
	float Quaternion::SquaredLength()
	{
		return (x*x + y*y + z*z + w*w);
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����m�̉��Z
	Quaternion Quaternion::operator +(const Quaternion &q) 
		const
	{
		return Quaternion(
			x + q.x,
			y + q.y,
			z + q.z,
			w + q.w
			);
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����m�̌��Z
	Quaternion Quaternion::operator -(const Quaternion &q) 
		const
	{
		return Quaternion(
			x - q.x,
			y - q.y,
			z - q.z,
			w - q.w
			);
	}
	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����m�̏�Z
	Quaternion Quaternion::operator *(const Quaternion& q) 
		const
	{

		return Quaternion(
			w*q.x + x*q.w + z*q.y - y*q.z,
			w*q.y + y*q.w + x*q.z - z*q.x,
			w*q.z + z*q.w + y*q.x - x*q.y,
			w*q.w - x*q.x - y*q.y - z*q.z
			);
	}
	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̃X�J����Z
	Quaternion Quaternion::operator *(const float s) 
		const
	{
		return Quaternion(
			x * s,
			y * s,
			z * s,
			w * s
			);
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̃X�J�����Z
	Quaternion Quaternion::operator /(const float s) 
		const
	{
		if (s<=Math::Epsilon) {return *this;}
		return Quaternion(
			x / s,
			y / s,
			z / s,
			w / s
			);
	}

	//-----------------------------------------------------------------------------------------
	//�N�I�[�^�j�I���̋���
	Quaternion Quaternion::operator ~()
		const
	{
		return Quaternion(
			-x,
			-y,
			-z,
			w
			);
	}


	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����m�̉��Z
	Quaternion& Quaternion::operator +=(const Quaternion &q)
	{
		*this = *this + q;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I�����m�̌��Z
	Quaternion& Quaternion::operator -=(const Quaternion &q)
	{
		*this = *this-q;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̏�Z
	Quaternion& Quaternion::operator *=(const float s)
	{
		*this = *this * s;
		return *this;
	}

	//�N�H�[�^�j�I�����m�̌��Z
	Quaternion& Quaternion::operator /=(const float s)
	{
		*this = *this / s;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̋t��
	Quaternion& Quaternion::Inverse()
	{
		float abs2 = Math::Pow2(Math::Abs(x*x+y*y+z*z+w*w));
		if (abs2<=Math::Epsilon) return *this;

		*this = ~(*this)/abs2;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//�N�H�[�^�j�I���̐��K��
	void Quaternion::Normalize() {
		float mag = Math::Sqrt(x*x + y*y + z*z + w*w);
		if (mag <= Math::Epsilon) {mag=1.f;}
		float inv = 1.f/mag;

		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;

	}
}
