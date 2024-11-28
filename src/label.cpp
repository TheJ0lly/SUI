#include "../include/label.hpp"
#include "../include/window_manager.hpp"
#include "../include/opengl_wrapper.hpp"

using namespace SUI::Widget;

Label::Label(const char *text, f32 x, f32 y, u16 padding) 
	: BaseWidget(text, x, y, 0, 0), m_pad(padding) {

	/*
	As of now we will use the default font of 8 by 13 that comes with glut.
	*/
	f32 font_width = 8;
	f32 font_height = 13;
	
	
	/* 
	We set these values so that the label will still have an invisible rectangle
	which will never be drawed, and these values will be used as a hitbox.
	This behaviour will only occur when there is no padding to the label.
	*/
	m_width = m_text.length() * font_width;
	m_height = font_height;

	// If we have padding, we simply add them to the width and height and substract them from the starting point.
	if (m_pad != 0) {
		m_x -= m_pad;
		m_y -= m_pad;
		m_width += m_pad;
		m_height += m_pad;
	}
}

Label::~Label() { m_text.clear(); }

void Label::ChangeText(const char *text) { m_text = text; }

void Label::Render(void) {
	GLW::Rectangle r;
	r.x1 = m_x;
	r.y1 = m_y;
	r.x2 = m_x + m_width;
	r.y2 = m_y + m_height;

	// If we added padding, this means that there is a colored border we should draw behind the label.
	// TODO: Change this and maybe add a IPaddable class/interface.
	if (m_pad != 0) {
		// Draw the rectangle that is the background of the label.
		GLW::RenderRectangle(r, m_background);
	}

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
		m_foreground.b.red, m_foreground.b.green, m_foreground.b.blue, m_foreground.b.alpha
		);
}

void Label::Click(void) {
	if (m_func == nullptr)
		return;

	// Do some drawing calls before and after.
    m_clickThread = std::thread(m_func, this, nullptr);

    // We immediately wait for the finishing of the thread.
    m_clickThread.join();
}
