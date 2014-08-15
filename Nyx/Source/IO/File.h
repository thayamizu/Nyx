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
#ifndef NYX_CORE_INCLUDED_FILE_H_
#define NYX_CORE_INCLUDED_FILE_H_
#include "Utility/NonCopyable.h"
#include "FileUtility.h"

namespace nyx {

	///ファイル入出力
	class file : private noncopyable
	{
	public:
		/**
		*
		*/
		file();
		/**
		*
		*/
		file(const std::wstring&  name, FILE_ACCESS_ATTRIBUTE attr = FILE_ACCESS_ATTRIBUTE_READ_WRITE);
		/**
		*
		*/
		~file();
		/**
		*
		*/
		bool open(const std::wstring&, FILE_ACCESS_ATTRIBUTE attr = FILE_ACCESS_ATTRIBUTE_READ_WRITE);
		/**
		*
		*/
		bool close();
		/**
		*
		*/
		uint64_t get_current_position() const ;

		/**
		*
		*/
		file_handle get_handle();
		
		/**
		*
		*/
		uint64_t get_size() const;
		
		/**
		*
		*/
		std::wstring get_file_name() const;
		
		/**
		*
		*/
		uint64_t read(void* buffer, uint64_t size);
		
		/**
		*
		*/
		uint64_t write(void* buffer, uint64_t size);
		
		/**
		*
		*/
		uint64_t seek(long offSet);
		
		/**
		*
		*/
		uint64_t seek_begin(long offSet);
		
		/**
		*
		*/
		uint64_t seek_end(long offSet);
		
		/**
		*
		*/
		bool is_opened();

		/**
		*
		*/			
		bool flush();

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};	

}
#endif