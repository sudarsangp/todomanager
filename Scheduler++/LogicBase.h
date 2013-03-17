//@author A0086671W

#ifndef LOGIC_BASE_H
#define LOGIC_BASE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "Display.h"
#include "SchedulerPPException.h"
#include "WriterException.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicBase {
public:
	static void initialize(Data*, Writer*);
	static Display getDisplay();

protected:
	// data and writer here
	static Data* _data;
	static Writer* _writer;

	// display
	static Display _display;

	void updateFileContents( vector<Task>& tasks );
	bool isOutOfBounds(int index, int size);
	bool isMultipleMatches(int size);
	ptime getCurrentDateTime();
	bool isDatePast(ptime datetime);
	bool isDateCorrectFormat(ptime startTime, ptime endTime);
	bool isTimeCorrectFormat( time_duration start, time_duration end );
	bool isDateClash(ptime startTime, ptime endTime, int taskID);
	void logDataErrors(string errorString);

	static const string MULTIPLE_MATCHES_FOUND;
	static const string PROMPT_ENTER_INDEX;
	static const string ERROR_NO_MATCHES_FOUND_MESSAGE;
	static const string ERROR_NO_COMPLETED_TASKS_MESSAGE;

	static const string ERROR_DATE_PAST_MESSAGE;
	static const string ERROR_DATE_START_END_MESSAGE;

	static const string INVALID_COMMAND;
	static const string ERROR_NOT_FOUND_MESSAGE;
	static const string ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	static const string RESET_STATUS;
	static const string DISPLAY_EMPTY;
	static const string FILE_EMPTY;

	static const string DATA_LOG_FILE_NAME;
	static const string ERROR_LOG_CONCAT;
	static const string ERROR_LOG_FILE_EOF;
};
#endif