#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color4.h"

namespace Nyx {

	class Window;
	enum class WindowMode;

	///DirectGraphics�f�o�C�X
	class GraphicsDevice 
	{
	public:
		/**
		* �R���X�g���N�^
		*/
		GraphicsDevice();
		
		
		/**
		* �R���X�g���N�^
		* @param std::sahred_ptr<Window>�@�`��E�C���h�E
		* @param WindowMode �E�C���h�E���[�h
		*/
		GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode);



		/**
		* �O���t�B�b�N�f�o�C�X�����������܂�
		* @param std::sahred_ptr<Window>�@�`��E�C���h�E
		* @param WindowMode �E�C���h�E���[�h
		*/
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode);



		/**
		* �r���[�|�[�g��ݒ肵�܂�
		* @param const Rect2i& �N���C�A���g�̈�
		* @param float 
		* @param float
		*/
		void SetViewport(const Rect2i clientRect, float minZ, float maxZ);

		void Clear(const Color4c& color);

		void Render();

		void OnRender(std::function<void(void)> render);

	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

}
#endif