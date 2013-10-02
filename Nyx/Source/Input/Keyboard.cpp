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
#include "Keyboard.h"
#include "DirectInputKeyboard.h"

namespace Nyx {
	struct Keyboard::PImpl {
		PImpl() 
			: isInitialized(false), keyboard(nullptr) {}

		bool isInitialized;
		std::shared_ptr<DirectInputKeyboard> keyboard;
	};

	Keyboard::Keyboard() 
		: pimpl_(std::make_shared<PImpl>()) {
	}

	Keyboard::Keyboard(const Keyboard& other) {
		this->pimpl_ = other.pimpl_;
	}
	
	Keyboard::Keyboard(const InputDeviceDesc& desc) 
		: pimpl_(std::make_shared<PImpl>()) {
			
		if (Initialize(desc) == false) {
			Nyx::DebugOutput::Trace("�L�[�{�[�h�f�o�C�X�̏������Ɏ��s���܂����B");
			throw Nyx::COMException("�L�[�{�[�h�f�o�C�X�̏������Ɏ��s���܂����B", 0);
		}

		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->keyboard != nullptr);
	}

	Keyboard::~Keyboard()  {
		if (pimpl_->keyboard != nullptr) {
			Release();
		}
	}

	bool Keyboard::IsInitialized() {
		Assert(pimpl_ != nullptr);

		return pimpl_->isInitialized;
	}

	bool Keyboard::Initialize(const InputDeviceDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (IsInitialized()) {
			return IsInitialized();
		}		

		pimpl_->keyboard = std::make_shared<DirectInputKeyboard>(desc.handle);
		pimpl_->isInitialized = (pimpl_->keyboard != nullptr) ? true : false;

		return pimpl_->isInitialized;
	}


	bool Keyboard::Update() {
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->keyboard != nullptr);

		return pimpl_->keyboard->Update();
	}


	void  Keyboard::Release() {
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->keyboard != nullptr);

		pimpl_->keyboard->Release();
	}

	bool Keyboard::Acquire() {
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->keyboard != nullptr);

		return pimpl_->keyboard->Acquire();
	}


	bool Keyboard::Unacquire() {
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->keyboard != nullptr);

		return pimpl_->keyboard->Unacquire();
	}
}