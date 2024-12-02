#include "../include/window/window.hpp"
#include "../include/widgets/label.hpp"
#include "../include/widgets/button.hpp"
#include "../include/widgets/checkbox.hpp"


int main(int argc, char **argv) {
	glutInit(&argc, argv);

	auto win = SUI::Window("SUI: Simple UI", 400, 400);
	win.SetBackground(56, 56, 56, 255);

	auto cb = new SUI::Widget::Checkbox("Am I checked?", 10, 10, 15, SUI::Widget::NONE);
	cb->SetForeground(230, 230, 230, 255);
	cb->SetBackground(27, 27, 27, 255);
	cb->SetClickFunc([](void *sender, void *eventArgs) -> void {
		auto box = (SUI::Widget::Checkbox *) sender;
		
		box->SetValue(!box->GetValue());
	});

	win.AddWidget(cb);
	
	win.Run();
}