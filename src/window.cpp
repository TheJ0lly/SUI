#include "../include/window.hpp"
#include "../include/utility.hpp"
#include "../include/window_manager.hpp"
#include <GL/freeglut.h>

SUI::Window::Window(const char *title, u16 width, u16 height)
    : m_width(width), m_height(height), m_window(nullptr) {
    m_widgets = std::vector<SUI::Widget::Base*>();

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
    SUI::WinMan::SetInstance(this);    
}


SUI::Window::~Window() { /* We free the window. */glfwDestroyWindow(m_window); }

void SUI::Window::SetBackground(u8 red, u8 green, u8 blue, u8 alpha) {
    glClearColor(
        Utility::U8ToGLclampf(red), 
        Utility::U8ToGLclampf(green), 
        Utility::U8ToGLclampf(blue), 
        Utility::U8ToGLclampf(alpha)
        );
}

u16 SUI::Window::GetWidth() const { return m_width; };

u16 SUI::Window::GetHeight() const { return m_height; }

void SUI::Window::SetWidth(u16 width) { m_width = width; };

void SUI::Window::SetHeight(u16 height) { m_height = height; }

void SUI::Window::AddWidget(SUI::Widget::Base *w) { m_widgets.push_back(w); }

void SUI::Window::Run(bool pollEvents, u8 swapInterval) {
    glfwSwapInterval(swapInterval);

    std::function<void()> ProccessEvents = glfwWaitEvents;

    if (pollEvents) {
        ProccessEvents = glfwPollEvents;
    }
    // Framebuffer resizing callback.
    glfwSetFramebufferSizeCallback(SUI::WinMan::GetInstance()->m_window, [](GLFWwindow *win, int width, int height) -> void {
        // We reset the orthographic projection matrix.
        SUI::WinMan::GetInstance()->ResetOrthoMatrix();
    });

    // Window resizing callback.
    glfwSetWindowSizeCallback(SUI::WinMan::GetInstance()->m_window, [](GLFWwindow *win, int width, int height) -> void {
        SUI::WinMan::GetInstance()->SetHeight(height);
        SUI::WinMan::GetInstance()->SetWidth(width);
        SUI::WinMan::GetInstance()->ResetOrthoMatrix();
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

void SUI::Window::ResetOrthoMatrix() {
     // We resize the viewport to the framebuffer size.
    glViewport(0, 0, m_width, m_height);
    // We reset the orthographic projection matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, m_width, m_height, 0);
}