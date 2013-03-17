//@author A0002927L

#ifndef COMMAND_EDIT_H
#define COMMAND_EDIT_H

#include <string>

#include "LogicEdit.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandEdit : public CommandBase {
public:
	enum EditType {
		EDIT_START_TIME,
		EDIT_START_DATETIME,
		EDIT_END_TIME,
		EDIT_END_DATETIME,
		EDIT_RENAME
	};

	void execute();

	CommandEdit( EditType editType ) { _editType = editType; };
	// for edit start|end date + optional time
	CommandEdit( EditType editType, int index, ptime date );
	// for edit start|end time only
	CommandEdit( EditType editType, int index, time_duration time );
	CommandEdit( EditType editType, int index, string taskName );

	EditType getEditType();
	ptime getDateTime();
	time_duration getTime();
	string getTaskName();

private:
	LogicEdit* _logicEdit;

	EditType _editType;

	ptime _date;
	time_duration _time;
	string _taskName;
	int _index;
};
#endif