#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "IRenderable.h"
#include "IResource.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"

namespace Nyx {

	///スプライト
	class Sprite : public IRenderable, public IResource
	{
	public:
		/*
		* コンストラクタ
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param std::wstring ファイル名
		*/
		Sprite(const std::wstring& fileName);
		
		
		/*
		*　コンストラクタ
		* @param int スプライトの幅
		* @param int スプライトの高さ
		* @param const Color4c& 色
		*/
		Sprite(int width, int height, const Color4c& color);
		
		
		/*
		*　デストラクタ
		*/
		~Sprite();
		
		/*
		*　スプライトを指定した色で塗りつぶします
		* @param const Color4c& 色
		*/
		void Fill(const Color4c& color);
		
		/*
		*　スプライトの描画色を取得します
		* @param const Color4c& 描画色
		*/
		void SetColor(const Color4c& color);
		
		/*
		*　スプライトの描画色を取得します
		* @return Colr4c 描画色
		*/
		Color4c GetColor() const;
		
		/*
		*　スプライトの描画矩形を設定します
		* @param const Rect2i& 矩形
		*/
		void SetRect(const Rect2i& rect);
		
		/*
		*　スプライトの描画矩形を取得します
		* @return Rect2i 矩形
		*/
		Rect2i GetRect() const;
		
		/*
		*　レンダリング
		* @param const Matrix44& 変換行列
		*/
		void Render(const Matrix44& matrix) const;

		/*
		* リソースを開放します
		*/
		void Release();
		
		/*
		* リソースを復元します
		*/
		void Recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif