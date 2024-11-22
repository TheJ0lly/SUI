#include "../include/label.hpp"

SUI::Widget::Label::Label(u16 x, u16 y, u16 width, u16 height, const char *text) 
    : SUI::Widget::Base(x, y, width, height), m_text(text) {}

SUI::Widget::Label::~Label() { m_text.clear(); }

void SUI::Widget::Label::ChangeText(const char *text) {
    // We free the underlying pointer.
    delete this->m_text.c_str();

    // We move the new text.
    this->m_text = std::move(text);
}

void SUI::Widget::Label::Render() {
    // Set the background color.
    glColor3f(
        Utility::U8ToGLclampf(this->m_background & 0x000000FF), 
        Utility::U8ToGLclampf((this->m_background & 0x0000FF00) >> 8), 
        Utility::U8ToGLclampf((this->m_background & 0x0000FF00) >> 16)
        );
	
	// Draw the background as a rect.
	glRectf(
		Utility::ScreenToOpenGLCoordX(0, 1920),
		Utility::ScreenToOpenGLCoordY(0, 1080), 
		Utility::ScreenToOpenGLCoordX(200, 1920), 
		Utility::ScreenToOpenGLCoordY(200, 1080)
		);
	

	// Set the foreground color. 
	glColor3f(
        Utility::U8ToGLclampf(this->m_foreground & 0x000000FF), 
        Utility::U8ToGLclampf((this->m_foreground & 0x0000FF00) >> 8), 
        Utility::U8ToGLclampf((this->m_foreground & 0x0000FF00) >> 16)
        );
	
	float textwidth = this->m_text.length() * 8;
	float textheight = 13;

	glRasterPos2f(
		Utility::ScreenToOpenGLCoordX(this->m_x + ((this->m_width - textwidth) / 2), 1920), 
		Utility::ScreenToOpenGLCoordY(this->m_y + ((this->m_height - textheight) - 13), 1080)
		);
	const char *text = this->m_text.c_str();
	
	while (*text)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
}

void SUI::Widget::Label::SetBackground(u8 red, u8 green, u8 blue) {
	return;
}

void SUI::Widget::Label::SetForeground(u8 red, u8 green, u8 blue) {
	return;
}
