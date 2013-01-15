/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Primitive/Vector2.h"

namespace Nyx
{
	//--------------------------------------------------------------------------------------
	// 定数定義
	//-------------------------------------------------------------------------------------- 
	const Vector2 Vector2::Zero = Vector2(0.f, 0.f);

	const Vector2 Vector2::UnitX = Vector2(1.f, 0.f);

	const Vector2 Vector2::UnitY = Vector2(0.f, 1.f);

	const Vector2 Vector2::ScaleUnit = Vector2(1.f, 1.f);

	//--------------------------------------------------------------------------------------
	// 値の設定
	//--------------------------------------------------------------------------------------
	//値の設定  
	void Vector2::Set(float x_, float y_) {
		x = x_;
		y = y_;
	}

	//--------------------------------------------------------------------------------------
	// コンストラクタ・デストラクタ
	//--------------------------------------------------------------------------------------
	//
	Vector2::Vector2():x(0.f),y(0.f){}

	// コンストラクタ
	Vector2::Vector2(float x_, float y_):x(x_), y(y_) {}

	// コピーコンストラクタ
	Vector2::Vector2(const Vector2& u):x(u.x), y(u.y) {}

	// デストラクタ
	Vector2::~Vector2() {}

	//--------------------------------------------------------------------------------------
	// 演算
	//--------------------------------------------------------------------------------------
	// 加算
	Vector2 Vector2::operator +(const Vector2& u) const {
		return Vector2( x + u.x, y + u.y); 
	}

	// 減算
	Vector2 Vector2::operator -(const Vector2& u) const {
		return Vector2( x - u.x, y - u.y); 
	}

	// 乗算
	Vector2 Vector2::operator *(const float u) const {
		return Vector2( x * u, y * u); 
	}

	// 乗算
	Vector2 Vector2::operator *(const Vector2& u) const {
		return Vector2( x * u.x, y * u.x); 
	}


	// 除算
	Vector2 Vector2::operator /(const float u) const {
		return Vector2( x / u, y / u); 
	}
	//--------------------------------------------------------------------------------------
	// 代入演算
	//--------------------------------------------------------------------------------------
	// 加算
	Vector2 & Vector2::operator +=(const Vector2& u) {
		x += u.x;
		y += u.y;

		return *this;
	}

	// 減算
	Vector2& Vector2::operator -=(const Vector2& u) {
		x -= u.x;
		y -= u.y;

		return *this;
	}

	// 乗算
	Vector2&  Vector2::operator *=(const float u) {
		x *= u;
		y *= u;

		return *this;
	} 

	// 乗算
	Vector2&  Vector2::operator *=(const Vector2& u) {
		x *= u.x;
		y *= u.y;

		return *this;
	}

	// 除算
	Vector2& Vector2::operator /=(const float u) {
		x /= u;
		y /= u;

		return *this;
	}

	// 反転
	Vector2 Vector2::operator ~() {
		return Vector2(-x, -y);
	}

	// 代入
	Vector2& Vector2::operator =(const Vector2& u) {
		x = u.x;
		y = u.y;

		return *this;
	}

	//--------------------------------------------------------------------------------------
	// ベクトル演算
	//--------------------------------------------------------------------------------------
	// ドット積
	float Vector2::Dot(const Vector2& u) {
		return (x * u.x + y * u.y);
	}

	// ベクトルの長さ
	float Vector2::Length() {
		return static_cast<float>(sqrt(x * x + y * y ));
	}

	// ベクトルの長さの二乗値
	float Vector2::SquaredLength() {
		return static_cast<float>(x * x + y * y );
	}

	//ベクトルの正規化
	void Vector2::Normalize() {
		float abs = Length();

		if (abs <= Math::Epsilon) { abs = 1.0;}

		x /= abs;
		y /= abs;

		if (Math::Abs(x) < Math::Epsilon) {x = 0.0f;}
		if (Math::Abs(y) < Math::Epsilon) {y = 0.0f;}
	}

	// ベクトルを反転
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
	// 論理演算
	//--------------------------------------------------------------------------------------
	// ゼロベクトルかどうか 
	bool Vector2::IsZero() const {
		return (
			Math::Abs(x) <= Math::Epsilon &&
			Math::Abs(y) <= Math::Epsilon);
	}

	// 単位ベクトルかどうか 
	bool Vector2::IsUnit() const {
		return (
			Math::Abs(x - 1.f) <= Math::Epsilon &&
			Math::Abs(y - 1.f) <= Math::Epsilon);
	}


	// ベクトルが等しいか 
	bool Vector2::Equal(const Vector2& v) const {
		return ( 
			Math::Abs(x - v.x ) < Math::Epsilon &&
			Math::Abs(y - v.y ) < Math::Epsilon);
	}

	// ベクトルか等しいか 
	bool Vector2::operator ==(const Vector2& v) const {
		return x == v.x && y == v.y; 
	}

	// ゼロベクトルが等しくないか 
	bool Vector2::operator !=(const Vector2& v) const {
		return x != v.x || y != v.y; 
	}

}