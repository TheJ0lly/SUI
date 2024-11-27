#pragma once

#include <iostream>

#include "core.hpp"
#include "opengl_wrapper.hpp"


namespace SUI {
namespace Widget {
    // The base class for all widgets.
    // It contains a position, width and height of the element.
    class IRenderable {
        public:
            IRenderable(u16 x, u16 y, u16 width, u16 height)
                : m_x(x), m_y(y), m_width(width), m_height(height) {};
            ~IRenderable() {};

            virtual void Render() = 0;
            virtual void SetBackground(u8 red, u8 green, u8 blue, u8 alpha) { 
                m_background.color = (alpha << 24) | (blue << 16) | (green << 8) | red; 
                LOG("New background:\n  R: %d\n  G: %d\n  B: %d\n  A: %d\n\n", m_background.red, m_background.green, m_background.blue, m_background.alpha);
            };
            virtual void SetBackground(GLW::Color c) { SetBackground(c.red, c.green, c.blue, c.alpha); };

            virtual void SetForeground(u8 red, u8 green, u8 blue, u8 alpha) { 
                m_foreground.color = (alpha << 24) | (blue << 16) | (green << 8) | red;
                LOG("New foreground:\n  R: %d\n  G: %d\n  B: %d\n  A: %d\n\n", m_foreground.red, m_foreground.green, m_foreground.blue, m_foreground.alpha);
            };
            virtual void SetForeground(GLW::Color c) { SetForeground(c.red, c.green, c.blue, c.alpha); };

        protected:
            u16 m_x, m_y;
            u16 m_width, m_height;
            GLW::Color m_background;
            GLW::Color m_foreground;

    };
}
}