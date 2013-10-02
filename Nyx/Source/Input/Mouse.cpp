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
#include "Mouse.h"
#include "DirectInputMouse.h"

namespace Nyx {
	struct Mouse::PImpl {
		bool isInitialized;
		std::shared_ptr<DirectInputMouse> mouse_;	
	};

	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse() 
		:pimpl_(std::make_shared<PImpl>())
	{
	}
	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse(const InputDeviceDesc& desc) 
		:pimpl_(std::make_shared<PImpl>())
	{

		if (Initialize(desc) == false) {
			Nyx::DebugOutput::Trace("マウスデバイスの初期化に失敗しました。");
			throw Nyx::COMException("マウスの初期化に失敗しました。", 0);
		}

		Assert(pimpl_!= nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);
	}
	

	//-------------------------------------------------------------------------------------------------------
	//
	Mouse::Mouse(const Mouse& other) {
		this->pimpl_ = other.pimpl_;
	}
	
	
	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Initialize(const InputDeviceDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (IsInitialized()) {
			return IsInitialized();
		}

		pimpl_->mouse_ = std::make_shared<DirectInputMouse>(desc.handle);
		pimpl_->isInitialized = (pimpl_->mouse_ !=nullptr) ? true :false;
		
		return IsInitialized();
	}


	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::IsInitialized() {
		return pimpl_->isInitialized;
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Update() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->Update();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Update() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->Update();
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::GetMouseButton(Nyx::uchar keycode) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->GetMouseButton(keycode);
	}
	
	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetRelativePos() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->GetRelativePos();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	Point2i Mouse::GetAbsolutePos() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->GetAbsolutePos();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	int Mouse::GetWheelState() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->GetWheelState();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Acquire() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->Acquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	bool Mouse::Unacquire(){
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		return pimpl_->mouse_->Unacquire();
	}

	//-------------------------------------------------------------------------------------------------------
	//
	void Mouse::Release() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->isInitialized);
		Assert(pimpl_->mouse_ != nullptr);

		pimpl_->mouse_->Release();
	}
}