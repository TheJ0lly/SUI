#pragma once

#include <string>

#include "core.hpp"
#include "opengl_wrapper.hpp"

namespace SUI {
namespace Widget {
    // The base class for all widgets.
    // It contains a position, width and height of the element.
    class IRenderable {
        public:
            IRenderable(f32 x, f32 y, f32 width, f32 height)
                : m_x(x), m_y(y), m_width(width), m_height(height) {};
            ~IRenderable() {};

            // Renders the specific item.
            virtual void Render(void) = 0;
            virtual void SetBackground(u8 red, u8 green, u8 blue, u8 alpha) { 
                m_background.color = (alpha << 24) | (blue << 16) | (green << 8) | red; 
                LOG("New background:\n  R: %d\n  G: %d\n  B: %d\n  A: %d\n\n", m_background.red, m_background.green, m_background.blue, m_background.alpha);
            };
            virtual void SetBackground(GLW::Color c) { SetBackground(c.b.red, c.b.green, c.b.blue, c.b.alpha); };

            virtual void SetForeground(u8 red, u8 green, u8 blue, u8 alpha) { 
                m_foreground.color = (alpha << 24) | (blue << 16) | (green << 8) | red;
                LOG("New foreground:\n  R: %d\n  G: %d\n  B: %d\n  A: %d\n\n", m_foreground.red, m_foreground.green, m_foreground.blue, m_foreground.alpha);
            };
            virtual void SetForeground(GLW::Color c) { SetForeground(c.b.red, c.b.green, c.b.blue, c.b.alpha); };

        protected:
            f32 m_x, m_y;
            f32 m_width, m_height;
            GLW::Color m_background;
            GLW::Color m_foreground;

    };

    // This class represents a widget that contains text.
    class ITextArea {
        public:
            ITextArea(const char *text)
                :m_text(text) {};
            ~ITextArea() {};
            
            // Sets the text of the label.
            virtual void ChangeText(const char *text) = 0;

        protected:
            std::string m_text;
    };
}
}