//@author A0086671W

#ifndef LOGIC_SORT_H
#define LOGIC_SORT_H

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

class LogicSort : public LogicBase {
public:
	static LogicSort& getInstance();

	Display sortTasksAlphabetically();
	Display sortTasksByFlag();
	Display sortTasksByDateTime();
	Display sortTasksByDone();

private:
	static LogicSort* _logicSort;

	// sort by name : ascending
	bool sortAlpha(Task t1, Task t2);
	struct sortA {
		bool operator() (Task t1, Task t2) { return t1.getTaskName() < t2.getTaskName(); };
	} sortObjAlpha;

	// sort by date : ascending
	bool sortDateTime(Task t1, Task t2);
	struct sortT {
		bool operator() (Task t1, Task t2) { return t1.getEndDateTime() < t2.getEndDateTime(); };
	} sortObjDateTime;

	// sort by flagged : ascending
	bool sortFlag(Task t1, Task t2);
	struct sortF {
		bool operator() (Task t1, Task t2) { return t1.getPriority() > t2.getPriority(); };
	} sortObjFlag;

	// sort by done|not done
	void sortByDone(vector<Task>& tasksVector);

	static const string SUCCESS_SORT_MESSAGE;
	static const string SUCCESS_SORT_INTERNAL_MESSAGE;
	static const string SUCCESS_SORT_ALPHA_MESSAGE;
	static const string SUCCESS_SORT_DONE_MESSAGE;
	static const string SUCCESS_SORT_FLAG_MESSAGE;
	static const string SUCCESS_SORT_DATE_TIME_MESSAGE;

	static const string SORT_EMPTY_DISPLAY;
	static const string ERROR_SORT_MESSAGE;
	static const string ERROR_SORT_FLAG_MESSAGE;
	static const string ERROR_SORT_DATE_TIME_MESSAGE;
	static const string ERROR_SORT_DONE_MESSAGE;
};
#endif