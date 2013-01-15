#ifndef NYX_CORE_INCLUDED_IFILE_H_
#define NYX_CORE_INCLUDED_IFILE_H_


namespace Nyx {

	enum AccessAttribute {
		ReadMode  = GENERIC_READ,
		WriteMode = GENERIC_WRITE,
		ReadWriteMode = GENERIC_WRITE | GENERIC_READ,
		None,
	};

	///ファイル入出力
	class IFile
	{
	public:
		virtual ~IFile() {};
		/**
		*
		*/
		virtual bool Open(const tstring & name, AccessAttribute attribute) =  0;

		/**
		*
		*/
		virtual bool Close() = 0;

		/**
		*
		*/
		virtual ulong GetCurrentPosition() const =0;

		/**
		*
		*/
		virtual ulong GetSize() const = 0;

		/**
		*
		*/
		virtual tstring GetFileName() const = 0;

		/**
		*
		*/
		virtual ulong Read(void* buffer, ulong size) = 0;

		/**
		*
		*/
		virtual ulong Write(void* buffer, ulong size) = 0;

		/**
		*
		*/
		virtual ulong Seek(long offSet) = 0;

		/**
		*
		*/
		virtual ulong SeekBegin(long offSet) = 0;

		/**
		*
		*/
		virtual ulong SeekEnd(long offSet) = 0;

		/**
		*
		*/			
		virtual bool Flush() =0;

		/**
		*
		*/
		bool IsOpened();


		static const uchar MaxPath= Nyx::Limits::UCharMax;///<

	};
}
#endif