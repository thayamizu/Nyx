#ifndef NYX_CORE_INCLUDED_COM_PTR_H_
#define NYX_CORE_INCLUDED_COM_PTR_H_


namespace nyx
{
	namespace detail
	{
		template<typename T>
		struct com_ptr_base
		{
			typedef typename std::remove_pointer<T>::type raw_type;
			typedef raw_type const &				const_reference_type;
			typedef raw_type const *				const_pointer_type;
			typedef raw_type &						reference_type;
			typedef raw_type *						pointer_type;
		};

	}

	template <class T>
	class com_ptr : public detail::com_ptr_base<T>
	{
		static_assert(std::is_base_of<IUnknown, T>::value == true, "T requires base_of IUnkown");

		typedef com_ptr this_type;
		pointer_type rawPointer_;
	public:
		com_ptr()
			:rawPointer_(nullptr)
		{
		}

		com_ptr(T *other, bool add_ref = true)
		:rawPointer_(other)
		{
			if (rawPointer_ != nullptr && add_ref) {
				px->AddRef();
			}
		}

		com_ptr(const com_ptr<T> & other)
			:rawPointer_(other->get())
		{
			if (rawPointer_ != nullptr) {
				rawPointer_->AddRef();
			}
		}

		com_ptr(com_ptr<T> && other)
			:rawPointer_(move(other).get()) {
			other.reset();
		}

		~com_ptr(void)
		{
			if (rawPointer_ != nullptr) {
				rawPointer_->Release();
			}
		}

		friend  bool operator == (com_ptr<T> const & lhs, com_ptr<T> const & rhs);
		friend  bool operator != (com_ptr<T> const & lhs, com_ptr<T> const & rhs);
		bool is_null()
		{
			return rawPointer_ ? false : true;
		}

		operator T*()
		{
			return rawPointer_;
		}

		operator T**()
		{
			return &rawPointer_;
		}

		operator T&()
		{
			return *rawPointer_;
		}

		T& operator*()
		{
			NYX_ASSERT(rawPointer_ != NULL);
			return *rawPointer_;
		}

		T** operator&()
		{
			if (rawPointer_) {
				reset();
			}
			return &rawPointer_;
		}

		T* operator->()
		{
			NYX_ASSERT(rawPointer_ != NULL);
			return rawPointer_;
		}

		T* operator=(T *other)
		{
			if (other == rawPointer_) {
				return rawPointer_;
			}
			if (rawPointer_) {
				reset();
			}

			rawPointer_ = other;
			return rawPointer_;
		}

		com_ptr<T>& operator=(com_ptr<T> & other)
		{
			this_type(other).swap(*this);
			return *this;
		}

		T* get()
		{
			return rawPointer_;
		}

		void reset()
		{
			this_type().swap(*this);
		}

		void reset(T* rhs)
		{
			this_type(rhs).swap(*this);
		}

		void swap(com_ptr<T>& value)
		{
			pointer_type tmp = rawPointer_;
			this->rawPointer_ = value.rawPointer_;
			value.rawPointer_ = tmp;
		}

		bool construct(GUID ClsID, GUID IID = __uuidof(T))
		{
			if (rawPointer_) {
				reset();
			}

			auto hResult = CoCreateInstance(ClsID, NULL, CLSCTX_ALL, IID, (void **)&rawPointer_);
			if (FAILED(hResult)) {
				rawPointer_ = nullptr;
			}

			return SUCCEEDED(hResult);
		}
	};

	template<typename T>
	inline bool operator == (com_ptr<T> const & lhs, com_ptr<T> const & rhs)
	{
		return rhs.rawPointer_ == lhs.rawPointer_;
	}

	template<typename T>
	inline bool operator != (com_ptr<T> const & lhs, com_ptr<T> const & rhs)
	{
		return !(rhs == lhs);
	}

	template<typename T>
	inline void swap(com_ptr<T> & lhs, com_ptr<T>& rhs)
	{
		lhs.swap(rhs);
	}

	template<typename T>
	inline com_ptr<T>&& move(com_ptr<T>&& value)
	{
		return std::move(value);
	}


	template<class T, class U>
	inline com_ptr<T> static_pointer_cast(com_ptr<U> const & p)
	{
		return static_cast<T *>(p.get());
	}


	template<class T, class U>
	inline com_ptr<T> const_pointer_cast(com_ptr<U> const & p)
	{
		return const_cast<T *>(p.get());
	}

	template<class T, class U>
	inline com_ptr<T> dynamic_pointer_cast(com_ptr<U> const & p)
	{
		return dynamic_cast<T *>(p.get());
	}
}

#endif