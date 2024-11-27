#include "../include/window_manager.hpp"

SUI::Window *SUI::WinMan::m_currentWindow;

SUI::Window *SUI::WinMan::GetInstance(void) { return SUI::WinMan::m_currentWindow; }

void SUI::WinMan::SetInstance(Window *current) { SUI::WinMan::m_currentWindow = current; }