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
#ifndef NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_IAUDIO_MANAGER_H_

namespace Nyx {

	///オーディオマネージャインタフェース
	class IAudioManager {
	public:
		/**
		* デストラクタ
		*/
		virtual ~IAudioManager() {}

		/**
		* 指定したインデックスの曲を再生
		* @param bool インデックス
		*/
		virtual void Play(size_t index) = 0;

		/**
		* すべての曲を再生
		*/
		virtual void PlayAll() = 0;

		/**
		* 指定したインデックスの曲を停止
		* @param bool インデックス
		*/
		virtual void Stop(size_t index) = 0;

		/**
		* すべての曲を停止
		*/
		virtual void StopAll() = 0;

		/**
		* 指定したインデックスの曲をレジュームする
		* @param bool インデックス
		*/
		virtual void Resume(size_t index) = 0;

		/**
		* すべての曲をレジューム
		*/
		virtual void ResumeAll() = 0;

		/**
		*指定したインデックスの曲をリセット
		* 再生中の曲を止めたうえで、先頭まで巻戻します
		* @param bool インデックス
		*/
		virtual void Reset(size_t index) = 0;

		/**
		* すべての曲をリセット.
		* 再生中の曲を止めたうえで、先頭まで巻戻します
		*/
		virtual void ResetAll() = 0;

		/**
		* 指定したインデックスの曲をポーズさせる
		* @param size_t インデックス
		* @param bool ポーズするならtrue
		*/
		virtual void SetPause(size_t index, bool) = 0;

		/**
		* すべての曲をポーズ
		* @param bool ポーズするならtrue
		*/
		virtual void SetPauseAll(bool) = 0;

		/**
		* マスターボリュームを取得
		* @return int マスターボリューム値
		*/
		virtual int GetMasterVolume() const = 0;

		/**
		* マスターボリュームを設定
		* @param int マスターボリューム値
		*/
		virtual  void SetMasterVolume(int v) = 0;
	};
}
#endif