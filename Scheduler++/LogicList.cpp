#include "LogicList.h"

// @author A0086671W
LogicList* LogicList::_logicList = NULL;

LogicList& LogicList::getInstance() {

	if (_logicList == NULL) {
		_logicList = new LogicList;
	}

	return *_logicList;
}

Display LogicList::listAllTasks() {
	
	stringstream displayMsg;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;

	displayMsg.str(RESET_STATUS);

	dataFeedback = _data->getAll(tasks);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << ERROR_LIST_NO_TASKS;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << ERROR_NOT_FOUND_MESSAGE;
	} else if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_LIST_MESSAGE << "LIST-ALL" << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		displayMsg << SUCCESS_LIST_ALL_MESSAGE;
	}

	_display = Display( displayMsg.str(), tasks );

	return _display;
}

Display LogicList::listTaskBySearchTerm( string searchTerm ) {
	
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	dataFeedback = _data->getBySearchTerm(tasks, searchTerm);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << ERROR_LIST_NO_TASKS;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << ERROR_NOT_FOUND_MESSAGE;
	} else if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_LIST_MESSAGE << "LIST-SEARCH-TERM" << ERROR_LOG_CONCAT;
		log << searchTerm << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		display = tasks;
		displayMsg << SUCCESS_LIST_SEARCHTERM << searchTerm;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}


Display LogicList::listTaskByDateTime( ptime start, ptime end )
{
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if ( isDatePast(end) ) {
		displayMsg << ERROR_DATE_PAST_MESSAGE;
		_display = Display( displayMsg.str(), display );
		return _display;
	}

	dataFeedback = _data->getByTimePeriod(tasks, start, end);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << ERROR_LIST_NO_TASKS;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << ERROR_NOT_FOUND_MESSAGE;
	} else if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_LIST_MESSAGE << "LIST-DATE-TIME" << ERROR_LOG_CONCAT;
		log << to_simple_string(start) << ERROR_LOG_CONCAT;
		log << to_simple_string(end) << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		display = tasks;
		displayMsg << SUCCESS_LIST_DAY_DATE << start.date() << SUCCESS_LIST_TO_CONNECTOR << end.date();
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicList::listTaskByDone( bool done ) {

	stringstream displayMsg;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	if( done == true ) {
		dataFeedback = _data->getByDone(tasks);
	} else {
		dataFeedback = _data->getByUndone(tasks);
	}
	
	if( dataFeedback == Data::EMPTY ) {
		displayMsg << ERROR_LIST_NO_TASKS;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << ERROR_NOT_FOUND_MESSAGE;
	} else if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_LIST_MESSAGE << "LIST-DONE" << ERROR_LOG_CONCAT;
		log << "bool:" << done << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		display = tasks;
		if( done == true ) {
			displayMsg << SUCCESS_LIST_DONE;
		} else {
			displayMsg << SUCCESS_LIST_UNDONE;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicList::listTasksOverdue()
{
	stringstream displayMsg;
	Data::DataFeedback dataFeedback;
	vector<Task> display;
	vector<Task> tasks;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	dataFeedback = _data->getByOverdue(tasks);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << ERROR_LIST_NO_TASKS;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << SUCCESS_LIST_NO_OVERDUE;
	} else if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_LIST_MESSAGE << "LIST-OVERDUE" << ERROR_LOG_CONCAT;
		log << second_clock::local_time() << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		display = tasks;
		displayMsg << SUCCESS_LIST_OVERDUE;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

const string LogicList::SUCCESS_LIST_OVERDUE = "Listed overdue tasks.";
const string LogicList::SUCCESS_LIST_NO_OVERDUE = "No overdue tasks.";
const string LogicList::SUCCESS_LIST_DONE = "Listed completed tasks.";
const string LogicList::SUCCESS_LIST_UNDONE = "Listed uncompleted tasks.";
const string LogicList::SUCCESS_LIST_TO_CONNECTOR = " To: ";
const string LogicList::SUCCESS_LIST_DAY_DATE = "Listed tasks from: ";
const string LogicList::SUCCESS_LIST_WEEK = "Listed tasks from: ";
const string LogicList::SUCCESS_LIST_MONTH = "Listed tasks in: ";
const string LogicList::ERROR_LIST_NO_COMPLETED_TASKS = "No tasks marked done.";
const string LogicList::SUCCESS_LIST_ALL_MESSAGE = "Listed all tasks.";
const string LogicList::SUCCESS_LIST_SEARCHTERM = "Listed tasks containing: ";
const string LogicList::SUCCESS_LIST_MESSAGE = "List completed.";
const string LogicList::ERROR_LIST_NO_TASKS = "No tasks to list.";
const string LogicList::ERROR_LIST_MESSAGE = "Unable to list.";