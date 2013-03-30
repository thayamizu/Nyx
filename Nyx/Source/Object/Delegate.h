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
#ifndef NYX_CORE_INCLUDED_DELEGATE_H_
#define NYX_CORE_INCLUDED_DELEGATE_H_

namespace Nyx {
	
	class Delegate0 {
	public:
		/**
		*
		*/
		Delegate0() {
		}
		/**
		*
		*/
		Delegate0(void (*fp)()) {
			delegate = new DelegateHolder1(fp);
		}
		/**
		*
		*/
		template < typename  T>
		Delegate0(T* class_, void (T::*method)()) {
			delegate = new DelegateHolder2<T>(class_, method);
		}
		/**
		*
		*/
		~Delegate0() {
			delete delegate;
		}
		/**
		*
		*/
		void Call() {
			delegate->Call();
		}
		/**
		*
		*/
		void operator()() {
			delegate->Call();
		}
	private:
		class IDelegateHolder {
		public:
			/**
			*
			*/
			IDelegateHolder() {}
			/**
			*
			*/
			virtual ~IDelegateHolder() {}
			/**
			*
			*/
			virtual void Call() = 0;
		};

		class DelegateHolder1 : public IDelegateHolder{
			typedef void (*FunctionPtr)();
			FunctionPtr function;
		public:
			DelegateHolder1(FunctionPtr fp):function(fp) {
			}
			virtual ~DelegateHolder1() {
				function = NULL;
			}
			void Call() {
				function();
			}
		};

		template<typename T>
		class DelegateHolder2 : public IDelegateHolder{
			typedef void (T::*FunctionPtr)();
			T* instance;
			FunctionPtr function;
		public:
			DelegateHolder2(T* class_,  FunctionPtr fp):instance(class_), function(fp) {
			}
			virtual ~DelegateHolder2() {
				delete instance;
				instance = NULL;
				function = NULL;
			}
			void Call() {
				(instance->*function)();
			}
		};

		IDelegateHolder* delegate;
	};

	template<typename A1>
	class Delegate1 {
	public:
		Delegate1() {
		}
		Delegate1(void (*fp)(A1 a1)) {
			delegate = new DelegateHolder1(fp);
		}
		template < typename  T>
		Delegate1(T* class_, void (T::*method)(A1 a1)) {
			delegate = new DelegateHolder2<T>(class_, method);
		}
		~Delegate1() {
			delete delegate;
		}

		void Call(A1 a) {
			delegate->Call(a);
		}

	private:
		class IDelegateHolder {
		public:
			IDelegateHolder() {}
			virtual ~IDelegateHolder() {}
			virtual void Call(A1 a) = 0;
		};

		class DelegateHolder1 : public IDelegateHolder{
			typedef void (*FunctionPtr)(A1 a);
			FunctionPtr function;
		public:
			DelegateHolder1(FunctionPtr fp):function(fp) {
			}
			virtual ~DelegateHolder1() {
				function = NULL;
			}
			void Call(A1 a) {
				function(a);
			}
		};

		template<typename T>
		class DelegateHolder2 : public IDelegateHolder{
			typedef void (T::*FunctionPtr)(A1 a);
			T* instance;
			FunctionPtr function;
		public:
			DelegateHolder2(T* class_,  FunctionPtr fp):instance(class_), function(fp) {
			}
			virtual ~DelegateHolder2() {
				delete instance;
				instance = NULL;
				function = NULL;
			}
			void Call(A1 a) {
				(instance->*function)(a);
			}
		};

		IDelegateHolder * delegate;
	};

	template<typename A1, typename A2>
	class Delegate2 {
	public:
		Delegate2() :delegate(NULL){
		}
		Delegate2(const Delegate2 & fp) :delegate(NULL){
			delegate = fp.delegate;
		}
		Delegate2(void (*fp)(A1 a1, A2 a2)):delegate(NULL) {
			delegate = new DelegateHolder1(fp);
		}
		template < typename  T>
		Delegate2(T* class_, void (T::*method)(A1 a1, A2 a2)):delegate(NULL) {
			delegate = new DelegateHolder2<T>(class_, method);
		}
		~Delegate2() {
			delete delegate;
		}

		void Call(A1 a1, A2 a2) {
			delegate->Call(a1, a2);
		}

	private:
		class IDelegateHolder {
		public:
			IDelegateHolder() {}
			virtual ~IDelegateHolder() {}
			virtual void Call(A1 a1, A2 a2) = 0;
		};

		class DelegateHolder1 : public IDelegateHolder{
			typedef void (*FunctionPtr)(A1 a1, A2 a2);
			FunctionPtr function;
		public:
			DelegateHolder1(FunctionPtr fp):function(fp) {
			}
			virtual ~DelegateHolder1() {
				function = NULL;
			}
			void Call(A1 a1, A2 a2) {
				function(a1, a2);
			}
		};

