#pragma once

#include <GL/freeglut.h>

#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Label : public SUI::Widget::IRenderable {
        public:
            Label(u16 x, u16 y, u16 width, u16 height, const char *text);
            ~Label();

            // Renders the specific item.
            virtual void Render();

            // Sets the text of the label.
            void ChangeText(const char *text);
        
        private:
            std::string m_text;
    };
}
}