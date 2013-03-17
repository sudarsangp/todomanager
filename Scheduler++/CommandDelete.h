//@author A0002927L

#ifndef COMMAND_DELETE_H
#define COMMAND_DELETE_H

#include <string>

#include "LogicDelete.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandDelete : public CommandBase {
public:
	enum DeleteType {
		DELETE_SEARCHTERM,
		DELETE_INDEX,
		DELETE_DONE,
		DELETE_LISTED
	};

	void execute();

	CommandDelete(DeleteType deleteType);
	CommandDelete(DeleteType deleteType, int index );
	CommandDelete(DeleteType deleteType, string searchType );
	CommandDelete(DeleteType deleteType, bool done );

	DeleteType getDeleteType();
	int getDeleteIndex();
	string getDeleteSearchString();

private:
	DeleteType _deleteType;

	int _index;
	string _searchType;
	bool _done;

};
#endif