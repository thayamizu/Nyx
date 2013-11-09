/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B
********************************************************************************/
#include "PCH/PCH.h"
#include "Graphics/TextureFont.h"
#include "detail/DX9/DirectXDefinition.h"
#include "detail/GDI/Font.h"
#include "Primitive/Rect.h"
#include "FontInfo.h"
namespace Nyx {
	struct TextureFont::PImpl
	{
		wchar_t character_;
		FontInfo fontInfo_;
		D3dXSprite9Ptr sprite_;
		D3dTexture9Ptr texture_;

		//-----------------------------------------------------------------------------------------
		//
		PImpl()
			: character_(L' '), fontInfo_(), sprite_(nullptr), texture_(nullptr){

		}

		//-----------------------------------------------------------------------------------------
		//
		PImpl(wchar_t ch, const FontInfo& fontInfo)
			: character_(ch), fontInfo_(fontInfo), sprite_(nullptr), texture_(nullptr) {
		}

		//-----------------------------------------------------------------------------------------
		//
		void Set(wchar_t ch, const FontInfo& fontInfo) {
			character_ = ch;
			fontInfo_ = fontInfo;

			LoadTexture();
		}

		//-----------------------------------------------------------------------------------------
		//
		void CreateSprite() {
			// D3dDevice9�I�u�W�F�N�g�̎擾
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			//�X�v���C�g�̍쐬
			LPD3DXSPRITE sprite = NULL;
			HRESULT hr = D3DXCreateSprite(d3dDevice.get(), &sprite);
			if (FAILED(hr)) {
				DebugOutput::Trace("�X�v���C�g�̐����Ɏ��s���܂����B[%s][%d]", __FILE__, __LINE__);
				throw COMException("�X�v���C�g�̐����Ɏ��s���܂����B", hr);
			}

			//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
			sprite_ = D3dXSprite9Ptr(sprite, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void LoadTexture() {
			// D3dDevice9�I�u�W�F�N�g�̎擾
			auto d3dDevice = D3d9Driver::GetD3dDevice9();

			using Nyx::GDI::Font;

			//DC�̎擾�ƃt�H���g�̐���
			HDC hdc = GetDC(NULL);
			Font font(fontInfo_.fontSize, 0, 400, false, false, false, SHIFTJIS_CHARSET, fontInfo_.fontFace.c_str());
			HFONT oldFont = (HFONT)SelectObject(hdc, font.GetFont());

			// �t�H���g�r�b�g�}�b�v�擾
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
			ReleaseDC(NULL, hdc);

			//�e�N�X�`���̐���
			LPDIRECT3DTEXTURE9 texture = NULL;
			HRESULT hr = d3dDevice->CreateTexture(
				GM.gmCellIncX, TM.tmHeight,
				1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
				&texture, NULL);
			if (FAILED(hr)) {
				DebugOutput::Trace("�e�N�X�`���̐����Ɏ��s���܂����B[%s][%d]", __FILE__, __LINE__);
				throw COMException("�e�N�X�`���̐����Ɏ��s���܂����B", hr);
			}

			// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
			{
				//�e�N�X�`���T�[�t�F�C�X�����b�N
				D3DLOCKED_RECT LockedRect = {};
				hr = texture->LockRect(0, &LockedRect, NULL, 0);
				if (FAILED(hr)) {
					DebugOutput::Trace("�e�N�X�`���̃��b�N�Ɏ��s���܂����B[%s][%d]", __FILE__, __LINE__);
					throw COMException("�e�N�X�`���̃��b�N�Ɏ��s���܂����B", hr);
				}

				//���������N���A
				::ZeroMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight);

				// �t�H���g���̏�������
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

				//�e�N�X�`���T�[�t�F�C�X���A�����b�N
				hr = texture->UnlockRect(NULL);
				if (FAILED(hr)) {
					DebugOutput::Trace("�e�N�X�`���̃A�����b�N�Ɏ��s���܂����B[%s][%d]", __FILE__, __LINE__);
					throw COMException("�e�N�X�`���̃A�����b�N�Ɏ��s���܂����B", hr);
				}
			}

			//�X�}�[�g�|�C���^�̊Ǘ����ɒu��
			texture_ = D3dTexture9Ptr(texture, false);
		}

		//-----------------------------------------------------------------------------------------
		//
		void Initialize() {
			CreateSprite();
			LoadTexture();
		}


		//-----------------------------------------------------------------------------------------
		//
		void Render(const Matrix44& matrix) {
			D3DXMATRIX world;
			::CopyMemory(&world, matrix.Mat, sizeof(D3DXMATRIX));

			sprite_->SetTransform(&world);
			sprite_->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);
			{
				const auto center = D3DXVECTOR3(fontInfo_.fontSize / 2.f, fontInfo_.fontSize / 2.f, 0.f);
				sprite_->Draw(
					texture_.get(), NULL, NULL, NULL,
					D3DCOLOR_RGBA(
					fontInfo_.fontColor.r, fontInfo_.fontColor.g,
					fontInfo_.fontColor.b, fontInfo_.fontColor.a));
			}
			sprite_->End();
		}
	};


	//-----------------------------------------------------------------------------------------
	//
	TextureFont::TextureFont()
		:pimpl_(std::make_shared<PImpl>())
	{
	}


	//-----------------------------------------------------------------------------------------
	//
	TextureFont::TextureFont(wchar_t character, const FontInfo& fontInfo)
		:pimpl_(std::make_shared<PImpl>(character, fontInfo))
	{
		Initialize(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Set(wchar_t character, const FontInfo& fontInfo) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(character, fontInfo);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Initialize(wchar_t character, const FontInfo& fontInfo) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(character, fontInfo);
		pimpl_->Initialize();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetFontInfo(const FontInfo& fontInfo){
		Assert(pimpl_ != nullptr);
		pimpl_->fontInfo_ = fontInfo;
	}


	//-----------------------------------------------------------------------------------------
	//
	FontInfo TextureFont::GetFontInfo() const{
		Assert(pimpl_ != nullptr);
		return pimpl_->fontInfo_;
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetRect(const Rect2i& rect) {
		Assert(pimpl_ != nullptr);
	}


	//-----------------------------------------------------------------------------------------
	//
	Rect2i TextureFont::GetRect() const {
		Assert(pimpl_ != nullptr);
		return Rect2i();
	}



	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::SetColor(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->fontInfo_.fontColor = color;
	}


	//-----------------------------------------------------------------------------------------
	//
	Color4c TextureFont::GetColor() const{
		Assert(pimpl_ != nullptr);
		return pimpl_->fontInfo_.fontColor;
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Render(const Matrix44& matrix) const{
		Assert(pimpl_ != nullptr);
		pimpl_->Render(matrix);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Release() {
		Assert(pimpl_ != nullptr);
		pimpl_->sprite_->OnLostDevice();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureFont::Recovery(){
		Assert(pimpl_ != nullptr);
		pimpl_->sprite_->OnResetDevice();
	}
}