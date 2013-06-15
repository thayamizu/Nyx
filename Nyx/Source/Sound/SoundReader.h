#ifndef NYX_CORE_INCLUDED_SOUND_READER_H_
#define NYX_CORE_INCLUDED_SOUND_READER_H_
#include "Object/NonCopyable.h"

namespace Nyx {

	struct WaveFileHeader;
	///サウンドリーダ
	class SoundReader : NonCopyable {
	public:
		/**
		* デストラクタ
		*/
		virtual ~SoundReader() {}
		/**
		* WAVファイルを開く
		* @param const std::wstring& ファイル名
		*/
		virtual void Open(const std::wstring& fileName) =0 ;
		

		/**
		* 読み込みカーソルを指定した位置にセットする
		* @param ulong 読み込みカーソル位置
		*/
		virtual void SetCursor(ulong cursor) =0 ;


		/**
		* 読み込みカーソルを取得する
		* @return ulong 読み込みカーソル位置
		*/
		virtual ulong GetCursor() const = 0;
		
		
		/**
		* Waveファイルヘッダの取得します
		* @return const WaveFileHeader& WAVEファイルヘッダ
		*/
		virtual const WaveFileHeader& ReadHeader() =0 ;


		/**
		* Waveデータを取得します
		* @param size_t  読み込みバイト数
		* @param size_t　実際に読み取ったサイズ
		* @return std::shared_ptr<char> WAVEデータ
		*/
		virtual std::shared_ptr<char> Read(size_t bufferSize, ulong* readSize=nullptr) =0 ;
	};
}
#endif