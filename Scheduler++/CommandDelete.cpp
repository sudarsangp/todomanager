#include "CommandDelete.h"

// @author A0086671W
void CommandDelete::execute() {
	if( _deleteType == DELETE_INDEX ) {
		LogicDelete::getInstance().deleteTaskByIndex( _index );
	}else if( _deleteType == DELETE_SEARCHTERM ) {
		LogicDelete::getInstance().deleteTaskByString( _searchType );
	}else if( _deleteType == DELETE_DONE ) {
		LogicDelete::getInstance().deleteDoneTask( _done );
	}else if ( _deleteType == DELETE_LISTED ) {
		LogicDelete::getInstance().deleteListedTasks();
	}
}

CommandDelete::CommandDelete( DeleteType deleteType, int index ) {
	_deleteType = deleteType;
	_index = index;
}

CommandDelete::CommandDelete( DeleteType deleteType, string searchType ) {
	_deleteType = deleteType;
	_searchType = searchType;
}

CommandDelete::CommandDelete( DeleteType deleteType, bool done ) {
	_deleteType = deleteType;
	_done = done;
}

CommandDelete::CommandDelete( DeleteType deleteType) {
	_deleteType = deleteType;
}

CommandDelete::DeleteType CommandDelete::getDeleteType() {
	return _deleteType;
}

int CommandDelete::getDeleteIndex() {
	return _index;
}
string CommandDelete::getDeleteSearchString() {
	return _searchType;
}