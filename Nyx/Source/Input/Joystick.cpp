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
#include "Joystick.h"
#include "DirectInputJoystick.h"

namespace Nyx {

	struct Joystick::PImpl {
		bool IsInitialized;
		std::shared_ptr<DirectInputJoystick> joystick;
	};

	//-----------------------------------------------------------------------------------------
	//
	Joystick::Joystick(HWND hwnd_, int range) 
	{
	}

	//-----------------------------------------------------------------------------------------
	//
	Joystick::~Joystick()  {
		pimpl_->joystick->Release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Update() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);

		return pimpl_->joystick->Update();
	}

	//-----------------------------------------------------------------------------------------
	//
	void  Joystick::Release() {
		Assert(pimpl_->joystick!= nullptr);

		return pimpl_->joystick->Release();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Acquire() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);

		return pimpl_->joystick->Acquire();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::Unacquire() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);
		
		return pimpl_->joystick->Unacquire();
	}
	
	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::IsInitialized() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);
		return pimpl_->joystick->IsInitialized();
	}

	//-----------------------------------------------------------------------------------------
	//
	bool Joystick::SetButtonMax(uchar num) {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);

		return pimpl_->joystick->SetButtonMAx(num);
	}

	//-----------------------------------------------------------------------------------------
	//
	uchar Joystick::GetButtonMax() {
		Assert(pimpl_!= nullptr);
		Assert(pimpl_->IsInitialized);
		Assert(pimpl_->joystick!= nullptr);
		
		return pimpl_->joystick->GetButtonMax();
	}
}