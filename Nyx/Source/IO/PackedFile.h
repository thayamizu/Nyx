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
#ifndef NYX_CORE_PACKED_FILE_H_
#define NYX_CORE_PACKED_FILE_H_
#include "Utility/NonCopyable.h"

namespace nyx
{
	using std::unique_ptr;
	using std::shared_ptr;
	///パックされたファイル
	NYX_DEPRECATED class packed_file :  private noncopyable
	{
	public:
		//-------------------------------------------------------
		//構築・破壊
		//-------------------------------------------------------
		packed_file(const wchar_t*  name, FILE_ACCESS_ATTRIBUTE attr=FILE_ACCESS_ATTRIBUTE_READ);
		~packed_file();

		//-----------------------------------------------------
		//値の取得
		//-----------------------------------------------------
		/**
		* ヘッダサイズの取得
		* @return ulong
		*/
		uint64_t get_header_size();
		/**
		* ヘッダサイズの取得
		* @return ヘッダサイズ
		*/
		uint32_t get_file_num();

		/**
		* ヘッダサイズの取得
		* @return ヘッダサイズ
		*/
		uint64_t get_file_size(uint32_t index);
		/**
		* index番目にパックされたデータの取得
		*@param index
		*@return shared_ptr<char> 
		*/
		std::shared_ptr<char> get_file_data(uint32_t index);

		//-----------------------------------------------------
		//ファイル操作
		//-----------------------------------------------------
		/**
		*
		*/
		bool open(const std::wstring&  name, FILE_ACCESS_ATTRIBUTE attr=FILE_ACCESS_ATTRIBUTE_READ);
		bool close();
		bool flush();

		/**
		*
		*/
		uint64_t get_current_position() const;

		/**
		*
		*/uint64_t get_size() const;

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

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}

#endif