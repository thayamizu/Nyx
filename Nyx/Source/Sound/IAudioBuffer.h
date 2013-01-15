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
		*　ループ中かどうか
		*/
		virtual bool IsLooping() const = 0;

		/**
		*　再生中かどうか
		*/
		virtual bool IsPlaying() const = 0;

		/**
		* ポーズ中かどうか
		*/
		virtual bool IsPause() const = 0;

		/**
		*　ポーズするかどうかを設定
		* @param　bool ポーズするならtrue
		*/
		virtual void SetPause(bool) = 0;

		/**
		*　ループするかどうかを設定
		* @param bool ループするならtrue
		*/
		virtual void SetLooping(bool loop) = 0;

		/**
		* 再生中かどうかを設定
		* @param bool 再生中ならtrue
		*/
		virtual void SetPlaying(bool play) = 0;

		/**
		* 再生ボリュームを設定する
		* @param int ボリューム
		*/
		virtual void SetVolume(int v)  = 0;

		/**
		* 再生ボリュームを取得する
		* @return long ボリューム
		*/
		virtual long GetVolume() const    = 0;

		/**
		* パンを設定する
		* @param int パン
		*/
		virtual void SetPan(int pan) = 0;

		/**
		* パンを取得する
		* @return long パン
		*/
		virtual long GetPan() const   = 0;
	};
}
#endif