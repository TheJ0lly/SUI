#include "../include/window.hpp"
#include "../include/label.hpp"
#include "../include/button.hpp"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_RGBA);

	auto win = SUI::Window("SUI: Simple UI", 400, 400);
	win.SetBackground(56, 56, 56, 255);

	auto l = new SUI::Widget::Label("Hello, World", 100, 100, 5);
	// As long as Alpha is 0, everything is transparent.
	l->SetBackground(0, 0, 0, 90);
	l->SetForeground(255, 255, 255, 255);
	l->SetClickFunc([](void *sender, void *eventArgs) -> void {
		// Both of these work.
		auto t = (SUI::Widget::BaseWidget*)sender;
		// auto t = (SUI::Widget::Label*)sender;

		printf("I am clicked from the label with the text: %s\n", t->GetText().c_str());
	});

	auto b = new SUI::Widget::Label("Current Folder.", 20, 20);
	b->SetBackground(255, 128, 128, 255);
	b->SetForeground(255, 255, 255, 255);
	b->SetClickFunc([](void *sender, void *eventArgs) -> void {
		system("ls -la && echo '\n'");

	});

	win.AddWidget(l);
	win.AddWidget(b);
	
	win.Run();
}