		template<typename T>
		class DelegateHolder2 : public IDelegateHolder{
			typedef void (T::*FunctionPtr)(A1 a1, A2 a2);
			T* instance;
			FunctionPtr function;
		public:
			DelegateHolder2(T* class_,  FunctionPtr fp):instance(class_), function(fp) {
			}
			virtual ~DelegateHolder2() {
				delete instance;
				instance = NULL;
				function = NULL;
			}
			void Call(A1 a1, A2 a2) {
				(instance->*function)(a1, a2);
			}
		};

		IDelegateHolder * delegate;
	};

	template<typename A1, typename A2, typename A3>
	class Delegate3 {
	public:
		Delegate3() {
		}
		Delegate3(void (*fp)(A1 a1, A2 a2, A3 a3)) {
			delegate = new DelegateHolder1(fp);
		}
		template < typename  T>
		Delegate3(T* class_, void (T::*method)(A1 a1, A2 a2, A3 a3)) {
			delegate = new DelegateHolder2<T>(class_, method);
		}
		~Delegate3() {
			delete delegate;
		}

		void Call(A1 a1, A2 a2, A3 a3) {
			delegate->Call(a1, a2, a3);
		}

	private:
		class IDelegateHolder {
		public:
			IDelegateHolder() {}
			virtual ~IDelegateHolder() {}
			virtual void Call(A1 a1, A2 a2, A3 a3) = 0;
		};

		class DelegateHolder1 : public IDelegateHolder{
			typedef void (*FunctionPtr)(A1 a1, A2 a2, A3 a3);
			FunctionPtr function;
		public:
			DelegateHolder1(FunctionPtr fp):function(fp) {
			}
			virtual ~DelegateHolder1() {
				function = NULL;
			}
			void Call(A1 a1, A2 a2, A3 a3) {
				function(a1, a2, a3);
			}
		};

		template<typename T>
		class DelegateHolder2 : public IDelegateHolder{
			typedef void (T::*FunctionPtr)(A1 a1, A2 a2, A3 a3);
			T* instance;
			FunctionPtr function;
		public:
			DelegateHolder2(T* class_,  FunctionPtr fp):instance(class_), function(fp) {
			}
			virtual ~DelegateHolder2() {
				delete instance;
				instance = NULL;
				function = NULL;
			}
			void Call(A1 a1, A2 a2, A3 a3) {
				(instance->*function)(a1, a2, a3);
			}
		};

		IDelegateHolder * delegate;
	};
	template<typename A1, typename A2, typename A3, typename A4>
	class Delegate4 {
	public:
		Delegate4() {
		}
		Delegate4(void (*fp)(A1 a1, A2 a2, A3 a3, A4 a4)) {
			delegate = new DelegateHolder1(fp);
		}
		template < typename  T>
		Delegate4(T* class_, void (T::*method)(A1 a1, A2 a2, A3 a3, A4 a4)) {
			delegate = new DelegateHolder2<T>(class_, method);
		}
		~Delegate4() {
			delete delegate;
		}

		void Call(A1 a1, A2 a2, A3 a3, A4 a4) {
			delegate->Call(a1, a2, a3, a4);
		}

	private:
		class IDelegateHolder {
		public:
			IDelegateHolder() {}
			virtual ~IDelegateHolder() {}
			virtual void Call(A1 a1, A2 a2, A3 a3, A4 a4) = 0;
		};

		class DelegateHolder1 : public IDelegateHolder{
			typedef void (*FunctionPtr)(A1 a1, A2 a2, A3 a3, A4 a4);
			FunctionPtr function;
		public:
			DelegateHolder1(FunctionPtr fp):function(fp) {
			}
			virtual ~DelegateHolder1() {
				function = NULL;
			}
			void Call(A1 a1, A2 a2, A3 a3, A4 a4) {
				function(a1, a2, a3, a4);
			}
		};

		template<typename T>
		class DelegateHolder2 : public IDelegateHolder{
			typedef void (T::*FunctionPtr)(A1 a1, A2 a2, A3 a3, A4 a4);
			T* instance;
			FunctionPtr function;
		public:
			DelegateHolder2(T* class_,  FunctionPtr fp):instance(class_), function(fp) {
			}
			virtual ~DelegateHolder2() {
				delete instance;
				instance = NULL;
				function = NULL;
			}
			void Call(A1 a1, A2 a2, A3 a3, A4 a4) {
				(instance->*function)(a1, a2, a3, a4);
			}
		};

		IDelegateHolder * delegate;
	};

}
#endif