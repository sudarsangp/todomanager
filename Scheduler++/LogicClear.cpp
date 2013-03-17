#include "LogicClear.h"

// @author A0086671W
LogicClear* LogicClear::_logicClear = NULL;

LogicClear& LogicClear::getInstance() {
	if( _logicClear == NULL ) {
		_logicClear = new LogicClear();
	}

	return *_logicClear;
}

Display LogicClear::clearTask() {
	
	string statusMessage;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;
	vector<Task> emptyDisplay;

	statusMessage = RESET_STATUS;

	dataFeedback = _data->getAll(tasks);

	if(dataFeedback == Data::EMPTY ) {
		statusMessage = FILE_EMPTY;
		_display = Display(statusMessage, emptyDisplay);
		return _display;
	} else if( dataFeedback == Data::FAILURE ) {
		logDataErrors(ERROR_CLEAR_MESSAGE);
	}

	dataFeedback = _data->executeClear();

	if( dataFeedback == Data::SUCCESS ) {
		tasks.clear();
		_data->executeLoad(tasks);
		try {
			_writer->write(emptyDisplay);
			LogicUndo::getInstance().undoStackPush(*_data);
			statusMessage = SUCCESS_CLEAR_MESSAGE;
		}catch (WriterException& e){
			throw(e);
		}
		
	}

	_display = Display( statusMessage, emptyDisplay );

	return _display;
}

const string LogicClear::SUCCESS_CLEAR_MESSAGE = "All tasks cleared.";
const string LogicClear::ERROR_CLEAR_MESSAGE = "Unable to clear tasks. Data failure.";