#include "../include/window/window.hpp"
#include "../include/widgets/label.hpp"
#include "../include/widgets/button.hpp"

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	auto win = SUI::Window("SUI: Simple UI", 400, 400);
	win.SetBackground(56, 56, 56, 255);

	auto b = new SUI::Widget::Button("Current Folder", 20, 20, 144, 50, SUI::Widget::DEFAULT);
	b->SetBackground(255, 128, 128, 255);
	b->SetForeground(255, 255, 255, 255);
	b->SetClickFunc([](void *sender, void *eventArgs) -> void {
		// Here we cast it as the actual type.
		auto t = (SUI::Widget::Button *)sender;
		printf("Hello! I'm the button with the text: \"%s\"\nAlso I can do this:\n", t->GetText().c_str());

		system("ls -la && echo '\n'");

	});

	win.AddWidget(b);
	
	win.Run();
}