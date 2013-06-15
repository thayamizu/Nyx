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
#ifndef NYX_CORE_INCLUDED_DIRECTSOUND_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_DIRECTSOUND_AUDIO_MANAGER_H_
#include "Sound/IAudioManager.h"
#include "DirectSoundDefinition.h"

namespace Nyx {
	class IAudioListener;
	///オーディオマネージャのDirectSoundによる実装
	class DirectSoundAudioManager : public IAudioManager{
	public:
		/**
		* コンストラクタ
		*/
		DirectSoundAudioManager();
		
		
		/**
		* コンストラクタ
		* @param AudioDesc オーディオ初期化記述子
		*/
		DirectSoundAudioManager(const AudioDesc& desc);
		
		
		/**
		* オーディオマネージャの初期化します
		* @param AudioDesc オーディオ初期化記述子
		*/
		void Initialize(const AudioDesc& desc);
		

		/**
		* オーディオバッファを生成します
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @return std::shared_ptr<AudioBuffer> オーディオバッファ
		*/
		std::shared_ptr<IAudioBuffer> CreateAudioBuffer(const std::wstring& fileName, const AudioBufferDesc& bufferDesc);	


		/**
		* オーディオリスナーを生成します
		* @return std::shared_ptr<IAudioListener> 
		*/
		std::shared_ptr<IAudioListener> CreateAudioListener();	


		/**
		* Waveファイルをロードしてきます
		* @param const std::wstring ファイル名
		* @param SoundBufferType バッファの種類
		* @return std::shared_ptr<AudioCache> オーディオキャッシュ
		*/
		std::shared_ptr<AudioCache> Load(const std::wstring& fileName, const AudioBufferDesc& bufferDesc);
		

		/**
		* DirectSoundオブジェクトを返します
		* @return const DirectSoundPtr 
		*/
		const DirectSoundPtr GetHandle();
	private:	
		/**
		* Waveファイルからオーディオバッファを生成します
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @return std::shared_ptr<AudioBuffer> オーディオバッファ
		*/
		std::shared_ptr<IAudioBuffer> CreateAudioBufferFromWave(const std::wstring& fileName, const AudioBufferDesc& bufferDesc);	
		
	
		/**
		* Oggファイルからオーディオバッファを生成します
		* @param const std::wstring& ファイル名
		* @param SoundBufferType バッファタイプ
		* @return std::shared_ptr<AudioBuffer> オーディオバッファ
		*/
		std::shared_ptr<IAudioBuffer> CreateAudioBufferFromOgg(const std::wstring& fileName, const AudioBufferDesc& bufferDesc);	
	
		int masterVolume_;	///< マスターボリューム
		DirectSoundPtr directSound_;///< DirectSoundオブジェクト
		DirectSoundPrimaryBufferPtr primaryBuffer_;
	};
}
#endif