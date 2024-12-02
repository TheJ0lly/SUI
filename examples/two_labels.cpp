#include "../include/window/window.hpp"
#include "../include/widgets/label.hpp"
#include "../include/widgets/button.hpp"

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	auto win = SUI::Window("SUI: Simple UI", 400, 400);
	win.SetBackground(56, 56, 56, 255);

	auto l = new SUI::Widget::Label("Hello, World", 0, 0, SUI::Widget::NONE);
	// As long as Alpha is 0, everything is transparent.
	l->SetBackground(0, 0, 0, 90);
	l->SetForeground(255, 255, 255, 255);
	l->SetClickFunc([](void *sender, void *eventArgs) -> void {
		// Both of these work.
		auto t = (SUI::Widget::BaseWidget*)sender;
		// auto t = (SUI::Widget::Label*)sender;

		printf("I am clicked from the label with the text: %s\n", t->GetText().c_str());
	});

	auto bc = new SUI::Widget::Label("Another button", 100, 100, SUI::Widget::CUSTOM);
	bc->SetBackground(25, 25, 25, 255);
	bc->SetForeground(255, 255, 255, 255);
	bc->SetClickFunc([](void *sender, void *eventArgs) -> void {
		// Here we cast it as the actual type.
		auto t = (SUI::Widget::Label *)sender;
		printf("Hello! I'm the label with the text: \"%s\"\nAlso I can do this:\n", t->GetText().c_str());

		system("ls -la && echo '\n'");

	});
	bc->SetHighlightFunc([](SUI::GLW::Color &bkg, SUI::GLW::Color &fg) -> void {
		SUI::Widget::DefaultHighlightingFunc(bkg, fg);
		fg.b.red = 255;
		fg.b.green = 128;
		fg.b.blue = 218;
	});


	win.AddWidget(l);
	win.AddWidget(bc);
	
	win.Run();
}