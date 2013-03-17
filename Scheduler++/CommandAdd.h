//@author A0002927L

#ifndef COMMAND_ADD_H
#define COMMAND_ADD_H

#include <string>

#include "LogicAdd.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandAdd : public CommandBase {
public:
	enum AddType{
		ADD_FLOATING_TASK,
		ADD_DEADLINE_TASK,
		ADD_TIMED_TASK,
	};

	void execute();

	CommandAdd(string taskName);
	CommandAdd(string taskName, ptime endTime);
	CommandAdd(string taskName, 
			   ptime startTime, 
			   ptime endTime);

	AddType getAddType();
	string getTaskName();
	ptime getStartTime();
	ptime getEndTime();

private:
	LogicAdd* _logicAdd;

	AddType _addType;

	string _taskName;
	ptime _startTime;
	ptime _endTime;
};
#endif