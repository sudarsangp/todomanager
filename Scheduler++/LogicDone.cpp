#include "LogicDone.h"

// @author A0086671W
LogicDone* LogicDone::_logicDone = NULL;

LogicDone& LogicDone::getInstance()
{
	if( _logicDone == NULL ) {
		_logicDone = new LogicDone;
	}

	return *_logicDone;
}

Display LogicDone::doneByIndex( int index ) {
	Task _task;
	int taskID;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool outOfBounds;
	bool isNotMarked;
	bool unMarkIt;
	bool markIt;
	stringstream displayMsg;

	unMarkIt = false;
	markIt = true;
	isNotMarked = true;

	displayMsg.str(RESET_STATUS);

	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());

	display = _display.getTaskList();

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}


	display = _display.getTaskList();
	
	// zero-based index of task
	int indexZeroed = index - 1;

	taskID = display[indexZeroed].getTaskID();

	// check done state of a task
	// if done mark undone
	// if undone mark done
	if( display[indexZeroed].getDone() == true ) {
		isNotMarked = false;
	} else if( display[indexZeroed].getDone() == false ) {
		isNotMarked = true;
	}

	// set task attributes
	if( isNotMarked ) {
		display[indexZeroed].setDone(markIt);
	} else {
		display[indexZeroed].setDone(unMarkIt);
	}
	_task = display[indexZeroed];
	
	dataFeedback = _data->executeEdit(_task);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_DONE_MESSAGE << "DONE-INDEX" << ERROR_LOG_CONCAT;
		log << index << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	if( dataFeedback == Data::SUCCESS ) {
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		if( isNotMarked ) {
			displayMsg << SUCCESS_DONE_MESSAGE;
		} else if( isNotMarked == false ) {
			displayMsg << SUCCESS_UNDONE_MESSAGE;
		} else {
			displayMsg << SUCCESS_DONE_MESSAGE;
		}
		displayMsg << _task.getTaskName();
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicDone::doneBySearchTerm( string searchTerm ) {
	Task _task;
	int taskID;
	bool multipleMatches;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool isNotMarked;
	bool unMarkIt;
	bool markIt;
	stringstream displayMsg;
	bool onDisplay;

	unMarkIt = false;
	markIt = true;
	isNotMarked = true;

	displayMsg.str(RESET_STATUS);

	dataFeedback = _data->getBySearchTerm(tasks, searchTerm);

	display = _display.getTaskList();

	// assume task is not on the display
	onDisplay = false;
	// assume there are no multiple matches
	multipleMatches = false;

	if( tasks.empty() ) {
		displayMsg << ERROR_NOT_FOUND_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}
	
	// found 1 match
	if( tasks.size() == FOUND_ONE_MATCH ) {
		_task = tasks[FIRST_POSITION];

		if( _task.getDone() == false ) {
			isNotMarked = true;
			_task.setDone(markIt);
		} else {
			isNotMarked = false;
			_task.setDone(unMarkIt);
		}

		taskID = _task.getTaskID();
		for( unsigned int i=0; i<display.size(); i++ ) {
			if( display[i].getTaskID() == taskID ) {
				onDisplay = true;
				if( isNotMarked ) {
					display[i].setDone(markIt);
				} else {
					display[i].setDone(unMarkIt);
				}
			}
		}
		dataFeedback = _data->executeEdit(_task);
		multipleMatches = false;
	} else {
		multipleMatches = true;
	}

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_DONE_MESSAGE << "DONE-SEARCH-TERM" << ERROR_LOG_CONCAT;
		log << searchTerm << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	if( !onDisplay ) {
		display.push_back(_task);
	}

	if( multipleMatches ) {
		display = tasks;
		displayMsg << MULTIPLE_MATCHES_FOUND;
		displayMsg << searchTerm;
		displayMsg << PROMPT_ENTER_INDEX;
	} else {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		if( isNotMarked ) {
			displayMsg << SUCCESS_DONE_MESSAGE;
		} else  {
			displayMsg << SUCCESS_UNDONE_MESSAGE;
		}
		displayMsg << _task.getTaskName();
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicDone::doneAllOnDisplay()
{
	Task _task;
	vector<Task> tasks;
	vector<Task> display;
	bool isNotMarked;
	bool notAllMarked;
	bool unMarkIt;
	bool markIt;
	stringstream displayMsg;
	int numMarkedTasks;

	isNotMarked = false;
	notAllMarked = true;
	unMarkIt = false;
	markIt = true;
	numMarkedTasks = 0;

	displayMsg.str(RESET_STATUS);
	
	display = _display.getTaskList();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// mark tasks done if not marked done
	// else tasks remains marked
	for( int i=0; i<(int)display.size(); i++ ) {
		_task = display[i];
		if( _task.getDone() == isNotMarked ) {
			display[i].setDone(markIt);
			_task.setDone(markIt);
			_data->executeEdit(_task);
		} else {
			// remain marked
			notAllMarked = false; // at least 1 task marked done
			numMarkedTasks++;
		}
	}

	if( notAllMarked ) {
		displayMsg << SUCCESS_DONE_ALL_MESSAGE;
	} else if ( numMarkedTasks == display.size() ) {
		for( int i=0; i<(int)display.size(); i++ ) {
			_task = display[i];
			display[i].setDone(unMarkIt);
			_task.setDone(unMarkIt);
			_data->executeEdit(_task);
		}
		displayMsg << SUCCESS_UNDONE_ALL_MESSAGE;
	} else {
		displayMsg << SUCCESS_DONE_ALL_MESSAGE;
	}

	updateFileContents(tasks);

	_display = Display(displayMsg.str(), display);

	return _display;
}

const string LogicDone::SUCCESS_DONE_MESSAGE = "Task marked done: ";
const string LogicDone::SUCCESS_UNDONE_MESSAGE = "Task marked undone: ";
const string LogicDone::SUCCESS_DONE_ALL_MESSAGE = "All tasks listed marked done.";
const string LogicDone::SUCCESS_UNDONE_ALL_MESSAGE = "All tasks listed marked undone.";

const string LogicDone::ERROR_DONE_MESSAGE = "Unable to mark done.";

const int LogicDone::FOUND_ONE_MATCH = 1;
const int LogicDone::FIRST_POSITION = 0;