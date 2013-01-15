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
#ifndef NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_
#define NYX_CORE_INCLUDED_DIRECT_SOUND_STREAMING_AUDIOBUFFER_H_

namespace Nyx {
	using std::shared_ptr;
	class AudioBuffer;
	///ストリーミンブオーディオバッファのDirectSoundによる実装
	class DirectSoundStreamingAudioBuffer : public AudioBuffer
	{
	public:
		//---------------------------------------------------------------------------
		//構築・破壊
		//---------------------------------------------------------------------------
		/**
		* コンストラクタ
		* @param DirectSound DirectSoundオブジェクト
		* @param tstring ファイル名
		*/
		DirectSoundStreamingAudioBuffer(DirectSound, tstring fileName);

		/**
		* コンストラクタ
		* @param DirectSound DirectSoundオブジェクト
		* @param shared_ptr<char> waveデータ
		*/
		DirectSoundStreamingAudioBuffer(DirectSound, shared_ptr<char> waveData);

		/**
		* デストラクタ
		*/
		~DirectSoundStreamingAudioBuffer();

		//---------------------------------------------------------------------------
		//再生・停止
		//---------------------------------------------------------------------------
		/**
		* 再生 
		*/
		void Play();

		/**
		* 停止
		*/
		void Stop();

		/**
		* レジューム
		*/
		void Resume();

		/**
		* リセット
		*/
		void Reset();

		//---------------------------------------------------------------------------
		//情報の取得
		//---------------------------------------------------------------------------
		/**
		* パンの取得
		* @return long パン
		*/
		long GetPan() const ;

		/**
		* パンの設定
		* @param int パン
		*/
		void SetPan(int pan_);

		/**
		* ボリュームの取得
		* @return long ボリューム
		*/
		long GetVolume() const ;

		/**
		* ボリュームの設定
		* @param ボリューム
		*/
		void SetVolume(int v);

		/*
		* 通知スレッドの起動関数
		* @param void* パラメータ
		* @return ulong
		*/
		friend ulong __stdcall NotifyThreadProc(void*);

	private:
		/**
		* 通知スレッド
		*/
		void NotifyThread();

		/**
		* バッファ書き込み
		* @param オフセット位置
		* @return HRESULT 書き込み結果
		*/
		HRESULT WriteToBuffer(ulong offset);

		static const int NotifyEventNums = 4; ///< 通知イベントの数

	private:
		long pan;	///< パン
		long volume;///< ボリューム
		bool isEOF; ///< Waveデータの終端
		ulong cursorPlay;///< 再生カーソル
		ulong cursorRead;///< 読み込みカーソル
		ulong waveSize;  ///< WAVEデータのサイズ
		ulong bufferSize;///< バッファサイズ
		ulong notifySize;///< 通知イベントが発生するサイズ
		ulong nextOffset;///< 次に書き込むオフセット位置
		shared_ptr<uchar> waveData;///<WAVEデータ
		HANDLE notifyEvent[NotifyEventNums]; ///< 通知イベントのハンドル
		HANDLE notifyThreadHandle;///< 通知スレッドのハンドル
		DirectSoundBuffer soundBuffer;///<DirectSoundセカンダリバッファ
	};
}
#endif