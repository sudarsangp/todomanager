//@author A0086671W

#ifndef LOGIC_ADD_H
#define LOGIC_ADD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "LogicBase.h"
#include "LogicUndo.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicAdd : public LogicBase {
public:
	static LogicAdd& getInstance();

	Display addFloatingTask(string taskName);
	Display addDeadlineTask(string taskName, ptime endTime);
	Display addTimedTask(string taskName, ptime startTime, ptime endTime);

private:
	static LogicAdd* _logicAdd;

	static const string SUCCESS_ADD_MESSAGE;
	static const string ADD_DEADLINE_BY_CONNECTOR;
	static const string ADD_TIMED_FROM_CONNECTOR;
	static const string ADD_TIMED_TO_CONNECTOR;

	static const string ERROR_ADD_MESSAGE;
	static const string ERROR_ADD_EXIST_MESSAGE;
	static const string ERROR_ADD_CLASH_MESSAGE;
};
#endif