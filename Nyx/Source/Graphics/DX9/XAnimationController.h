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
#ifndef NYX_CORE_INCLUDED_XANIMATION_CONTROLLER_H_
#define NYX_CORE_INCLUDED_XANIMATION_CONTROLLER_H_

#include "Graphics/IAnimationController.h"
namespace Nyx {
	namespace DX9 {
		///�A�j���[�V�����Z�b�g�L�q�\����
		struct AnimationSetDesc
		{
			uint AnimatinID;       /// �A�j���[�V����ID
			float loopTime;        /// 1���[�v�̎��� 
			float shiftTime;       /// �V�t�g����̂ɂ����鎞��
			float trackSpeed;      /// �g���b�N�X�s�[�h���ߒl
			float currentWeightTime;/// ���݂̃E�F�C�g���� 
			ID3DXAnimationSet *animationSet;/// �A�j���[�V�����Z�b�g

			AnimationSetDesc() {
				ZeroMemory(this, sizeof(AnimationSetDesc));
			}
		};

		///�A�j���[�V�����R���g���[���[
		class XAnimationController : public IAnimationController{
			typedef std::vector<AnimationSetDesc> AnimationSetContainer;
		public:
			XAnimationController();

			virtual ~XAnimationController() {}
			// �A�j���[�V�����R���g���[����ݒ�
			bool SetAnimationController( D3DXAnimationController animationController );
			// �A�j���[�V�����R���g���[�����擾
			bool GetAnimationController( D3DXAnimationController *animationController );
			// ���[�v���Ԃ�ݒ�
			bool SetLoopTime( uint animID, float time );
			// ����J�n�ɂ����鎞�Ԃ�ݒ�
			bool SetShiftTime( uint animID, float interval );
			// �A�j���[�V������؂�ւ�
			bool ChangeAnimation( uint animID ); 
			// �A�j���[�V�������X�V
			bool AdvanceTime( float time );
			int GetNumAnimationSet();
		private:
			uint currentAnimationID;
			uint previousAnimationID;
			AnimationSetContainer animationSets;
			D3DXAnimationController animationController;
		};

	}
}
#endif