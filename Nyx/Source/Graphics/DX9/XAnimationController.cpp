/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*�ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g�E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F
*�A�𖳐����Ɉ������Ƃ𖳏��ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA�Еz�A�T�u���C�Z���X�A�����/��
*���͔̔����錠���A����у\�t�g�E�F�A��񋟂��鑊��ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B
*
*��L�̒��쌠�\������і{�����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ����ɋL�ڂ�����̂Ƃ��܂��B
*
*�\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ؂��Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖�*�I�ւ̓K�����A����ь�����N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@
*�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g�E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈����ɂ���Đ������؂̐�
*���A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ����̂Ƃ��܂��B 
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
		// �A�j���[�V�����R���g���[����ݒ�
		bool XAnimationController::SetAnimationController( D3DXAnimationController animationController ) {
			if (animationController == NULL) {return false;}

			//�A�j���[�V�����Z�b�g������vector�����U�[�u���Ă���
			int num = animationController->GetNumAnimationSets();
			animationSets.reserve(num);

			//�A�j���[�V�����Z�b�g��������
			for (int i=0; i < num; i++) {
				AnimationSetDesc animSet;
				animSet.loopTime   = 0;
				animSet.shiftTime  = 0;
				animSet.trackSpeed = 1;
				animSet.currentWeightTime = 0;
				animationController->GetAnimationSet(i, &animSet.animationSet);
				animationSets.push_back(animSet);
			}	

			//�A�j���[�V�����R���g���[����o�^
			this->animationController = animationController;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// �A�j���[�V�����R���g���[�����擾
		bool XAnimationController::GetAnimationController( D3DXAnimationController *animationController ) {
			if (this->animationController == NULL) {
				return false;
			}

			animationController = &(this->animationController);
			return true;
		}

		//---------------------------------------------------------------------------------------
		// ���[�v���Ԃ�ݒ�
		bool XAnimationController::SetLoopTime( uint animID, float time ) {
			// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
			if( animationSets.size() <= animID ) {
				return false;
			}

			// �g���b�N�X�s�[�h���ߒl���Z�o
			double defTime = animationSets[animID].animationSet->GetPeriod();
			animationSets[animID].loopTime = time;
			animationSets[animID].trackSpeed = defTime / time;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// ����J�n�ɂ����鎞�Ԃ�ݒ�
		bool XAnimationController::SetShiftTime( uint animID, float interval ) {
			// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
			if( animationSets.size() <= animID ) {return false;}

			// �V�t�g���Ԃ�o�^
			animationSets[animID].shiftTime = interval;
			return true;
		}

		//---------------------------------------------------------------------------------------
		// �A�j���[�V������؂�ւ�
		bool XAnimationController::ChangeAnimation( uint animID ) {
			// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
			if( animationSets.size() <= animID ) {return false;}

			// �قȂ�A�j���[�V�����ł��邩���`�F�b�N
			if( currentAnimationID == animID ) {return false;}

			// ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
			D3DXTRACK_DESC TD;    // �g���b�N
			animationController->GetTrackDesc(0, &TD );

			// ���̃A�j���[�V�������g���b�N1�Ɉڍs��
			// �g���b�N�̐ݒ�l���ڍs
			animationController->SetTrackAnimationSet( 1, animationSets[currentAnimationID].animationSet );
			animationController->SetTrackDesc( 1, &TD );

			// �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
			animationController->SetTrackAnimationSet( 0, animationSets[animID].animationSet );

			// �g���b�N0�̃X�s�[�h�̐ݒ�
			animationController->SetTrackSpeed( 0, animationSets[animID].trackSpeed );

			// �g���b�N�̍���������
			animationController->SetTrackEnable( 0, true );
			animationController->SetTrackEnable( 1, true );

			// �E�F�C�g���Ԃ�������
			animationSets[animID].currentWeightTime = 0.0f;

			// ���݂̃A�j���[�V�����ԍ���؂�ւ�
			previousAnimationID = currentAnimationID;
			currentAnimationID = animID;

			return true;
		}

		//---------------------------------------------------------------------------------------
		// �A�j���[�V�������X�V
		bool XAnimationController::AdvanceTime( float time ) {
			// ���������ۂ��𔻒�
			animationSets[currentAnimationID].currentWeightTime += time;
			if( animationSets[currentAnimationID].currentWeightTime <= animationSets[currentAnimationID].shiftTime ) {
				// �������B�E�F�C�g���Z�o
				float weight = animationSets[currentAnimationID].currentWeightTime / animationSets[currentAnimationID].shiftTime;
				// �E�F�C�g��o�^
				animationController->SetTrackWeight( 0, weight );       // ���݂̃A�j���[�V����
				animationController->SetTrackWeight( 1, 1 - weight );   // �O�̃A�j���[�V����
			}
			else {
				// �����I�����B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l��
				animationController->SetTrackWeight( 0, 1.f );       // ���݂̃A�j���[�V����
				animationController->SetTrackEnable(1, false );      // �O�̃A�j���[�V�����𖳌��ɂ���
			}

			// ���Ԃ��X�V
			animationController->AdvanceTime( time, NULL );
			return true;

		}

		//---------------------------------------------------------------------------------------
		// �A�j���[�V�����Z�b�g�����擾
		int XAnimationController::GetNumAnimationSet() {
			return animationSets.size();
		}

	}
}