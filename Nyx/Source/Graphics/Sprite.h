#ifndef NYX_CORE_INCLUDED_SPRITE_H_
#define NYX_CORE_INCLUDED_SPRITE_H_
#include "IRenderable.h"
#include "IResource.h"
#include "Primitive/Color4.h"
#include "Primitive/Rect.h"

namespace Nyx {

	///�X�v���C�g
	class Sprite : public IRenderable, public IResource
	{
	public:
		/*
		* �R���X�g���N�^
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param std::wstring �t�@�C����
		*/
		Sprite(const std::wstring& fileName);
		
		
		/*
		*�@�R���X�g���N�^
		* @param int �X�v���C�g�̕�
		* @param int �X�v���C�g�̍���
		* @param const Color4c& �F
		*/
		Sprite(int width, int height, const Color4c& color);
		
		
		/*
		*�@�f�X�g���N�^
		*/
		~Sprite();
		
		/*
		*�@�X�v���C�g���w�肵���F�œh��Ԃ��܂�
		* @param const Color4c& �F
		*/
		void Fill(const Color4c& color);
		
		/*
		*�@�X�v���C�g�̕`��F���擾���܂�
		* @param const Color4c& �`��F
		*/
		void SetColor(const Color4c& color);
		
		/*
		*�@�X�v���C�g�̕`��F���擾���܂�
		* @return Colr4c �`��F
		*/
		Color4c GetColor() const;
		
		/*
		*�@�X�v���C�g�̕`���`��ݒ肵�܂�
		* @param const Rect2i& ��`
		*/
		void SetRect(const Rect2i& rect);
		
		/*
		*�@�X�v���C�g�̕`���`���擾���܂�
		* @return Rect2i ��`
		*/
		Rect2i GetRect() const;
		
		/*
		*�@�����_�����O
		* @param const Matrix44& �ϊ��s��
		*/
		void Render(const Matrix44& matrix) const;

		/*
		* ���\�[�X���J�����܂�
		*/
		void Release();
		
		/*
		* ���\�[�X�𕜌����܂�
		*/
		void Recovery();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};
}

#endif