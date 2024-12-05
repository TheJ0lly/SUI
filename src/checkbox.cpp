#include "../include/widgets/checkbox.hpp"

using namespace SUI::Widget;

Checkbox::Checkbox(const char *text, f32 x, f32 y, f32 dist, HighlightType ht) 
    : BaseWidget(text, x, y, 0, 0, ht), m_txtbox_dist(dist), m_checked(false) {
    
    /*
	As of now we will use the default font of 8 by 13 that comes with glut.
	*/
    f32 font_width = 8;
    f32 font_height = 13;

    // We add the box side length and 5 to also take in place the space between text and box.
    m_width = m_text.length() * font_width + dist;
    m_height = font_height;
};

Checkbox::~Checkbox() {};

void Checkbox::ChangeText(const char *text) {
    m_text = text;

    f32 font_width = 8;
    m_width = m_text.length() * font_width + m_txtbox_dist;
}

void Checkbox::SetValue(bool val) {
    m_checked = val;
}

bool Checkbox::GetValue() {
    return m_checked;
}

void Checkbox::Render(void) {
    GLW::Rectangle hitbox;
    hitbox.x1 = m_x;
    hitbox.y1 = m_y;
    hitbox.x2 = m_x + m_width;
    hitbox.y2 = m_y + m_height;
    
    f32 font_width = 8;
    f32 font_height = 9;

    // We render the checkbox.
    GLW::Rectangle chkbox;
    chkbox.x1 = m_x;
    chkbox.y1 = m_y;
    chkbox.x2 = m_x + font_width;
    chkbox.y2 = m_y + 13;
    GLW::RenderRectangle(chkbox, m_background);

    if (m_checked) {
        GLW::Point checkMark;

        checkMark.x = chkbox.x1 + ((chkbox.x2 - chkbox.x1) - font_width) / 2.0f;
        checkMark.y = GLW::GetRectangleCenter(chkbox).y + (font_height / 2.0f);

        GLW::RenderText("X", checkMark.x, checkMark.y, m_foreground);
    }

    // We render the text.
    f32 textlen = m_text.length() * font_width;
    GLW::Point textStart;
    
    textStart.x = chkbox.x2 + (abs(m_width - textlen)) / 2.0f;
    textStart.y = GLW::GetRectangleCenter(hitbox).y + (font_height / 2.0f);
    GLW::RenderText(
        m_text.c_str(),
        textStart.x,
        textStart.y,
        m_foreground
        );
}