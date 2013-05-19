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
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目
*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
#ifndef NYX_CORE_INCLUDED_AUDIO_UTILITY_H_
#define NYX_CORE_INCLUDED_AUDIO_UTILITY_H_
#include "WaveFileHeader.h"

namespace Nyx {
	///オーディオユーティリティ
	class AudioUtility {
	public:

		///フォーカスタイプ
		enum FocusType {
			FocusType_DefaultFoucus,
			FocusType_GlobalFocus,
			FocusType_StickyFocus,
			FocusType_FocusTypeNum,
		};


		///オーディオバッファタイプ
		enum BufferType{
			BufferType_StaticAudioBuffer,
			BufferType_Static3DAudioBuffer,
			BufferType_StreamingAudioBuffer,
			BufferType_Streaming3DAudioBuffer,
			BufferType_BufferTypeNum,
		};


		///オーディオエフェクトタイプ
		enum EffectType {
			EffectType_Chorus,
			EffectType_Distortion,
			EffectType_Echo,
			EffectType_Flanger,
			EffectType_Gargle,
			EffectType_ParametricEqualizer,
			EffectType_Reverb,
			EffectType_Reset,
			EffectType_EffectTypeNum
		};

		///利用可能API
		enum APIType {
			APIType_DirectSound,
			APIType_APITypeNum
		};


		///デフォルトビットレート
		static const double DefaultBitRate;


		///デフォルトサンプリングレート
		static const double DefaultSamplingRate;

		
		/**
		* ボリュームをデシベルに変換します
		* @param long ボリューム（1 ~ 100)
		* @return long デシベル
		*/
		static long VolumeToDecibel(long volume);


		/**
		* デシベルをボリュームに変換します
		* @param  long ボリューム
		* @return long デシベル
		*/
		static long DecibelToVolume(long decibel);


		/**
		* WaveファイルヘッダからWaveフォーマット情報を構築します
		* @param[out] WAVEFORMATEX    Waveファイルフォーマット
		* @param const WaveFileHeader Waveファイルヘッダ
		*/
		static void BuildWaveFormatEx(WAVEFORMATEX* wfx, const WaveFileHeader& waveHeader);
	private:
		AudioUtility();//生成禁止
	};


	///オーディオ初期化記述子
	struct AudioDesc {
		ulong                 reserved; ///< 予約領域
		HWND				  handle;   ///< 初期化ハンドル
		AudioUtility::APIType apiType;  ///< APIの種類
	};


	///オーディオバッファ記述子
	struct AudioBufferDesc {
		ulong                    reserved;  ///< 予約領域
		GUID                     algorithm; ///< 3Dバッファの再生アルゴリズム
		AudioUtility::BufferType bufferType;///< オーディオバッファのバッファタイプ
		AudioUtility::FocusType  focusType; ///< オーディオバッファのフォーカスタイプ
		WaveFileHeader           waveFormat;
	};


	///オーディオエフェクト記述子
	struct AudioEffectDesc {
		ulong reserved;///< 予約領域
		AudioUtility::EffectType effectType;///< エフェクトの種類
	};


	///オーディオステータス
	struct AudioState {
		bool isPlaying;  ///< 再生しているかどうか
		bool isLooping;  ///< ループ再生かどうか
		bool isBufferLost;///< オーディオバッファがロストしてるか
	};
}

#endif