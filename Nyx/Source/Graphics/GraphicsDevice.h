#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color4.h"

namespace Nyx {

	class Window;
	enum class WindowMode;

	///DirectGraphicsデバイス
	class GraphicsDevice 
	{
	public:
		/**
		* コンストラクタ
		*/
		GraphicsDevice();
		
		
		/**
		* コンストラクタ
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		*/
		GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode);



		/**
		* グラフィックデバイスを初期化します
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		*/
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode);



		/**
		* ビューポートを設定します
		* @param const Rect2i& クライアント領域
		* @param float 
		* @param float
		*/
		void SetViewport(const Rect2i clientRect, float minZ, float maxZ);

		void Clear(const Color4c& color);

		void Render();

		void OnRender(std::function<void(void)> render);

	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

}
#endif