#pragma once

#include "core.hpp"

#include <GL/freeglut.h>

namespace SUI {
namespace GLW {
    typedef struct {
        f32 x1, x2, y1, y2;
    } Rectangle;

    typedef struct {
        f32 x, y;
    } Point;

    typedef struct {
        // In accordance to the endianess of the system, this is how the bytes should be aligned. 
        #if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ 
        u8 alpha, blue, green, red;
        #else
        u8 red, green, blue, alpha;
        #endif
    } RGBA;

    typedef union {
        u32 color;
        RGBA b;
    } Color;

    /*
    It will render a rectangle.
    */
    GLenum RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, u8 red, u8 green, u8 blue, u8 alpha);
    GLenum RenderRectangle(Rectangle r, u8 red, u8 green, u8 blue, u8 alpha);
    GLenum RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Color c);
    GLenum RenderRectangle(Rectangle r, Color c);
    
    /*
    Returns XY coordinates of the center of the rectangle.
    */
    Point GetRectangleCenter(Rectangle r);
    Point GetRectangleCenter(f32 x1, f32 y1, f32 x2, f32 y2);
    
    /*
    It will render text.
    */
    GLenum RenderText(const char *text, f32 x, f32 y, u8 red, u8 green, u8 blue, u8 alpha);
    GLenum RenderText(const char *text, f32 x, f32 y, Color c);
}
}