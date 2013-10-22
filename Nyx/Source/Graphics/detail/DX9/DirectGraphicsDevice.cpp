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
#include "Primitive/Vector3.h"

#include "Primitive/Matrix44.h"

#include "Graphics/IGraphicsDevice.h"
#include "Graphics/detail/DX9/DirectXDefinition.h"
#include "Graphics/detail/DX9/DirectGraphicsDevice.h"

namespace Nyx {
	namespace DX9 {

		DirectGraphicsDevice::DirectGraphicsDevice(HWND hWnd, int w, int h, bool mode)
			:hwnd(hWnd), backBufferWidth(w), backBufferHeight(h), hMenu(NULL), isWindowed(mode), isShowCursor(false), isLostDevice(false)
		{
			//�E�C���h�E�T�C�Y�̋L��
			GetWindowRect(hwnd, &windowSize);

			// Direct3D�I�u�W�F�N�g�̍쐬
			LPDIRECT3D9  d3d = Direct3DCreate9(D3D_SDK_VERSION);
			Assert(d3d != NULL);

			//�v���C�}���f�B�X�v���C�̃A�_�v�^�f�B�X�v���C���[�h���擾
			D3DDISPLAYMODE display;
			d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);

			// D3DPresentParameters�̐ݒ�
			ZeroMemory(&presentParameter, sizeof(D3DPRESENT_PARAMETERS));

			//(�E�C���h�E�E���[�h�p)
			presentParameter.BackBufferWidth			= backBufferWidth;
			presentParameter.BackBufferHeight			= backBufferHeight;
			presentParameter.BackBufferFormat			= /*isWindowed?D3DFMT_UNKNOWN:*/display.Format;
			presentParameter.BackBufferCount			= 1;
			presentParameter.MultiSampleType			= D3DMULTISAMPLE_NONE;
			presentParameter.MultiSampleQuality			= 0;
			presentParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
			presentParameter.hDeviceWindow				= hWnd;
			presentParameter.Windowed					= isWindowed? true: false;
			presentParameter.EnableAutoDepthStencil		= true;
			presentParameter.AutoDepthStencilFormat		= D3DFMT_D16;
			presentParameter.Flags						= 0;
			presentParameter.FullScreen_RefreshRateInHz = 0;
			presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

