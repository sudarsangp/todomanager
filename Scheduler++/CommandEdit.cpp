#include "CommandEdit.h"

// @author A0086671W
void CommandEdit::execute() {
	if( _editType == EDIT_START_TIME ) {
		LogicEdit::getInstance().editTaskByStartTime( _time, _index );
	} else if( _editType == EDIT_START_DATETIME ) {
		LogicEdit::getInstance().editTaskByStartDateTime(_date, _index );
	} else if( _editType == EDIT_END_TIME ) {
		LogicEdit::getInstance().editTaskByEndTime( _time, _index );
	} else if( _editType == EDIT_END_DATETIME ) {
		LogicEdit::getInstance().editTaskByEndDateTime( _date, _index );
	} else if( _editType == EDIT_RENAME ) {
		LogicEdit::getInstance().editTaskByName( _taskName, _index );
	}
}

CommandEdit::CommandEdit( EditType editType, int index, ptime date ) {
	_editType = editType;
	_index = index;
	_date = date;
}

CommandEdit::CommandEdit( EditType editType, int index, time_duration time ) {
	_editType = editType;
	_index = index;
	_time = time;
}

CommandEdit::CommandEdit( EditType editType, int index, string taskName ) {
	_editType = editType;
	_index = index;
	_taskName = taskName;
}

CommandEdit::EditType CommandEdit::getEditType() {
	return _editType;
}

ptime CommandEdit::getDateTime() {
	return _date;
}

time_duration CommandEdit::getTime() {
	return _time;
}

string CommandEdit::getTaskName() {
	return _taskName;
}