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
		Rect2i rect_;
		Color4c color_;
		D3dTexture9Ptr texture_;///<
		D3dXSprite9Ptr sprite_;///<
		std::wstring fileName_ ;

		//----------------------------------------------------------------------------------------
		//
		PImpl(int width, int height, const Color4c& color)
			:fileName_(L""), rect_(0, 0, width, height), color_(Color4c::White), texture_(nullptr), sprite_(nullptr)
		{
			CreateSprite();
			LoadTexture(width, height);
			Fill(color);
		}


		//----------------------------------------------------------------------------------------
		//
		PImpl(int width, int height, const std::wstring& fileName)
			:fileName_(fileName), rect_(0, 0, width, height), color_(Color4c::White), texture_(nullptr), sprite_(nullptr)
		{
			CreateSprite();
			LoadTexture(fileName);
		}

		//----------------------------------------------------------------------------------------
		//
		void CreateSprite() {
			//デバイスの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			// スプライトの作成
			ID3DXSprite *sprite = NULL;
			auto hr = D3DXCreateSprite(d3dDevice.get() , &sprite);
			if (FAILED(hr)) {
				DebugOutput::Trace("スプライトの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("スプライトの作成に失敗しました。", hr);
			}

			sprite_  = D3dXSprite9Ptr(sprite, false);
		}


		//----------------------------------------------------------------------------------------
		//
		void LoadTexture(int width, int height) {
			//「テクスチャオブジェクト」の作成
			LPDIRECT3DTEXTURE9 texture = NULL;
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			auto hr = D3DXCreateTexture(d3dDevice.get(), width, height, NULL, NULL,	D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &texture);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャの作成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}
		//----------------------------------------------------------------------------------------
		//
		void LoadTexture(const std::wstring& fileName) {
			//「テクスチャオブジェクト」の作成
			LPDIRECT3DTEXTURE9 texture = NULL;
			auto d3dDevice = D3d9Driver::GetD3dDevice9();
			auto hr = D3DXCreateTextureFromFileEx(
				d3dDevice.get(), fileName.c_str(), NULL, NULL, NULL, NULL, D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, D3DX_FILTER_NONE,D3DX_DEFAULT,
				0xFF,NULL,NULL,&texture);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャの作成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャの作成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}


		//----------------------------------------------------------------------------------------
		//
		void Finalize() {
			texture_.reset();
			sprite_.reset();
		}

		//-----------------------------------------------------------------------------------------
		//
		void Fill(const Color4c& color) {
			Assert(texture_ != nullptr);

			//テクスチャサーフェイスをロック
			D3DLOCKED_RECT lockedRect = {};
			auto hr = texture_->LockRect(0, &lockedRect, NULL, 0);
			if (FAILED(hr)) {
				DebugOutput::Trace("テクスチャのロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャのロックに失敗しました。", hr);
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
				DebugOutput::Trace("テクスチャのアンロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw COMException("テクスチャのアンロックに失敗しました。", hr);
			}
		}

		//-----------------------------------------------------------------------------------------
		//
		void SetColor(const Color4c& color) {
			color_ = color;
		}

		//-----------------------------------------------------------------------------------------
		//
		Color4c GetColor() {
			return color_;
		}

		//-----------------------------------------------------------------------------------------
		//
		void SetRect(const Rect2i& rect) {
			rect_ = rect;
		}

		//-----------------------------------------------------------------------------------------
		//
		Rect2i GetRect() const {
			return rect_;
		}

		//-----------------------------------------------------------------------------------------
		//
		void Render(const Matrix44& matrix) {	
			D3DXMATRIX world;
			::CopyMemory(&world, matrix.Mat, sizeof(D3DXMATRIX));

			sprite_->SetTransform(&world);
			sprite_->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);
			{
				RECT rect = {rect_.x, rect_.y, rect_.width -rect_.x, rect_.height -rect_.y};
				const auto center   = D3DXVECTOR3(rect_.width/2.f, rect_.height/2.f, 0.f);
				sprite_->Draw(texture_.get(), &rect, &center, NULL, D3DCOLOR_RGBA(color_.r, color_.g, color_.b, color_.a));
			}
			sprite_->End();
		}

	};

	Sprite::Sprite(int width,  int height, const Color4c& color)
		:pimpl_(std::make_shared<Sprite::PImpl>(width, height, color)) {
	}

	Sprite::Sprite(int width,  int height, const std::wstring& fileName)
		:pimpl_(std::make_shared<Sprite::PImpl>( width, height, fileName)) {
	}

	Sprite::~Sprite() {
		pimpl_->Finalize();
		DebugOutput::Trace("call destructor.");
	}


	void Sprite::Fill(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->Fill(color);

	}

	void Sprite::SetColor(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetColor(color);
	}

	Color4c Sprite::GetColor() const {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetColor();
	}

	void Sprite::SetRect(const Rect2i& rect) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetRect(rect);
	}

	Rect2i Sprite::GetRect() const {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetRect();
	}

	void Sprite::Render(const Matrix44& matrix) const {
		Assert(pimpl_ != nullptr);
		pimpl_->Render(matrix);
	}

	void Sprite::Release() {
		Assert(pimpl_ != nullptr);
	}
	
	void Sprite::Recovery(){
		Assert(pimpl_ != nullptr);
	}
}
