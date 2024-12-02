#pragma once

#include "../core_GL/core.hpp"
#include "../core_GL/opengl_wrapper.hpp"

namespace SUI {
namespace Widget {
    // It contains a position, width and height of the element.
    class IRenderable {
        public:
            IRenderable(f32 x, f32 y, f32 width, f32 height)
                : m_x(x), m_y(y), m_width(width), m_height(height) {};
            ~IRenderable() {};

            // Renders the specific item.
            virtual void Render(void) = 0;
            
            void SetBackground(u8 red, u8 green, u8 blue, u8 alpha) { m_background.color = (alpha << 24) | (blue << 16) | (green << 8) | red; }
            void SetBackground(GLW::Color c) { SetBackground(c.b.red, c.b.green, c.b.blue, c.b.alpha); }

            void SetForeground(u8 red, u8 green, u8 blue, u8 alpha) { m_foreground.color = (alpha << 24) | (blue << 16) | (green << 8) | red; }
            void SetForeground(GLW::Color c) { SetForeground(c.b.red, c.b.green, c.b.blue, c.b.alpha); }

            f32 GetX() { return m_x; }
            f32 GetY() { return m_y; }
            f32 GetWidth() { return m_width; }
            f32 GetHeight() { return m_height; }

        protected:
            f32 m_x, m_y;
            f32 m_width, m_height;
            GLW::Color m_background;
            GLW::Color m_foreground;

    };
}   
}