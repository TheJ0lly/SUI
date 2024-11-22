#pragma once

#include "coretypes.hpp"

namespace Utility {
    // Convert an `u8` (byte) to a `GLclampf`.
    inline f32 U8ToGLclampf(u8 byte) {
        /* 
        We try to convert X in range [a, b] to Y in [c, d].
        In our case, the ranges are  [0, 255]       [0, 1].
        The formula is y = c + (d - c) * (x - a) / (b - a)
        */

       f32 a = 0.0f, b = 255.0f, c = 0.0f, d = 1.0f;

       return (c + (d - c) * (byte - a) / (b - a));
    }

    // We convert a screen coordinate X to OpenGL normalized device coordinates(NDC).
    inline f32 ScreenToOpenGLCoordX (f32 x, u16 window_width) {
        return 2.0f * x / window_width - 1.0f;
    }
    // We convert a screen coordinate Y to OpenGL normalized device coordinates(NDC).
    inline f32 ScreenToOpenGLCoordY (f32 y, u16 window_height) {
        return 1.0f - 2.0f * y / window_height;
    }
}