#include "../include/opengl_wrapper.hpp"

GLenum SUI::GLW::RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, u8 red, u8 green, u8 blue, u8 alpha) {
    GLenum err;

    // Set the color of the rectangle.
    glColor4ub(red, green, blue, alpha); 
    if ((err = glGetError()) != GL_NO_ERROR) {
        return err;
    }
	
    // Draw the rectangle.
	glRectf(x1, y1, x2, y2);
    if ((err = glGetError()) != GL_NO_ERROR) {
        return err;
    }

    return GL_NO_ERROR;
}

f32 SUI::GLW::GetRectangleCenterX(f32 x1, f32 x2) {
    return (x1 + x2) / 2.0f;
}
    
f32 SUI::GLW::GetRectangleCenterY(f32 y1, f32 y2) {
    return (y1 + y2) / 2.0f;
}


GLenum SUI::GLW::RenderText(const char *text, u32 textlen, f32 x, f32 y, u8 red, u8 green, u8 blue, u8 alpha) {
    GLenum err;
    
    // Set the foreground color.
	glColor4ub(red, green, blue, alpha);
    if ((err = glGetError()) != GL_NO_ERROR) {
        return err;
    }
	
    // As of now we only use the font that comes with OpenGL.
	f32 textwidth = textlen * 8;
	f32 textheight = 13;

	// The first character position. 
	// TODO: Technically in the middle of the button.
	f32 textX = x - (textwidth / 2.0f);
	f32 textY = y - (textheight / 2.0f);

	glRasterPos2f(textX, textY);

    if ((err = glGetError()) != GL_NO_ERROR) {
        return err;
    }

	while (*text) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
        if ((err = glGetError()) != GL_NO_ERROR) {
            return err;
        }
    }

    return GL_NO_ERROR;
}
