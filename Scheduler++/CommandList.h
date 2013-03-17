//@author A0002927L

#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

#include <string>

#include "LogicList.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandList : public CommandBase {
public:
	enum ListType {
		LIST_ALL,
		LIST_SEARCH_TERM,
		LIST_PERIOD,
		LIST_DONE,
		LIST_NOT_DONE,
		LIST_OVERDUE,
	};

	void execute();

	// Constructor for creating list done and list invalid
	CommandList(ListType listType);

	// Constructor for list searchterm
	CommandList(string searchTerm );

	// Constructor for list period
	CommandList(ptime startTime, ptime endTime);

	// Accessors for testing
	ListType getListType();
	string getSearchTerm();
	ptime getEndTime();
	ptime getStartTime();

private:
	ListType _listType;

	string _searchTerm;
	ptime _startTime;
	ptime _endTime;
};
#endif