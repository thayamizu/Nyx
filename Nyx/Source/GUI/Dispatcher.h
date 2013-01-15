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

#include <unordered_map>
#include "GUI/IDispatcher.h"
#include "Object/NonCopyable.h"
#include "Object/Delegate.h"
namespace Nyx {
	//前方宣言
	class IControl;
	struct EventArgs;

	///ディスパッチャ
	class Dispatcher : public IDispatcher, private NonCopyable 
	{
		typedef std::unordered_map<uint, Delegate2<IControl*, EventArgs*>*> HookList;
		typedef std::unordered_map<uint, Delegate2<IControl*, EventArgs*>*>::iterator HookListIterator;
	public:
		//---------------------------------------------------------------------------------------
		//構築・破壊
		//---------------------------------------------------------------------------------------
		/**
		* コンストラクタ
		*/
		explicit Dispatcher();

		/**
		* デストラクタ
		*/
		virtual ~Dispatcher();
		
		//---------------------------------------------------------------------------------------
		//イベントの追加と削除
		//---------------------------------------------------------------------------------------
		/**
		* ディスパッチャにコントロールを登録する
		* @param Delegate2<IControl*, EventArgs*>* 
		*/
		void Add(IControl* control, Delegate2<IControl*, EventArgs*>* delegate);

		/**
		* ディスパッチャに登録されているコントロールを削除する
		* @param uint id
		*/
		void Del(IControl* control);

		/**
		* ディスパッチャに登録されているコントロールをクリアする
		*/
		void Clear();

		/**
		* ディスパッチャに登録されているコントロールを取得する
		* @param uint id
		* @return Delegate2<IControl*, EventArgs*>* 
		*/
		Delegate2<IControl*, EventArgs*>* Get(IControl* control);
		
		//---------------------------------------------------------------------------------------
		//イベントの割り当て
		//---------------------------------------------------------------------------------------
		/**
		* イベントの割り当て
		* @param IControl* sender
		* @param EventArgs* e
		*/
		void Dispatch(IControl* control, EventArgs* e);
	private:
		///ディスパッチャにフックされているコントロールのリスト
		HookList hooklist;
	};
}

#endif
