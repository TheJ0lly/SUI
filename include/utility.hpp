#pragma once

#include "core.hpp"

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
}