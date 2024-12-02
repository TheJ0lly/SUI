#pragma once

#include <string>
#include <thread>

#include "core.hpp"
#include "opengl_wrapper.hpp"

namespace SUI {
namespace Widget {
    // The base class for all widgets.
    // It contains a position, width and height of the element.
    class IRenderable {
        public:
            IRenderable(f32 x, f32 y, f32 width, f32 height)
                : m_x(x), m_y(y), m_width(width), m_height(height) {};
            ~IRenderable() {};

            // Renders the specific item.
            virtual void Render(void) = 0;
            
            void SetBackground(u8 red, u8 green, u8 blue, u8 alpha) { m_background.color = (alpha << 24) | (blue << 16) | (green << 8) | red; }
            void SetBackground(GLW::Color c) { SetBackground(c.b.red, c.b.green, c.b.blue, c.b.alpha); }

            void SetForeground(u8 red, u8 green, u8 blue, u8 alpha) { m_foreground.color = (alpha << 24) | (blue << 16) | (green << 8) | red; }
            void SetForeground(GLW::Color c) { SetForeground(c.b.red, c.b.green, c.b.blue, c.b.alpha); }

            f32 GetX() { return m_x; }
            f32 GetY() { return m_y; }
            f32 GetWidth() { return m_width; }
            f32 GetHeight() { return m_height; }

        protected:
            f32 m_x, m_y;
            f32 m_width, m_height;
            GLW::Color m_background;
            GLW::Color m_foreground;

    };



    // This class represents a widget that contains text.
    class ITextArea {
        public:
            ITextArea(const char *text)
                :m_text(text) {};
            ~ITextArea() {};
            
            // Sets the text of the label.
            virtual void ChangeText(const char *text) = 0;
            std::string GetText() { return m_text; }

        protected:
            std::string m_text;
    };




    typedef struct {
        f64 xpos, ypos;
        s32 action, button, mods;
    } MouseEvent;

    typedef enum {
        // No highlight.
        NONE = 0,
        // The default behaviour.
        DEFAULT,
        /*
        A custom highlight behaviour.
        If you haven't set a custom function, `DefaultHighlightingFunc` will be used.
        */
        CUSTOM
    } HighlightType;
    
    // A generic function that is used for all click events.
    typedef void (*ClickFunc)(void *sender, void *eventArgs);

    // A generic function that is used to create custom highlighting.
    typedef void (*HighlightFunc)(GLW::Color &bkg, GLW::Color &fg);

    // The default highlighting function.
    const HighlightFunc DefaultHighlightingFunc = [](GLW::Color &bkg, GLW::Color &fg) -> void {
        bkg.b.red -= bkg.b.red < 28 ? 128 : bkg.b.red / 2;
        bkg.b.green -= bkg.b.green < 28 ? 128 : bkg.b.green / 2;
        bkg.b.blue -= bkg.b.blue < 28 ? 128 : bkg.b.blue / 2;
    };

    // This class represents a widget that can be clicked.
    class IClickable {
        public:
            IClickable(HighlightType ht)
                : m_highlightType(ht), m_highlightFunc(nullptr), m_clickFunc(nullptr) {};
            ~IClickable() {};

            virtual void Click(void) = 0;
            void SetClickFunc(ClickFunc func) { m_clickFunc = func; }
            void SetHighlightFunc(HighlightFunc func) { m_highlightFunc = func; }
        protected:
            HighlightType m_highlightType;
            HighlightFunc m_highlightFunc;
            ClickFunc m_clickFunc;
            std::thread m_clickThread;
    };




    // The base class for all widgets
    class BaseWidget : public IRenderable, public ITextArea, public IClickable {
        public:
            BaseWidget(const char *text, f32 x, f32 y, f32 width, f32 height, HighlightType ht)
                : IRenderable(x, y, width, height), ITextArea(text), IClickable(ht) {};
            ~BaseWidget() {};

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

                if (m_clickFunc != nullptr) {
                    // Do some drawing calls before and after.
                    m_clickThread = std::thread(m_clickFunc, this, nullptr);

                    // We immediately wait for the finishing of the thread.
                    m_clickThread.join();
                }

                // Then we just reset the background and foreground colors.
                m_background.color = prevBkg;
                m_foreground.color = prevFg;
            }
    };
}
}