#include "CommandDone.h"

// @author A0086671W
void CommandDone::execute() {
	if( _doneType == DONE_INDEX ) {
		LogicDone::getInstance().doneByIndex( _index );
	} else if( _doneType == DONE_SEARCHTERM ) {
		LogicDone::getInstance().doneBySearchTerm( _searchTerm );
	} else if( _doneType == DONE_ALL ) {
		LogicDone::getInstance().doneAllOnDisplay();
	}
}

CommandDone::CommandDone( int index ) {
	_doneType = DONE_INDEX;
	_index = index;
}

CommandDone::CommandDone( string searchTerm ) {
	_doneType = DONE_SEARCHTERM;
	_searchTerm = searchTerm;
}

CommandDone::CommandDone( DoneType doneType )
{
	_doneType = doneType;
}

CommandDone::DoneType CommandDone::getDoneType() {
	return _doneType;
}

int CommandDone::getDoneIndex() {
	return _index;
}

string CommandDone::getDoneSearchTerm() {
	return _searchTerm;	
}