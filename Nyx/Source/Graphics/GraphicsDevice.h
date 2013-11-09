#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color3.h"
#include "Primitive/Color4.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "GraphicsDeviceType.h"

namespace Nyx {

	class Window;

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
		* @param MultiSamplingLevel �T���v�����O���x���i0~16)
		*/
		GraphicsDevice(std::shared_ptr<Window> window, WindowMode windowMode, MultiSamplingLevel level);



		/**
		* �O���t�B�b�N�f�o�C�X�����������܂�
		* @param std::sahred_ptr<Window>�@�`��E�C���h�E
		* @param WindowMode �E�C���h�E���[�h
		* @param MultiSamplingLevel �T���v�����O���x���i0~16)
		*/
		bool Initialize(std::shared_ptr<Window> window, WindowMode windowMode, MultiSamplingLevel level);

		/**
		* ���݂̃E�C���h�E���[�h���擾���܂�
		* @return WindowMode
		*/
		WindowMode GetWindowMode();
		
		/**
		* �E�C���h�E���[�h��ύX���܂�
		*/
		void ChangeWindowMode();

		/**
		* �r���[�|�[�g��ݒ肵�܂�
		* @param const Rect2i& �N���C�A���g�̈�
		* @param float 
		* @param float
		*/
		void SetViewport(const Rect2i& clientRect, float minZ, float maxZ);


		//���C�e�B���O
		/**
		* ���C�g��ݒ�
		* @param Vector3f ���C�g�ʒu
		* @param Vector3f �����x�N�g��
		* @param Color3f �g�U���ˌ��̒l(RGB)
		* @param Color3f ���ʔ��ˌ��̒l(RGB)
		* @param float ���C�g�͈̔�
		* @param D3DLIGHTTYPE ���C�g�̎��(�|�C���g���C�g�f�B���N�V���i�����C�g�Ȃ�)
		*/
		void SetLight(const Vector3f& pos, const Vector3f& dir, const Color3f& diffuse, const Color3f& specular, float range, LightType lightType);
		
		//�g�����X�t�H�[��
		void SetWorldMatrix(const Matrix44& world);
		void SetModelViewMatrix(const Matrix44& view);
		void SetProjectionMatrix(const Matrix44& proj);

		//�X�e�[�g
		void EnableZBuffer(bool enalbe);
		//�X�e�[�g�u���b�N
		void ApplyStateBlock();
		void BeginStateBlock();
		void EndStateBlock();

		void SetIndexBuffer(std::vector<Vector3f> index);
		void SetVertexBuffer(std::vector<Vector3f> vertex);

		//�����_�����O�֌W
		void Clear(const Color4c& color);
		void Render();
		void OnRender(std::function<void(void)> scene);

	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

	


}
#endif