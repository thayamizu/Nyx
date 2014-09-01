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
#ifndef NYX_CORE_INCLUDED_WAVE_READER_H_
#define NYX_CORE_INCLUDED_WAVE_READER_H_
#include "SoundReader.h"

namespace nyx {
	class file;

	///wavファイルリーダ
	class wave_reader : public sound_reader {
	public:
		/**
		* コンストラクタ
		*/
		wave_reader();


		/**
		* コンストラクタ
		* @param const std::wstring& ファイル名
		*/
		wave_reader(const std::wstring& fileName);


		/**
		* WAVファイルを開く
		* @param const std::wstring& ファイル名
		*/
		void open(const std::wstring& fileName);
		

		/**
		* 読み込みカーソルを指定した位置にセットする
		* @param ulong 読み込みカーソル位置
		*/
		void set_cursor(uint64_t cursor);


		/**
		* 読み込みカーソルを取得する
		* @return ulong 読み込みカーソル位置
		*/
		uint64_t get_cursor() const;
		
		
		/**
		* Waveファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		const wav_file_header& read_header();


		/**
		* Waveデータを取得します
		* @param size_t  読み込みバイト数
		* @param size_t　実際に読み取ったサイズ
		* @return std::shared_ptr<char> WAVEデータ
		*/
		std::shared_ptr<char> read(size_t bufferSize, uint64_t* readSize=nullptr);
	private:
		bool isReadHeader_;             ///< ヘッダを読み込んでいるか
		char align_[3];                 ///< アライメント調整
		uint64_t cursor_;                  ///< カーソル
		std::wstring   fileName_;       ///< ファイル名
		std::shared_ptr<file> waveFile_;///< Waveファイル
		wav_file_header waveHeader_;     ///< Waveファイルヘッダ
	};
}
#endif
