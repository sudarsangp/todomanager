//@author A0002927L

#ifndef COMMAND_FLAG_H
#define COMMAND_FLAG_H

#include <string>

#include "LogicFlag.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandFlag : public CommandBase {
public:
	enum FlagType {
		FLAG_INDEX,
		FLAG_SEARCHTERM,
		FLAG_ALL
	};

	void execute();

	CommandFlag( FlagType flagType );
	CommandFlag( int index );
	CommandFlag( string searchTerm );

	FlagType getFlagType();
	int getFlagIndex();
	string getFlagSearchTerm();

private:
	LogicFlag* _logicFlag;

	FlagType _flagType;

	int _index;
	string _searchTerm;
};
#endif