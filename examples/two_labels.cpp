#include "../include/window.hpp"
#include "../include/label.hpp"
#include "../include/opengl_wrapper.hpp"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	SUI::Window win = SUI::Window("SUI: Simple UI", 400, 400);
	win.SetBackground(56, 56, 56, 255);

	auto l = new SUI::Widget::Label("Hello, World!", 100, 100);
	l->SetBackground(win.GetBackground());
	l->SetForeground(255, 255, 255, 255);

	auto w = new SUI::Widget::Label("WTF IS GOING ON!", 600, 600, 20);
	w->SetBackground(128, 255, 128, 255);
	w->SetForeground(0, 0, 0, 255);

	win.AddWidget(l);
	win.AddWidget(w);
	
	win.Run();
}