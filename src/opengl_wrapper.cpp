#include "../include/core_GL/opengl_wrapper.hpp"

namespace SUI::GLW {

    GLenum RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, u8 red, u8 green, u8 blue, u8 alpha) {
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

    GLenum RenderRectangle(Rectangle r, u8 red, u8 green, u8 blue, u8 alpha) {
        return RenderRectangle(r.x1, r.y1, r.x2, r.y2, red, green, blue, alpha);
    }

    GLenum RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Color c) {
        return RenderRectangle(x1, y1, x2, y2, c.b.red, c.b.green, c.b.blue, c.b.alpha);
    }

    GLenum RenderRectangle(Rectangle r, Color c) {
        return RenderRectangle(r.x1, r.y1, r.x2, r.y2, c.b.red, c.b.green, c.b.blue, c.b.alpha);
    }

    Point GetRectangleCenter(Rectangle r) {
        return GetRectangleCenter(r.x1, r.y1, r.x2, r.y2);
    }

    Point GetRectangleCenter(f32 x1, f32 y1, f32 x2, f32 y2) {
        Point center;
        center.x = (x1 + x2) / 2.0f;
        center.y = (y1 + y2) / 2.0f;
        return center;
    }

    GLenum RenderText(const char *text, f32 x, f32 y, u8 red, u8 green, u8 blue, u8 alpha) {
        GLenum err;
        
        // Set the foreground color.
        glColor4ub(red, green, blue, alpha);
        if ((err = glGetError()) != GL_NO_ERROR) {
            return err;
        }

        // The bottom-left position of the first character. 
        glRasterPos2f(x, y);

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

    GLenum RenderText(const char *text, f32 x, f32 y, Color c) {
        return RenderText(text, x, y, c.b.red, c.b.green, c.b.blue, c.b.alpha);
    }
}
