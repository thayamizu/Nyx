#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_
#include "SoundReader.h"

namespace Nyx {
	struct WaveFileHeader;
	///oggファイルリーダ
	class OggReader : public SoundReader {
	public:
		/**
		* コンストラクタ
		*/
		OggReader();


		/**
		* コンストラクタ
		* @param const std::wstring& ファイル名
		*/
		OggReader(const std::wstring& fileName);


		/**
		* WAVファイルを開く
		* @param const std::wstring& ファイル名
		*/
		void Open(const std::wstring& fileName);
		

		/**
		* 読み込みカーソルを指定した位置にセットする
		* @param ulong 読み込みカーソル位置
		*/
		void SetCursor(ulong cursor);


		/**
		* 読み込みカーソルを取得する
		* @return ulong 読み込みカーソル位置
		*/
		ulong GetCursor() const;
		
		
		/**
		* Waveファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		const WaveFileHeader& ReadHeader();


		/**
		* Waveデータを取得します
		* @param size_t  読み込みバイト数
		* @param size_t　実際に読み取ったサイズ
		* @return std::shared_ptr<char> WAVEデータ
		*/
		std::shared_ptr<char> Read(size_t bufferSize, ulong* readSize=nullptr);
	private:
		WaveFileHeader header;
	};
}

#endif