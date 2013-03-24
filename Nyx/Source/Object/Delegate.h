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