#pragma once

#include <string>

#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Label : public IRenderable, public ITextArea {
        public:
            Label(const char *text, u16 x, u16 y, u16 padding=0);
            ~Label();

            virtual void Render(void);

            virtual void ChangeText(const char *text);
        
        private:
            u16 m_pad;
    };
}
}