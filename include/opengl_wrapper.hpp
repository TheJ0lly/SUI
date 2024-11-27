#pragma once

#include "core.hpp"

#include <GL/freeglut.h>

namespace SUI {
namespace GLW {
    /*
    It will render a rectangle.
    */
    GLenum RenderRectangle(f32 x1, f32 y1, f32 x2, f32 y2, u8 red, u8 green, u8 blue, u8 alpha);

    /*
    Returns the X coordinate of the center of the rectangle.
    */
    f32 GetRectangleCenterX(f32 x1, f32 x2);

    /*
    Returns the Y coordinate of the center of the rectangle.
    */
    f32 GetRectangleCenterY(f32 y1, f32 y2);

    /*
    It will render text.
    */
    GLenum RenderText(const char *text, u32 textlen, f32 x, f32 y, u8 red, u8 green, u8 blue, u8 alpha);
}
}