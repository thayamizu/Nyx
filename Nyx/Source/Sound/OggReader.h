#ifndef NYX_CORE_INCLUDED_OGG_READER_H_
#define NYX_CORE_INCLUDED_OGG_READER_H_

namespace Nyx {
	///oggファイルリーダ
	class OggReader {
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
		* oggファイルを開く
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
		* ファイルからoggファイルを読み込みます
		* @param std::wstring wavファイル名
		*/
		//void ReadFromFile(const std::wstring& fileName);


		/**
		* oggファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		const WaveFileHeader& ReadHeader();


		/**
		* oggデータを取得します
		* @return std::shared_ptr<char> WAVEデータ
		*/
		std::shared_ptr<char> Read(size_t bufferSize);
	private:
	};
}

#endif