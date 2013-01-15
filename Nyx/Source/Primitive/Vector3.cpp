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
#include "Primitive/Vector3.h"

namespace Nyx
{

	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------

	// ゼロベクトル   
	const Vector3 Vector3::Zero = Vector3(0.f, 0.f, 0.f);  

	// X軸単位ベクトル
	const Vector3 Vector3::UnitX = Vector3(1.f, 0.f, 0.f);

	// Y軸単位ベクトル
	const Vector3 Vector3::UnitY = Vector3(0.f, 1.f, 0.f); 

	// Z軸ベクトル
	const Vector3 Vector3::UnitZ = Vector3(0.f, 0.f, 1.f); 

	// スケール単位ベクトル
	const Vector3 Vector3::ScaleUnit = Vector3(1.f, 1.f, 1.f);

	//--------------------------------------------------------------------------------------
	// コンストラクタ・デストラクタ
	//--------------------------------------------------------------------------------------
	// デフォルトコンストラクタ
	Vector3::Vector3():x(0.f), y(0.f), z(0.f) {}

	// 引数つきコンストラクタ
	Vector3::Vector3(float x_, float y_, float z_): x(x_), y(y_), z(z_) {}

	// コピーコンストラクタ
	Vector3:: Vector3(const Vector3 & u) :x(u.x), y(u.y), z(u.z) {}

	//デストラクタ
	Vector3::~Vector3() {}

	//--------------------------------------------------------------------------------------
	// 値の設定
	//--------------------------------------------------------------------------------------
	//値の設定  
	void Vector3::Set(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	}

	//--------------------------------------------------------------------------------------
	// 演算
	//--------------------------------------------------------------------------------------
	// 加算
	Vector3 Vector3::operator +(const Vector3& u) const {
		return Vector3( x + u.x, y + u.y, z + u.z); 
	}

	// 減算
	Vector3 Vector3::operator -(const Vector3& u) const {
		return Vector3( x - u.x, y - u.y, z - u.z); 
	}

	// 乗算
	Vector3 Vector3::operator *(const float u) const {
		return Vector3( x * u, y * u, z * u);
	}

	// 乗算
	Vector3 operator *(const float u, const Vector3& v) {
		return Vector3( v.x * u, v.y * u, v.z * u);
	}

	// 除算
	Vector3 Vector3::operator /(const float u) const {
		return Vector3( x / u, y / u, z / u);
	}
	//--------------------------------------------------------------------------------------
	// 代入演算
	//--------------------------------------------------------------------------------------
	// 加算代入
	Vector3&  Vector3::operator +=(const Vector3& u) {
		x += u.x;
		y += u.y;
		z += u.z;
		return *this;
	}

	// 減算代入
	Vector3&  Vector3::operator -=(const Vector3& u){
		x -= u.x;
		y -= u.y;
		z -= u.z;
		return *this;
	}

	// 乗算代入
	Vector3&  Vector3::operator *=(const float u){
		x *= u;
		y *= u;
		z *= u;
		return *this;
	}

	// 除算代入
	Vector3&  Vector3::operator /=(const float u){
		x /= u;
		y /= u;
		z /= u;
		return *this;
	}

	// 代入
	Vector3&  Vector3::operator =(Vector3& u){
		x = u.x;
		y = u.y;
		z = u.z;
		return *this;
	}

	// 反転 
	Vector3&  Vector3::operator ~(){
		x = - x;
		y = - y;
		z = - z;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	// ベクトル演算
	//--------------------------------------------------------------------------------------
	// ドット積
	float Vector3::Dot(Vector3 & u) {
		return (x * u.x + y * u.y + z * u.z);
	}

	// クロス積
	Vector3 Vector3::Cross(Vector3 &u) {
		return Vector3(
			(y * u.z - z * u.y ),
			(x * u.z - z * u.x ),
			(x * u.y - y * u.x ));
	}

	// 長さ
	float Vector3::Length() {
		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	//　長さの二乗値
	float Vector3::SquaredLength() {
		return static_cast<float>(x * x + y * y + z * z);
	}

	// ベクトルの正規化
	void Vector3::Normalize() {
		float abs = Length(); 

		if (abs <= Math::Epsilon) { abs = 1.f;}

		x /= abs;
		y /= abs;
		z /= abs;

		if (Math::Abs(x) < Math::Epsilon) {x = 0.f;}
		if (Math::Abs(y) < Math::Epsilon) {y = 0.f;}
		if (Math::Abs(z) < Math::Epsilon) {z = 0.f;}
	}

	//ベクトルの反転
	void Vector3::Inverse() {
		x = - x;
		y = - y;
		z = - z;
	}
	//線形補間
	Vector3 Vector3::Lerp(const Vector3& v1, const Vector3& v2, float s) {
		Vector3 lerp;
		if (s > 1) s = 1;
		if (s < 0) s = 0;
		lerp.x = v1.x * (1 - s) + v2.x * s;
		lerp.y = v1.y * (1 - s) + v2.y * s;
		lerp.z = v1.z * (1 - s) + v2.z * s;

		return lerp;	
	}

	//--------------------------------------------------------------------------------------
	// 論理演算
	//--------------------------------------------------------------------------------------
	// ゼロベクトルかどうか
	bool  Vector3::IsZero() const {
		return (
			Math::Abs(x) <= Math::Epsilon &&
			Math::Abs(y) <= Math::Epsilon &&
			Math::Abs(z) <= Math::Epsilon);
	}

	// 単位ベクトルかどうか
	bool  Vector3::IsUnit() const {
		return (
			Math::Abs(x - 1.f) <= Math::Epsilon &&
			Math::Abs(y - 1.f) <= Math::Epsilon &&
			Math::Abs(z - 1.f) <= Math::Epsilon);
	}

	// ベクトルが等しいか
	bool  Vector3::operator ==(const Vector3& u) const {
		return (x == u.x && y == u.y && z == u.z);
	}

	// ベクトルが等しいか（丸め対策）
	bool  Vector3::Equal(const Vector3& u) const {
		return (
			Math::Abs(x - u.x) <= Math::Epsilon &&
			Math::Abs(y - u.y) <= Math::Epsilon &&
			Math::Abs(z - u.z) <= Math::Epsilon);
	}  

	// ベクトルが等しくないか
	bool  Vector3::operator !=(const Vector3& u) const {
		return (x != u.x || y != u.y && z != u.z);
	}

}

