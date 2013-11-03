#include "PCH/PCH.h"
#include "Sprite.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceCapacity.h"
#include "GraphicsDeviceType.h"
#include "detail/DX9/DirectXDefinition.h"
#include "Utility/Exception.h"


namespace Nyx{

	struct Sprite::PImpl
	{
		Rect2f rect_;
		Color4c color_;
		D3DTexture texture;///<
		D3dXSprite9Ptr sprite_;///<

		//-----------------------------------------------------------------------------------------
		//
		PImpl(size_t width, size_t height) 
		{

			//デバイスの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			// スプライトの作成
			ID3DXSprite *sprite = NULL;
			auto hr = D3DXCreateSprite(d3dDevice.get(), &sprite);
			if (FAILED(hr)) {
				DebugOutput::Trace("スプライトの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("スプライトの作成に失敗しました。", hr);
			}

			//「テクスチャオブジェクト」の作成
			hr = D3DXCreateTexture(d3dDevice.get(), width, height, 0, 0,	D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, &texture);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャの作成に失敗しました。", hr);
			}

			//テクスチャの幅と高さを保存
			rect_   = Rect2f(0, 0, width, height);
			sprite_ = D3dXSprite9Ptr(sprite, true); 
		}

		//----------------------------------------------------------------------------------------
		//
		PImpl(std::wstring fileName, size_t x, size_t y, size_t width, size_t height)
		{
			//デバイスの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			// スプライトの作成
			ID3DXSprite *sprite = NULL;
			auto hr = D3DXCreateSprite(d3dDevice.get() , &sprite);
			if (FAILED(hr)) {
				DebugOutput::Trace("スプライトの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("スプライトの作成に失敗しました。", hr);
			}


			//「テクスチャオブジェクト」の作成
			hr = D3DXCreateTextureFromFileEx(d3dDevice.get(), fileName.c_str(), width, height, 0, 0,	D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,
				0xFF,NULL,NULL,&texture);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャの作成に失敗しました。", hr);
			}

			//テクスチャの幅と高さを保存
			rect_ = Rect2f(x, y, width, height);
			sprite_ = D3dXSprite9Ptr(sprite, true); 
		}

		//-----------------------------------------------------------------------------------------
		//
		void SetColor(const Color4c& color) {
			color_ = color;
		}

		//-----------------------------------------------------------------------------------------
		//
		void SetRect(const Rect2f& rect) {
			rect_ = rect;
		}
		
		//-----------------------------------------------------------------------------------------
		//
		void Render(float x, float y, float rad) {	
			auto world = D3DXMATRIX();
			::D3DXMatrixIdentity(&world);
			::D3DXMatrixRotationZ(&world, rad);
			
			sprite_->SetTransform(&world);
			sprite_->Begin(D3DXSPRITE_ALPHABLEND);
			{
				RECT rect = {rect_.x, rect_.y, rect_.width -rect_.x, rect_.height -rect_.y};
				const auto center   = D3DXVECTOR3(rect_.width/2.f, rect_.height/2.f, 0.f);
				const auto position = D3DXVECTOR3(x, y, 0);
				sprite_->Draw(texture, &rect, &center, &position, D3DCOLOR_RGBA(color_.r, color_.g, color_.b, color_.a));
			}
			
			auto hr = sprite_->End();
		}

		
		//-----------------------------------------------------------------------------------------
		//
		void OnLostDevice() {
			auto hr = sprite_->OnLostDevice();
			if (FAILED(hr)) {
				DebugOutput::Trace("OnLostDeviceメソッドに失敗しました。[%s][%d]",__FILE__, __LINE__);
				throw COMException("OnLostDeviceメソッドに失敗しました。", hr);
			}
		}


		//-----------------------------------------------------------------------------------------
		//
		void OnResetDevice() {
			auto hr = sprite_->OnResetDevice();
			if (FAILED(hr)) {
				DebugOutput::Trace("OnResetDeviceメソッドに失敗しました。[%s][%d]",__FILE__, __LINE__);
				throw COMException("OnResetDeviceメソッドに失敗しました。", hr);
			}
		}
	};

	Sprite::Sprite(size_t width, size_t height)
		: pimpl_(std::make_shared<Sprite::PImpl>(width, height)) {

	}
	
	Sprite::Sprite(const std::wstring filename, size_t x, size_t y, size_t width,  size_t height)
		:pimpl_(std::make_shared<Sprite::PImpl>(filename, x, y, width, height)) {

	}

	void Sprite::SetColor(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetColor(color);
	}

	void Sprite::SetRect(const Rect2f& rect) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetRect(rect);
	}

	void Sprite::Render(float x, float y, float rad) {
		Assert(pimpl_ != nullptr);
		pimpl_->Render(x, y, rad);
	}

	void Sprite::Render(const Vector2f& position, float rad) {
		Assert(pimpl_ != nullptr);
		pimpl_->Render(position.x, position.y, rad);
	}


	void Sprite::OnLostDevice() {
		pimpl_->OnLostDevice();
	}

	void Sprite::OnResetDevice() {
		pimpl_->OnResetDevice();
	}
}
