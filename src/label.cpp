#include "../include/label.hpp"
#include "../include/window_manager.hpp"
#include "../include/opengl_wrapper.hpp"

SUI::Widget::Label::Label(u16 x, u16 y, u16 width, u16 height, const char *text) 
    : SUI::Widget::Base(x, y, width, height), m_text(text) {}

SUI::Widget::Label::~Label() { m_text.clear(); }

void SUI::Widget::Label::ChangeText(const char *text) { m_text = text; }

void SUI::Widget::Label::Render() {
	u16 win_height = SUI::WinMan::GetInstance()->GetHeight();
	u16 win_width = SUI::WinMan::GetInstance()->GetWidth();

	f32 red = m_background & 0x000000FF;
	f32 green = (m_background & 0x0000FF00) >> 8;
	f32 blue = (m_background & 0x00FF0000) >> 16;
	
	f32 x1 = m_x;
	f32 y1 = m_y;
	f32 x2 = m_x + m_width;
	f32 y2 = m_y + m_height;
	LOG("Label Rect:\n  x1: %f\n  y1: %f\n  x2: %f\n  y2: %f\n\n", x1, y1, x2, y2);

	// Draw the rectangle that is the background of the label.
	GLW::RenderRectangle(x1, y1, x2, y2, red, green, blue, 1);

	// Set the foreground color.
	red = m_foreground & 0x000000FF;
	green = (m_foreground & 0x0000FF00) >> 8;
	blue = (m_foreground & 0x00FF0000) >> 16;

	f32 textX = GLW::GetRectangleCenterX(x1, x2);
	f32 textY = GLW::GetRectangleCenterY(y1, y2);
	
	GLW::RenderText(
		m_text.c_str(), 
		m_text.length(), 
		textX, 
		textY,
		red, green,	blue, 1
		);

	LOG("Label Text:\n  x: %f\n  y: %f\n\n", textX, textY);
}

void SUI::Widget::Label::SetBackground(u8 red, u8 green, u8 blue) { m_background = (blue << 16) | (green << 8) | red; }

void SUI::Widget::Label::SetForeground(u8 red, u8 green, u8 blue) { m_foreground = (blue << 16) | (green << 8) | red; }
