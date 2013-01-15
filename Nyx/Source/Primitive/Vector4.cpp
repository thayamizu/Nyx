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
#include "Primitive/Vector4.h"

namespace Nyx
{

	//--------------------------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------------------------

	// �[���x�N�g��   
	const Vector4 Vector4::Zero = Vector4(0.f, 0.f, 0.f, 0.f);  

	// X���P�ʃx�N�g��
	const Vector4 Vector4::UnitX = Vector4(1.f, 0.f, 0.f, 0.f);

	// Y���P�ʃx�N�g��
	const Vector4 Vector4::UnitY = Vector4(0.f, 1.f, 0.f, 0.f); 

	// Z���x�N�g��
	const Vector4 Vector4::UnitZ = Vector4(0.f, 0.f, 1.f, 0.f); 

	// �X�P�[���P�ʃx�N�g��
	const Vector4 Vector4::ScaleUnit = Vector4(1.f, 1.f, 1.f, 1.f);

	//--------------------------------------------------------------------------------------
	// �R���X�g���N�^�E�f�X�g���N�^
	//--------------------------------------------------------------------------------------
	// �f�t�H���g�R���X�g���N�^
	Vector4::Vector4():x(0.f), y(0.f), z(0.f), w(0.f) {}

	// �������R���X�g���N�^
	Vector4::Vector4(float x_, float y_, float z_, float w_): x(x_), y(y_), z(z_), w(w_) {}

	// �R�s�[�R���X�g���N�^
	Vector4:: Vector4(const Vector4 & u) :x(u.x), y(u.y), z(u.z) ,w(u.w){}

	//�f�X�g���N�^
	Vector4::~Vector4() {}

	//--------------------------------------------------------------------------------------
	// �l�̐ݒ�
	//--------------------------------------------------------------------------------------
	//�l�̐ݒ�  
	void Vector4::Set(float x_, float y_, float z_, float w_) {
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

	//--------------------------------------------------------------------------------------
	// ���Z
	//--------------------------------------------------------------------------------------
	// ���Z
	Vector4 Vector4::operator +(const Vector4& u) const {
		return Vector4( x + u.x, y + u.y, z + u.z, w + u.w); 
	}

	// ���Z
	Vector4 Vector4::operator -(const Vector4& u) const {
		return Vector4( x - u.x, y - u.y, z - u.z, w - u.w); 
	}

	// ��Z
	Vector4 Vector4::operator *(const float u) const {
		return Vector4( x * u, y * u, z * u, w * u);
	}

	// ��Z
	Vector4 Vector4::operator *(const Vector4& u) const {
		return Vector4( x * u.x, y * u.y, z * u.z,w * u.w);
	}

	// ���Z
	Vector4 Vector4::operator /(const float u) const {
		return Vector4( x / u, y / u, z / u, w / u);
	}
	//--------------------------------------------------------------------------------------
	// ������Z
	//--------------------------------------------------------------------------------------
	// ���Z���
	Vector4&  Vector4::operator +=(const Vector4& u) {
		x += u.x;
		y += u.y;
		z += u.z;
		w += u.w;
		return *this;
	}

	// ���Z���
	Vector4&  Vector4::operator -=(const Vector4& u){
		x -= u.x;
		y -= u.y;
		z -= u.z;
		w -= u.w;

		return *this;
	}

	// ��Z���
	Vector4&  Vector4::operator *=(const float u){
		x *= u;
		y *= u;
		z *= u;
		w *= u;

		return *this;
	}

	// ��Z���
	Vector4&  Vector4::operator *=(const Vector4& u){
		x *= u.x;
		y *= u.y;
		z *= u.z;
		w *= u.w;

		return *this;
	}

	// ���Z���
	Vector4&  Vector4::operator /=(const float u){
		x /= u;
		y /= u;
		z /= u;
		w /= u;
		return *this;
	}

	// ���
	Vector4&  Vector4::operator =(Vector4& u){
		x = u.x;
		y = u.y;
		z = u.z;
		return *this;
	}

	// ���] 
	Vector4&  Vector4::operator ~(){
		x = - x;
		y = - y;
		z = - z;
		w = - w;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	// �x�N�g�����Z
	//--------------------------------------------------------------------------------------
	// �h�b�g��
	float Vector4::Dot(Vector4 & u) {
		return (x * u.x + y * u.y + z * u.z + w*u.w);
	}


	// ����
	float Vector4::Length() {
		return static_cast<float>(sqrt(x * x + y * y + z * z+ w * w));
	}

	//�@�����̓��l
	float Vector4::SquaredLength() {
		return static_cast<float>(x * x + y * y + z * z + w * w);
	}

	// �x�N�g���̐��K��
	void Vector4::Normalize() {
		float abs = Length(); 

		if (abs <= Math::Epsilon) { abs = 1.f;}

		x /= abs;
		y /= abs;
		z /= abs;
		w /= abs;

		if (Math::Abs(x) < Math::Epsilon) {x = 0.f;}
		if (Math::Abs(y) < Math::Epsilon) {y = 0.f;}
		if (Math::Abs(z) < Math::Epsilon) {z = 0.f;}
		if (Math::Abs(w) < Math::Epsilon) {w = 0.f;}
	}

	//�x�N�g���̔��]
	void Vector4::Inverse() {
		x = - x;
		y = - y;
		z = - z;
		w = - w;
	}

	//���`���
	Vector4 Vector4::Lerp(const Vector4& v1, const Vector4& v2, float s) {
		Vector4 lerp;
		if (s > 1) s = 1;
		if (s < 0) s = 0;
		lerp.x = v1.x * (1 - s) + v2.x * s;
		lerp.y = v1.y * (1 - s) + v2.y * s;
		lerp.z = v1.z * (1 - s) + v2.z * s;
		lerp.w = v1.w * (1 - s) + v2.w * s;


		return lerp;	
	}

	//--------------------------------------------------------------------------------------
	// �_�����Z
	//--------------------------------------------------------------------------------------
	// �[���x�N�g�����ǂ���
	bool  Vector4::IsZero() const {
		return (
			Math::Abs(x) <= Math::Epsilon &&
			Math::Abs(y) <= Math::Epsilon &&
			Math::Abs(z) <= Math::Epsilon &&
			Math::Abs(w) <= Math::Epsilon);
	}

	// �P�ʃx�N�g�����ǂ���
	bool  Vector4::IsUnit() const {
		return (
			Math::Abs(x - 1.f) <= Math::Epsilon &&
			Math::Abs(y - 1.f) <= Math::Epsilon &&
			Math::Abs(z - 1.f) <= Math::Epsilon &&
			Math::Abs(w - 1.f) <= Math::Epsilon);
	}

	// �x�N�g������������
	bool  Vector4::operator ==(const Vector4& u) const {
		return (x == u.x && y == u.y && z == u.z && w == u.w);
	}

	// �x�N�g�������������i�ۂߑ΍�j
	bool  Vector4::Equal(const Vector4& u) const {
		return (
			Math::Abs(x - u.x) <= Math::Epsilon &&
			Math::Abs(y - u.y) <= Math::Epsilon &&
			Math::Abs(z - u.z) <= Math::Epsilon &&
			Math::Abs(w - u.w) <= Math::Epsilon);
	}  

	// �x�N�g�����������Ȃ���
	bool  Vector4::operator !=(const Vector4& u) const {
		return (x != u.x || y != u.y && z != u.z && w != u.w);
	}

}