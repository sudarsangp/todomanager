#include "UI.h"

UI::UI() {
	try {
		tutorial = tutorial->getInstance();
	}catch (SchedulerPPException& e){
		cout << e.getMessage() << " " << endl;
	}
	try {
		logic = logic->getInstance();
	}catch (SchedulerPPException& e){
		cout << e.getMessage() << " " << endl;
	}
	_display = new Display( status, taskList );
}

UI::~UI() {
	delete _display;
}

string UI::readUserInput(string userInput) {
	stringstream userFeedback;

	*_display = logic->executeTextCommand(userInput);
	taskList = _display->getTaskList();
	userFeedback << displayTasks() << endl;
	userFeedback << _display->getStatus() << endl;

	return userFeedback.str();
}

string UI::displayTasks() {
	stringstream displayString;
	for(unsigned int i=0; i<taskList.size(); i++) {
		displayString << i+1 << ". " << taskList[i].getTaskName() <<" done: "<<taskList[i].getDone()<< ", start:" 
			<< taskList[i].getStartDateTime() << " end: " << taskList[i].getEndDateTime() << endl;
	}

	return displayString.str();
}