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
#include "PCH/PCH.h"
#include "Primitive/Vector2.h"

namespace Nyx
{
	//--------------------------------------------------------------------------------------
	// �萔��`
	//-------------------------------------------------------------------------------------- 
	const Vector2 Vector2::Zero = Vector2(0.f, 0.f);

	const Vector2 Vector2::UnitX = Vector2(1.f, 0.f);

	const Vector2 Vector2::UnitY = Vector2(0.f, 1.f);

	const Vector2 Vector2::ScaleUnit = Vector2(1.f, 1.f);

	//--------------------------------------------------------------------------------------
	// �l�̐ݒ�
	//--------------------------------------------------------------------------------------
	//�l�̐ݒ�  
	void Vector2::Set(float x_, float y_) {
		x = x_;
		y = y_;
	}

	//--------------------------------------------------------------------------------------
	// �R���X�g���N�^�E�f�X�g���N�^
	//--------------------------------------------------------------------------------------
	//
	Vector2::Vector2():x(0.f),y(0.f){}

	// �R���X�g���N�^
	Vector2::Vector2(float x_, float y_):x(x_), y(y_) {}

	// �R�s�[�R���X�g���N�^
	Vector2::Vector2(const Vector2& u):x(u.x), y(u.y) {}

	// �f�X�g���N�^
	Vector2::~Vector2() {}

	//--------------------------------------------------------------------------------------
	// ���Z
	//--------------------------------------------------------------------------------------
	// ���Z
	Vector2 Vector2::operator +(const Vector2& u) const {
		return Vector2( x + u.x, y + u.y); 
	}

	// ���Z
	Vector2 Vector2::operator -(const Vector2& u) const {
		return Vector2( x - u.x, y - u.y); 
	}

	// ��Z
	Vector2 Vector2::operator *(const float u) const {
		return Vector2( x * u, y * u); 
	}

	// ��Z
	Vector2 Vector2::operator *(const Vector2& u) const {
		return Vector2( x * u.x, y * u.x); 
	}


	// ���Z
	Vector2 Vector2::operator /(const float u) const {
		return Vector2( x / u, y / u); 
	}
	//--------------------------------------------------------------------------------------
	// ������Z
	//--------------------------------------------------------------------------------------
	// ���Z
	Vector2 & Vector2::operator +=(const Vector2& u) {
		x += u.x;
		y += u.y;

		return *this;
	}

	// ���Z
	Vector2& Vector2::operator -=(const Vector2& u) {
		x -= u.x;
		y -= u.y;

		return *this;
	}

	// ��Z
	Vector2&  Vector2::operator *=(const float u) {
		x *= u;
		y *= u;

		return *this;
	} 

	// ��Z
	Vector2&  Vector2::operator *=(const Vector2& u) {
		x *= u.x;
		y *= u.y;

		return *this;
	}

	// ���Z
	Vector2& Vector2::operator /=(const float u) {
		x /= u;
		y /= u;

		return *this;
	}

	// ���]
	Vector2 Vector2::operator ~() {
		return Vector2(-x, -y);
	}

	// ���
	Vector2& Vector2::operator =(const Vector2& u) {
		x = u.x;
		y = u.y;

		return *this;
	}

	//--------------------------------------------------------------------------------------
	// �x�N�g�����Z
	//--------------------------------------------------------------------------------------
	// �h�b�g��
	float Vector2::Dot(const Vector2& u) {
		return (x * u.x + y * u.y);
	}

	// �x�N�g���̒���
	float Vector2::Length() {
		return static_cast<float>(sqrt(x * x + y * y ));
	}

	// �x�N�g���̒����̓��l
	float Vector2::SquaredLength() {
		return static_cast<float>(x * x + y * y );
	}

	//�x�N�g���̐��K��
	void Vector2::Normalize() {
		float abs = Length();

		if (abs <= Math::Epsilon) { abs = 1.0;}

		x /= abs;
		y /= abs;

		if (Math::Abs(x) < Math::Epsilon) {x = 0.0f;}
		if (Math::Abs(y) < Math::Epsilon) {y = 0.0f;}
	}

	// �x�N�g���𔽓]
	void Vector2::Inverse() {
		x = - x;
		y = - y;
	}

	Vector2 Vector2::Lerp(const Vector2& v1, const Vector2& v2, float s) {
		Vector2 lerp;
		if (s > 1) s = 1;
		if (s < 0) s = 0;
		lerp.x = v1.x * (1 - s) + v2.x * s;
		lerp.y = v1.y * (1 - s) + v2.y * s;

		return lerp;
	}

	//--------------------------------------------------------------------------------------
	// �_�����Z
	//--------------------------------------------------------------------------------------
	// �[���x�N�g�����ǂ��� 
	bool Vector2::IsZero() const {
		return (
			Math::Abs(x) <= Math::Epsilon &&
			Math::Abs(y) <= Math::Epsilon);
	}

	// �P�ʃx�N�g�����ǂ��� 
	bool Vector2::IsUnit() const {
		return (
			Math::Abs(x - 1.f) <= Math::Epsilon &&
			Math::Abs(y - 1.f) <= Math::Epsilon);
	}


	// �x�N�g������������ 
	bool Vector2::Equal(const Vector2& v) const {
		return ( 
			Math::Abs(x - v.x ) < Math::Epsilon &&
			Math::Abs(y - v.y ) < Math::Epsilon);
	}

	// �x�N�g������������ 
	bool Vector2::operator ==(const Vector2& v) const {
		return x == v.x && y == v.y; 
	}

	// �[���x�N�g�����������Ȃ��� 
	bool Vector2::operator !=(const Vector2& v) const {
		return x != v.x || y != v.y; 
	}

}