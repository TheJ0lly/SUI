#pragma once

#include "widget_base.hpp"

namespace SUI {
namespace Widget {
    class Button : public BaseWidget {
        public:
            Button(const char *text, f32 x, f32 y, f32 width, f32 height);
            ~Button();

            virtual void Render(void);

            virtual void ChangeText(const char *text);

            virtual void Click(void);
    };
}
}