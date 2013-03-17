#include "LogicSort.h"

// @author A0086671W
LogicSort* LogicSort::_logicSort = NULL;

LogicSort& LogicSort::getInstance() {
	if(_logicSort == NULL) {
		_logicSort = new LogicSort();
	}

	return *_logicSort;
}

Display LogicSort::sortTasksAlphabetically() {
	
	stringstream displayMsg;
	vector<Task> display;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// sort UI's display
	sort(display.begin(), display.end(), sortObjAlpha);

	displayMsg << SUCCESS_SORT_ALPHA_MESSAGE;

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicSort::sortTasksByFlag() {

	stringstream displayMsg;
	vector<Task> display;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// sort UI's display
	sort(display.begin(), display.end(), sortObjFlag);
	
	displayMsg << SUCCESS_SORT_FLAG_MESSAGE;

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicSort::sortTasksByDateTime() {
	stringstream displayMsg;
	vector<Task> display;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	sort(display.begin(), display.end(), sortObjDateTime);

	displayMsg << SUCCESS_SORT_DATE_TIME_MESSAGE;

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicSort::sortTasksByDone() {

	stringstream displayMsg;
	vector<Task> display;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// sort UI's display
	sortByDone(display);

	displayMsg << SUCCESS_SORT_DONE_MESSAGE;

	_display = Display( displayMsg.str(), display );

	return _display;
}

void LogicSort::sortByDone(vector<Task>& tasksVector) {
	
	vector<Task> doneTasks;
	vector<Task> undoneTasks;

	// populate doneTasks with done tasks
	for( unsigned int i=0; i<tasksVector.size(); i++ ) {
		if(tasksVector[i].getDone() == true) {
			doneTasks.push_back(tasksVector[i]);
		}
	}
	// sort the done tasks alphabetically
	sort(doneTasks.begin(), doneTasks.end(), sortObjAlpha);

	// populate undoneTasks with undone tasks
	for( unsigned int j=0; j<tasksVector.size(); j++ ) {
		if( tasksVector[j].getDone() == false ) {
			undoneTasks.push_back(tasksVector[j]);
		}
	}
	// sort the undone tasks alphabetically
	sort(undoneTasks.begin(), undoneTasks.end(), sortObjAlpha);
	//check 
	LogicUndo::getInstance().undoStackPush(*_data);

	tasksVector.clear();

	for( unsigned int k=0; k<doneTasks.size(); k++ ) {
		tasksVector.push_back(doneTasks[k]);
	}
	
	for( unsigned int l=0; l<undoneTasks.size(); l++ ) {
		tasksVector.push_back(undoneTasks[l]);
	}
}

bool LogicSort::sortAlpha(Task t1, Task t2) {
	return t1.getTaskName() < t2.getTaskName();
}

bool LogicSort::sortDateTime(Task t1, Task t2) {
	return t1.getStartDateTime() < t2.getStartDateTime();
}

bool LogicSort::sortFlag( Task t1, Task t2 ) {
	return t1.getPriority() < t2.getPriority();
}

const string LogicSort::SUCCESS_SORT_MESSAGE = "Sort completed.";
const string LogicSort::SUCCESS_SORT_ALPHA_MESSAGE = "Sorted by alphabetical order.";
const string LogicSort::SUCCESS_SORT_DONE_MESSAGE = "Sorted by completed tasks on top.";
const string LogicSort::SUCCESS_SORT_FLAG_MESSAGE = "Sorted by flagged tasks on top.";
const string LogicSort::SUCCESS_SORT_DATE_TIME_MESSAGE = "Sorted by date and time.";

const string LogicSort::SORT_EMPTY_DISPLAY = "No tasks on display to sort.";
const string LogicSort::ERROR_SORT_MESSAGE = "Unable to sort.";
const string LogicSort::ERROR_SORT_FLAG_MESSAGE = "Unable to sort by flagged tasks.";
const string LogicSort::ERROR_SORT_DATE_TIME_MESSAGE = "Unable to sort by date time.";
const string LogicSort::ERROR_SORT_DONE_MESSAGE = "Unable to sort by completed tasks.";