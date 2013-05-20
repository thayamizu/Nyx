#ifndef NYX_CORE_INCLUDED_ISTEREO_AUDIO_BUFFER_H_
#define NYX_CORE_INCLUDED_ISTEREO_AUDIO_BUFFER_H_

namespace Nyx {
	
	///ステレオサウンドの機能を持つオーディオバッファインタフェース
	class IStereoAudioBuffer {
	public:
		virtual ~IStereoAudioBuffer() {}
		/**
		* オーディオバッファのパン値を設定します
		* @param long パン
		*/
		virtual void SetPan(long pan) = 0;


		/**
		* オーディオバッファのパン値を取得します
		* @return long 
		*/
		virtual long GetPan()= 0;

	};
}
#endif

