#pragma once

#include <string>

#include "widget_base.hpp"

namespace SUI::Widget {
    class Label : public BaseWidget {
        public:
            /*
            `padding` - if you set it to a non-zero value, it will draw a rectangle around the label text.
            */
            Label(const char *text, f32 x, f32 y, HighlightType ht);
            ~Label();

            virtual void Render(void);

            virtual void ChangeText(const char *text);
    };
}