#include "../include/window.hpp"
#include "../include/window_manager.hpp"
#include <GL/freeglut.h>

namespace SUI {
    Window::Window(const char *title, u16 width, u16 height)
        : m_width(width), m_height(height), m_window(nullptr) {
        m_widgets = std::vector<Widget::IRenderable*>();

        if (!glfwInit()) {
            exit(1);
        }

        // TODO: These make the drawing to not work.
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


        // We create the window and the context.
        m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        ResetOrthoMatrix();

        // Creating a new window, automatically selects it as the current window.
        WinMan::SetInstance(this);    
    }


    Window::~Window() { /* We free the window. */glfwDestroyWindow(m_window); }

    void Window::SetBackground(u8 red, u8 green, u8 blue, u8 alpha) {
        m_background.color = (alpha << 24) | (blue << 16) | (green << 8) | red;
        glClearColor( red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f );
    }

    GLW::Color Window::GetBackground(void) {
        return m_background;
    }

    u16 Window::GetWidth(void) const { return m_width; };

    u16 Window::GetHeight(void) const { return m_height; }

    void Window::SetWidth(u16 width) { m_width = width; };

    void Window::SetHeight(u16 height) { m_height = height; }

    void Window::AddWidget(Widget::IRenderable *w) { m_widgets.push_back(w); }

    void Window::Run(bool pollEvents, u8 swapInterval) {
        glfwSwapInterval(swapInterval);

        void (*ProccessEvents)(void) = glfwWaitEvents;

        if (pollEvents) {
            ProccessEvents = glfwPollEvents;
        }
        // Framebuffer resizing callback.
        glfwSetFramebufferSizeCallback(WinMan::GetInstance()->m_window, [](GLFWwindow *win, int width, int height) -> void {
            // We reset the orthographic projection matrix.
            WinMan::GetInstance()->ResetOrthoMatrix();
        });

        // Window resizing callback.
        glfwSetWindowSizeCallback(WinMan::GetInstance()->m_window, [](GLFWwindow *win, int width, int height) -> void {
            WinMan::GetInstance()->SetHeight(height);
            WinMan::GetInstance()->SetWidth(width);
            WinMan::GetInstance()->ResetOrthoMatrix();
        });

        while (!glfwWindowShouldClose(m_window)) {
            // We clear the current frame and front buffer.
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            // We render all widgets of the current window onto the back buffer.
            for (auto w : m_widgets) {
                w->Render();
            }

            // We flush all drawing calls.
            glFlush();
            // We swap buffers.
            glfwSwapBuffers(m_window);
            
            
            // Either if we wait or poll events, we call one variable. 
            ProccessEvents();
        }
        glfwTerminate();
    }

    void Window::ResetOrthoMatrix() {
        // We resize the viewport to the framebuffer size.
        glViewport(0, 0, m_width, m_height);
        LOG("Setting viewport:\n  Width: %d\n  Height: %d\n\n", m_width, m_height);

        // We reset the orthographic projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, m_width, m_height, 0);
        LOG("Setting Ortographic Matrix:\n  Right: %d\n  Bottom: %d\n\n", m_width, m_height);
    }
}
