#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color3.h"
#include "Primitive/Color4.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "GraphicsDeviceType.h"

namespace nyx {

	class window;

	///DirectGraphicsデバイス
	class graphics_device 
	{
		friend class sprite;
		friend class texture;
	public:
		/**
		* コンストラクタ
		*/
		graphics_device();
		
		
		/**
		* コンストラクタ
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		* @param MultiSamplingLevel サンプリングレベル（0~16)
		*/
		graphics_device(std::shared_ptr<window> window, WINDOW_MODE windowMode, sampling_level level);



		/**
		* グラフィックデバイスを初期化します
		* @param std::sahred_ptr<Window>　描画ウインドウ
		* @param WindowMode ウインドウモード
		* @param MultiSamplingLevel サンプリングレベル（0~16)
		*/
		bool initialize(std::shared_ptr<window> window, WINDOW_MODE windowMode, sampling_level level);

		/**
		* 現在のウインドウモードを取得します
		* @return WindowMode
		*/
		WINDOW_MODE get_window_mode();
		
		/**
		* ウインドウモードを変更します
		*/
		void change_window_mode();

		/**
		* ビューポートを設定します
		* @param const Rect2i& クライアント領域
		* @param float 
		* @param float
		*/
		void set_view_port(const rect2i& clientRect, float minZ, float maxZ);


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
		void set_light(const vector3f& pos, const vector3f& dir, const color3f& diffuse, const color3f& specular, float range, LIGHT_TYPE lightType);
		
		//トランスフォーム
		void set_world(const matrix& world);
		void set_modelview(const matrix& view);
		void set_projection(const matrix& proj);

		//ステート
		void enable_z_buffer(bool enalbe);
		//ステートブロック
		void apply_state_block();
		void begin_state_block();
		void end_state_block();

		void set_index_buffer(std::vector<vector3f> index);
		void set_vertex_buffer(std::vector<vector3f> vertex);

		//レンダリング関係
		void clear(const color4c& color);
		void render();
		void on_render(std::function<void(std::shared_ptr<void>)> scene);
		void set_scene(std::shared_ptr<void> sceneobj);
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

	


}
#endif