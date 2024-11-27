#pragma once

#include <string>

#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Label : public SUI::Widget::IRenderable {
        public:
            Label(const char *text, u16 x, u16 y, u16 padding=0);
            ~Label();

            // Renders the specific item.
            virtual void Render(void);

            // Sets the text of the label.
            void ChangeText(const char *text);
        
        private:
            std::string m_text;
            u16 m_pad;
    };
}
}