			//Direct3DDevice�I�u�W�F�N�g�̐���
			LPDIRECT3DDEVICE9 d3dDevice = nullptr;
			HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&presentParameter, &d3dDevice );
			if( FAILED(hr)) {  
				hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&presentParameter, &d3dDevice);
				if( FAILED(hr)) {	  
					hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&presentParameter, &d3dDevice);
					if( FAILED(hr)){
						hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&presentParameter, &d3dDevice);
						Assert(hr == S_OK);
					}
				}
			}

			ResetDevice(presentParameter);

			d3d_ = D3d9Ptr(d3d, true);
			d3dDevice_ = D3dDevice9Ptr(d3dDevice, true);
		}

		//-----------------------------------------------------------------------------------------
		// �E�C���h�E���[�h���ǂ����̔���
		DirectGraphicsDevice::~DirectGraphicsDevice() {
		}

		//-----------------------------------------------------------------------------------------
		// �E�C���h�E���[�h���ǂ����̔���
		void DirectGraphicsDevice::ShowCursor(bool showCursor) {
			isShowCursor = showCursor;
			d3dDevice_->ShowCursor(showCursor);
		}

		//-----------------------------------------------------------------------------------------
		// �E�C���h�E���[�h���ǂ����̔���
		bool DirectGraphicsDevice::IsWindowed() {
			return isWindowed;
		}

		//-----------------------------------------------------------------------------------------
		// �t���X�N���[�����ǂ����̔���
		bool DirectGraphicsDevice::IsFullScreen() {
			return !isWindowed;
		}

		//-----------------------------------------------------------------------------------------
		// �t���X�N���[��<->�E�C���h�E�̐؂�ւ�
		bool DirectGraphicsDevice::ChangeDisplayMode() {

			//�E�C���h�E���[�h�����ւ�
			isWindowed= !isWindowed;
			presentParameter.Windowed = isWindowed;
			if (isWindowed) {
				/*presentParameter.BackBufferWidth=backBufferWidth;
				presentParameter.BackBufferHeight=0;
				presentParameter.BackBufferFormat = D3DFMT_UNKNOWN;*/
			}
			else {
				//�v���C�}���f�B�X�v���C�̃A�_�v�^�f�B�X�v���C���[�h���擾
				/*D3DDISPLAYMODE display;
				d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);
				presentParameter.BackBufferWidth = backBufferWidth;
				presentParameter.BackBufferHeight = backBufferHeight;
				presentParameter.BackBufferFormat = display.Format;
				*/
			}

			//�f�o�C�X���Z�b�g
			ResetDevice(presentParameter);

			return isWindowed;
		}
	
		//-----------------------------------------------------------------------------------------
		// �T���v���[�X�e�[�g�̎擾
		void DirectGraphicsDevice::GetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD* value) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetSamplerState(sampler, type, value);

		}

		//-----------------------------------------------------------------------------------------
		// �T���v���[�X�e�[�g�̐ݒ�
		void DirectGraphicsDevice::SetSamplerState(DWORD sampler,D3DSAMPLERSTATETYPE type, DWORD value) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->SetSamplerState(sampler, type, value);
		}

		//-----------------------------------------------------------------------------------------
		// ���C�e�B���O�̎擾
		void DirectGraphicsDevice::GetLight(D3DLIGHT9* light) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetLight(0, light);
		}

		//-----------------------------------------------------------------------------------------
		// ���C�e�B���O�̐ݒ�
		void DirectGraphicsDevice::SetLight(Vector3f pos, Vector3f dir, Color3f diffuse, Color3f specular, float range, D3DLIGHTTYPE type) {
			Assert(d3dDevice_ != nullptr);
			D3DLIGHT9 light;
			ZeroMemory( &light, sizeof(D3DLIGHT9) );
			
			light.Type       = type;
			light.Range      = range;

			light.Position.x = pos.x;
			light.Position.y = pos.y;
			light.Position.z = pos.z;

			light.Diffuse.r  = diffuse.r;
			light.Diffuse.g  = diffuse.g;
			light.Diffuse.b  = diffuse.b;

			light.Specular.r = specular.r;
			light.Specular.g = specular.g;
			light.Specular.b = specular.b;

			D3DXVec3Normalize( 
				reinterpret_cast<D3DXVECTOR3*>(&light.Direction), reinterpret_cast<D3DXVECTOR3*>(&dir) );

			HRESULT hr = d3dDevice_->SetLight( 0, &light );
			d3dDevice_->LightEnable( 0, true );
			Assert(hr == S_OK);

		}

		//-----------------------------------------------------------------------------------------
		// �r���[�|�[�g�̎擾
		void DirectGraphicsDevice::GetViewPort(D3DVIEWPORT9* vp) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->GetViewport(vp);
		}

		//-----------------------------------------------------------------------------------------
		// �r���[�|�[�g�̐ݒ�
		void DirectGraphicsDevice::SetViewPort(int x, int y, int width, int height, float front, float back) {
			Assert(d3dDevice_ != nullptr);
			D3DVIEWPORT9 vp;
			vp.X  = x;
			vp.Y  = y;
			vp.Width  = width;
			vp.Height = height;
			vp.MinZ=front;
			vp.MaxZ=back;
			d3dDevice_->SetViewport(&vp);
		}

		//-----------------------------------------------------------------------------------------
		// �g�����X�t�H�[���s��̐ݒ�
		void DirectGraphicsDevice::SetTransform(  D3DTRANSFORMSTATETYPE state, const Matrix44 * matrix)
		{
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->SetTransform(state, reinterpret_cast<const D3DXMATRIX*>(matrix));
		}

		//-----------------------------------------------------------------------------------------
		// �g�����X�t�H�[���s��̎擾
		void DirectGraphicsDevice::GetTransform(  D3DTRANSFORMSTATETYPE state, Matrix44 * matrix) {
			Assert(d3dDevice_ != nullptr);
			d3dDevice_->SetTransform(state, reinterpret_cast<D3DXMATRIX*>(matrix));
		}

		//-----------------------------------------------------------------------------------------
		// �f�o�C�X�̎擾
		D3dDevice9Ptr DirectGraphicsDevice::GetDevice() {
			Assert(d3dDevice_ != nullptr);
			return d3dDevice_;
		}


		//-----------------------------------------------------------------------------------------
		//�f�o�C�X�̃��Z�b�g
		bool DirectGraphicsDevice::ResetDevice(D3DPRESENT_PARAMETERS& d3dpp) {

			HRESULT hr = d3dDevice_->Reset(&d3dpp);
			switch(hr) {
			case D3DERR_INVALIDCALL: 
				DebugOutput::DebugMessage("�����ȌĂяo���ł�");
				return false;
			case D3DERR_DEVICELOST:
				DebugOutput::DebugMessage("�f�o�C�X���X�g");
				isLostDevice=true;
				return false;
			case D3DERR_DRIVERINTERNALERROR: 
				DebugOutput::DebugMessage("�h���C�o�[�����G���[");
				PostQuitMessage(0);//�����I��
				return false;
			}
			//�r���[�|�[�g�̐ݒ�
			SetViewPort(0, 0, backBufferWidth, backBufferHeight, 0.f, 1.f);

			// Z�o�b�t�@�[������L���ɂ���
			d3dDevice_->SetRenderState( D3DRS_ZENABLE, true );  
			//�\���b�h
			d3dDevice_->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
			// �J�����O
			d3dDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			// ���C�g��L���ɂ���
			d3dDevice_->SetRenderState( D3DRS_LIGHTING, true );
			// �A���r�G���g���C�g�i�����j��ݒ肷��
			d3dDevice_->SetRenderState( D3DRS_AMBIENT, 0x00111111 );
			// �X�y�L�����i���ʔ��ˁj��L���ɂ���
			d3dDevice_->SetRenderState(D3DRS_SPECULARENABLE,true);
			//�V�F�[�f�B���O���[�h(�O�[���[)
			d3dDevice_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
			//�A���t�@�u�����f�B���O��ݒ肷��
			d3dDevice_->SetRenderState ( D3DRS_ALPHABLENDENABLE, true );	
			d3dDevice_->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			d3dDevice_->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			d3dDevice_->SetRenderState( D3DRS_ALPHATESTENABLE, true );	
			

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//�N���A
		void DirectGraphicsDevice::Clear() {
			Assert(d3dDevice_ != nullptr);

			d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(125, 125, 125, 0), 1.f, 0);
		}

		//-----------------------------------------------------------------------------------------
		//�`��̊J�n
		bool DirectGraphicsDevice::BeginScene() {
			if (isLostDevice) {
				return false;
			}
			Assert(d3dDevice_ != nullptr);
			// ��ʂ�ŃN���A����
			d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 128), 1.f, 0);
			// �`��J�n
			if (SUCCEEDED(d3dDevice_->BeginScene())) {
				return true;
			}
			return false;
		}

		//-----------------------------------------------------------------------------------------
		//�`��̏I��
		void DirectGraphicsDevice::EndScene() {
			Assert(d3dDevice_ != nullptr);
			// �`��I��
			d3dDevice_->EndScene();
			// ���ۂɉ�ʂɕ`�挋�ʂ�\������
			switch (d3dDevice_->Present(NULL, NULL, NULL, NULL)) {

				// �f�o�C�X�����������Ă����ꍇ
			case D3DERR_DEVICELOST:
				isLostDevice = true;
				break;
				// �h���C�o�G���[���N�����ꍇ
			case D3DERR_DRIVERINTERNALERROR:
				throw std::runtime_error("�����h���C�o�G���[������");
				break;
			default:
				break;
			}
		}

		//-----------------------------------------------------------------------------------------
		//�f�o�C�X���X�g���̏���
		bool DirectGraphicsDevice::OnLostDevice() {
			// �f�o�C�X�̃��Z�b�g���o���邩�𒲂ׂ�
			if (d3dDevice_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
				// �f�o�C�X�����Z�b�g����
				if (!ResetDevice(presentParameter)) {
					return false;	
				}
				else {
					isLostDevice=false;
				}
			}
			else {
				return false;
			}
			return true;;
		}
	}
}