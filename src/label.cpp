#include "../include/widgets/label.hpp"
#include "../include/window/window_manager.hpp"
#include "../include/core_GL/opengl_wrapper.hpp"

using namespace SUI::Widget;

Label::Label(const char *text, f32 x, f32 y, HighlightType ht) 
	: BaseWidget(text, x, y, 0, 0, ht) {

	/*
	As of now we will use the default font of 8 by 13 that comes with glut.
	*/
	f32 font_width = 8;
	f32 font_height = 13;
	
	
	/* 
	We set these values so that the label will still have an invisible rectangle
	which will never be drawed, and these values will be used as a hitbox.
	*/
	m_width = m_text.length() * font_width;
	m_height = font_height;
}

Label::~Label() { m_text.clear(); }

void Label::ChangeText(const char *text) { 
	m_text = text; 
	f32 font_width = 8;
	m_width = m_text.length() * font_width;
}

void Label::Render(void) {
	GLW::Rectangle r;
	r.x1 = m_x;
	r.y1 = m_y;
	r.x2 = m_x + m_width;
	r.y2 = m_y + m_height;

	f32 font_width = 8;
    f32 font_height = 9;
    f32 textlen = m_text.length() * font_width;
	GLW::Point textStart;

	// We take the absolute difference between the width and text len and divide it by 2 to get the left/right padding.
    textStart.x = r.x1 + (abs(m_width - textlen)) / 2.0f;

    // We get the rectangle center and add half of the font size.
    // We are adding to Y since the characters are drawn from the baseline.
    textStart.y = GLW::GetRectangleCenter(r).y + (font_height / 2.0f);
	
	GLW::RenderText(
		m_text.c_str(), 
		textStart.x, 
		textStart.y,
		m_foreground
		);
}
