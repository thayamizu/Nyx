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
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目
*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#include "PCH/PCH.h"
#include "Primitive/Vector3.h"
#include "Primitive/Quaternion.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	//ゼロ
	const Quaternion Quaternion::Zero=Quaternion(0, 0, 0, 0);

	//-----------------------------------------------------------------------------------------
	//単位四元
	const Quaternion Quaternion::Unit=Quaternion(1, 1, 1, 1);

	//-----------------------------------------------------------------------------------------
	//デフォルトコンストラクタ
	Quaternion::Quaternion ()
		:x(0), y(0), z(0), w(0)
	{
	}

	//-----------------------------------------------------------------------------------------
	//コンストラクタ
	Quaternion::Quaternion(Vector3f v, float n)
		:x(v.x), y(v.y), z(v.z), w(n)
	{

	}

	//-----------------------------------------------------------------------------------------
	//コンストラクタ
	Quaternion::Quaternion (float x_, float y_, float z_, float n_)
		:x(x_), y(y_), z(z_), w(n_)
	{

	}

	//-----------------------------------------------------------------------------------------
	// デストラクタ
	Quaternion::~Quaternion()
	{
	}
	//-----------------------------------------------------------------------------------------
	//クォータニオンの大きさ
	float Quaternion::Length()
	{
		return Math::Sqrt(x*x + y*y + z*z + w*w);
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオンの大きさ
	float Quaternion::SquaredLength()
	{
		return (x*x + y*y + z*z + w*w);
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオン同士の加算
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
	//クォータニオン同士の減算
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
	//クォータニオン同士の乗算
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
	//クォータニオンのスカラ乗算
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
	//クォータニオンのスカラ除算
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
	//クオータニオンの共役
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
	//クォータニオン同士の加算
	Quaternion& Quaternion::operator +=(const Quaternion &q)
	{
		*this = *this + q;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオン同士の減算
	Quaternion& Quaternion::operator -=(const Quaternion &q)
	{
		*this = *this-q;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオンの乗算
	Quaternion& Quaternion::operator *=(const float s)
	{
		*this = *this * s;
		return *this;
	}

	//クォータニオン同士の減算
	Quaternion& Quaternion::operator /=(const float s)
	{
		*this = *this / s;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオンの逆元
	Quaternion& Quaternion::Inverse()
	{
		float abs2 = Math::Pow2(Math::Abs(x*x+y*y+z*z+w*w));
		if (abs2<=Math::Epsilon) return *this;

		*this = ~(*this)/abs2;
		return *this;
	}

	//-----------------------------------------------------------------------------------------
	//クォータニオンの正規化
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
