//@author A0086671W

#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>

#include "Task.h"

using namespace std;

class Display {
public:
	Display( string status, vector<Task> tasks );
	Display( string status );
	Display() {};

	string getStatus();
	void clearStatus();
	vector<Task> getTaskList();

	int getDisplaySize();

private:
	string _status;
	vector<Task> _tasks;
};
#endif