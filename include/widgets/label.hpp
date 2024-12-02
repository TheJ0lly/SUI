#pragma once

#include <string>

#include "widget_base.hpp"

namespace SUI::Widget {
    class Label : public BaseWidget {
        public:
            Label(const char *text, f32 x, f32 y, HighlightType ht);
            ~Label();

            virtual void Render(void);

            virtual void ChangeText(const char *text);
    };
}