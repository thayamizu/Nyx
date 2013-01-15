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
#include "IO/File.h"
#include "Graphics/ISprite.h"
#include "Graphics/DX9/DirectGraphicsDevice.h"
#include "Graphics/DX9/DXSprite.h"

namespace Nyx {
	namespace DX9 {
		using std::shared_ptr;
		using Nyx::File;

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, int w, int h) 
			:ISprite()
		{
			//�f�o�C�X�̎擾
			Direct3DDevice d3dDevice = device.GetDevice();

			// �X�v���C�g�̍쐬
			HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
			Assert(hr == S_OK);

			//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
			hr = D3DXCreateTexture(d3dDevice, w, h, 0, 0,	D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED, &texture);
			Assert(hr == S_OK);

			//�e�N�X�`���̕��ƍ�����ۑ�
			SetWidth(w);
			SetHeight(h);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, tstring fileName, int w, int h, int cw, int ch)
			: ISprite(w, h, 0, 0, cw, ch)  {
				//�`�b�v�T�C�Y
				SetChipSize(cw, ch);

				//�f�o�C�X�̎擾
				Direct3DDevice d3dDevice = device.GetDevice();

				// �X�v���C�g�̍쐬
				HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
				Assert(hr == S_OK);

				//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
				hr = D3DXCreateTextureFromFileEx(d3dDevice, fileName.c_str(), w, h, 0, 0,	D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,
					0xFF,NULL,NULL,&texture);
				Assert(hr == S_OK);

				//�t�@�C�����烊�\�[�X�f�[�^���L���b�V������
				std::unique_ptr<File> file = std::unique_ptr<File>(new File(fileName, Nyx::ReadMode));
				ulong size = file->GetSize();
				uchar *buffer = NULL;
				buffer = new uchar [size];
				file->Read(buffer, size);
				SetResourceData(fileName, size, buffer);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::DXSprite(DirectGraphicsDevice& device, shared_ptr<char> data, uint size, int w, int h, int cw, int ch)
			: ISprite(w, h, 0, 0, cw, ch) {
				//�`�b�v�T�C�Y�̐ݒ�
				SetChipSize(cw, ch);

				///�f�o�C�X�̎擾
				Direct3DDevice d3dDevice = device.GetDevice();

				// �X�v���C�g�̍쐬
				HRESULT hr = D3DXCreateSprite(d3dDevice,&sprite);
				Assert(hr == S_OK);

				//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
				hr = D3DXCreateTextureFromFileInMemoryEx(d3dDevice, &*data, size, w,h, 0, 0, D3DFMT_UNKNOWN, 
					D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xFF, NULL, NULL, &texture);
				//hr =D3DXCreateTextureFromFileInMemory(d3dDevice, (void*)&*data, size, &texture);
				Assert(hr == S_OK);

				//���\�[�X�f�[�^���L���b�V������
				SetResourceData(L"�X�v���C�g", size, (uchar*)(&*data));
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Restore() 
		{
			//���\�[�X���L���b�V������Ă��Ȃ�
			if (GetResourceSize() == 0) {return;}

			//�L���b�V�����Ă��郊�\�[�X�f�[�^��ǂݍ���
			uchar* buffer;
			uint size = GetResourceSize();
			buffer = new uchar[size];
			GetResourceData(&buffer);

			Direct3DDevice d3dDevice;
			HRESULT hr = sprite->GetDevice(&d3dDevice);
			Assert(SUCCEEDED(hr));
			int w = this->GetWidth();
			int h = this->GetHeight();

			//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
			hr = D3DXCreateTextureFromFileInMemoryEx(d3dDevice, buffer, size, w,h, 0, 0, D3DFMT_UNKNOWN, 
				D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,0xff000000, NULL, NULL, &texture);
			Assert(hr == S_OK);
			SafeDelete(buffer);
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Release() 
		{
			SafeRelease(sprite);
			SafeRelease(texture);
		}

		//-----------------------------------------------------------------------------------------
		//
		DXSprite::~DXSprite() 
		{
			Release();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Fill(Rect2i rect, Color4c color) {
			Assert(sprite  != NULL);
			Assert(texture != NULL);

			RECT r = {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
			D3DLOCKED_RECT lr;
			HRESULT hr = texture->LockRect(0, &lr, &r, 0);
			Assert(hr == S_OK);
			if(FAILED(hr)) {
				return;
			}
			FillMemory(lr.pBits , lr.Pitch * GetHeight(), 
				D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			hr = texture->UnlockRect(0);
			Assert(hr == S_OK);

		}
		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, Color4c color) {	
			RECT rect= {0,0, GetWidth(), GetHeight()};
			D3DXVECTOR3 pos(0, 0, 0);
			D3DXVECTOR3 center(GetWidth()/2.f, GetHeight()/2.f, 0);

			//
			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;	
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, int cx, int cy, Color4c color) {
			int height, width;
			GetChipSize(width, height);

			RECT rect= {cx*width, cy*height, cx*width+width, cy*height+height};
			D3DXVECTOR3 center(cx*width+width/2.f, cy*height+height/2.f, 0);
			D3DXVECTOR3 pos(0, 0, 0);

			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture,&rect, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &rect, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		void DXSprite::Render(Matrix44& world, Rect2i rect, Color4c color) {
			RECT r = {rect.x, rect.y, rect.x + rect.width, rect.y+rect.height};
			D3DXVECTOR3 center(rect.width/2.f, rect.height/2.f, 0.f);
			D3DXVECTOR3 pos(0, 0, 0);

			world.Mat[3][0] += center.x;
			world.Mat[3][1] += center.y;
			sprite->SetTransform(reinterpret_cast<D3DXMATRIX*>(&world.Mat));
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			//sprite->Draw(texture,&r, &center, &pos, D3DCOLOR_ARGB(color.a, color.r, color.g, color.b));
			sprite->Draw(texture, &r, &center, &pos, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			sprite->End();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::OnLostDevice() {
			return sprite->OnLostDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::OnResetDevice() {
			return sprite->OnResetDevice();
		}

		//-----------------------------------------------------------------------------------------
		//
		HRESULT DXSprite::CreateSprite(DirectGraphicsDevice& device) {
			return D3DXCreateSprite(device.GetDevice(),&sprite);
		}
	}
}