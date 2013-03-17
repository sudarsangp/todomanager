//@author A0086671W

#ifndef LOGIC_LIST_H
#define LOGIC_LIST_H

#include <iostream>
#include <string>
#include <vector>

#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "LogicBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicList : public LogicBase {
public:
	static LogicList& getInstance();

	Display listAllTasks();
	Display listTaskBySearchTerm( string searchTerm );
	Display listTaskByDateTime( ptime start, ptime end );
	Display listTaskByDone( bool done );
	Display listTasksOverdue();

private:
	static LogicList* _logicList;

	static const string SUCCESS_LIST_MESSAGE;
	static const string SUCCESS_LIST_ALL_MESSAGE;
	static const string SUCCESS_LIST_SEARCHTERM;
	static const string SUCCESS_LIST_MONTH;
	static const string SUCCESS_LIST_WEEK;
	static const string SUCCESS_LIST_TO_CONNECTOR;
	static const string SUCCESS_LIST_DAY_DATE;
	static const string SUCCESS_LIST_DONE;
	static const string SUCCESS_LIST_UNDONE;
	static const string SUCCESS_LIST_NO_OVERDUE;
	static const string SUCCESS_LIST_OVERDUE;

	static const string ERROR_LIST_NO_COMPLETED_TASKS;
	static const string ERROR_LIST_NO_TASKS;
	static const string ERROR_LIST_MESSAGE;
};
#endif