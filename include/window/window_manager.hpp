#pragma once

#include "window.hpp"

namespace SUI {
    class WinMan {
        public:
            WinMan(void) = delete;
            static Window *GetInstance(void);
            static void SetInstance(Window *current);
        private:
            static Window *m_currentWindow;
    };
}