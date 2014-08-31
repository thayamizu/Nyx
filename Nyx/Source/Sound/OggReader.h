#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_
#include "SoundReader.h"
#include "vorbis/vorbisfile.h"

namespace nyx {
	struct wav_file_header;
	///oggファイルリーダ
	class ogg_reader : public sound_reader {
	public:
		/**
		* コンストラクタ
		*/
		ogg_reader();


		/**
		* コンストラクタ
		* @param const std::wstring& ファイル名
		*/
		ogg_reader(const std::wstring& fileName);

		/**
		* デストラクタ
		*/
		~ogg_reader();

		/**
		* WAVファイルを開く
		* @param const std::wstring& ファイル名
		*/
		void open(const std::wstring& fileName);
		
		/**
		* WAVファイルを閉じます
		*/
		void close();
		
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
		wav_file_header header_;
		OggVorbis_File* vorbisFile_;
		vorbis_info *  vorbisInfo_;

	};
}

#endif