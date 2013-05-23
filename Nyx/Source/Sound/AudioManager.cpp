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
#include "AudioCache.h"
#include "AudioManager.h"
#include "AudioUtility.h"
#include "DirectSoundAudioManager.h"

namespace Nyx {
	
	//-------------------------------------------------------------------------------------------------------
	//Pimpl
	struct AudioManager::PImpl {
		PImpl()
			:isInitialized_(false), audioManager_(nullptr) {
		}
		
		bool isInitialized_;
		
		std::shared_ptr<IAudioManager> audioManager_;
	};


	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager()
		: pimpl_(new PImpl()){
	}


	//-------------------------------------------------------------------------------------------------------
	//
	AudioManager::AudioManager(const AudioDesc& desc)
		: pimpl_(new PImpl()) {
			Initialize(desc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	void AudioManager::Initialize(const AudioDesc& desc) {
		Assert(pimpl_ != nullptr);
		if (pimpl_->isInitialized_) {
			return ;
		}
		
		//�I�[�f�B�I�}�l�[�W����������
		pimpl_->audioManager_ = std::make_shared<DirectSoundAudioManager>();
		pimpl_->audioManager_->Initialize(desc);

		//�������t���O
		pimpl_->isInitialized_ = true;
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioBuffer> AudioManager::CreateAudioBuffer(const std::wstring& fileName,  const AudioBufferDesc& bufferDesc) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->CreateAudioBuffer(fileName, bufferDesc);
	}


	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<IAudioListener> AudioManager::CreateAudioListener() {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->CreateAudioListener();
	}	
	
	
	//-------------------------------------------------------------------------------------------------------
	//
	std::shared_ptr<AudioCache> AudioManager::Load(const std::wstring& fileName,  const AudioBufferDesc& bufferDesc) {
		Assert(pimpl_ != nullptr);
		Assert(pimpl_->audioManager_ != nullptr);
		return pimpl_->audioManager_->Load(fileName, bufferDesc);
	}
}
