#include "CommandSort.h"

// @author A0086671W
void CommandSort::execute() {
	if( _sortType == SORT_TIME ) {
		LogicSort::getInstance().sortTasksByDateTime();
	} else if( _sortType == SORT_ALPHABET ) {
		LogicSort::getInstance().sortTasksAlphabetically();
	} else if( _sortType == SORT_FLAG ) {
		LogicSort::getInstance().sortTasksByFlag();
	} else if( _sortType == SORT_COMPLETED ) {
		LogicSort::getInstance().sortTasksByDone();
	}
}

CommandSort::CommandSort( SortType sortType ) {
	_sortType = sortType;
}

CommandSort::SortType CommandSort::getSortType() {
	return _sortType;
}