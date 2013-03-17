#include "LogicAdd.h"

// @author A0086671W
LogicAdd* LogicAdd::_logicAdd = NULL;

LogicAdd& LogicAdd::getInstance() {

	if (_logicAdd == NULL) {
		_logicAdd = new LogicAdd();
	}

	return *_logicAdd;
}

Display LogicAdd::addFloatingTask(string taskName) {
	Task _task;
	string statusMessage;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	int currentTaskID;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	// task creation
	_task = Task(taskName, 0, Task::FLOATING, false, 0, not_a_date_time, not_a_date_time);

	// add into internal data
	dataFeedback = _data->executeAdd(_task);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << _task.getTaskName() << ERROR_LOG_CONCAT;
		log << _task.getTaskType() << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	currentTaskID = _data->getCurrentTaskID();

	_task.setTaskID(currentTaskID);
	
	if( dataFeedback == Data::SUCCESS ) {
		updateFileContents(tasks);
		displayMsg << SUCCESS_ADD_MESSAGE << taskName;
		LogicUndo::getInstance().undoStackPush(*_data);
	} else {
		displayMsg << ERROR_ADD_MESSAGE;
	}

	// update UI's display
	_display = Display(displayMsg.str(), tasks);

	return _display;
}

Display LogicAdd::addDeadlineTask(string taskName, ptime endTime) {
	Task _task;
	string statusMessage;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	int currentTaskID;
	stringstream displayMsg;
	bool pastTime;

	displayMsg.str(RESET_STATUS);

	pastTime = isDatePast( endTime );
	if( pastTime == true ) {
		displayMsg << ERROR_DATE_PAST_MESSAGE;
		tasks = _display.getTaskList();
		_display = Display(displayMsg.str(), tasks);
		return _display;
	}

	// task creation
	_task = Task(taskName, 0, Task::DEADLINE, false, 0, not_a_date_time, endTime);

	// add to internal data
	dataFeedback = _data->executeAdd(_task);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << _task.getTaskName() << ERROR_LOG_CONCAT;
		log << _task.getTaskType() << ERROR_LOG_CONCAT;
		log << _task.getEndDateTime() << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	// update UI's display
	currentTaskID = _data->getCurrentTaskID();
	_task.setTaskID(currentTaskID);

	// return status message to UI
	if( dataFeedback == Data::SUCCESS ) {
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_ADD_MESSAGE << taskName;
		displayMsg << ADD_DEADLINE_BY_CONNECTOR << endTime.date();
	} else {
		displayMsg << ERROR_ADD_MESSAGE;
	}

	// update UI's display
	_display = Display(displayMsg.str(), tasks);

	return _display;
}

Display LogicAdd::addTimedTask(string taskName, ptime startTime, ptime endTime) {
	Task _task;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	bool clash;
	int currentTaskID;
	stringstream displayMsg;
	bool pastStartTime;
	bool pastEndTime;

	displayMsg.str(RESET_STATUS);

	pastStartTime = isDatePast( startTime );
	pastEndTime = isDatePast( endTime );
	if( pastStartTime == true || pastEndTime == true ) {
		displayMsg << ERROR_DATE_PAST_MESSAGE;
		tasks = _display.getTaskList();
		_display = Display(displayMsg.str(), tasks);
		return _display;
	}

	if( !isDateCorrectFormat(startTime, endTime) ) {
		displayMsg << ERROR_DATE_START_END_MESSAGE;
		tasks = _display.getTaskList();
		_display = Display(displayMsg.str(), tasks);
		return _display;
	}

	// task creation
	_task = Task(taskName, 0, Task::TIMED, false, 0, startTime, endTime);

	// add to internal data
	dataFeedback = _data->executeAdd(_task);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << _task.getTaskName() << ERROR_LOG_CONCAT;
		log << _task.getTaskType() << ERROR_LOG_CONCAT;
		log << _task.getStartDateTime() << ERROR_LOG_CONCAT;
		log << _task.getEndDateTime() << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	// update UI's display
	currentTaskID = _data->getCurrentTaskID();
	_task.setTaskID(currentTaskID);

	clash = false;
	clash = isDateClash(startTime, endTime, currentTaskID);

	// return status message to UI
	if( dataFeedback == Data::SUCCESS ) {
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_ADD_MESSAGE << taskName;
		displayMsg << ADD_TIMED_FROM_CONNECTOR << startTime.date();
		displayMsg << ADD_TIMED_TO_CONNECTOR << endTime.date();
		if( clash ) {
			displayMsg << ERROR_ADD_CLASH_MESSAGE;
		}
	}

	// update UI's display
	_display = Display(displayMsg.str(), tasks);

	return _display;
}

const string LogicAdd::SUCCESS_ADD_MESSAGE = "Task added: ";

const string LogicAdd::ADD_DEADLINE_BY_CONNECTOR = " By ";
const string LogicAdd::ADD_TIMED_FROM_CONNECTOR = " From ";
const string LogicAdd::ADD_TIMED_TO_CONNECTOR = " To ";

const string LogicAdd::ERROR_ADD_CLASH_MESSAGE = " [CLASH]";
const string LogicAdd::ERROR_ADD_MESSAGE = "Unable to add";