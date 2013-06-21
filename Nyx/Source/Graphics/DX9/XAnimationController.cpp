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
#include "PCH/PCH.h"
#include "Debug/Assert.h"
#include "Debug/DebugOutput.h"
#include "Graphics/DX9/XAnimationController.h"


namespace Nyx {
	namespace DX9 {
		XAnimationController::XAnimationController() {
			currentAnimationID  = 0;
			previousAnimationID = 0;

			animationSets.reserve(10);
			animationController=NULL;
		}


		//--------------------------------------------------------------------------------------------
		// アニメーションコントローラを設定
		bool XAnimationController::SetAnimationController( D3DXAnimationController animationController ) {
			if (animationController == NULL) {return false;}

			//アニメーションセット分だけvectorをリザーブしておく
			int num = animationController->GetNumAnimationSets();
			animationSets.reserve(num);

			//アニメーションセットを初期化
			for (int i=0; i < num; i++) {
				AnimationSetDesc animSet;
				animSet.loopTime   = 0;
				animSet.shiftTime  = 0;
				animSet.trackSpeed = 1;
				animSet.currentWeightTime = 0;
				animationController->GetAnimationSet(i, &animSet.animationSet);
				animationSets.push_back(animSet);
			}	

			//アニメーションコントローラを登録
			this->animationController = animationController;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// アニメーションコントローラを取得
		bool XAnimationController::GetAnimationController( D3DXAnimationController *animationController ) {
			if (this->animationController == NULL) {
				return false;
			}

			animationController = &(this->animationController);
			return true;
		}

		//---------------------------------------------------------------------------------------
		// ループ時間を設定
		bool XAnimationController::SetLoopTime( uint animID, float time ) {
			// 指定のアニメーションIDの存在をチェック
			if( animationSets.size() <= animID ) {
				return false;
			}

			// トラックスピード調節値を算出
			double defTime = animationSets[animID].animationSet->GetPeriod();
			animationSets[animID].loopTime = time;
			animationSets[animID].trackSpeed = defTime / time;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// 動作開始にかかる時間を設定
		bool XAnimationController::SetShiftTime( uint animID, float interval ) {
			// 指定のアニメーションIDの存在をチェック
			if( animationSets.size() <= animID ) {return false;}

			// シフト時間を登録
			animationSets[animID].shiftTime = interval;
			return true;
		}

		//---------------------------------------------------------------------------------------
		// アニメーションを切り替え
		bool XAnimationController::ChangeAnimation( uint animID ) {
			// 指定のアニメーションIDの存在をチェック
			if( animationSets.size() <= animID ) {return false;}

			// 異なるアニメーションであるかをチェック
			if( currentAnimationID == animID ) {return false;}

			// 現在のアニメーションセットの設定値を取得
			D3DXTRACK_DESC TD;    // トラック
			animationController->GetTrackDesc(0, &TD );

			// 今のアニメーションをトラック1に移行し
			// トラックの設定値も移行
			animationController->SetTrackAnimationSet( 1, animationSets[currentAnimationID].animationSet );
			animationController->SetTrackDesc( 1, &TD );

			// 新しいアニメーションセットをトラック0に設定
			animationController->SetTrackAnimationSet( 0, animationSets[animID].animationSet );

			// トラック0のスピードの設定
			animationController->SetTrackSpeed( 0, animationSets[animID].trackSpeed );

			// トラックの合成を許可
			animationController->SetTrackEnable( 0, true );
			animationController->SetTrackEnable( 1, true );

			// ウェイト時間を初期化
			animationSets[animID].currentWeightTime = 0.0f;

			// 現在のアニメーション番号を切り替え
			previousAnimationID = currentAnimationID;
			currentAnimationID = animID;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// アニメーションを更新
		bool XAnimationController::AdvanceTime( float time ) {
			// 合成中か否かを判定
			animationSets[currentAnimationID].currentWeightTime += time;
			if( animationSets[currentAnimationID].currentWeightTime <= animationSets[currentAnimationID].shiftTime ) {
				// 合成中。ウェイトを算出
				float weight = animationSets[currentAnimationID].currentWeightTime / animationSets[currentAnimationID].shiftTime;
				// ウェイトを登録
				animationController->SetTrackWeight( 0, weight );       // 現在のアニメーション
				animationController->SetTrackWeight( 1, 1 - weight );   // 前のアニメーション
			}
			else {
				// 合成終了中。通常アニメーションをするTrack0のウェイトを最大値に
				animationController->SetTrackWeight( 0, 1.f );       // 現在のアニメーション
				animationController->SetTrackEnable(1, false );      // 前のアニメーションを無効にする
			}

			// 時間を更新
			animationController->AdvanceTime( time, NULL );
			return true;

		}

		//---------------------------------------------------------------------------------------
		// アニメーションセット数を取得
		int XAnimationController::GetNumAnimationSet() {
			return animationSets.size();
		}

	}
}