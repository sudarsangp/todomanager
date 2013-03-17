//@author A0086671W

#ifndef LOGIC_DONE_H
#define LOGIC_DONE_H

#include <iostream>
#include <string>
#include <vector>

#include "LogicBase.h"
#include "LogicUndo.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicDone : public LogicBase {
public:
	static LogicDone& getInstance();

	Display doneByIndex( int index );
	Display doneBySearchTerm( string searchTerm );
	Display doneAllOnDisplay();

private:
	static LogicDone* _logicDone;

	static const string SUCCESS_DONE_MESSAGE;
	static const string SUCCESS_UNDONE_MESSAGE;
	static const string SUCCESS_DONE_ALL_MESSAGE;
	static const string SUCCESS_UNDONE_ALL_MESSAGE;

	static const string ERROR_DONE_MESSAGE;

	static const int FOUND_ONE_MATCH;
	static const int FIRST_POSITION;
};
#endif