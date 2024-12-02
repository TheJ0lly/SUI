#pragma once

#include "widget_base.hpp"

namespace SUI::Widget {
    class Checkbox : public BaseWidget {
        public:
            Checkbox(const char *text, f32 x, f32 y, f32 dist, HighlightType ht);
            ~Checkbox();

            virtual void ChangeText(const char *text);
        
            void SetValue(bool val);

            bool GetValue();

            virtual void Render(void);

        private:
            f32 m_txtbox_dist;
            bool m_checked;
    };
}