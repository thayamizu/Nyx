#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "IRenderable.h"
#include "IResource.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"

namespace nyx {

	///スプライト
	class sprite_batch : public irenderable, public iresource
	{
	public:
		/*
		* コンストラクタ
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param std::wstring ファイル名
		*/
		sprite_batch(const std::wstring& fileName);
		
		
		/*
		*　コンストラクタ
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param const Color4c& 色
		*/
		sprite_batch(int width, int height, const color4c& color);
		
		
		/*
		*　デストラクタ
		*/
		~sprite_batch();
		
		/*
		*　スプライトを指定した色で塗りつぶします
		* @param const Color4c& 色
		*/
		void fill(const color4c& color);
		
		/*
		*　スプライトの描画色を取得します
		* @param const Color4c& 描画色
		*/
		void set_color(const color4c& color);
		
		/*
		*　スプライトの描画色を取得します
		* @return Colr4c 描画色
		*/
		color4c get_color() const;
		
		/*
		*　スプライトの描画矩形を設定します
		* @param const Rect2i& 矩形
		*/
		void set_rect(const rect2i& rect);
		
		/*
		*　スプライトの描画矩形を取得します
		* @return Rect2i 矩形
		*/
		rect2i get_rect() const;
		
		/*
		*　レンダリング
		* @param const Matrix44& 変換行列
		*/
		void render(const matrix& matrix) const;

		/*
		* リソースを開放します
		*/
		void release();
		
		/*
		* リソースを復元します
		*/
		void recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif