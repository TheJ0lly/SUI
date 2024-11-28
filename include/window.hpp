#pragma once

// STD Libraries
#include <vector>

// OpenGL libraries
#include <GLFW/glfw3.h>

// Internal
#include "core.hpp"
#include "widget_base.hpp"

namespace SUI {
    class Window {
        public:
            Window(const char *title, u16 width, u16 height);
            ~Window();

            /* All values should be passed in the range 0-255. */
            void SetBackground(u8 red, u8 green, u8 blue, u8 alpha);

            GLW::Color GetBackground(void);

            /*
            Get window width.
            */
            u16 GetWidth(void) const;

            /*
            Get window height.
            */
            u16 GetHeight(void) const;

            /*
            Set window width.
            */
            void SetWidth(u16 width);

            /*
            Set window height.
            */
            void SetHeight(u16 height);

            /*
            Add a new widget that the window should manage.
            */
            void AddWidget(Widget::BaseWidget *w);

            /*
            Triggers when there is a click on the current window.
            Sets `m_selected` to the clicked widget.
            */
            void CheckClick(Widget::MouseEvent eventArgs);

            /*
            Run the program.

            `pollEvents`    - if set to `true`, we will use `glfwPollEvents` instead of `glfwWaitEvents`.
            `swapInterval`  - the minimum amount of frames to pass before we swap buffers.
            */ 
            void Run(bool pollEvents = false, u8 swapInterval = 1);

        private:
            void ResetOrthoMatrix(void);

            // Window sizes
            u16 m_width;
            u16 m_height;

            // The window
            GLFWwindow *m_window;

            Widget::BaseWidget *m_selected;

            // The background color
            GLW::Color m_background;

            // The widgets this window will handle.
            std::vector<Widget::BaseWidget *> m_widgets;
    };
}
