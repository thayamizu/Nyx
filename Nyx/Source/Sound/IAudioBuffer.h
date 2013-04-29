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
		*　オーディオバッファを再生します
		*/
		virtual void Play() = 0;


		/**
		*　オーディオバッファを停止します
		*/
		virtual void Stop() = 0;
		
		
		/**
		*　オーディオバッファをレジュームします
		*/
		virtual void Resume() = 0;
		
		
		/**
		*　オーディオバッファをリセットします
		*/
		virtual void Reset()  = 0; 

		/**
		*　オーディオバッファをフェードインします
		*/
		virtual void FadeIn()  = 0; 

		/**
		*　オーディオバッファをフェードアウトします
		*/
		virtual void FadeOut()  = 0; 
		
		
		/**
		* オーディオバッファのパン値を設定します
		* @param long パン
		*/
		virtual void SetPan(long p)=0;


		/**
		* オーディオバッファのパン値を取得します
		* @return long 
		*/
		virtual long GetPan() const = 0;


		/**
		* オーディオバッファのボリューム値を設定します
		* @return int　ボリューム
		*/
		virtual void SetVolume(long volume) = 0;

		
		/**
		* オーディオバッファのボリュームを取得します
		* @return int ボリューム
		*/
		virtual long GetVolume() const = 0;


		/**
		* オーディオバッファがループ再生中かどうか判定します
		* @return bool　ループ再生ならtrue
		*/
		virtual bool IsLooping() = 0;

		
		/**
		* オーディオバッファが再生中かどうかを判定します
		* @return bool 再生中ならtrue
		*/
		virtual bool IsPlaying() = 0;


		/**
		* オーディオバッファがポーズ中かどうかを判定します
		* @return bool ポーズ中ならtrue
		*/
		virtual bool IsPause() const = 0;
	};
}
#endif