//@author A0086671W

#ifndef LOGIC_DELETE_H
#define LOGIC_DELETE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "LogicBase.h"
#include "LogicUndo.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicDelete : public LogicBase {
public:
	static LogicDelete& getInstance();

	Display deleteTaskByIndex( int index );
	Display deleteDoneTask( bool done );
	Display deleteTaskByString( string searchType );
	Display deleteListedTasks();

private:
	static LogicDelete* _logicDelete;

	Display deleteTaskByName( string taskName );
	Display deleteTaskBySearchTerm( string searchTerm );

	static const string SUCCESS_DELETE_MESSAGE;
	static const string SUCCESS_DELETE_DONE_MESSAGE;
	static const string SUCCESS_DELETE_LISTED_MESSAGE;
	static const string ERROR_DELETE_MESSAGE;
	static const string ERROR_DELETE_LISTED_MESSAGE;

	static const int FIRST_POSITION;

	enum DeleteType {
		NAME,
		SEARCH_TERM,
		NOT_FOUND,
		EMPTY,
		FAILURE
	};

	bool isDeleteByDone(string term);
	DeleteType isDeleteByName(string term);
	DeleteType isDeleteBySearchTerm(string term);
};
#endif