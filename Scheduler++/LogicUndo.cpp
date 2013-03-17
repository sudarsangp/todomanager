//@author A0092076A
#include "LogicUndo.h"

LogicUndo* LogicUndo::_logicUndo = NULL;

LogicUndo& LogicUndo::getInstance() {
	if( _logicUndo == NULL ) {
		_logicUndo = new LogicUndo();
		_logicUndo->undoStackPush(*_data);
	}

	return *_logicUndo;
}

Display LogicUndo::undo(){

	string statusMessage;
	vector<Task> tasksVector;

	statusMessage = RESET_STATUS;

	try{
		if( undoStackData.size() != 1 ) {
			tasksVector.clear();
			undoStackData.pop();
			undoStackData.top().getAll( tasksVector );
			// load and write will destroy the contents if tasksvector is subdisplay of the orginal 
			// list of tasks
			_writer->write( tasksVector );
			_data->executeLoad( tasksVector );
			statusMessage = SUCCESS_UNDO_MESSAGE;
			_display = Display(statusMessage, tasksVector);
		}
		else {
			statusMessage = ERROR_UNDO_MESSAGE;
			undoStackData.top().getAll( tasksVector );
			_display = Display(statusMessage, tasksVector);
		}
		return _display;
	}
	catch( SchedulerPPException& e ){
		statusMessage = "Exception : "+ e.getMessage();
		return _display;
	}
	catch (...) {
		statusMessage = "Unknown exception ";
		return _display;
	}
}

void LogicUndo::undoStackPush( Data stackData) {
	undoStackData.push( stackData );

}

const string LogicUndo::SUCCESS_UNDO_MESSAGE = "Undo successful.";

const string LogicUndo::ERROR_UNDO_MESSAGE = "Unable to undo further.";