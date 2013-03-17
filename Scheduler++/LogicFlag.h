//@author A0086671W

#ifndef LOGIC_FLAG_H
#define LOGIC_FLAG_H

#include <iostream>
#include <string>
#include <vector>

#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "LogicBase.h"
#include "LogicUndo.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicFlag : public LogicBase {
public:
	static LogicFlag& getInstance();

	Display flagTaskByIndex( int index );
	Display flagTaskBySearchTerm( string searchTerm );
	Display flagAllOnDisplay();

private:
	static LogicFlag* _logicFlag;

	static const string SUCCESS_FLAG_MESSAGE;
	static const string SUCCESS_UNFLAG_MESSAGE;
	static const string SUCCESS_FLAG_ALL_MESSAGE;
	static const string SUCCESS_FLAG_SOME_MESSAGE;
	static const string SUCCESS_UNFLAG_ALL_MESSAGE;

	static const string ERROR_FLAG_MESSAGE;
	static const string ERROR_UNFLAG_MESSAGE;

	static const int FLAGGED;
	static const int UNFLAGGED;

	static const int FIRST_POSITION;
};
#endif