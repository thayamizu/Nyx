#ifndef NYX_CORE_DSMOVIE_PLAYER_H_
#define NYX_CORE_DSMOVIE_PLAYER_H_
#include "DirectShowDefinition.h"
#include "Movie/IMoviePlayer.h"

namespace Nyx
{
	class Window;
	class DSMoviePlayer {
	public:
		/**
		* �R���X�g���N�^
		*/
		DSMoviePlayer();


		/**
		* �R���X�g���N�^
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @param const std::wstring& �t�@�C����
		*/
		DSMoviePlayer(const std::shared_ptr<Nyx::Window> window, const std::wstring& fileName);
		

		/**
		*������
		* @param const std::shared_ptr<Nyx::Window> �E�C���h�E
		* @return bool(true�Ȃ琬��)
		*/
		void Initialize(const std::shared_ptr<Nyx::Window> window);


		/**
		* ����t�@�C�����J���܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		void Open(const std::wstring& name);


		/**
		* ����t�@�C������܂�
		* @param const std::wstring& �t�@�C����
		* @return bool(true�Ȃ琬��)
		*/
		void Close();


		/**
		* ������Đ����܂�
		*/
		void Play();


		/**
		* ������~���܂�
		*/
		void Stop();


		/**
		* ������ꎞ��~���܂�
		*/
		void Pause();


		/**
		* ����Đ������W���[�����܂�
		*/
		void Resume();
	private:
		IMediaControlPtr  mediaControl_;
		IMediaEventExPtr  mediaEvent_;
		IGraphBuilderPtr  graphBuilder_;
		IBaseFilterPtr    videoMixingRenderer_;
		IBaseFilterPtr    sourceFilter_;
		IVMRWindowlessControlPtr   windowlessControl_;
		ICaptureGraphBuilder2Ptr   captureGraphBuilder_;
		RECT clientRect_; 
	};
}
#endif