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
/*******************************************************************************
*@file
*@author t.hayamizu
* todo:今の実装ではちらつくので、ダブルバッファリングの実装をする
*DIB自体は、そんなに使わないので後回しでもいいが。
*******************************************************************************/
#ifndef NYX_CORE_INCLUDED_IMAGE_H_
#define NYX_CORE_INCLUDED_IMAGE_H_

namespace Nyx {
	namespace GDI {

		///DIB
		class  DIBitmap{
		public:
			//---------------------------------------------------------------
			//構築・破壊
			//---------------------------------------------------------------
			/**
			*
			*/
			DIBitmap(const std::wstring fileName_);
			/**
			*
			*/
			~DIBitmap();

			//---------------------------------------------------------------
			//データ読み込み
			//---------------------------------------------------------------
			/**
			*
			*///いらなくね？
			//bool LoadFromFile(const std::wstring fileName);

			//---------------------------------------------------------------
			//描画
			//---------------------------------------------------------------
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, ulong op=SRCCOPY);
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, int sx, int sy, ulong op=SRCCOPY);
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, ulong op=SRCCOPY);
			//   void Draw(HDC hdc, int x, int y, int rotate);
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, int colorKey);
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey);
			/**
			*
			*/
			void Draw(HDC hdc, int x, int y, int width, int height, int tx, int ty, int colorKey, uchar alpha); 


			//---------------------------------------------------------------
			//情報の取得
			//---------------------------------------------------------------
			long GetWidth();
			long GetHeight();
			long* GetPixel();


			//---------------------------------------------------------------
			//解放処理
			//---------------------------------------------------------------
			void Release();
		private:
			//デフォルトコンストラクタの禁止
			//初期化・リソースの読み込みをすべてコンストラクタで行う(RAII)
			DIBitmap();

			HDC hMemDC;
			BITMAP bitmap;
			HBITMAP hbitmap;

		};
	}
}
#endif