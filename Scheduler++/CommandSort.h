//@author A0002927L

#ifndef COMMAND_SORT_H
#define COMMAND_SORT_H

#include <string>

#include "LogicSort.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandSort : public CommandBase {
public:
	enum SortType {
		SORT_TIME,
		SORT_ALPHABET,
		SORT_FLAG,
		SORT_COMPLETED,
	};

	void execute();

	CommandSort( SortType sortType );

	SortType getSortType();

private:
	LogicSort* _logicSort;

	SortType _sortType;
};
#endif