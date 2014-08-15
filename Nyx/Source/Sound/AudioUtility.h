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

namespace nyx {
	///オーディオユーティリティ

	class AudioUtility {
	public:
		///フォーカスタイプ
		enum FOCUS_TYPE {
			FOCUS_TYPE_DEFAULT,
			FOCUS_TYPE_GLOBAL,
			FOCUS_TYPE_STICKY,
			FOCUS_TYPE_NUM,
		};


		///オーディオバッファタイプ
		enum AUDIO_BUFFER_TYPE{
			AUDIO_BUFFER_TYPE_STATIC,
			AUDIO_BUFFER_TYPE_STATIC_3D,
			AUDIO_BUFFER_TYPE_STREAMING,
			AUDIO_BUFFER_TYPE_STREAMING_3D,
			AUDIO_BUFFER_TYPE_NUM,
		};


		///オーディオエフェクトタイプ
		enum AUDIO_EFFECT_TYPE {
			AUIO_EFFECT_TYPE_CHORUS,
			AUDIO_EFFECT_TYPE_DISTORTION,
			AUDIO_EFFECT_TYPE_ECHO,
			AUDIO_EFFECT_TYPE_FLANGER,
			AUDIO_EFFECT_TYPE_GARGLE,
			AUDIO_EFFECT_TYPE_PARAMETRIC_EQUALIZER,
			AUDIO_EFFECT_TYPE_REVERB,
			AUDIO_EFFECT_TYPE_RESET,
			AUDIO_EFFECT_TYPE_NUM
		};

		///利用可能API
		enum AUDIO_API_TYPE {
			AUDIO_API_DIRECT_SOUND,
			AUDIO_API_TYPE_NUM
		};


		///デフォルトビットレート
		static const double DEFAULT_BIT_RATE;


		///デフォルトサンプリングレート
		static const double DEFAULT_SAMPLING_RATE;


		/**
		* ボリュームをデシベルに変換します
		* @param long ボリューム（1 ~ 100)
		* @return long デシベル
		*/
		static long volume_to_decibel(long volume);


		/**
		* デシベルをボリュームに変換します
		* @param  long ボリューム
		* @return long デシベル
		*/
		static long decibel_to_volume(long decibel);


		/**
		* WaveファイルヘッダからWaveフォーマット情報を構築します
		* @param[out] WAVEFORMATEX    Waveファイルフォーマット
		* @param const WaveFileHeader Waveファイルヘッダ
		*/
		static void build_wav_format_ex(WAVEFORMATEX* wfx, const wav_file_header& waveHeader);

	};
	///オーディオ初期化記述子
	struct audio_desc {
		uint64_t              reserved; ///< 予約領域
		HWND				  handle;   ///< 初期化ハンドル
		AudioUtility::AUDIO_API_TYPE apiType;  ///< APIの種類
	};


	///オーディオバッファ記述子
	struct audio_buffer_desc {
		uint64_t                 reserved;  ///< 予約領域
		GUID                     algorithm; ///< 3Dバッファの再生アルゴリズム
		AudioUtility::AUDIO_BUFFER_TYPE bufferType;///< オーディオバッファのバッファタイプ
		AudioUtility::FOCUS_TYPE  focusType; ///< オーディオバッファのフォーカスタイプ
		wav_file_header           waveFormat;
	};


	///オーディオエフェクト記述子
	struct audio_effect_desc {
		uint64_t reserved;///< 予約領域
		AudioUtility::AUDIO_EFFECT_TYPE effectType;///< エフェクトの種類
	};


	///オーディオステータス
	struct audio_state {
		bool isPlaying;  ///< 再生しているかどうか
		bool isLooping;  ///< ループ再生かどうか
		bool isBufferLost;///< オーディオバッファがロストしてるか
	};
}

#endif