#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#include "Primitive/Rect.h"
#include "Primitive/Color3.h"
#include "Primitive/Color4.h"
#include "Primitive/Vector3.h"
#include "Primitive/Matrix44.h"
#include "GraphicsDeviceType.h"

namespace nyx {

	class window;

	///DirectGraphics�f�o�C�X
	class graphics_device 
	{
		friend class sprite;
		friend class texture;
	public:
		/**
		* �R���X�g���N�^
		*/
		graphics_device();
		
		
		/**
		* �R���X�g���N�^
		* @param std::sahred_ptr<Window>�@�`��E�C���h�E
		* @param WindowMode �E�C���h�E���[�h
		* @param MultiSamplingLevel �T���v�����O���x���i0~16)
		*/
		graphics_device(std::shared_ptr<window> window, WINDOW_MODE windowMode, sampling_level level);



		/**
		* �O���t�B�b�N�f�o�C�X�����������܂�
		* @param std::sahred_ptr<Window>�@�`��E�C���h�E
		* @param WindowMode �E�C���h�E���[�h
		* @param MultiSamplingLevel �T���v�����O���x���i0~16)
		*/
		bool initialize(std::shared_ptr<window> window, WINDOW_MODE windowMode, sampling_level level);

		/**
		* ���݂̃E�C���h�E���[�h���擾���܂�
		* @return WindowMode
		*/
		WINDOW_MODE get_window_mode();
		
		/**
		* �E�C���h�E���[�h��ύX���܂�
		*/
		void change_window_mode();

		/**
		* �r���[�|�[�g��ݒ肵�܂�
		* @param const Rect2i& �N���C�A���g�̈�
		* @param float 
		* @param float
		*/
		void set_view_port(const rect2i& clientRect, float minZ, float maxZ);


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
		void set_light(const vector3f& pos, const vector3f& dir, const color3f& diffuse, const color3f& specular, float range, LIGHT_TYPE lightType);
		
		//�g�����X�t�H�[��
		void set_world(const matrix& world);
		void set_modelview(const matrix& view);
		void set_projection(const matrix& proj);

		//�X�e�[�g
		void enable_z_buffer(bool enalbe);
		//�X�e�[�g�u���b�N
		void apply_state_block();
		void begin_state_block();
		void end_state_block();

		void set_index_buffer(std::vector<vector3f> index);
		void set_vertex_buffer(std::vector<vector3f> vertex);

		//�����_�����O�֌W
		void clear(const color4c& color);
		void render();
		void on_render(std::function<void(std::shared_ptr<void>)> scene);
		void set_scene(std::shared_ptr<void> sceneobj);
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

	


}
#endif