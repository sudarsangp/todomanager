#include "LogicEdit.h"

// @author A0086671W
LogicEdit* LogicEdit::_logicEdit = NULL;

LogicEdit& LogicEdit::getInstance() {
	if (_logicEdit == NULL) {
		_logicEdit = new LogicEdit;
	}

	return *_logicEdit;
}

Display LogicEdit::editTaskByName( string taskName, int index ) {
	Task _task;
	int taskID;
	string oldTaskName;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// find task on display
	taskID = display[index-1].getTaskID();

	// if no changes made
	if( display[index-1].getTaskName() == taskName ) {
		displayMsg << ERROR_EDIT_NO_CHANGES_MESSAGE;
	} else {
		oldTaskName = display[index-1].getTaskName();
		// update display
		display[index-1].setTaskName(taskName);
		// set edited task attributes
		_task = display[index-1];

		// update internal data
		dataFeedback = _data->executeEdit(_task);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << ERROR_EDIT_MESSAGE << "RENAME" << ERROR_LOG_CONCAT;
			log << taskName << ERROR_LOG_CONCAT;
			log << _task.getTaskName() << ERROR_LOG_CONCAT;
			log << _task.getTaskID() << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}

		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		displayMsg << SUCCESS_EDIT_RENAME;
		displayMsg << EDIT_FROM_CONNECTOR << oldTaskName;
		displayMsg << EDIT_TO_CONNECTOR << taskName;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicEdit::editTaskByStartTime( time_duration newStartTime, int index ) {
	Task _task;
	int taskID;
	string taskName;
	time_duration oldStartTime;
	time_duration endTime;
	ptime newStartDate;
	ptime endDate;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	stringstream displayMsg;
	bool isDeadline;
	bool clash;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// find task on display
	taskID = display[index-1].getTaskID();

	if( display[index-1].getStartDateTime().time_of_day() == newStartTime ) {
		displayMsg << ERROR_EDIT_NO_CHANGES_MESSAGE;
	} else if ( display[index-1].getTaskType() == Task::FLOATING ) {
		displayMsg << ERROR_EDIT_FLOAT_TASK_TIME_MESSAGE;
	}else {
		if ( display[index-1].getStartDateTime() == not_a_date_time ) {
			isDeadline = true;
			display[index-1].setTaskType(Task::TIMED);
		} else {
			isDeadline = false;
		}

		_task = display[index-1];
		taskName = _task.getTaskName();
		oldStartTime = _task.getStartDateTime().time_of_day();
		endDate = _task.getEndDateTime();
		endTime = _task.getEndDateTime().time_of_day();

		newStartDate = _task.getStartDateTime();
		if( newStartDate == not_a_date_time ) {
			newStartDate = second_clock::local_time();
		}
		
		newStartDate = ptime(newStartDate.date(), newStartTime);

		clash = isDateClash(newStartDate, endDate, taskID);

		if( !isDateCorrectFormat(newStartDate, endDate) ) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( !isTimeCorrectFormat(newStartTime, endTime)) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( isDatePast(newStartDate) ) {
			displayMsg << ERROR_DATE_PAST_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		// update display
		display[index-1].setStartDateTime(newStartDate);
		// set edited task attributes
		_task = display[index-1];

		// update internal data
		dataFeedback = _data->executeEdit(_task);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << ERROR_EDIT_MESSAGE << "START-TIME" << ERROR_LOG_CONCAT;
			log << newStartTime << ERROR_LOG_CONCAT;
			log << _task.getTaskName() << ERROR_LOG_CONCAT;
			log << _task.getTaskID() << ERROR_LOG_CONCAT;
			log << _task.getStartDateTime() << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}

		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		displayMsg << SUCCESS_EDIT_MESSAGE;
		displayMsg << taskName << SUCCESS_EDIT_START_TIME;
		if( oldStartTime != not_a_date_time ) {
			displayMsg << EDIT_FROM_CONNECTOR << oldStartTime;
		} else {
			displayMsg << EDIT_FROM_CONNECTOR << NA_DATE_TIME;
		}
		displayMsg << EDIT_TO_CONNECTOR << newStartTime;

		if( isDeadline ) {
			displayMsg << PROMPT_EDIT_DEADLINE_START_TIME_MESSAGE;
		}

		if(clash) {
			displayMsg << ERROR_EDIT_CLASH_MESSAGE;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicEdit::editTaskByEndTime( time_duration newEndTime, int index ) {
	Task _task;
	int taskID;
	string taskName;
	time_duration oldEndTime;
	time_duration startTime;
	ptime startDate;
	ptime newEndDate;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	stringstream displayMsg;
	bool clash;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// find task on display
	taskID = display[index-1].getTaskID();

	if( display[index-1].getEndDateTime().time_of_day() == newEndTime ) {
		displayMsg << ERROR_EDIT_NO_CHANGES_MESSAGE;
	} else {
		if( display[index-1].getTaskType() == Task::FLOATING ) {
			display[index-1].setTaskType(Task::DEADLINE);
		}

		_task = display[index-1];
		oldEndTime = _task.getEndDateTime().time_of_day();
		taskName = _task.getTaskName();

		startDate = _task.getStartDateTime();
		newEndDate = _task.getEndDateTime();
		if( newEndDate == not_a_date_time ) {
			newEndDate = second_clock::local_time();
		}

		newEndDate = ptime(newEndDate.date(), newEndTime);
		
		startTime = _task.getStartDateTime().time_of_day();

		clash = isDateClash(startDate, newEndDate, taskID);

		if( !isDateCorrectFormat(startDate, newEndDate) ) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( !isTimeCorrectFormat(startTime, newEndTime)) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( isDatePast(newEndDate) ) {
			displayMsg << ERROR_DATE_PAST_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		// set edited task attributes
		display[index-1].setEndDateTime(newEndDate);
		_task = display[index-1];

		// update internal data
		dataFeedback = _data->executeEdit(_task);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << ERROR_EDIT_MESSAGE << "END-TIME" << ERROR_LOG_CONCAT;
			log << newEndTime << ERROR_LOG_CONCAT;
			log << _task.getTaskName() << ERROR_LOG_CONCAT;
			log << _task.getTaskID() << ERROR_LOG_CONCAT;
			log << _task.getEndDateTime() << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}

		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		displayMsg << SUCCESS_EDIT_MESSAGE;
		displayMsg << taskName << SUCCESS_EDIT_END_TIME;
		if( oldEndTime != not_a_date_time ) {
			displayMsg << EDIT_FROM_CONNECTOR << oldEndTime;
		} else {
			displayMsg << EDIT_FROM_CONNECTOR << NA_DATE_TIME;
		}
		displayMsg << EDIT_TO_CONNECTOR << newEndTime;

		if(clash) {
			displayMsg << ERROR_EDIT_CLASH_MESSAGE;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicEdit::editTaskByStartDateTime( ptime newStartDate, int index ) {
	Task _task;
	int taskID;
	string taskName;
	ptime oldStartDate;
	ptime endDate;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	stringstream displayMsg;
	bool clash;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// find task on display
	taskID = display[index-1].getTaskID();

	if( display[index-1].getStartDateTime() == newStartDate ) {
		displayMsg << ERROR_EDIT_NO_CHANGES_MESSAGE;
	} else if( display[index-1].getTaskType() == Task::FLOATING ) {
		displayMsg << PROMPT_EDIT_FLOATING_START_DATE_MESSAGE;
	} else {
		if( display[index-1].getTaskType() == Task::DEADLINE ) {
			display[index-1].setTaskType(Task::TIMED);
		}

		_task = display[index-1];
		taskName = _task.getTaskName();
		oldStartDate = _task.getStartDateTime();
		endDate = _task.getEndDateTime();

		clash = isDateClash(newStartDate, endDate, taskID);

		if( !isDateCorrectFormat(newStartDate, endDate) ) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( isDatePast(newStartDate) ) {
			displayMsg << ERROR_DATE_PAST_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		// set edited task attributes
		display[index-1].setStartDateTime(newStartDate);
		_task = display[index-1];

		// update internal data
		dataFeedback = _data->executeEdit(_task);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << ERROR_EDIT_MESSAGE << "START-DATE-TIME" << ERROR_LOG_CONCAT;
			log << newStartDate << ERROR_LOG_CONCAT;
			log << _task.getTaskName() << ERROR_LOG_CONCAT;
			log << _task.getTaskID() << ERROR_LOG_CONCAT;
			log << _task.getStartDateTime() << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}

		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		displayMsg << SUCCESS_EDIT_MESSAGE;
		displayMsg << taskName << SUCCESS_EDIT_START_DATE;
		if( oldStartDate != not_a_date_time ) {
			displayMsg << EDIT_FROM_CONNECTOR << oldStartDate;
		} else {
			displayMsg << EDIT_FROM_CONNECTOR << NA_DATE_TIME;
		}
		displayMsg << EDIT_TO_CONNECTOR << newStartDate;

		if(clash) {
			displayMsg << ERROR_EDIT_CLASH_MESSAGE;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicEdit::editTaskByEndDateTime( ptime newEndDate, int index ) {
	Task _task;
	int taskID;
	string taskName;
	ptime oldEndDate;
	ptime startDate;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	stringstream displayMsg;
	bool clash;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// find task on display
	taskID = display[index-1].getTaskID();

	if( display[index-1].getEndDateTime() == newEndDate ) {
		displayMsg << ERROR_EDIT_NO_CHANGES_MESSAGE;
	} else {
		if( display[index-1].getTaskType() == Task::FLOATING ) {
			display[index-1].setTaskType(Task::DEADLINE);
		}

		_task = display[index-1];
		taskName = _task.getTaskName();
		oldEndDate = _task.getEndDateTime();
		startDate = _task.getStartDateTime();

		if( !isDateCorrectFormat(startDate, newEndDate) ) {
			displayMsg << ERROR_EDIT_DATE_START_END_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		if( isDatePast(newEndDate) ) {
			displayMsg << ERROR_DATE_PAST_MESSAGE;
			_display = Display(displayMsg.str(), display);
			return _display;
		}

		clash = isDateClash(startDate, newEndDate, taskID);

		// set edited task attributes
		display[index-1].setEndDateTime(newEndDate);
		_task = display[index-1];

		// update internal data
		dataFeedback = _data->executeEdit(_task);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << ERROR_EDIT_MESSAGE << "END-DATE-TIME" << ERROR_LOG_CONCAT;
			log << newEndDate << ERROR_LOG_CONCAT;
			log << _task.getTaskName() << ERROR_LOG_CONCAT;
			log << _task.getTaskID() << ERROR_LOG_CONCAT;
			log << _task.getEndDateTime() << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}

		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		displayMsg << SUCCESS_EDIT_MESSAGE;
		displayMsg << taskName << SUCCESS_EDIT_END_DATE;
		if( oldEndDate != not_a_date_time ) {
			displayMsg << EDIT_FROM_CONNECTOR << oldEndDate;
		} else {
			displayMsg << EDIT_FROM_CONNECTOR << NA_DATE_TIME;
		}
		displayMsg << EDIT_TO_CONNECTOR << newEndDate;
		
		if(clash) {
			displayMsg << ERROR_EDIT_CLASH_MESSAGE;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

const string LogicEdit::PROMPT_EDIT_FLOATING_START_DATE_MESSAGE = "Please enter an end date for floating task.";
const string LogicEdit::PROMPT_EDIT_FLOATING_END_DATE_MESSAGE = "Please enter a date for floating task.";
const string LogicEdit::ERROR_EDIT_DATE_START_END_MESSAGE = "Please ensure start time is before end time.";
const string LogicEdit::ERROR_EDIT_CLASH_MESSAGE = " [CLASH]";
const string LogicEdit::PROMPT_EDIT_DEADLINE_START_TIME_MESSAGE = " Deadline task start time edited";
const string LogicEdit::ERROR_EDIT_FLOAT_TASK_TIME_MESSAGE = "Cannot edit floating task start time";

const string LogicEdit::SUCCESS_EDIT_MESSAGE = "Task edited: ";
const string LogicEdit::SUCCESS_EDIT_RENAME = "Task renamed: ";
const string LogicEdit::SUCCESS_EDIT_START_TIME = " Start time updated";
const string LogicEdit::SUCCESS_EDIT_END_TIME = " End time updated";
const string LogicEdit::SUCCESS_EDIT_START_DATE = " Start date updated";
const string LogicEdit::SUCCESS_EDIT_END_DATE = " End date updated";

const string LogicEdit::EDIT_FROM_CONNECTOR = " From: ";
const string LogicEdit::EDIT_TO_CONNECTOR = " To: ";

const string LogicEdit::NA_DATE_TIME = "N.A.";
const string LogicEdit::ERROR_EDIT_MESSAGE = "Unable to edit.";
const string LogicEdit::ERROR_EDIT_NO_CHANGES_MESSAGE = "No changes have been made.";