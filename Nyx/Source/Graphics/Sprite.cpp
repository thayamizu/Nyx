#include "PCH/PCH.h"
#include "Sprite.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceCapacity.h"
#include "GraphicsDeviceType.h"
#include "detail/DX9/DirectXDefinition.h"
#include "Utility/Exception.h"


namespace nyx{

	struct sprite::PImpl
	{
		rect2i rect_;
		color4c color_;
		D3dTexture9Ptr texture_;///<
		D3dXSprite9Ptr sprite_;///<
		std::wstring fileName_;

		//----------------------------------------------------------------------------------------
		//
		PImpl(int width, int height, const color4c& color)
			:fileName_(L""), rect_(0, 0, width, height), color_(color4c::WHITE), texture_(nullptr), sprite_(nullptr)
		{
			make_sprite();
			load_texture(width, height);
			fill(color);
		}


		//----------------------------------------------------------------------------------------
		//
		PImpl(const std::wstring& fileName)
			:fileName_(fileName), rect_(0, 0, 0, 0), color_(color4c::WHITE), texture_(nullptr), sprite_(nullptr)
		{
			make_sprite();
			load_texture(fileName);
		}

		//----------------------------------------------------------------------------------------
		//
		void make_sprite() {
			//デバイスの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			// スプライトの作成
			ID3DXSprite *sprite = NULL;
			auto hr = D3DXCreateSprite(d3dDevice.get(), &sprite);
			if (FAILED(hr)) {
				debug_out::trace("スプライトの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("スプライトの作成に失敗しました。", hr);
			}

			sprite_ = D3dXSprite9Ptr(sprite, false);
		}


		//----------------------------------------------------------------------------------------
		//
		void load_texture(int width, int height) {
			//「テクスチャオブジェクト」の作成
			LPDIRECT3DTEXTURE9 texture = NULL;
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			auto hr = D3DXCreateTexture(d3dDevice.get(), width, height, NULL, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &texture);
			if (FAILED(hr)) {
				debug_out::trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("テクスチャの作成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}
		//----------------------------------------------------------------------------------------
		//
		void load_texture(const std::wstring& fileName) {
			//「テクスチャオブジェクト」の作成
			LPDIRECT3DTEXTURE9 texture = NULL;
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			auto hr = D3DXCreateTextureFromFileEx(
				d3dDevice.get(), fileName.c_str(), NULL, NULL, NULL, NULL, D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
				0xFF, NULL, NULL, &texture);
			if (FAILED(hr)) {
				debug_out::trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("テクスチャの作成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}


		//----------------------------------------------------------------------------------------
		//
		void finalize() {
			texture_.reset();
			sprite_.reset();
		}

		//-----------------------------------------------------------------------------------------
		//
		void fill(const color4c& color) {
			NYX_ASSERT(texture_ != nullptr);

			//テクスチャサーフェイスをロック
			D3DLOCKED_RECT lockedRect = {};
			auto hr = texture_->LockRect(0, &lockedRect, NULL, 0);
			if (FAILED(hr)) {
				debug_out::trace("テクスチャのロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("テクスチャのロックに失敗しました。", hr);
			}

			//メモリをクリア
			::ZeroMemory(lockedRect.pBits, lockedRect.Pitch * rect_.height);

			//色データの書き込み
			for (auto y = 0; y < rect_.height; ++y) {
				for (auto x = 0; x < rect_.width; ++x){
					DWORD c = D3DCOLOR_RGBA(color.r, color.g, color.b, color.a);
					::CopyMemory((BYTE*)lockedRect.pBits + lockedRect.Pitch * y + 4 * x, &c, sizeof(DWORD));
				}
			}

			//テクスチャサーフェイスをアンロック
			hr = texture_->UnlockRect(NULL);
			if (FAILED(hr)) {
				debug_out::trace("テクスチャのアンロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("テクスチャのアンロックに失敗しました。", hr);
			}
		}

		//-----------------------------------------------------------------------------------------
		//
		void set_color(const color4c& color) {
			color_ = color;
		}

		//-----------------------------------------------------------------------------------------
		//
		color4c get_color() {
			return color_;
		}

		//-----------------------------------------------------------------------------------------
		//
		void set_rect(const rect2i& rect) {
			rect_ = rect;
		}

		//-----------------------------------------------------------------------------------------
		//
		rect2i get_rect() const {
			return rect_;
		}

		//-----------------------------------------------------------------------------------------
		//
		void render(const matrix& matrix) {
			D3DXMATRIX world;
			::CopyMemory(&world, matrix.mat_, sizeof(D3DXMATRIX));

			sprite_->SetTransform(&world);
			sprite_->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);
			{
				const auto center = D3DXVECTOR3(rect_.width / 2.f, rect_.height / 2.f, 0.f);
				if (rect_.width == 0 && rect_.height == 0) {
					sprite_->Draw(texture_.get(), NULL, NULL, NULL, D3DCOLOR_RGBA(color_.r, color_.g, color_.b, color_.a));
				}
				else {
					RECT rect = { rect_.x, rect_.y, rect_.width - rect_.x, rect_.height - rect_.y };
					sprite_->Draw(texture_.get(), &rect, NULL, NULL, D3DCOLOR_RGBA(color_.r, color_.g, color_.b, color_.a));
				}
			}
			sprite_->End();
		}


		void release() {
			sprite_->OnLostDevice();
			texture_.reset();
		}

		void recovery(){
			sprite_->OnResetDevice();
			if (fileName_ == L"") {
				load_texture(rect_.width, rect_.height);
				fill(color_);
			}
			else {
				load_texture(fileName_);
			}
		}

	};


	//----------------------------------------------------------------------------------------
	//
	sprite::sprite(int width,  int height, const color4c& color)
		:pimpl_(std::make_shared<sprite::PImpl>(width, height, color)) {
	}


	//----------------------------------------------------------------------------------------
	//
	sprite::sprite(const std::wstring& fileName)
		:pimpl_(std::make_shared<sprite::PImpl>(fileName)) {
	}


	//----------------------------------------------------------------------------------------
	//
	sprite::~sprite() {
		pimpl_->finalize();
	}


	//----------------------------------------------------------------------------------------
	//
	void sprite::fill(const color4c& color) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->fill(color);

	}


	//----------------------------------------------------------------------------------------
	//
	void sprite::set_fore_color(const color4c& color) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_color(color);
	}


	//----------------------------------------------------------------------------------------
	//
	color4c sprite::get_fore_color() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_color();
	}


	//----------------------------------------------------------------------------------------
	//
	void sprite::set_rect(const rect2i& rect) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_rect(rect);
	}


	//----------------------------------------------------------------------------------------
	//
	rect2i sprite::get_rect() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_rect();
	}


	//----------------------------------------------------------------------------------------
	//
	void sprite::render(const matrix& matrix) const {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->render(matrix);
	}


	//----------------------------------------------------------------------------------------
	//
	void sprite::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->release();
	}
	

	//----------------------------------------------------------------------------------------
	//
	void sprite::recovery(){
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->recovery();
	}
}
