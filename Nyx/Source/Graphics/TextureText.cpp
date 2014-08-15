#include "PCH/PCH.h"
#include "Utility/Limits.h"
#include "TextureFont.h"
#include "TextureText.h"
#include "detail/DX9/DirectXDefinition.h"

namespace nyx
{
	struct texture_text::PImpl
	{
		size_t speed_ = 25;
		size_t rendered_ = 0;
		size_t columns_ = 0;
		size_t rows_ = 0;
		uint8_t transparency_ = limits::UCHAR_MAXIMUM;
		rect2i rect_ = rect2i();
		TextureFontList text_;

		void set_text(const TextureFontList & text) {
			text_ = text;
		}

		void set_transparency(uint8_t transparency) {
			using std::swap;
			swap(transparency_, transparency);
		}
		uint8_t get_transparency() {
			return transparency_;
		}

		void set_speed(size_t speed) {
			using std::swap;
			swap(speed_, speed);
		}

		size_t get_speed() const {
			return speed_;
		}

		void set_rect(const rect2i& rect) {
			rect_ = rect;
			const size_t width = rect.width;
			const size_t height = rect.height;
			const size_t fontSize = text_[0]->get_font_info().fontSize;

			columns_ = width / (fontSize);
			rows_ = height / (fontSize);
		}

		rect2i get_rect() const {
			return rect_;
		}

		void set_color(const color4c& color) {
			for (auto item : text_) {
				item->set_color(color);
			}
		}


		void set_font_info(const font_info& info) {
			for (auto item : text_) {
				item->set_font_info(info);
			}
		}

		void render(const matrix& matrix) {
			auto length = text_.size();
			auto world(matrix);

			for (auto index = 0U; index < rendered_; ++index) {
				text_[index]->render(world);
				matrix::add_translate(&world, (float)text_[index]->get_rect().width, 0.f, 0.f);
			}
			if (rendered_ >= length) {
				return;
			}

			//テキストスピードに合わせて少しずつ不透明度を上げていく
			auto color = text_[rendered_]->get_color();
			color.a = (uint8_t)(((color.a + speed_) >= transparency_) ? transparency_ : color.a + speed_);
			text_[rendered_]->set_color(color);
			text_[rendered_]->render(world);
			matrix::add_translate(&world, (float)text_[rendered_]->get_rect().width, 0, 0);

			//255になったら次へ行く
			if (color.a >= transparency_) {
				++rendered_;
			}
		}

		std::shared_ptr<texture_font> get_char(size_t index) {
			return text_.at(index);
		}

		void release() {
			for (auto item : text_) {
				item->release();
			}
		}

		void recovery() {
			for (auto item : text_) {
				item->recovery();
			}
		}
	};

	//-----------------------------------------------------------------------------------------
	//
	texture_text::texture_text(const TextureFontList&text)
		:pimpl_(std::make_shared<PImpl>()) {

		pimpl_->set_text(text);
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set(const TextureFontList&text ) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_text(text);
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set_rect(const rect2i& rect) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_rect(rect);
	}


	//-----------------------------------------------------------------------------------------
	//
	rect2i texture_text::get_rect() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_rect();
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set_color(const color4c& color) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_color(color);
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::render(const matrix& matrix) const{
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->render(matrix);
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set_text_speed(size_t speed) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_speed(speed);
	}

	//-----------------------------------------------------------------------------------------
	//
	size_t texture_text::get_text_speed() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_speed();
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set_transparency(uint8_t transparency) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_transparency(transparency);
	}


	//-----------------------------------------------------------------------------------------
	//
	uint8_t texture_text::get_transparency() const {
		NYX_ASSERT(pimpl_ != nullptr);
		return pimpl_->get_transparency();
	}


	//-----------------------------------------------------------------------------------------
	//
	void texture_text::set_font_info(const font_info& info) {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->set_font_info(info);
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::release() {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->release();
	}

	//-----------------------------------------------------------------------------------------
	//
	void texture_text::recovery() {
		NYX_ASSERT(pimpl_ != nullptr);
		pimpl_->recovery();
	}
}
