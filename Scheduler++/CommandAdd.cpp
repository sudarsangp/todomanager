#include "CommandAdd.h"

// @author A0086671W
void CommandAdd::execute() {
	if ( _addType == ADD_FLOATING_TASK ) {
		LogicAdd::getInstance().addFloatingTask(_taskName);
	} else if ( _addType == ADD_DEADLINE_TASK ) {
		LogicAdd::getInstance().addDeadlineTask(_taskName, _endTime);
	} else if ( _addType == ADD_TIMED_TASK ) {
		LogicAdd::getInstance().addTimedTask(_taskName, _startTime, _endTime);
	}
}

CommandAdd::CommandAdd(string taskName) {
	_addType = ADD_FLOATING_TASK;
	_taskName = taskName;
}

CommandAdd::CommandAdd(string taskName, 
					   ptime endTime) {
	_addType = ADD_DEADLINE_TASK;
	_taskName = taskName;
	_endTime = endTime;
}

CommandAdd::CommandAdd(string taskName, 
					   ptime startTime, 
					   ptime endTime) {
	_addType = ADD_TIMED_TASK;
	_taskName = taskName;
	_startTime = startTime;
	_endTime = endTime;
}

CommandAdd::AddType CommandAdd::getAddType() {
	return _addType;
}
string CommandAdd::getTaskName() {
	return _taskName;
}
ptime CommandAdd::getStartTime() {
	return _startTime;
}
ptime CommandAdd::getEndTime() {
	return _endTime;
}