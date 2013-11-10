#include "PCH/PCH.h"
#include "TextureFont.h"
#include "TextureText.h"
#include "detail/DX9/DirectXDefinition.h"

namespace Nyx
{
	struct TextureText::PImpl
	{
		size_t speed_ = 50;
		size_t rendered_  = 0; 
		Rect2i rect_   = Rect2i();

		typedef std::deque<std::shared_ptr<TextureFont>> TextureText;
		TextureText text_;

		void Set(std::wstring text, const FontInfo& fontInfo) {
			for (auto chara : text) {
				text_.push_back(std::make_shared<TextureFont>(chara, fontInfo));
			}
		}

		void SetSpeed(size_t speed) {
			speed_ = speed;
		}
		
		size_t GetSpeed() const {
			return speed_;
		}

		void SetRect(const Rect2i& rect) {
			rect_ = rect;
		}

		Rect2i GetRect() const {
			return rect_;
		}

		void SetColor(size_t index, const Color4c& color) {
			auto chara = text_.at(index);
			chara->SetColor(color);
		}

		Color4c GetColor(size_t index) const {
			auto chara = text_.at(index);
			return chara->GetColor();
		}

		void SetFontInfo(size_t index, const FontInfo& info) {
			auto chara = text_.at(index);
			chara->SetFontInfo(info);
		}

		FontInfo GetFontInfo(size_t index) const {
			auto chara = text_.at(index);
			return chara->GetFontInfo();
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
			color.a = (uchar)(((color.a + speed_) >= 255) ? 255 : color.a + speed_);
			text_[rendered_]->SetColor(color);
			Matrix44::AddTranslate(&world, (float)text_[rendered_]->GetRect().width, 0, 0);

			//255になったら次へ行く
			if (color.a >= 255) {
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
	TextureText::TextureText(std::wstring text, const FontInfo& fontInfo)
		:pimpl_(std::make_shared<PImpl>()) {
		
		pimpl_->Set(text, fontInfo);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Set(std::wstring text, const FontInfo& fontInfo) {
		Assert(pimpl_ != nullptr);
		pimpl_->Set(text, fontInfo);
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
	void TextureText::SetColor(size_t index, const Color4c& color) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetColor(index, color);
	}

	//-----------------------------------------------------------------------------------------
	//
	Color4c TextureText::GetColor(size_t index) {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetColor(index);
	}

	//-----------------------------------------------------------------------------------------
	//
	void TextureText::Render(const Matrix44& matrix) const{
		Assert(pimpl_ != nullptr);
		pimpl_->Render(matrix);
	}

	//-----------------------------------------------------------------------------------------
	//
	std::shared_ptr<TextureFont> TextureText::GetChar(size_t index) {
		Assert(pimpl_ != nullptr);
		return pimpl_->text_[index];
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
	void TextureText::SetFontInfo(size_t index, const FontInfo& info) {
		Assert(pimpl_ != nullptr);
		pimpl_->SetFontInfo(index, info);
	}

	//-----------------------------------------------------------------------------------------
	//
	FontInfo TextureText::GetFontInfo(size_t index) {
		Assert(pimpl_ != nullptr);
		return pimpl_->GetFontInfo(index);
	}

	void TextureText::Release() {
		Assert(pimpl_ != nullptr);
		pimpl_->Release();
	}
	void TextureText::Recovery() {
		Assert(pimpl_ != nullptr);
		pimpl_->Recovery();
	}
}
