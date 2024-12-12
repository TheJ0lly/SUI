#pragma once


#include "../interfaces/IRenderable.hpp"
#include "../interfaces/ITextArea.hpp"
#include "../interfaces/IClickable.hpp"

namespace SUI::Widget {
    // The base class for all widgets
    class BaseWidget : public IRenderable, public ITextArea, public IClickable {
        public:
            BaseWidget(const char *text, f32 x, f32 y, f32 width, f32 height, HighlightType ht)
                : IRenderable(x, y, width, height), ITextArea(text), IClickable(ht) {};
            ~BaseWidget() {};

            // The default Click function. Can be overwritten.
            virtual void Click(void) {
                u32 prevBkg = m_background.color;
                u32 prevFg = m_foreground.color;

                switch(m_highlightType) {
                case DEFAULT:
                    DefaultHighlightingFunc(m_background, m_foreground);
                    break;
                case CUSTOM:
                    if (m_highlightFunc == nullptr)
                        DefaultHighlightingFunc(m_background, m_foreground);
                    else
                        m_highlightFunc(m_background, m_foreground);

                    break;

                default: // This should be the NONE case.
                    break;
                }

                Render();
                
                // Then we just reset the background and foreground colors.
                // We must do this after the render call, because the click func may change the colors.
                m_background.color = prevBkg;
                m_foreground.color = prevFg;

                if (m_clickFunc != nullptr) {
                    // Do some drawing calls before and after.
                    m_clickThread = std::thread(m_clickFunc, (void *)this, nullptr);

                    // We immediately wait for the finishing of the thread.
                    m_clickThread.join();
                }

            }

            void SetParent(void *obj) {parent = obj;}
            void *GetParent() {return parent;}

        private:
            void *parent;
    };
}