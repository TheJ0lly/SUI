#pragma once

#include <GL/freeglut.h>

#include "utility.hpp"
#include "widget.hpp"

namespace SUI {
namespace Widget {
    class Label : public SUI::Widget::Base {
        public:
            Label(u16 x, u16 y, u16 width, u16 height, const char *text);
            ~Label();

            virtual void Render();
            virtual void SetBackground(u8 red, u8 green, u8 blue);
            virtual void SetForeground(u8 red, u8 green, u8 blue);
            void ChangeText(const char *text);
        
        private:
            std::string m_text;  
            u32 m_background;
            u32 m_foreground;
    };
}
}