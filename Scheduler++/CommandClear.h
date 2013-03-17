//@author A0002927L

#ifndef COMMAND_CLEAR_H
#define COMMAND_CLEAR_H

#include <string>

#include "LogicClear.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandClear : public CommandBase {
public:
	void execute();

private:
	LogicClear* _logicClear;
};
#endif