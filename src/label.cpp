#include "../include/label.hpp"
#include "../include/window_manager.hpp"
#include "../include/opengl_wrapper.hpp"

namespace SUI {
namespace Widget {
	Label::Label(u16 x, u16 y, u16 width, u16 height, const char *text) 
		: IRenderable(x, y, width, height), m_text(text) {}

	Label::~Label() { m_text.clear(); }

	void Label::ChangeText(const char *text) { m_text = text; }

	void Label::Render() {
		u16 win_height = SUI::WinMan::GetInstance()->GetHeight();
		u16 win_width = SUI::WinMan::GetInstance()->GetWidth();
		
		f32 x1 = m_x;
		f32 y1 = m_y;
		f32 x2 = m_x + m_width;
		f32 y2 = m_y + m_height;
		LOG("Label Rect:\n  x1: %f\n  y1: %f\n  x2: %f\n  y2: %f\n\n", x1, y1, x2, y2);

		// Draw the rectangle that is the background of the label.
		GLW::RenderRectangle(x1, y1, x2, y2, m_background.red, m_background.green, m_background.blue, m_background.alpha);

		f32 textX = GLW::GetRectangleCenterX(x1, x2);
		f32 textY = GLW::GetRectangleCenterY(y1, y2);
		
		GLW::RenderText(
			m_text.c_str(), 
			m_text.length(), 
			textX, 
			textY,
			m_foreground.red, m_foreground.green, m_foreground.blue, m_foreground.alpha
			);

		LOG("Label Text:\n  x: %f\n  y: %f\n\n", textX, textY);
	}
}
}
