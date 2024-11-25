#include "../include/label.hpp"
#include "../include/window_manager.hpp"

SUI::Widget::Label::Label(u16 x, u16 y, u16 width, u16 height, const char *text) 
    : SUI::Widget::Base(x, y, width, height), m_text(text) {}

SUI::Widget::Label::~Label() { m_text.clear(); }

void SUI::Widget::Label::ChangeText(const char *text) {
    // We move the new text.
    this->m_text = text;
}

void SUI::Widget::Label::Render() {
	
	u16 win_height = SUI::WinMan::GetInstance()->GetHeight();
	u16 win_width = SUI::WinMan::GetInstance()->GetWidth();

    // Set the background color.
	f32 red = Utility::U8ToGLclampf(this->m_background & 0x000000FF);
	f32 green = Utility::U8ToGLclampf((this->m_background & 0x0000FF00) >> 8);
	f32 blue = Utility::U8ToGLclampf((this->m_background & 0x00FF0000) >> 16);
    glColor3f(red, green, blue);
	

	f32 x1 = Utility::ScreenToOpenGLCoordX(this->m_x, win_width);
	f32 x2 = Utility::ScreenToOpenGLCoordX(this->m_x + this->m_width, win_width);
	f32 y1 = Utility::ScreenToOpenGLCoordY(this->m_y, win_height);
	f32 y2 = Utility::ScreenToOpenGLCoordY(this->m_y + this->m_height, win_height);
	
	// Draw the background as a rect.
	glRectf(x1, y1, x2, y2);

	

	// Set the foreground color.
	red = Utility::U8ToGLclampf(this->m_foreground & 0x000000FF);
	green = Utility::U8ToGLclampf((this->m_foreground & 0x0000FF00) >> 8);
	blue = Utility::U8ToGLclampf((this->m_foreground & 0x00FF0000) >> 16);
	glColor3f(red, green, blue);
	
	float textwidth = this->m_text.length() * 8;
	float textheight = 13;

	// The first character position. 
	// TODO: Technically in the middle of the button.
	glRasterPos2f(
		Utility::ScreenToOpenGLCoordX(this->m_x + ((this->m_width - textwidth) / 2), win_width), 
		Utility::ScreenToOpenGLCoordY(this->m_y + ((this->m_height - textheight) - 13), win_height)
		);
	const char *text = this->m_text.c_str();
	
	while (*text)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
}

void SUI::Widget::Label::SetBackground(u8 red, u8 green, u8 blue) {
	this->m_background = (blue << 16) | (green << 8) | red;
}

void SUI::Widget::Label::SetForeground(u8 red, u8 green, u8 blue) {
	this->m_foreground = (blue << 16) | (green << 8) | red;
}
