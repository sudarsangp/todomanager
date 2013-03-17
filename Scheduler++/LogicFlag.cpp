#include "LogicFlag.h"

// @author A0086671W
LogicFlag* LogicFlag::_logicFlag = NULL;

LogicFlag& LogicFlag::getInstance() {
	if (_logicFlag == NULL) {
		_logicFlag = new LogicFlag();
	}

	return *_logicFlag;
}

Display LogicFlag::flagTaskByIndex( int index ) {
	Task _task;
	string taskName;
	int taskID;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	int flagState;
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

	taskID = display[index-1].getTaskID();
	taskName = display[index-1].getTaskName();

	_data->getByID(tasks, taskID);

	if( display[index-1].getPriority() == UNFLAGGED ) {
		flagState = FLAGGED;
	} else {
		flagState = UNFLAGGED;
	}

	display[index-1].setPriority(flagState);
	_task = display[index-1];

	dataFeedback = _data->executeEdit(_task);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << ERROR_FLAG_MESSAGE << "FLAG-INDEX" << ERROR_LOG_CONCAT;
		log << index << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	if( dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		if( flagState ) {
			displayMsg << SUCCESS_FLAG_MESSAGE;
			displayMsg << taskName;
		} else {
			displayMsg << SUCCESS_UNFLAG_MESSAGE;
			displayMsg << taskName;
		}
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicFlag::flagTaskBySearchTerm( string searchTerm ) {
	Task _task;
	int taskID;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	bool multipleMatch;
	bool onDisplay;
	int flagState;
	int isFlagged;
	stringstream displayMsg;
	string taskName;

	displayMsg.str(RESET_STATUS);

	_data->getBySearchTerm(tasks, searchTerm);

	display = _display.getTaskList();

	if( tasks.empty() ) {
		displayMsg << ERROR_NO_MATCHES_FOUND_MESSAGE;
		displayMsg << searchTerm;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	// assume task is not on the display
	onDisplay = false;

	multipleMatch = isMultipleMatches(tasks.size());

	if( multipleMatch ) {
		display = tasks;
		displayMsg << MULTIPLE_MATCHES_FOUND;
		displayMsg << searchTerm;
		displayMsg << PROMPT_ENTER_INDEX;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	_task = tasks[FIRST_POSITION];
	flagState = _task.getPriority();
	taskName = _task.getTaskName();

	if( flagState == FLAGGED ) {
		isFlagged = UNFLAGGED;
	} else if( flagState == UNFLAGGED ) {
		isFlagged = FLAGGED;
	}

	_task.setPriority(isFlagged);
	taskID = _task.getTaskID();
	dataFeedback = _data->executeEdit(_task);

	// find if task is on the display
	for( unsigned int i=0; i<display.size(); i++ ) {
		if( display[i].getTaskID() == taskID ) {
			display[i].setPriority(isFlagged);
			onDisplay = true;
		}
	}

	if( !onDisplay ) {
		display.push_back(_task);
	}

	if( dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);

		if( isFlagged ) {
			displayMsg << SUCCESS_FLAG_MESSAGE;
			displayMsg << taskName;
		} else {
			displayMsg << SUCCESS_UNFLAG_MESSAGE;
			displayMsg << taskName;
		}
	} else {
		displayMsg << ERROR_FLAG_MESSAGE;
		displayMsg << taskName;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicFlag::flagAllOnDisplay()
{
	Task _task;
	vector<Task> tasks;
	vector<Task> display;
	int isNotFlagged;
	int notAllFlagged;
	int unFlagIt;
	int flagIt;
	stringstream displayMsg;
	int numFlaggedTasks;

	isNotFlagged = UNFLAGGED;
	notAllFlagged = FLAGGED;
	unFlagIt = UNFLAGGED;
	flagIt = FLAGGED;
	numFlaggedTasks = 0;

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
		if( _task.getPriority() == isNotFlagged ) {
			display[i].setPriority(flagIt);
			_task.setPriority(flagIt);
			_data->executeEdit(_task);
		} else {
			// remain marked
			notAllFlagged = false; // at least 1 task marked done
			numFlaggedTasks++;
		}
	}

	if( notAllFlagged ) {
		displayMsg << SUCCESS_FLAG_ALL_MESSAGE;
	} else if ( numFlaggedTasks == display.size() ) {
		for( int i=0; i<(int)display.size(); i++ ) {
			_task = display[i];
			display[i].setPriority(unFlagIt);
			_task.setPriority(unFlagIt);
			_data->executeEdit(_task);
		}
		displayMsg << SUCCESS_UNFLAG_ALL_MESSAGE;
	} else {
		displayMsg << SUCCESS_FLAG_ALL_MESSAGE;
	}

	updateFileContents(tasks);

	_display = Display(displayMsg.str(), display);

	return _display;
}

const string LogicFlag::SUCCESS_FLAG_MESSAGE = "Task flagged: ";
const string LogicFlag::SUCCESS_UNFLAG_MESSAGE = "Task unflagged: ";
const string LogicFlag::SUCCESS_FLAG_ALL_MESSAGE = "All tasks listed flagged.";
const string LogicFlag::SUCCESS_FLAG_SOME_MESSAGE = "Tasks listed flagged.";
const string LogicFlag::SUCCESS_UNFLAG_ALL_MESSAGE = "All tasks listed unflagged.";

const string LogicFlag::ERROR_FLAG_MESSAGE = "Unable to flag.";
const string LogicFlag::ERROR_UNFLAG_MESSAGE = "Unable to unflag.";

const int LogicFlag::FLAGGED = 1;
const int LogicFlag::UNFLAGGED = 0;

const int LogicFlag::FIRST_POSITION = 0;