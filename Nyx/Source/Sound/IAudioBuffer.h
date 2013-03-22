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
#ifndef NYX_CORE_INCLUDED_IAUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_IAUDIO_BUFFER_H_

namespace Nyx {
	///オーディオバッファインタフェース
	class IAudioBuffer {
	public:
		IAudioBuffer() :pan(0), volume(0), isLooping(false), isPlaying(false), isPause(false){}
		virtual ~IAudioBuffer() {}
		/**
		*　再生
		*/
		virtual void Play() = 0;
		/**
		*　停止
		*/
		virtual void Stop() = 0;
		/**
		*　レジューム
		*/
		virtual void Resume() = 0;
		/**
		*　リセット
		*/
		virtual void Reset()  = 0; 

		/**
		* ループ再生かどうか判定
		* @return bool　ループ再生ならtrue
		*/
		bool IsLooping() const {
			return isLooping;
		} 

		/**
		* 再生中かどうか
		* @return bool 再生中ならtrue
		*/
		bool IsPlaying() const  {
			return isPlaying;
		}

		/**
		* ポーズ中かどうか
		* @return bool ポーズ中ならtrue
		*/
		bool IsPause() const {
			return isPause;
		}

		/**
		* ループ再生するかどうかを設定
		* @param bool ループ再生ならtrue
		*/
		void SetLooping(bool loop) {
			isLooping = loop;
		}

		/**
		* 再生中かどうか
		* @param bool 再生中ならtrue
		*/
		void SetPlaying(bool play) {
			isPlaying = play;
		}

		/**
		* ポーズ中かどうか
		* @param bool ポーズ中ならtrue
		*/
		void SetPause(bool pause) {
			isPause = pause;
		}

		/**
		* パンを設定する
		* @param int パン
		*/
		void SetPan(int p) {
			pan = p;
		}

		/**
		* パンを取得する
		* @return long パン
		*/
		int GetPan()  {
			return pan;
		}

		void SetVolume(int v) {
			volume = v;
		}
		int GetVolume() const {
			return volume;
		}
	private:
		long pan;
		int volume;
		bool isPlaying;///< 再生中
		bool isLooping;///< ループ
		bool isPause;///< ポーズ
	};
}
#endif