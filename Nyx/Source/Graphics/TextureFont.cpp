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
#include "PCH/PCH.h"
#include "Graphics/TextureFont.h"
#include "detail/DX9/DirectXDefinition.h"
#include "detail/GDI/Font.h"
#include "Primitive/Rect.h"
#include "FontInfo.h"
namespace nyx {
	struct texture_font::PImpl
	{
		wchar_t character_;
		font_info fontInfo_;
		D3dXSprite9Ptr sprite_;
		D3dTexture9Ptr texture_;
		rect2i         rect_;
		//-----------------------------------------------------------------------------------------
		//
		PImpl()
			: character_(L' '), fontInfo_(), sprite_(nullptr), texture_(nullptr){

		}

		//-----------------------------------------------------------------------------------------
		//
		PImpl(wchar_t ch, const font_info& fontInfo)
			: character_(ch), fontInfo_(fontInfo), sprite_(nullptr), texture_(nullptr) {
		}

		//-----------------------------------------------------------------------------------------
		//
		void set(wchar_t ch, const font_info& fontInfo) {
			character_ = ch;
			fontInfo_ = fontInfo;

			load_texture();
		}

		//-----------------------------------------------------------------------------------------
		//
		void make_sprite() {
			// D3dDevice9オブジェクトの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			//スプライトの作成
			LPD3DXSPRITE sprite = NULL;
			HRESULT hr = D3DXCreateSprite(d3dDevice.get(), &sprite);
			if (FAILED(hr)) {
				debug_out::trace("スプライトの生成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("スプライトの生成に失敗しました。", hr);
			}

			//スマートポインタの管理下に置く
			sprite_ = D3dXSprite9Ptr(sprite, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void load_texture() {
			// D3dDevice9オブジェクトの取得
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			using nyx::win32::font;

			//DCの取得とフォントの生成
			wchar_t fontFace[32] = {};
			wcsncpy_s(fontFace, 32, fontInfo_.fontFace.c_str(), fontInfo_.fontFace.length());
			HDC hdc = GetDC(NULL);

			LOGFONT lf = { fontInfo_.fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
				CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, fontFace[0] };
			HFONT hFont;
			if (!(hFont = CreateFontIndirect(&lf))){
			}
			HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

			// フォントビットマップ取得
			TEXTMETRIC TM;
			GetTextMetrics(hdc, &TM);
			GLYPHMETRICS GM;
			CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
			auto size = GetGlyphOutline(
				hdc, (UINT)character_,
				GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			auto ptr = std::unique_ptr<BYTE[]>(new BYTE[size]);
			GetGlyphOutline(hdc, (UINT)character_, GGO_GRAY4_BITMAP, &GM, size, ptr.get(), &Mat);

			SelectObject(hdc, oldFont);
			DeleteObject(hFont);
			ReleaseDC(NULL, hdc);

			//テクスチャの生成
			LPDIRECT3DTEXTURE9 texture = NULL;
			HRESULT hr = d3dDevice->CreateTexture(
				GM.gmCellIncX, TM.tmHeight,
				1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
				&texture, NULL);
			if (FAILED(hr)) {
				debug_out::trace("テクスチャの生成に失敗しました。[%s][%d]", __FILE__, __LINE__);
				throw com_exception("テクスチャの生成に失敗しました。", hr);
			}

			// テクスチャにフォントビットマップ書き込み
			{
				//テクスチャサーフェイスをロック
				D3DLOCKED_RECT LockedRect = {};
				hr = texture->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD);
				if (FAILED(hr)) {
					debug_out::trace("テクスチャのロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
					throw com_exception("テクスチャのロックに失敗しました。", hr);
				}

				//メモリをクリア
				::ZeroMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight);

				// フォント情報の書き込み
				const int startX = GM.gmptGlyphOrigin.x;
				const int startY = TM.tmAscent - GM.gmptGlyphOrigin.y;
				const int fontW = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
				const int fontH = GM.gmBlackBoxY;
				const int endY = startY + fontH;
				const int endX = startX + fontW;
				const int Level = 17;
				for (auto y = startY; y < endY; ++y) {
					for (auto x = startX; x < endX; ++x){
						DWORD alpha = (255 * ptr[x - startX + fontW * (y - startY)]) / (Level - 1);
						DWORD color = 0x00ffffff | (alpha << 24);
						::CopyMemory(
							(BYTE*)LockedRect.pBits + LockedRect.Pitch * y + 4 * x,
							&color, sizeof(DWORD));
					}
				}

				//テクスチャサーフェイスをアンロック
				hr = texture->UnlockRect(NULL);
				if (FAILED(hr)) {
					debug_out::trace("テクスチャのアンロックに失敗しました。[%s][%d]", __FILE__, __LINE__);
					throw com_exception("テクスチャのアンロックに失敗しました。", hr);
				}
			}

			rect_ = rect2i(0, 0, GM.gmCellIncX, TM.tmHeight);
			//スマートポインタの管理下に置く
			texture_ = D3dTexture9Ptr(texture, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void initialize() {
			make_sprite();
			load_texture();
		}

		//-----------------------------------------------------------------------------------------
		//
		rect2i get_rect() {
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
				sprite_->Draw(
					texture_.get(), NULL, &center, NULL,
					D3DCOLOR_RGBA(
					fontInfo_.fontColor.r, fontInfo_.fontColor.g,
					fontInfo_.fontColor.b, fontInfo_.fontColor.a));
			}
			sprite_->End();
		}
	};


	//-----------------------------------------------------------------------------------------
	//
	texture_font::texture_font()
		:pimpl_(std::make_shared<PImpl>())
	{
	}


	//-----------------------------------------------------------------------------------------
	//
	texture_font::texture_font(wchar_t character, const font_info& fontInfo)
		:pimpl_(std::make_shared<PImpl>(character, fontInfo))
	{
		initialize(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::set(wchar_t character, const font_info& fontInfo) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::initialize(wchar_t character, const font_info& fontInfo) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set(character, fontInfo);
		pimpl_->initialize();
	}

	//-----------------------------------------------------------------------------------------
	//
	rect2i texture_font::get_rect() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_rect();
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_font::set_font_info(const font_info& fontInfo){
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->fontInfo_ = fontInfo;
	}


	//-----------------------------------------------------------------------------------------
	//
	font_info texture_font::get_font_info() const{
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->fontInfo_;
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::set_color(const color4c& color) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->fontInfo_.fontColor = color;
	}


	//-----------------------------------------------------------------------------------------
	//
	color4c texture_font::get_color() const{
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->fontInfo_.fontColor;
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::render(const matrix& matrix) const{
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->render(matrix);
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->sprite_->OnLostDevice();
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_font::recovery(){
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->sprite_->OnResetDevice();
	}
}