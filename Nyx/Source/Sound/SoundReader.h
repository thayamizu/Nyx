#ifndef NYX_CORE_INCLUDED_SOUND_READER_H_
#define NYX_CORE_INCLUDED_SOUND_READER_H_
#include "Utility/NonCopyable.h"
#include "WaveFileHeader.h"

namespace nyx {

	struct wav_file_header;
	///サウンドリーダ
	class sound_reader : noncopyable {
	public:
		/**
		* デストラクタ
		*/
		virtual ~sound_reader() {}
		/**
		* WAVファイルを開く
		* @param const std::wstring& ファイル名
		*/
		virtual void open(const std::wstring& fileName) =0 ;
		

		/**
		* 読み込みカーソルを指定した位置にセットする
		* @param ulong 読み込みカーソル位置
		*/
		virtual void set_cursor(uint64_t cursor) =0 ;


		/**
		* 読み込みカーソルを取得する
		* @return ulong 読み込みカーソル位置
		*/
		virtual uint64_t get_cursor() const = 0;
		
		
		/**
		* Waveファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		virtual const wav_file_header& read_header() =0 ;


		/**
		* Waveデータを取得します
		* @param size_t  読み込みバイト数
		* @param size_t　実際に読み取ったサイズ
		* @return std::shared_ptr<char> WAVEデータ
		*/
		virtual std::shared_ptr<char> read(size_t bufferSize, uint64_t* readSize=nullptr) =0 ;
	};
}
#endif