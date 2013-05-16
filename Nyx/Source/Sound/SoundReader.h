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
		* 音楽ファイルをオープンします
		* @param const std::wstring& ファイル名
		*/
		virtual void Open(const std::wstring& fileName) = 0;
		
		
		/**
		* 読み込みカーソルを指定した位置にセットする
		* @param ulong 読み込みカーソル位置
		*/
		virtual void SetCursor(ulong cursor) = 0;


		/**
		* 読み込みカーソルを取得する
		* @return ulong 読み込みカーソル位置
		*/
		virtual ulong GetCursor() const = 0;


		/**
		* 音楽ファイルから指定したバッファサイズ分だけ読み込む
		* @param size_t バッファサイズ
		*/
		virtual std::shared_ptr<char> Read(size_t size) = 0;
		

		/**
		* ヘッダ情報を取得する
		* @return WaveHeader Waveファイルのヘッダ
		*/
		virtual const WaveFileHeader& ReadHeader() = 0;
	};
}
#endif