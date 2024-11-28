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
    
    // A generic function that is used for all click events.
    typedef void (*ClickFunc)(void *sender, void *eventArgs);
    // This class represents a widget that can be clicked.
    class IClickable {
        public:
            IClickable()
                : m_func(nullptr) {};
            ~IClickable() {};

            virtual void Click(void) = 0;
            void SetClickFunc(ClickFunc func) { m_func = func; }
        protected:
            ClickFunc m_func;
            std::thread m_clickThread;
    };


    // The base class for all widgets
    class BaseWidget : public IRenderable, public ITextArea, public IClickable {
        public:
            BaseWidget(const char *text, f32 x, f32 y, f32 width, f32 height)
                : IRenderable(x, y, width, height), ITextArea(text), IClickable() {};
            ~BaseWidget() {};
    };
}
}