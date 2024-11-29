#pragma once

#include <string>

#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Label : public BaseWidget {
        public:
            /*
            `padding` - if you set it to a non-zero value, it will draw a rectangle around the label text.
            */
            Label(const char *text, f32 x, f32 y, HighlightType ht, u16 padding=0);
            ~Label();

            virtual void Render(void);

            virtual void ChangeText(const char *text);

            virtual void Click(void);
        
        private:
            u16 m_pad;
    };
}
}