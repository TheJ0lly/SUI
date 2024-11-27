#pragma once

#include <iostream>

#include "core.hpp"


namespace SUI {
namespace Widget {
    // The base class for all widgets.
    // It contains a position, width and height of the element.
    class Base {
        public:
            Base(u16 x, u16 y, u16 width, u16 height)
                : m_x(x), m_y(y), m_width(width), m_height(height) {};
            ~Base() {};

            virtual void Render() = 0;
            virtual void SetBackground(u8 red, u8 green, u8 blue) = 0;
            virtual void SetForeground(u8 red, u8 green, u8 blue) = 0;

        protected:
            u16 m_x, m_y;
            u16 m_width, m_height;

    };
}
}