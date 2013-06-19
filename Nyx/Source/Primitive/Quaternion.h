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
/*@file
*@brief 四元数の演算
*テスト実装なので、できれば使わないでください。
*Todo：単体テストの実施
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
		//!デフォルトコンストラクタ
		//各要素を０初期化する
		Quaternion();

		/*!コンストラクタ
		*@param Vector3f v
		*@param float n
		*/
		Quaternion(Vector3f v, float n);

		/*!コンストラクタ
		*@param float x
		*@param float y
		*@param float z
		*@param float n
		*/
		Quaternion (float x, float y, float z, float n);

		//!デストラクタ
		~Quaternion();

		/*!四元数の大きさ
		*@return float 四元数の大きさ
		*/
		float Length();

		/*!四元数の大きさ
		*@return float 四元数の大きさ
		*/
		float SquaredLength();

		/*!四元数同士の加算
		*@param const Quaternion q
		*@return Quaternion
		*/
		inline Quaternion operator + (const Quaternion& q) const ;

		/*!四元数同士の減算
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator - (const Quaternion& q) const ;

		/*!四元数同士の乗算
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator * (const Quaternion& q) const ;

		/*!四元数のスカラ乗算
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator * (const float s) const ;

		/*!四元数のスカラ除算
		*@param const Quaternion q
		*@return Quaternion 
		*/
		inline Quaternion operator / (const float  s) const ;

		/*!四元数の加算
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion& operator += (const Quaternion& q);

		/*!四元数の減算
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion& operator -= (const Quaternion& q);

		/*!四元数同士の乗算
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator *= (const Quaternion& q);

		/*!四元数のスカラ乗算
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator *= (const float s);

		/*!四元数のスカラ除算
		*@param const float q
		*@return Quaternion &
		*/
		inline Quaternion& operator /= (const float s);

		/*!共役
		*@param const Quaternion q
		*@return Quaternion &
		*/
		inline Quaternion operator ~ () const;

		/**
		* 逆元
		* @return Quaternion&
		*/
		Quaternion& Inverse();

		/**
		* 四元数の正規化
		*/
		void Normalize();

	};

}
#endif