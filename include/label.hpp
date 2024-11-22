#pragma once

#include <GL/freeglut.h>

#include "utility.hpp"
#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Label : public SUI::Widget::Base {
        public:
            Label(u16 x, u16 y, u16 width, u16 height, const char *text);
            ~Label();

            // Renders the specific item.
            virtual void Render();

            // Sets the background color.
            virtual void SetBackground(u8 red, u8 green, u8 blue);

            // Sets the foreground color.
            virtual void SetForeground(u8 red, u8 green, u8 blue);

            // Sets the text of the label.
            void ChangeText(const char *text);
        
        private:
            std::string m_text;

            // The colors
            u32 m_background;
            u32 m_foreground;
    };
}
}