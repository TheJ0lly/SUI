#include "../include/window.hpp"
#include "../include/utility.hpp"
#include "../include/window_manager.hpp"
#include <GL/freeglut.h>

SUI::Window::Window(const char *title, u16 width, u16 height)
    : m_width(width), m_height(height), m_window(nullptr) {
    this->m_widgets = std::vector<SUI::Widget::Base*>();

    if (!glfwInit()) {
        exit(1);
    }

    // TODO: These make the drawing to not work.
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // We create the window and the context.
    this->m_window = glfwCreateWindow(this->m_width, this->m_height, title, nullptr, nullptr);
    glfwMakeContextCurrent(this->m_window);

    // Creating a new window, automatically selects it as the current window.
    SUI::WinMan::SetInstance(this);    
}

SUI::Window::~Window() {
    // We free the window.
    glfwDestroyWindow(this->m_window);
}

void SUI::Window::SetBackground(u8 red, u8 green, u8 blue, u8 alpha) {
    glClearColor(
        Utility::U8ToGLclampf(red), 
        Utility::U8ToGLclampf(green), 
        Utility::U8ToGLclampf(blue), 
        Utility::U8ToGLclampf(alpha)
        );
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

    // The dynamic variables at runtime.
    s32 new_height = this->m_height, new_width = this->m_width;
    s32 fbHeight, fbWidth;
    // We get the first frame buffer sizes.
    glfwGetFramebufferSize(this->m_window, &fbWidth, &fbHeight);

    while (!glfwWindowShouldClose(this->m_window)) {
        
        // TODO: As of now, we will always check for the window size, and if something has changed, we get the new
        // framebuffer size 
        glfwGetWindowSize(this->m_window, &new_width, &new_height);
        if (new_height != this->m_height || new_width != this->m_width) {
            // We get the new framebuffer sizes.
            glfwGetFramebufferSize(this->m_window, &fbWidth, &fbHeight);
            // We set the new viewport.
            glViewport(0, 0, fbWidth, fbHeight);
        }
        
        // We clear the current frame and front buffer.
        glClear(GL_COLOR_BUFFER_BIT);

        // We render all widgets of the current window onto the back buffer.
        for (auto w : this->m_widgets) {
            w->Render();
        }

        // We swap buffers.
        glfwSwapBuffers(this->m_window);
        // Either if we wait or poll events, we call one variable. 
        ProccessEvents();
    }
    glfwTerminate();
}