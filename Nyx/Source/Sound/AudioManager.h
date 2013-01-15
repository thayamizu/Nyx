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
#ifndef NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#include "Sound/IAudioManager.h"

namespace Nyx {
	using std::shared_ptr;
	//前方宣言
	class AudioBuffer;

	enum SoundBufferType
	{
		Static,		///< 静的バッファ
		Static3D,	///< 静的3Dバッファ
		Streaming,	///< ストリーミングバッファ
		Streaming3D, ///< ストリーミング3Dバッファ
		NumSoundBufferType
	};

	///オーディオマネージャ
	class AudioManager : public IAudioManager{
		typedef std::vector< AudioBuffer* > AudioBufferList;
		typedef std::vector< AudioBuffer* >::iterator AudioBufferListIterator;
	public:
		/**
		* デストラクタ
		*/
		virtual ~AudioManager();

		/**
		* 指定したインデックスの曲を再生する
		* @param uint インデックス
		*/
		virtual void Play(uint index);

		/**
		* すべての曲を再生する
		*/
		virtual void PlayAll();

		/**
		* 指定したインデックスの曲を停止
		* @param uint インデックス
		*/
		virtual void Stop(uint index);

		/**
		*すべての曲を停止
		*/
		virtual void StopAll();

		/**
		* 指定したインデックスの曲をレジュームする
		* @param uint インデックス
		*/
		virtual void Resume(uint index);

		/**
		* すべての曲をレジュームする
		*/
		virtual void ResumeAll();

		/**
		* 指定したインデックスの曲をリセット
		* つまり、オーディオをいったん止めて、先頭まで巻戻します。
		* @param uint インデックス
		*/
		virtual void Reset(uint index);

		/**
		* すべての曲をリセットする
		*/
		virtual void ResetAll();

		/**
		*　指定したインデックスをポーズさせる
		* @param uint インデックス
		* @param bool ポーズするならtrue
		*/
		virtual void SetPause(uint index, bool);

		/**
		* すべての曲をポーズさせる
		* @param bool ポーズするならtrue  
		*/
		virtual void SetPauseAll(bool) ;

		/**
		* マスターボリュームを取得
		* @return int マスターボリューム値
		*/
		virtual int GetMasterVolume() const ;

		/**
		* マスターボリュームを設定
		* @param int マスターボリューム値
		*/
		virtual  void SetMasterVolume(int v) ;

		/**
		* オーディオバッファを取得
		* @param uint インデックス
		*/
		virtual AudioBuffer* GetAudioBuffer(uint index);
	protected:
		int masterVolume;///< マスターボリューム
		AudioBufferList audioBufferList;///< オーディオバッファのリスト
	};
}
#endif