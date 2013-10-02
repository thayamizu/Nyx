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
			Nyx::DebugOutput::Trace("キーボードデバイスの初期化に失敗しました。");
			throw Nyx::COMException("キーボードデバイスの初期化に失敗しました。", 0);
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