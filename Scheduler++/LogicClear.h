//@author A0086671W

#ifndef LOGIC_CLEAR_H
#define LOGIC_CLEAR_H

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

class LogicClear : public LogicBase {
public:
	static LogicClear& getInstance();

	Display clearTask();

private:
	static LogicClear* _logicClear;

	static const string SUCCESS_CLEAR_MESSAGE;
	static const string ERROR_CLEAR_MESSAGE;
};
#endif