#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color3.h"
#include "Primitive/Color4.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "GraphicsDeviceType.h"

namespace Nyx {

	class Window;

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
		* @param MultiSamplingLevel サンプリングレベル（0~16)
		*/
		GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode, MultiSamplingLevel level);



		/**
		* グラフィックデバイスを初期化します
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		* @param MultiSamplingLevel サンプリングレベル（0~16)
		*/
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode, MultiSamplingLevel level);

		WindowMode GetWindowMode();
		void ChangeWindowMode();

		/**
		* ビューポートを設定します
		* @param const Rect2i& クライアント領域
		* @param float 
		* @param float
		*/
		void SetViewport(const Rect2i& clientRect, float minZ, float maxZ);


		//ライティング
		/**
		* ライトを設定
		* @param Vector3f ライト位置
		* @param Vector3f 方向ベクトル
		* @param Color3f 拡散反射光の値(RGB)
		* @param Color3f 鏡面反射光の値(RGB)
		* @param float ライトの範囲
		* @param D3DLIGHTTYPE ライトの種類(ポイントライトディレクショナルライトなど)
		*/
		void SetLight(const Vector3f& pos, const Vector3f& dir, const Color3f& diffuse, const Color3f& specular, float range, LightType lightType);
		
		//ステート
		void SetBlendeState();
		void SetSamplerState();
		void SetAddressingMode();
		void SetZTest();
		void SetFog();

		//トランスフォーム
		void SetWorldMatrix(const Matrix44& world);
		void SetModelViewMatrix(const Matrix44& view);
		void SetProjectionMatrix(const Matrix44& proj);

		//ステートブロック
		void CreateStateBlock();
		void BeginStateBlock();
		void EndStateBlock();
		void ApplyStateBlock();

		//レンダリング関係
		void Clear(const Color4c& color);
		void Render();
		void OnRender(std::function<void(void)> scene);
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

}
#endif