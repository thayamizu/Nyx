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
#include "Primitive/Vector4.h"

namespace Nyx
{

	//--------------------------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------------------------

	// ゼロベクトル   
	const Vector4 Vector4::Zero = Vector4(0.f, 0.f, 0.f, 0.f);  

	// X軸単位ベクトル
	const Vector4 Vector4::UnitX = Vector4(1.f, 0.f, 0.f, 0.f);

	// Y軸単位ベクトル
	const Vector4 Vector4::UnitY = Vector4(0.f, 1.f, 0.f, 0.f); 

	// Z軸ベクトル
	const Vector4 Vector4::UnitZ = Vector4(0.f, 0.f, 1.f, 0.f); 

	// スケール単位ベクトル
	const Vector4 Vector4::ScaleUnit = Vector4(1.f, 1.f, 1.f, 1.f);

	//--------------------------------------------------------------------------------------
	// コンストラクタ・デストラクタ
	//--------------------------------------------------------------------------------------
	// デフォルトコンストラクタ
	Vector4::Vector4():x(0.f), y(0.f), z(0.f), w(0.f) {}

	// 引数つきコンストラクタ
	Vector4::Vector4(float x_, float y_, float z_, float w_): x(x_), y(y_), z(z_), w(w_) {}

	// コピーコンストラクタ
	Vector4:: Vector4(const Vector4 & u) :x(u.x), y(u.y), z(u.z) ,w(u.w){}

	//デストラクタ
	Vector4::~Vector4() {}

	//--------------------------------------------------------------------------------------
	// 値の設定
	//--------------------------------------------------------------------------------------
	//値の設定  
	void Vector4::Set(float x_, float y_, float z_, float w_) {
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

	//--------------------------------------------------------------------------------------
	// 演算
	//--------------------------------------------------------------------------------------
	// 加算
	Vector4 Vector4::operator +(const Vector4& u) const {
		return Vector4( x + u.x, y + u.y, z + u.z, w + u.w); 
	}

	// 減算
	Vector4 Vector4::operator -(const Vector4& u) const {
		return Vector4( x - u.x, y - u.y, z - u.z, w - u.w); 
	}

	// 乗算
	Vector4 Vector4::operator *(const float u) const {
		return Vector4( x * u, y * u, z * u, w * u);
	}

	// 乗算
	Vector4 Vector4::operator *(const Vector4& u) const {
		return Vector4( x * u.x, y * u.y, z * u.z,w * u.w);
	}

	// 除算
	Vector4 Vector4::operator /(const float u) const {
		return Vector4( x / u, y / u, z / u, w / u);
	}
	//--------------------------------------------------------------------------------------
	// 代入演算
	//--------------------------------------------------------------------------------------
	// 加算代入
	Vector4&  Vector4::operator +=(const Vector4& u) {
		x += u.x;
		y += u.y;
		z += u.z;
		w += u.w;
		return *this;
	}

	// 減算代入
	Vector4&  Vector4::operator -=(const Vector4& u){
		x -= u.x;
		y -= u.y;
		z -= u.z;
		w -= u.w;

		return *this;
	}

	// 乗算代入
	Vector4&  Vector4::operator *=(const float u){
		x *= u;
		y *= u;
		z *= u;
		w *= u;

		return *this;
	}

	// 乗算代入
	Vector4&  Vector4::operator *=(const Vector4& u){
		x *= u.x;
		y *= u.y;
		z *= u.z;
		w *= u.w;

		return *this;
	}

	// 除算代入
	Vector4&  Vector4::operator /=(const float u){
		x /= u;
		y /= u;
		z /= u;
		w /= u;
		return *this;
	}

	// 代入
	Vector4&  Vector4::operator =(Vector4& u){
		x = u.x;
		y = u.y;
		z = u.z;
		return *this;
	}

	// 反転 
	Vector4&  Vector4::operator ~(){
		x = - x;
		y = - y;
		z = - z;
		w = - w;
		return *this;
	}

	//--------------------------------------------------------------------------------------
	// ベクトル演算
	//--------------------------------------------------------------------------------------
	// ドット積
	float Vector4::Dot(Vector4 & u) {
		return (x * u.x + y * u.y + z * u.z + w*u.w);
	}


	// 長さ
	float Vector4::Length() {
		return static_cast<float>(sqrt(x * x + y * y + z * z+ w * w));
	}

	//　長さの二乗値
	float Vector4::SquaredLength() {
		return static_cast<float>(x * x + y * y + z * z + w * w);
	}

	// ベクトルの正規化
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

	//ベクトルの反転
	void Vector4::Inverse() {
		x = - x;
		y = - y;
		z = - z;
		w = - w;
	}

	//線形補間
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
	// 論理演算
	//--------------------------------------------------------------------------------------
	// ゼロベクトルかどうか
	bool  Vector4::IsZero() const {
		return (
			Math::Abs(x) <= Math::Epsilon &&
			Math::Abs(y) <= Math::Epsilon &&
			Math::Abs(z) <= Math::Epsilon &&
			Math::Abs(w) <= Math::Epsilon);
	}

	// 単位ベクトルかどうか
	bool  Vector4::IsUnit() const {
		return (
			Math::Abs(x - 1.f) <= Math::Epsilon &&
			Math::Abs(y - 1.f) <= Math::Epsilon &&
			Math::Abs(z - 1.f) <= Math::Epsilon &&
			Math::Abs(w - 1.f) <= Math::Epsilon);
	}

	// ベクトルが等しいか
	bool  Vector4::operator ==(const Vector4& u) const {
		return (x == u.x && y == u.y && z == u.z && w == u.w);
	}

	// ベクトルが等しいか（丸め対策）
	bool  Vector4::Equal(const Vector4& u) const {
		return (
			Math::Abs(x - u.x) <= Math::Epsilon &&
			Math::Abs(y - u.y) <= Math::Epsilon &&
			Math::Abs(z - u.z) <= Math::Epsilon &&
			Math::Abs(w - u.w) <= Math::Epsilon);
	}  

	// ベクトルが等しくないか
	bool  Vector4::operator !=(const Vector4& u) const {
		return (x != u.x || y != u.y && z != u.z && w != u.w);
	}

}