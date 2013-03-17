//@author A0086671W

#ifndef LOGIC_EDIT_H
#define LOGIC_EDIT_H

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

class LogicEdit : public LogicBase {
public:
	static LogicEdit& getInstance();

	Display editTaskByName( string taskName, int index );
	Display editTaskByStartTime( time_duration startTime, int index );
	Display editTaskByEndTime( time_duration endTime, int index );
	Display editTaskByStartDateTime( ptime startDate, int index );
	Display editTaskByEndDateTime( ptime endDate, int index );

private:
	static LogicEdit* _logicEdit;

	static const string SUCCESS_EDIT_MESSAGE;

	static const string SUCCESS_EDIT_RENAME;
	static const string SUCCESS_EDIT_START_TIME;
	static const string SUCCESS_EDIT_END_TIME;
	static const string SUCCESS_EDIT_START_DATE;
	static const string SUCCESS_EDIT_END_DATE;

	static const string EDIT_FROM_CONNECTOR;
	static const string EDIT_TO_CONNECTOR;

	static const string NA_DATE_TIME;
	static const string PROMPT_EDIT_FLOATING_START_DATE_MESSAGE;
	static const string PROMPT_EDIT_DEADLINE_START_TIME_MESSAGE;
	static const string PROMPT_EDIT_FLOATING_END_DATE_MESSAGE;
	static const string ERROR_EDIT_FLOAT_TASK_TIME_MESSAGE;
	static const string ERROR_EDIT_START_TIME_MESSAGE;
	static const string ERROR_EDIT_MESSAGE;
	static const string ERROR_EDIT_CLASH_MESSAGE;
	static const string ERROR_EDIT_DATE_START_END_MESSAGE;
	static const string ERROR_EDIT_NO_CHANGES_MESSAGE;
};
#endif