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
#ifndef NYX_CORE_DIRECT_GRAPHICS_SPRITE_H_
#define NYX_CORE_DIRECT_GRAPHICS_SPRITE_H_

#include "Graphics/ISprite.h"
#include "Primitive/Rect2i.h"
#include "Primitive/Color4c.h"

namespace Nyx {
	namespace DX9 {


		///スプライトのDirectXによる実装
		/**
		こんな感じで描画できるとうれしい
		//コンストラクタやらなんやらで初期化
		ctor {
		Sprite * sprite = new Sprite("image", int w, int h);
		}

		なんらかの描画タスクで描画するときに変換行列を作成して描画する
		void Task::Render() {
		Matrix44 world = Matrix44::Unit;
		Matrix44::Tranform(&world, sx, sy, sz, rx, ry, rz, tx, ty, tz);
		これは
		Matrix44::Tranform(&world, Vector3(sx, sy, sz), Vector3(rx, ry, rz), Vector3(tx, ty, tz));
		としてもかまわないだろう
		sprite->Render(world);	
		}

		変換行列を作るのがややめんどうで（そして、若干遅い（行列的な意味でぁ））あるが、それは致し方あるまい。それ以外は、かなり楽ちんのはずである。
		チップとして使いたければ、コンストラクタでのように、ｘ方向とｙ方向のチップ番号および幅・高さを指定すればよい。
		ctor {
		Sprite * sprite = new Sprite("image", int w, int h, int cx, int cy, int cw, int ch);
		}

		void Task::Render(camera) {
		cx = counter%2 //まぁ、たぶんカウンタ使ってチップ番号求めるよね=>アニメーションパターンの取得は内部的に書いてもいいかしれん
		cy = counter%2 // 
		//必要があればチップサイズを変更することもできる
		sprite->SetChipSize(64, 64);
		Matrix44 world = Matrix44::Unit;
		Matrix44::TranformMatrix(&world, sx, sy, sz, rx, ry, rz, tx, ty, tz);
		sprite->Render(world, cx, cy);	
		}

		*/


		///スプライト
		class DXSprite :public ISprite {
		public:
			//----------------------------------------------------------------------------------------------
			//構築・破壊
			//----------------------------------------------------------------------------------------------
			/**
			* コンストラクタ
			*/
			DXSprite(DirectGraphicsDevice& device, int w, int h);
			/**
			*
			*/
			DXSprite(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw=0, int ch=0);
			/**
			*
			*/
			DXSprite(DirectGraphicsDevice& device, std::shared_ptr<char> data, uint size,  
				int w, int h, int cw=0, int ch=0);
			/**
			*
			*/
			~DXSprite();
			/**
			*
			*/

			void Restore();
			/**
			*
			*/
			void Release();

			/**
			*
			*/
			void Fill(Rect2i rect,Color4c color);
			/**
			*
			*/
			void Render(Matrix44& world, Color4c color);

			/**
			*
			*/
			void Render(Matrix44& world, int cx, int cy, Color4c color);

			/**
			*
			*/
			void Render(Matrix44& world, Rect2i rect, Color4c color);

			/**
			*
			*/
			HRESULT OnLostDevice();

			/**
			*
			*/
			HRESULT OnResetDevice();
			/**
			*
			*/
			HRESULT CreateSprite(DirectGraphicsDevice& device);

		private:
			D3DTexture texture;///<
			ID3DXSprite * sprite;///<
		};
	}
}
#endif