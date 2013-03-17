//@author A0002927L

#ifndef COMMAND_DONE_H
#define COMMAND_DONE_H

#include <string>

#include "LogicDone.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandDone : public CommandBase {
public:
	enum DoneType {
		DONE_INDEX,
		DONE_SEARCHTERM,
		DONE_ALL
	};

	void execute();

	CommandDone( DoneType doneType );
	CommandDone( int index );
	CommandDone( string searchTerm );

	DoneType getDoneType();
	int getDoneIndex();
	string getDoneSearchTerm();

private:
	LogicDone* _logicDone;
	
	DoneType _doneType;

	int _index;
	string _searchTerm;
};
#endif