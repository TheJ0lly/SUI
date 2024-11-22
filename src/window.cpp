#include "../include/window.hpp"
#include "../include/utility.hpp"

SUI::Window::Window(const char *title, u16 width, u16 height)
    : m_width(width), m_height(height), m_window(nullptr, glfwDestroyWindow) {
    this->m_widgets = std::vector<SUI::Widget::Base*>();

    if (!glfwInit()) {
        exit(1);
    }

    // We set the OpenGL version 4.6.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // We create the window and the context.
    this->m_window.reset(glfwCreateWindow(this->m_width, this->m_height, title, nullptr, nullptr));
    glfwMakeContextCurrent(this->m_window.get());
}

SUI::Window::~Window() {
    // We free the window.
    glfwDestroyWindow(this->m_window.release());
}

void SUI::Window::SetBackground(u8 red, u8 green, u8 blue, u8 alpha) {
    glClearColor(red, green, blue, alpha);
}

u16 SUI::Window::GetWidth() const {
    return this->m_width;
};

u16 SUI::Window::GetHeight() const {
    return this->m_height;
}

void SUI::Window::AddWidget(SUI::Widget::Base *w) {
    this->m_widgets.push_back(w);
}

void SUI::Window::Run(bool waitForEvents, u8 swapInterval) const {
    glfwSwapInterval(swapInterval);

    std::function<void()> ProccessEvents = glfwPollEvents;

    if (waitForEvents) {
        ProccessEvents = glfwWaitEvents;
    }

    while (!glfwWindowShouldClose(this->m_window.get())) {

        // We clear the current frame and front buffer.
        glClear(GL_COLOR_BUFFER_BIT);
        
        // We render all widgets of the current window onto the back buffer.
        for (auto w : this->m_widgets) {
            w->Render();
        }


        // We swap buffers.
        glfwSwapBuffers(this->m_window.get());
        // Either if we wait or poll events, we call one variable. 
        ProccessEvents();
    }
    glfwTerminate();
}