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

namespace nyx {
	//-----------------------------------------------------------------------------------------
	dispatcher::dispatcher()
	{

	}


	//-----------------------------------------------------------------------------------------
	dispatcher::~dispatcher() {
		clear_callback();
	}


	//-----------------------------------------------------------------------------------------
	void dispatcher::add_callback(WIDGET_EVENT_TYPE eventType, gui_callback callback) {
		//hooklist_.insert(hook_list::value_type(eventType, callback));
		hooklist_[eventType] = callback;
	}

	//-----------------------------------------------------------------------------------------
	void dispatcher::remove_callback(WIDGET_EVENT_TYPE eventType) {
		hook_list_iterator it = hooklist_.find(eventType);
		if (it != hooklist_.end()) {
			hooklist_.erase(it);
		}
	}

	//-----------------------------------------------------------------------------------------
	void dispatcher::clear_callback() {
		hooklist_.clear();
	}

	//-----------------------------------------------------------------------------------------
	gui_callback   dispatcher::get_callback(WIDGET_EVENT_TYPE eventType) {
		hook_list_iterator it = hooklist_.find(eventType);
		if (it == hooklist_.end()) {
			return nullptr;
		}
		return it->second;
	}

	//-----------------------------------------------------------------------------------------
	void dispatcher::dispatch(WIDGET_EVENT_TYPE eventType, iwidget& sender, event_args& e) {
		gui_callback callback = hooklist_[eventType];
		if (callback != nullptr) {
			callback(sender, e);
		}
	}
}
