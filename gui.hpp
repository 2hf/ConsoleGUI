#pragma once
#include <Windows.h>
#include <deque>
#include <string>
#include <functional>
#include <iostream>
#include <utility>
#include <algorithm>
#include <thread>

inline HANDLE consoleOutHandle; 

enum class MENU {
	TABSELECTION,
	ELEMENTSELECTION
};
class element {
public:
	std::string name;
	std::function<void()> function;
public:
	// an element function shall not have any arguments.
	element(std::string name, std::function<void()> function);
};
class tab {
public:
	std::string name;
	std::deque<element> elementArray;
public:
	tab(std::string name, std::deque<element> elementArray);
};
class gui {
public:
	std::deque<tab> tabArray;
	int selectedTab;
	MENU menuPage;
	int hoveredTextIndex;
public:
	gui(std::deque<tab> tabArray);
	void clearConsole();
	void setConsoleColor(unsigned short color);
	void render();
	MENU intToEnum(int index);
	void input();
};