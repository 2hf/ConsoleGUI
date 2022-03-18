#include "gui.hpp"
element::element(std::string name, std::function<void()> function) {
	this->name = name;
	this->function = function;
}
tab::tab(std::string name, std::deque<element> elementArray) {
	this->elementArray = elementArray;
	this->name = name;
}
gui::gui(std::deque<tab> tabArray) {
	this->tabArray = tabArray;
	consoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}
void gui::clearConsole() {

	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(consoleOutHandle, &screen);
	FillConsoleOutputCharacterA(
		consoleOutHandle, ' ', screen.dwSize.X * screen.dwSize.Y, { 0, 0 }, &written
	);
	FillConsoleOutputAttribute(
		consoleOutHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, { 0, 0 }, &written
	);
	SetConsoleCursorPosition(consoleOutHandle, { 0, 0 });
}
void gui::setConsoleColor(unsigned short color)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, color);
}
void gui::render() {
	clearConsole();
	switch (menuPage) {
	case MENU::TABSELECTION:
	{
		int index = 0;
		// render tabs
		for (const auto& tab : tabArray) {
			std::cout << (hoveredTextIndex == index ? "-> " : "") << tab.name.c_str() << std::endl;
			++index;
		}
		break;
	}
	case MENU::ELEMENTSELECTION:
	{
		int index = -1;
		std::cout << (hoveredTextIndex == -1 ? "-> " : "") << "back" << std::endl;
		++index;
		// render elements
		for (const auto& tab : tabArray) {
			const auto& elementArray = tab.elementArray;
			for (const auto& element : elementArray) {
				std::cout << (hoveredTextIndex == index ? "-> " : "") << element.name.c_str() << std::endl;
				++index;
			}
		}
		break;
	}
	}
}
MENU gui::intToEnum(int index) {
	switch (index) {
	case 0:
	{
		return MENU::TABSELECTION;
		break;
	}
	case 1:
	{
		return MENU::ELEMENTSELECTION;
		break;
	}
	}
	return MENU::TABSELECTION;
}
void gui::input() {
	if (GetAsyncKeyState(VK_DOWN)) {
		++hoveredTextIndex;
		switch (menuPage) {
		case MENU::TABSELECTION:
		{
			hoveredTextIndex = std::clamp<int>(hoveredTextIndex, 0, tabArray.size() - 1);
			break;
		}
		case MENU::ELEMENTSELECTION:
		{
			const auto& tab = tabArray.at(selectedTab);
			hoveredTextIndex = std::clamp<int>(hoveredTextIndex, -1, tab.elementArray.size() - 1);
			break;
		}
		}
	}
	else if (GetAsyncKeyState(VK_UP)) {
		--hoveredTextIndex;
		switch (menuPage) {
		case MENU::TABSELECTION:
		{
			hoveredTextIndex = std::clamp<int>(hoveredTextIndex, 0, tabArray.size() - 1);
			break;
		}
		case MENU::ELEMENTSELECTION:
		{
			const auto& tab = tabArray.at(selectedTab);
			hoveredTextIndex = std::clamp<int>(hoveredTextIndex, -1, tab.elementArray.size() - 1);
			break;
		}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		switch (menuPage) {
		case MENU::TABSELECTION:
		{
			menuPage = intToEnum(hoveredTextIndex);
			break;
		}
		case MENU::ELEMENTSELECTION:
		{
			if (hoveredTextIndex == -1) {
				menuPage = MENU::TABSELECTION;
			}
			else {
				const auto& tab = tabArray.at(selectedTab);
				const auto& element = tab.elementArray.at(hoveredTextIndex);
				element.function();
			}
			break;
		}
		}
		hoveredTextIndex = 0;
	}
	else  if (GetAsyncKeyState(VK_LEFT)) {
		if (menuPage == MENU::ELEMENTSELECTION && hoveredTextIndex == -1) {
			menuPage = MENU::TABSELECTION;
			hoveredTextIndex = 0;
		}
	}
}