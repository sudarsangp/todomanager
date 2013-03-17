#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <sstream>

#include "Logic.h"
#include "Task.h"
#include "Display.h"
#include "LogicTutorial.h"

using namespace std;

class UI {
	Logic* logic;
	LogicTutorial * tutorial;
	vector<Task> taskList;

	string displayTasks();

	Display* _display;

	string status;

public:
	string readUserInput(string userInput);
	
	UI();
	~UI();
};

#endif UI_H