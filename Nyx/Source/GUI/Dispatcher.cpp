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
#include "GUI/IControl.h"
#include "GUI/Dispatcher.h"
#include "Thread/CriticalSection.h"

namespace Nyx {
	//-----------------------------------------------------------------------------------------
	Dispatcher::Dispatcher() 
		:IDispatcher() {

	}


	//-----------------------------------------------------------------------------------------
	Dispatcher::~Dispatcher() {
		Clear();
	}


	//-----------------------------------------------------------------------------------------
	void Dispatcher::Add(std::shared_ptr<IControl> control, GUICallback delegate) {
		uint index = control->GetID();
		hooklist[index] = delegate;
	}

	//-----------------------------------------------------------------------------------------
	void Dispatcher::Del(std::shared_ptr<IControl> control) {
		HookListIterator it = hooklist.find(control->GetID());
		if (it != hooklist.end()) {
			hooklist.erase(it);
		}
	}

	//-----------------------------------------------------------------------------------------
	void Dispatcher::Clear() {
		hooklist.clear();
	}
	
	//-----------------------------------------------------------------------------------------
	GUICallback   Dispatcher::GetCallback(std::shared_ptr<IControl> control) {
		size_t id = control->GetID();
		HookListIterator it = hooklist.find(id);
		if (it == hooklist.end()) {
			return nullptr;
		}
		return it->second;
	}

	//-----------------------------------------------------------------------------------------
	void Dispatcher::Dispatch(std::shared_ptr<IControl> sender, EventArgs& e) {
		size_t id = sender->GetID();
		GUICallback callback = hooklist[id];
		if (callback != nullptr) {
			callback(sender, e);
		}
	}
}
