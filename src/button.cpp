#include "../include/button.hpp"

#include <math.h>

using namespace SUI::Widget;

Button::Button(const char *text, f32 x, f32 y, f32 width, f32 height)
                : IRenderable(x, y, width, height), ITextArea(text) {};

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