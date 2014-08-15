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
#ifndef NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#define NYX_CORE_INCLUDED_AUDIO_MANAGER_H_
#include "Utility/NonCopyable.h"
#include "IAudioManager.h"

namespace nyx {
	//�O���錾
	class audio_cache;
	class iaudio_buffer;
	class iaudio_listener;
	struct audio_buffer_desc;
	struct audio_desc;
	
	///�I�[�f�B�I�}�l�[�W��
	class audio_manager : noncopyable, public iaudio_manager{
	public:
		/**
		 * �R���X�g���N�^
		 */
		explicit audio_manager();


		/**
		 * �R���X�g���N�^
		 * @param const const AudioDesc& �I�[�f�B�I�o�b�t�@
		 */
		explicit audio_manager(const audio_desc& desc);
		

		/**
		* �I�[�f�B�I�}�l�[�W���̏�����
		* @return bool
		*/
		void initialize(const audio_desc& desc);


		/**
		* �I�[�f�B�I�o�b�t�@�𐶐����܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @return std::shared_ptr<IAudioBuffer> �I�[�f�B�I�o�b�t�@
		*/

		std::shared_ptr<iaudio_buffer> create_audio_buffer(const std::wstring& fileName, const audio_buffer_desc& bufferDesc);

		/**
		* �I�[�f�B�I���X�i�[�𐶐����܂�
		* @return std::shared_ptr<IAudioListener> 
		*/
		std::shared_ptr<iaudio_listener> create_audio_listener();	


		/**
		* �I�[�f�B�I�f�[�^�������[�h���Ă��܂�
		* @param const std::wstring& �t�@�C����
		* @param SoundBufferType �o�b�t�@�^�C�v
		* @return std::shared_ptr<AudioCache> �I�[�f�B�I�L���b�V��
		*/
		std::shared_ptr<audio_cache> load_audio(const std::wstring& fileName,  const audio_buffer_desc& bufferDesc);
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}
#endif