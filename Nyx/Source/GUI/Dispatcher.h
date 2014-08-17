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
#ifndef NYX_CORE_INCLUDED_DISPATCHER_H_
#define NYX_CORE_INCLUDED_DISPATCHER_H_
#include <Windows.h>
#include <unordered_map>
#include "IControl.h"
#include "Utility/NonCopyable.h"
namespace nyx {

	///ディスパッチャ
	class dispatcher : private noncopyable {
		typedef std::unordered_map<WIDGET_EVENT_TYPE, gui_callback> hook_list;
		typedef std::unordered_map<WIDGET_EVENT_TYPE, gui_callback>::iterator hook_list_iterator;
	public:
		//---------------------------------------------------------------------------------------
		//構築・破壊
		//---------------------------------------------------------------------------------------
		/**
		* コンストラクタ
		*/
		explicit dispatcher();

		/**
		* デストラクタ
		*/
		virtual ~dispatcher();
		
		//---------------------------------------------------------------------------------------
		//イベントの追加と削除
		//---------------------------------------------------------------------------------------
		/**
		* ディスパッチャにコントロールを登録する
		* @param GUICallback
		*/
		void add_callback(WIDGET_EVENT_TYPE eventType, gui_callback callback);

		/**
		* ディスパッチャに登録されているコントロールを削除する
		* @param uint id
		*/
		void remove_callback(WIDGET_EVENT_TYPE eventType);

		/**
		* ディスパッチャに登録されているコントロールをクリアする
		*/
		void clear_callback();

		/**
		* ディスパッチャに登録されているコントロールを取得する
		* @param uint id
		* @return Delegate2<std::shared_ptr<IControl>, EventArgs*>* 
		*/
		gui_callback get_callback(WIDGET_EVENT_TYPE eventType);
		
		//---------------------------------------------------------------------------------------
		//イベントの割り当て
		//---------------------------------------------------------------------------------------
		/**
		* イベントの割り当て
		* @param std::shared_ptr<IControl> sender
		* @param EventArgs* e
		*/
		void dispatch(WIDGET_EVENT_TYPE eventType, iwidget& widget, event_args& e);
	private:
		///ディスパッチャにフックされているコントロールのリスト
		hook_list hooklist_;
	};
}

#endif
