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
#include "IO/IFile.h"
namespace Nyx
{
	using std::unique_ptr;
	using std::shared_ptr;
	///パックされたファイル
	class PackedFile : public IFile
	{
	public:
		//-------------------------------------------------------
		//構築・破壊
		//-------------------------------------------------------
		PackedFile(const wchar_t*  name, AccessAttribute attr=ReadMode);
		~PackedFile();

		//-----------------------------------------------------
		//値の取得
		//-----------------------------------------------------
		/**
		* ヘッダサイズの取得
		* @return ulong
		*/
		ulong GetHeaderSize();
		/**
		* ヘッダサイズの取得
		* @return ヘッダサイズ
		*/
		uint GetFileNum();

		/**
		* ヘッダサイズの取得
		* @return ヘッダサイズ
		*/
		ulong GetFileSize(uint index);
		/**
		* index番目にパックされたデータの取得
		*@param index
		*@return shared_ptr<char> 
		*/
		shared_ptr<char> GetFileData(uint index);

		//-----------------------------------------------------
		//ファイル操作
		//-----------------------------------------------------
		/**
		*
		*/
		bool Open(const std::wstring&  name, AccessAttribute attr=ReadMode);
		bool Close();
		bool Flush();

		/**
		*
		*/
		ulong GetCurrentPosition() const;

		/**
		*
		*/ulong GetSize() const;

		/**
		*
		*/
		std::wstring GetFileName() const;


		/**
		*
		*/
		ulong Read(void* buffer, ulong size);
		
		/**
		*
		*/
		ulong Write(void* buffer, ulong size);
		/**
		*
		*/
		ulong Seek(long offSet);

		/**
		*
		*/
		ulong SeekBegin(long offSet);

		/**
		*
		*/
		ulong SeekEnd(long offSet);

		/**
		*
		*/
		bool IsOpened();

	private:
		struct PImpl;
		std::unique_ptr<PImpl> pimpl_;
	};

}

#endif