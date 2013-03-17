//@author A0086671W

#include "Display.h"

Display::Display( string status, vector<Task> tasks ) {
	_status = status;
	_tasks = tasks;
}

Display::Display( string status )
{
	_status = status;
}

string Display::getStatus() {
	return _status;
}

vector<Task> Display::getTaskList() {
	return _tasks;
}

int Display::getDisplaySize() {
	return (int)_tasks.size();
}

void Display::clearStatus()
{
	_status = "";
}
