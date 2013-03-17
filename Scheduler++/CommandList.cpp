#include "CommandList.h"

// @author: A0002927L

void CommandList::execute() {
	if(_listType == LIST_ALL) {
		LogicList::getInstance().listAllTasks();
	}else if (_listType == LIST_SEARCH_TERM) {
		LogicList::getInstance().listTaskBySearchTerm(_searchTerm);
	}else if (_listType == LIST_DONE) {
		LogicList::getInstance().listTaskByDone(true);
	}else if (_listType == LIST_PERIOD) {
		LogicList::getInstance().listTaskByDateTime(_startTime, _endTime);
	}else if(_listType == LIST_OVERDUE) {
		LogicList::getInstance().listTasksOverdue();
	}else if(_listType == LIST_NOT_DONE){
		LogicList::getInstance().listTaskByDone(false);
	}
}

CommandList::CommandList( ListType listType ) {
	_listType = listType;
}

CommandList::CommandList(string searchTerm) {
	_listType = LIST_SEARCH_TERM;
	_searchTerm = searchTerm;
}

CommandList::CommandList(ptime startTime, ptime endTime) {
	_startTime = startTime;
	_endTime = endTime;
	_listType = LIST_PERIOD;
}

CommandList::ListType CommandList::getListType() {
	return _listType;
}

string CommandList::getSearchTerm() {
	return _searchTerm;
}

ptime CommandList::getEndTime() {
	return _endTime;
}

ptime CommandList::getStartTime() {
	return _startTime;
}