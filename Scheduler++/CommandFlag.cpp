#include "CommandFlag.h"

// @author A0086671W
void CommandFlag::execute() {
	if( _flagType == FLAG_INDEX ) {
		LogicFlag::getInstance().flagTaskByIndex( _index );
	} else if( _flagType == FLAG_SEARCHTERM ) {
		LogicFlag::getInstance().flagTaskBySearchTerm( _searchTerm );
	} else if ( _flagType == FLAG_ALL ) {
		LogicFlag::getInstance().flagAllOnDisplay();
	}
}

CommandFlag::CommandFlag( int index ) {
	_flagType = FLAG_INDEX;
	_index = index;
}

CommandFlag::CommandFlag( string searchTerm ) {
	_flagType = FLAG_SEARCHTERM;
	_searchTerm = searchTerm;
}

CommandFlag::CommandFlag( FlagType flagType )
{
	_flagType = flagType;
}


CommandFlag::FlagType CommandFlag::getFlagType() {
	return _flagType;
}

int CommandFlag::getFlagIndex() {
	return _index;
}

string CommandFlag::getFlagSearchTerm() {
	return _searchTerm;	
}