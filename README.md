# ConsoleGUI
W.I.P Console GUI

GUI Inheritance: gui->tabarray(tab1->elementarray(element1),tab2->elementarray(),tab3->elementarray())

example:

```cpp
#include "GUI\gui.hpp"

void Sleep500ms() {
	Sleep(500);
}

int main()
{
	std::deque<element> page_1 = { element ("Sleep for 500ms",Sleep500ms)};
	std::deque<element> page_2 = {};
	std::deque<element> page_3 = {};

	std::deque<tab> tabs = { tab("Nothing here",page_1), tab("Sleep (500ms) element here",page_2),tab("Nothing here #2",page_3) };
	gui main_gui = gui(tabs);
	while (1) {
		main_gui.render();
		main_gui.input();
		Sleep(200);
	}
}
```
