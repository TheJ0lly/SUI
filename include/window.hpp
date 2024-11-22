#pragma once

// STD Libraries
#include <functional>
#include <vector>
#include <memory>

// OpenGL libraries
#include <GLFW/glfw3.h>

// Internal
#include "coretypes.hpp"
#include "widget_base.hpp"

namespace SUI {
    class Window {
        public:
            Window(const char *title, u16 width, u16 height);
            ~Window();

            /* All values should be passed in the range 0-255. */
            void SetBackground(u8 red, u8 green, u8 blue, u8 alpha);

            /*
            Get window width.
            */
            u16 GetWidth() const;

            /*
            Get window height.
            */
            u16 GetHeight() const;

            /*
            Add a new widget that the window should manage.
            */
            void AddWidget(SUI::Widget::Base *w);

            /*
            Run the program.

            `waitForEvents` - if set to `true`, we will use glfwWaitEvents instead of glfwPollEvents.
            `swapInterval`  - the minimum amount of frames to pass before we swap buffers.
            */ 
            void Run(bool waitForEvents = false, u8 swapInterval = 1) const;

        private:
            // Window sizes
            u16 m_width;
            u16 m_height;

            // The window
            GLFWwindow *m_window;

            // The background color
            u32 m_background;

            // The widgets this window will handle.
            std::vector<SUI::Widget::Base *> m_widgets;
    };
}
