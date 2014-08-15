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
#ifndef NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#define NYX_CORE_INCLDUED_DIRECTSOUND_AUDIO_BUFFER_H_
#include "DirectSoundDefinition.h"
#include "Sound/IAudioBuffer.h"

namespace nyx {
	///オーディオバッファのDirectSoundによる実装
	class dsound_audio_buffer : public iaudio_buffer{
	public:
		/**
		* コンストラクタ
		*/
		explicit dsound_audio_buffer();

		/**
		* コンストラクタ
		* @param const AudioBufferDesc オーディオバッファ記述子
		* @param const DirectSound DirectSoundオブジェクト
		* @param std::wstring ファイル名
		*/
		virtual void load(const audio_buffer_desc& bufferDesc, const dsound_ptr ds);


		/**
		* 再生
		*/
		virtual void play(bool isLoop);


		/**
		* 停止
		*/
		virtual void stop();


		/**
		* レジューム
		*/
		virtual void resume();


		/**
		* リセット
		*/
		virtual void reset();


		/**
		* ボリュームの設定
		* @param long ボリューム
		*/
		virtual void set_volume(long volume);


		/**
		* ボリュームの取得
		* @return long
		*/
		virtual long get_volume() const;


		/**
		* ステータスコードの取得
		* @return ulong
		*/
		virtual uint64_t get_status() const;


		/**
		*　オーディオバッファにエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		virtual void set_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファのエフェクトをリセットします
		*/
		virtual void reset_effect();


		/**
		* DirectSoundBufferのポインタを返します
		* @return const DirectSoundBufferPtr& DirectSoundBufferのポインタ
		*/
		virtual const dsound_buffer_ptr& get_handle() const;


		/**
		* オーディオバッファの状態の取得
		* @return AudioState
		*/
		virtual audio_state get_audio_state() const;


	protected:
		/**
		* AudioBufferDescからDSBUFFERDESCを構築します
		* @param [out] DSBUFFERDESC
		* @param const AudioBufferDesc&
		*/
		virtual void build_dsound_buffer_desc(DSBUFFERDESC* bufferDesc, WAVEFORMATEX& wfx) = 0;


		/**
		* バッファにWaveデータを書き込みます
		* @param size_t バッファサイズ
		*/
		virtual void write_wave_data() = 0;
	private:	
		/**
		*　オーディオバッファにコーラスエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_chorus_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにディストーションエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_distortion_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにエコーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_echo_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにフランジャーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_flanger_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにガーグルエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_gargle_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにパラメトリックイコライザーエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_parametric_equalizer_effect(const audio_effect_desc& effectDesc);


		/**
		*　オーディオバッファにリバーブエフェクトを設定します
		* @param const AudioEffectDesc& オーディオエフェクト記述子
		*/
		void set_reverb_effect(const audio_effect_desc& effectDesc);
	private:
		bool isLoop_;
		dsound_buffer_ptr soundBuffer_;
	};
}
#endif