#pragma once

// STD Libraries
#include <functional>
#include <vector>
#include <memory>

// OpenGL libraries
#include <GLFW/glfw3.h>

// Internal
#include "coretypes.hpp"
#include "widget.hpp"

namespace SUI {
    class Window {
        public:
            Window(const char *title, u16 width, u16 height);
            ~Window();

            /* All values should be passed in the range 0-255. */
            void SetBackground(u8 red, u8 green, u8 blue, u8 alpha);

            u16 GetWidth() const;

            u16 GetHeight() const;

            void AddWidget(SUI::Widget::Base *w);

            void Run(bool waitForEvents = false, u8 swapInterval = 1) const;

        private:
            // Window sizes
            u16 m_width;
            u16 m_height;

            GLFWwindow *m_window;
            std::function<void()> m_proccessEventsFunc;
            u32 m_background;
            std::vector<SUI::Widget::Base *> m_widgets;
    };
}
