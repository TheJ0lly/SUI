#pragma once

#include "window.hpp"

namespace SUI {
    class WinMan {
        public:
            WinMan() = delete;
            static Window *GetInstance();
            static void SetInstance(Window *current);
        private:
            static Window *m_currentWindow;
    };
}