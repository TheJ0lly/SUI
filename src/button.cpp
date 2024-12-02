#include "../include/button.hpp"

#include <math.h>
#include <unistd.h>

using namespace SUI::Widget;

Button::Button(const char *text, f32 x, f32 y, f32 width, f32 height, HighlightType ht)
                : BaseWidget(text, x, y, width, height, ht) {};

Button::~Button() {};

void Button::Render(void) {
    GLW::Rectangle r;
    r.x1 = m_x;
    r.x2 = m_x + m_width;
    r.y1 = m_y;
    r.y2 = m_y + m_height;
    GLW::RenderRectangle(r, m_background);

    /* We use 8 by 9 because as of now we do not support any other fonts.
    Even though the font we use is 8 by 13, 
    only 9 pixels are required to get to the top drawable pixel in the character.

    Thus meaning that out of the 13 pixels we have for height, starting from the bottom line, we use only 9 in height.
    I discovered this through trial and error.
    */
    f32 font_width = 8;
    f32 font_height = 9;
    f32 textlen = m_text.length() * font_width;
    GLW::Point textStart;

    // We take the absolute difference between the width and text len and divide it by 2 to get the left/right padding.
    textStart.x = r.x1 + (abs(m_width - textlen)) / 2.0f;

    // We get the rectangle center and add half of the font size.
    // We are adding to Y since the characters are drawn from the baseline.
    textStart.y = GLW::GetRectangleCenter(r).y + (font_height / 2.0f);

    GLW::RenderText(m_text.c_str(), textStart.x, textStart.y, m_foreground);
}

void Button::ChangeText(const char *text) { m_text = text; }

void Button::Click(void) {
    u32 prevBkg = m_background.color;
    u32 prevFg = m_foreground.color;

    switch(m_highlightType) {
	case DEFAULT:
		DefaultHighlightingFunc(m_background, m_foreground);
		break;
	case CUSTOM:
		if (m_highlightFunc == nullptr)
			DefaultHighlightingFunc(m_background, m_foreground);
		else
			m_highlightFunc(m_background, m_foreground);

		break;

	default: // This should be the NONE case.
		break;
	}

    Render();

    if (m_clickFunc != nullptr) {
        // Do some drawing calls before and after.
        m_clickThread = std::thread(m_clickFunc, this, nullptr);

        // We immediately wait for the finishing of the thread.
        m_clickThread.join();
    }

    // Then we just reset the background and foreground colors.
    m_background.color = prevBkg;
    m_foreground.color = prevFg;
}