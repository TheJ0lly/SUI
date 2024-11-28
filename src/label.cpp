#include "../include/label.hpp"
#include "../include/window_manager.hpp"
#include "../include/opengl_wrapper.hpp"

using namespace SUI::Widget;

Label::Label(const char *text, f32 x, f32 y, u16 padding) 
	: IRenderable(x, y, 0, 0), ITextArea(text), m_pad(padding) {}

Label::~Label() { m_text.clear(); }

void Label::ChangeText(const char *text) { m_text = text; }

void Label::Render(void) {

	if (m_pad != 0) {
		/* We use 8 by 9 because as of now we do not support any other fonts.
		Even though the font we use is 8 by 13, 
		only 9 pixels are required to get to the top drawable pixel in the character.

		Thus meaning that out of the 13 pixels we have for height, starting from the bottom line, we use only 9 in height.
		I discovered this through trial and error.
		*/
		f32 font_width = 8;
		f32 font_height = 9;

		f32 x1 = m_x - m_pad;
		f32 y1 = m_y - font_height - m_pad;
		f32 x2 = m_x + m_text.length() * font_width + m_pad;
		f32 y2 = m_y + m_pad;
		LOG("Label Rect:\n  x1: %f\n  y1: %f\n  x2: %f\n  y2: %f\n\n", x1, y1, x2, y2);

		// Draw the rectangle that is the background of the label.
		GLW::RenderRectangle(x1, y1, x2, y2, m_background);
	}
	
	GLW::RenderText(
		m_text.c_str(), 
		m_x, 
		m_y,
		m_foreground.b.red, m_foreground.b.green, m_foreground.b.blue, m_foreground.b.alpha
		);

	LOG("Label Text:\n  x: %f\n  y: %f\n\n", textX, textY);
}
