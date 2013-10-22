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
		* 初期化
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		*/
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode);


		void Render(const Color4c& color);

		void OnRender(std::function<void(void)> render);

	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;

	};

}
#endif