#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "IRenderable.h"
#include "IResource.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"

namespace nyx {

	///�X�v���C�g
	class sprite_batch : public irenderable, public iresource
	{
	public:
		/*
		* �R���X�g���N�^
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param std::wstring �t�@�C����
		*/
		sprite_batch(const std::wstring& fileName);
		
		
		/*
		*�@�R���X�g���N�^
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param const Color4c& �F
		*/
		sprite_batch(int width, int height, const color4c& color);
		
		
		/*
		*�@�f�X�g���N�^
		*/
		~sprite_batch();
		
		/*
		*�@�X�v���C�g���w�肵���F�œh��Ԃ��܂�
		* @param const Color4c& �F
		*/
		void fill(const color4c& color);
		
		/*
		*�@�X�v���C�g�̕`��F���擾���܂�
		* @param const Color4c& �`��F
		*/
		void set_color(const color4c& color);
		
		/*
		*�@�X�v���C�g�̕`��F���擾���܂�
		* @return Colr4c �`��F
		*/
		color4c get_color() const;
		
		/*
		*�@�X�v���C�g�̕`���`��ݒ肵�܂�
		* @param const Rect2i& ��`
		*/
		void set_rect(const rect2i& rect);
		
		/*
		*�@�X�v���C�g�̕`���`���擾���܂�
		* @return Rect2i ��`
		*/
		rect2i get_rect() const;
		
		/*
		*�@�����_�����O
		* @param const Matrix44& �ϊ��s��
		*/
		void render(const matrix& matrix) const;

		/*
		* ���\�[�X���J�����܂�
		*/
		void release();
		
		/*
		* ���\�[�X�𕜌����܂�
		*/
		void recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif