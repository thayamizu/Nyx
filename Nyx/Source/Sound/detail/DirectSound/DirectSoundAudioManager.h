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
	///オーディオマネージャのDirectSoundによる実装
	class DirectSoundAudioManager : public IAudioManager{
	public:
		/**
		* コンストラクタ
		* @param HWND ウインドウハンドル
		*/
		DirectSoundAudioManager(const AudioDesc& desc);


		/**
		* Waveファイルをロードしてきます
		* @param const std::wstring ファイル名
		* @param SoundBufferType バッファの種類
		*/
		void Load(const std::wstring fileName, AudioUtility::AudioBufferType bufferType, size_t& index);
		
		
		const DirectSoundPtr GetHandle();
	private:
		/**
		* Waveファイルからデータを読み込んできます
		* @param const std::wstring ファイル名
		* @param SoundBufferType バッファの種類
		* @return bool 読み込みに成功すればtrue
		*/
		void LoadFromWaveFile(const std::wstring , AudioUtility::AudioBufferType  bufferType, size_t& index);

	private:	
		int masterVolume;	///マスターボリューム
		DirectSoundPtr directSound_;///< DirectSoundオブジェクト
	};
}
#endif