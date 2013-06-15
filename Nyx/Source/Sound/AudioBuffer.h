#ifndef NYX_CORE_INCLUDED_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_AUDIO_BUFFER_H_

namespace Nyx
{
	class IAudioBuffer;
	struct AudioState;
	struct AudioBufferDesc;

	///オーディオバッファ
	class AudioBuffer {
	public:
		/**
		* コンストラクタ
		*/
		explicit AudioBuffer(std::shared_ptr<IAudioBuffer> audioBuffer);
		

		/**
		*　オーディオバッファを再生します
		*/
		void Play(bool isLoop = false);


		/**
		*　オーディオバッファを停止します
		*/
		void Stop();


		/**
		*　オーディオバッファをレジュームします
		*/
		void Resume();


		/**
		*　オーディオバッファをリセットします
		*/
		void Reset();

		/**
		* オーディオバッファのパン値を設定します
		* @param int パン
		*/
		void SetPan(long pan);


		/**
		* オーディオバッファのパン値を取得します
		* @return long パン
		*/
		long GetPan() const;


		/**
		* オーディオバッファのボリューム値を設定します
		* @return int　ボリューム
		*/
		void SetVolume(long volume);


		/**
		* オーディオバッファのボリューム値を取得します
		* @return int ボリューム
		*/
		long GetVolume() const;

		/**
		*
		*/
		AudioState GetState() const;
		
		/**
		* ファイル名を取得します
		* @return const std::wstring& ファイル名
		*/
		const std::wstring& GetName() const;

	private:
		std::wstring fileName_;
		std::shared_ptr<IAudioBuffer> audio_;
	};
}

#endif