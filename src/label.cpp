#include "../include/label.hpp"
#include "../include/window_manager.hpp"

SUI::Widget::Label::Label(u16 x, u16 y, u16 width, u16 height, const char *text) 
    : SUI::Widget::Base(x, y, width, height), m_text(text) {}

SUI::Widget::Label::~Label() { m_text.clear(); }

void SUI::Widget::Label::ChangeText(const char *text) { m_text = text; }

void SUI::Widget::Label::Render() {
	
	u16 win_height = SUI::WinMan::GetInstance()->GetHeight();
	u16 win_width = SUI::WinMan::GetInstance()->GetWidth();

    // Set the background color.
	f32 red = Utility::U8ToGLclampf(m_background & 0x000000FF);
	f32 green = Utility::U8ToGLclampf((m_background & 0x0000FF00) >> 8);
	f32 blue = Utility::U8ToGLclampf((m_background & 0x00FF0000) >> 16);
    glColor3f(red, green, blue);
	
	f32 x1 = m_x;
	f32 y1 = m_y;
	f32 x2 = m_x + m_width;
	f32 y2 = m_y + m_height;
	LOG("Label Rect:\n  x1: %f\n  y1: %f\n  x2: %f\n  y2: %f\n\n", x1, y1, x2, y2);

	// Draw the background as a rect.
	glRectf(x1, y1, x2, y2);

	

	// Set the foreground color.
	red = Utility::U8ToGLclampf(m_foreground & 0x000000FF);
	green = Utility::U8ToGLclampf((m_foreground & 0x0000FF00) >> 8);
	blue = Utility::U8ToGLclampf((m_foreground & 0x00FF0000) >> 16);
	glColor3f(red, green, blue);
	
	float textwidth = m_text.length() * 8;
	float textheight = 13;

	// The first character position. 
	// TODO: Technically in the middle of the button.
	f32 textX = (x1 + x2) / 2.0f - (textwidth / 2.0f);
	f32 textY = (y1 + y2) / 2.0f - (textheight / 2.0f);
	LOG("Label Text:\n  x: %f\n  y: %f\n\n", textX, textY);

	glRasterPos2f(textX, textY);
	
	const char *text = m_text.c_str();
	
	while (*text)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
}

void SUI::Widget::Label::SetBackground(u8 red, u8 green, u8 blue) { m_background = (blue << 16) | (green << 8) | red; }

void SUI::Widget::Label::SetForeground(u8 red, u8 green, u8 blue) { m_foreground = (blue << 16) | (green << 8) | red; }
