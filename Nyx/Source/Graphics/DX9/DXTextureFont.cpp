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
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ITextureFont.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXTextureFont.h"
#include "Graphics/GDI/Font.h"
#include "Primitive/Matrix44.h"
#include "Primitive/Color4c.h"


namespace Nyx {
	namespace DX9 {
		using Nyx::GDI::Font;

		//--------------------------------------------------------------------------------
		//
		DXTextureFont::DXTextureFont():ITextureFont(1,1, false, false) 
		{
		}

		//--------------------------------------------------------------------------------
		//
		DXTextureFont::~DXTextureFont() 
		{
			Release();
		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Release() 
		{
			if (sprite!=NULL) {
				SafeRelease(sprite);
			}
			if (texture!=NULL) {
				//	texture->AddRef();//���܍��킹
				SafeRelease(texture);
			}


		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Create(DirectGraphicsDevice& device, int fontSize, wchar_t *ch, std::wstring fontName) 
		{
			HRESULT hr;

			//DC�̎擾�ƃt�H���g�̐���
			HDC hdc = GetDC(NULL);
			Font font(fontSize, 0, 500, false, false, false, SHIFTJIS_CHARSET, fontName.c_str());
			HFONT oldFont = (HFONT)SelectObject(hdc, font.GetFont());

			// �t�H���g�r�b�g�}�b�v�擾
			uint code = (uint)*ch;
			TEXTMETRIC TM;
			GetTextMetrics( hdc, &TM );
			GLYPHMETRICS GM;
			CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
			DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			BYTE *ptr = new BYTE[size];
			GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);


			//TEXTMETRIC TM;
			//GetTextMetrics( hdc, &TM );   
			//GLYPHMETRICS GM;
			//static const MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
			//ulong size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			//uchar *ptr = new uchar[size];
			//GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

			SelectObject(hdc, oldFont);
			ReleaseDC(NULL, hdc);

			// �e�N�X�`���쐬
			Direct3DDevice d3dDevice = device.GetDevice();
			SetWidth( fontSize);
			SetHeight(fontSize);

			//�X�v���C�g�̍쐬
			hr = D3DXCreateSprite(d3dDevice,&sprite);
			Assert(hr == S_OK);

			hr = d3dDevice->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
			texture->AddRef();//�J�E���g�𑝂₵�Ă���
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				//�f�o�C�X���X�g�΍�
				/*	hr = d3dDevice->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
				Assert(hr == S_OK);	
				if (FAILED(hr)) {
				return;
				}*/
			}

			// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
			D3DLOCKED_RECT LockedRect;
			hr = texture->LockRect(0, &LockedRect, NULL, 0);
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				return;
			}

			// �t�H���g���̏�������
			// iOfs_x, iOfs_y : �����o���ʒu(����)
			// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
			// Level : ���l�̒i�K (GGO_GRAY8_BITMAP�Ȃ̂�65�i�K)
			int iOfs_x = GM.gmptGlyphOrigin.x;
			int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;
			int iBmp_h = GM.gmBlackBoxY;
			int Level = 17;
			int x, y;
			DWORD Alpha, Color;
			FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);
			for(y=iOfs_y; y<iOfs_y+iBmp_h; y++)
				for(x=iOfs_x; x<iOfs_x+iBmp_w; x++){
					Alpha = (255 * ptr[x-iOfs_x + iBmp_w*(y-iOfs_y)]) / (Level-1);
					Color = 0x00ffffff | (Alpha<<24);
					memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4*x, &Color, sizeof(DWORD));
				}


				texture->UnlockRect(0);
				SafeDelete(ptr);


				//���\�[�X�f�[�^���L���b�V��
				//SetResourceData(L"�t�H���g",LockedRect.Pitch * TM.tmHeight, (uchar*)LockedRect.pBits+LockedRect.Pitch*iOfs_y + 4*iOfs_x);
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXTextureFont::OnLostDevice() {
			return sprite->OnLostDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXTextureFont::OnResetDevice() {
			return sprite->OnResetDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXTextureFont::Restore() {
			//���\�[�X���L���b�V������Ă��Ȃ�
			if (GetResourceSize() == 0) {return;}
			////�L���b�V�����Ă��郊�\�[�X�f�[�^��ǂݍ���
			//uchar* buffer;
			//uint size = GetResourceSize();
			//buffer = new uchar[size];
			//GetResourceData(&buffer);

			//Direct3DDevice d3dDevice;
			//HRESULT hr = sprite->GetDevice(&d3dDevice);
			//Assert(SUCCEEDED(hr));

			//hr = D3DXCreateTextureFromFileInMemory(d3dDevice, (void*)buffer, size, &texture);
			//Assert(hr == S_OK);
		}

		//--------------------------------------------------------------------------------
		//
		void DXTextureFont::Render(Matrix44& world, Color4c color) 
		{
			//�`��ʒu����
			RECT rect= {0,0, GetWidth(),GetHeight()};
			D3DXVECTOR3 pos(0, 0, 0);
			D3DXVECTOR3 center(GetWidth()/2.f, GetHeight()/2.f, 0);
			//���[���h�s��ɒ��S�ʒu�̕������Z
			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;

			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			sprite->Draw(texture,&rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}
	}
}
