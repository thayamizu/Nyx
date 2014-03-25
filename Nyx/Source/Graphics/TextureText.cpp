#include "PCH/PCH.h"
#include "Utility/Limits.h"
#include "TextureFont.h"
#include "TextureText.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx
{
	struct TextureText::PImpl
	{
		size_t speed_ = 25;
		size_t rendered_ = 0;
		size_t columns_ = 0;
		size_t rows_ = 0;
		uchar transparency_ = Limits::UCharMax;
		Rect2i rect_ = Rect2i();
		TextureFontList text_;

		void Set(const TextureFontList & text) {
			text_ = text;
		}

		void SetTransparency(uchar transparency) {
			using std::swap;
			swap(transparency_, transparency);
		}
		uchar GetTransparency() {
			return transparency_;
		}

		void SetSpeed(size_t speed) {
			using std::swap;
			swap(speed_, speed);
		}

		size_t GetSpeed() const {
			return speed_;
		}

		void SetRect(const Rect2i& rect) {
			rect_ = rect;
			const size_t width = rect.width;
			const size_t height = rect.height;
			const size_t fontSize = text_[0]->GetFontInfo().fontSize;

			columns_ = width / (fontSize);
			rows_ = height / (fontSize);
		}

		Rect2i GetRect() const {
			return rect_;
		}

		void SetColor(const Color4c& color) {
			for (auto item : text_) {
				item->SetColor(color);
			}
		}


		void SetFontInfo(const FontInfo& info) {
			for (auto item : text_) {
				item->SetFontInfo(info);
			}
		}

		void Render(const Matrix44& matrix) {
			auto length = text_.size();
			auto world(matrix);

			for (auto index = 0U; index < rendered_; ++index) {
				text_[index]->Render(world);
				Matrix44::AddTranslate(&world, (float)text_[index]->GetRect().width, 0.f, 0.f);
			}
			if (rendered_ >= length) {
				return;
			}

			//テキストスピードに合わせて少しずつ不透明度を上げていく
			auto color = text_[rendered_]->GetColor();
			color.a = (uchar)(((color.a + speed_) >= transparency_) ? transparency_ : color.a + speed_);
			text_[rendered_]->SetColor(color);
			text_[rendered_]->Render(world);
			Matrix44::AddTranslate(&world, (float)text_[rendered_]->GetRect().width, 0, 0);

			//255になったら次へ行く
			if (color.a >= transparency_) {
				++rendered_;
			}
		}

		std::shared_ptr<TextureFont> GetChar(size_t index) {
			return text_.at(index);
		}

		void Release() {
			for (auto item : text_) {
				item->Release();
			}
		}

		void Recovery() {
			for (auto item : text_) {
				item->Recovery();
			}
		}
	};

	//-----------------------------------------------------------------------------------------
	//
	TextureText::TextureText(const TextureFontList&text)
		:pimpl_(std::make_shared<PImpl>()) {

		pimpl_->Set(text);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Set(const TextureFontList&text ) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(text);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::SetRect(const Rect2i& rect) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetRect(rect);
	}


	//-----------------------------------------------------------------------------------------
	//
	Rect2i TextureText::GetRect() const {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetRect();
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::SetColor(const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetColor(color);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Render(const Matrix44& matrix) const{
		Assert(pimpl_ != nullptr);
		pimpl_->Render(matrix);
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureText::SetTextSpeed(size_t speed) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetSpeed(speed);
	}

	//-----------------------------------------------------------------------------------------
	//
	size_t TextureText::GetTextSpeed() const {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetSpeed();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureText::SetTransparency(uchar transparency) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetTransparency(transparency);
	}


	//-----------------------------------------------------------------------------------------
	//
	uchar TextureText::GetTransparency() const {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetTransparency();
	}


	//-----------------------------------------------------------------------------------------
	//
	void TextureText::SetFontInfo(const FontInfo& info) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetFontInfo(info);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Release() {
		Assert(pimpl_ != nullptr);
		pimpl_->Release();
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Recovery() {
		Assert(pimpl_ != nullptr);
		pimpl_->Recovery();
	}
}
