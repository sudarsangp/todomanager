#include "LogicDelete.h"

// @author A0086671W
LogicDelete* LogicDelete::_logicDelete = NULL;

LogicDelete& LogicDelete::getInstance() {
	if (_logicDelete == NULL) {
		_logicDelete = new LogicDelete();
	}

	return *_logicDelete;
}

Display LogicDelete::deleteTaskByString( string searchString ) {

	string term;
	DeleteType deleteType;
	vector<Task> display;
	stringstream displayMsg;

	term = searchString;
	displayMsg.str(RESET_STATUS);
	deleteType = isDeleteByName(term);
	deleteType = isDeleteBySearchTerm(term);
	if( deleteType == NAME ) {
		_display = deleteTaskByName( searchString );
	} else if( deleteType == SEARCH_TERM ) {
		_display = deleteTaskBySearchTerm( searchString );
	} else if ( deleteType == EMPTY ) {
		display = _display.getTaskList();
		displayMsg << FILE_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	} else if ( deleteType == NOT_FOUND ) {
		display = _display.getTaskList();
		displayMsg << ERROR_NO_MATCHES_FOUND_MESSAGE;
		displayMsg << searchString;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	return _display;
}

LogicDelete::DeleteType LogicDelete::isDeleteByName( string term )
{
	Data::DataFeedback dataFeedback;
	DeleteType deleteType;

	vector<Task> tasks;
	dataFeedback = _data->getByName(tasks, term);

	if( dataFeedback == Data::NOT_FOUND ) {
		deleteType = NOT_FOUND;
	} else if( dataFeedback == Data::SUCCESS ) {
		deleteType = NAME;
	} else if( dataFeedback == Data::EMPTY ) {
		deleteType = EMPTY;
	} else {
		deleteType = FAILURE;
	}

	return deleteType;
}

LogicDelete::DeleteType LogicDelete::isDeleteBySearchTerm( string term )
{
	Data::DataFeedback dataFeedback;
	DeleteType deleteType;

	vector<Task> tasks;
	dataFeedback = _data->getBySearchTerm(tasks, term);

	if( dataFeedback == Data::NOT_FOUND ) {
		deleteType = NOT_FOUND;
	} else if( dataFeedback == Data::SUCCESS ) {
		deleteType = SEARCH_TERM;
	} else if( dataFeedback == Data::EMPTY ) {
		deleteType = EMPTY;
	} else {
		deleteType = FAILURE;
	}

	return deleteType;
}

Display LogicDelete::deleteTaskByIndex( int index ) {
	
	string taskName;
	Data::DataFeedback dataFeedback;
	vector<Task> display;
	vector<Task> tasks;
	bool outOfBounds;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	dataFeedback = _data->getAll(tasks);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << FILE_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	} else {
		tasks.clear();
	}
	
	outOfBounds = isOutOfBounds(index, _display.getDisplaySize());
	
	display = _display.getTaskList();

	if( outOfBounds ) {
		displayMsg << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	int taskId = display[index-1].getTaskID();

	taskName = display[index-1].getTaskName();

	dataFeedback = _data->executeDeleteTaskID(taskId);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << "DELETE-INDEX" << ERROR_LOG_CONCAT;
		log << index << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		display.erase(display.begin()+index-1);
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_DELETE_MESSAGE;
		displayMsg << taskName;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicDelete::deleteTaskByName( string taskName ) {

	int taskId;
	string name;
	Data::DataFeedback dataFeedback;
	vector<Task> display;
	vector<Task> tasks;
	bool multipleMatch;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	dataFeedback = _data->getByName(tasks ,taskName);

	multipleMatch = isMultipleMatches(tasks.size());

	if(multipleMatch) {
		display = tasks;
		displayMsg << MULTIPLE_MATCHES_FOUND;
		displayMsg << taskName;
		displayMsg << PROMPT_ENTER_INDEX;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	taskId = tasks[FIRST_POSITION].getTaskID();
	display = _display.getTaskList();
	// if task is in the display, remove it.
	for( unsigned int i=0; i<display.size(); i++ ) {
		if( display[i].getTaskID() == taskId ) {
			display.erase(display.begin()+i);
		}
	}
	name = tasks[FIRST_POSITION].getTaskName();
	dataFeedback = _data->executeDeleteTaskID(taskId);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << "DELETE-NAME" << ERROR_LOG_CONCAT;
		log << taskName << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_DELETE_MESSAGE;
		displayMsg << name;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicDelete::deleteTaskBySearchTerm( string searchTerm ) {
	
	int taskId;
	string taskName;
	Data::DataFeedback dataFeedback;
	vector<Task> display;
	vector<Task> tasks;
	bool multipleMatch;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	dataFeedback = _data->getBySearchTerm(tasks, searchTerm);

	multipleMatch = isMultipleMatches(tasks.size());

	if(multipleMatch) {
		display = tasks;
		displayMsg << MULTIPLE_MATCHES_FOUND;
		displayMsg << searchTerm;
		displayMsg << PROMPT_ENTER_INDEX;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	taskId = tasks[FIRST_POSITION].getTaskID();
	display = _display.getTaskList();
	// if task is in the display, remove it.
	for( unsigned int i=0; i<display.size(); i++ ) {
		if( display[i].getTaskID() == taskId ) {
			display.erase(display.begin()+i);
		}
	}
	taskName = tasks[FIRST_POSITION].getTaskName();
	dataFeedback = _data->executeDeleteTaskID(taskId);

	if( dataFeedback == Data::FAILURE ) {
		stringstream log;
		log << "DELETE-SEARCH-TERM" << ERROR_LOG_CONCAT;
		log << searchTerm << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	} else if( dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_DELETE_MESSAGE;
		displayMsg << taskName;
	}

	_display = Display( displayMsg.str(), display );

	return _display;
}

Display LogicDelete::deleteDoneTask( bool done ) {

	int taskId;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	int numDoneTasks;
	stringstream displayMsg;
	string taskName;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	dataFeedback = _data->getByDone(tasks);

	if( dataFeedback == Data::EMPTY ) {
		displayMsg << FILE_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	} else if( dataFeedback == Data::NOT_FOUND ) {
		displayMsg << ERROR_NO_COMPLETED_TASKS_MESSAGE;
		_display = Display(displayMsg.str(), display);
		return _display;
	} else if (dataFeedback == Data::FAILURE) {
		stringstream log;
		log << "DELETE-DONE" << ERROR_LOG_CONCAT;
		log << "bool:" << done << ERROR_LOG_CONCAT;
		log << endl;
		logDataErrors(log.str());
	}

	numDoneTasks = tasks.size();

	for( unsigned int i=0; i<tasks.size(); i++ ) {
		taskId = tasks[i].getTaskID();
		taskName = tasks[i].getTaskName();
		dataFeedback = _data->executeDeleteTaskID(taskId);

		if( dataFeedback == Data::FAILURE ) {
			stringstream log;
			log << "DELETE-DONE" << ERROR_LOG_CONCAT;
			log << "bool:" << done << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
		}
	}

	if(dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		updateFileContents(tasks);
		LogicUndo::getInstance().undoStackPush(*_data);
		if( numDoneTasks > 1 ) {
			displayMsg << SUCCESS_DELETE_DONE_MESSAGE;
		} else if ( numDoneTasks == 1 ) {
			displayMsg << SUCCESS_DELETE_MESSAGE;
			displayMsg << taskName;
		}
	}

	_display = Display( displayMsg.str(), tasks );

	return _display;
}

Display LogicDelete::deleteListedTasks()
{
	int taskId;
	int numTasksDeleted;
	int numTasksOnDisplay;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> display;
	vector<Task> undeletedTasks;
	stringstream displayMsg;

	displayMsg.str(RESET_STATUS);

	display = _display.getTaskList();

	numTasksOnDisplay = display.size();

	if( display.empty() ) {
		displayMsg << DISPLAY_EMPTY;
		_display = Display(displayMsg.str(), display);
		return _display;
	}

	numTasksDeleted = 0;

	for( int i=0; i<numTasksOnDisplay; i++ ) {
		taskId = display[i].getTaskID();
		dataFeedback = _data->executeDeleteTaskID(taskId);
		
		if( dataFeedback == Data::EMPTY ) {
			displayMsg << FILE_EMPTY;
			_display = Display(displayMsg.str(), display);
			return _display;
		} else if( dataFeedback == Data::NOT_FOUND ) {
			stringstream log;
			log << "DELETE-LISTED-NOT-FOUND" << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
			undeletedTasks.push_back(display[i]);
		} else if (dataFeedback == Data::FAILURE) {
			stringstream log;
			log << "DELETE-LISTED" << ERROR_LOG_CONCAT;
			log << endl;
			logDataErrors(log.str());
			undeletedTasks.push_back(display[i]);
		} else if ( dataFeedback == Data::SUCCESS ) {
			numTasksDeleted++;
			continue;
		}
	}

	if( numTasksDeleted == numTasksOnDisplay ) {
		tasks.clear();
		updateFileContents(tasks);
		tasks.clear();
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << SUCCESS_DELETE_LISTED_MESSAGE;
	} else {
		tasks.clear();
		updateFileContents(tasks);
		tasks = undeletedTasks; // shows user the tasks that were unable to delete
		LogicUndo::getInstance().undoStackPush(*_data);
		displayMsg << ERROR_DELETE_LISTED_MESSAGE;
	}

	_display = Display( displayMsg.str(), tasks );

	return _display;
}

const string LogicDelete::SUCCESS_DELETE_MESSAGE = "Task deleted: ";
const string LogicDelete::SUCCESS_DELETE_DONE_MESSAGE = "All completed tasks deleted.";
const string LogicDelete::SUCCESS_DELETE_LISTED_MESSAGE = "All tasks on display deleted.";

const string LogicDelete::ERROR_DELETE_MESSAGE = "Unable to delete.";
const string LogicDelete::ERROR_DELETE_LISTED_MESSAGE = "We're sorry. Some error occurred and we're unable to delete some tasks. The tasks are listed on display.";

const int LogicDelete::FIRST_POSITION = 0;