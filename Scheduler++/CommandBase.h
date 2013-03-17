//@author A0002927L

#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include <iostream>

#include "Display.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandBase {
public:
	virtual void execute() = 0;
};
#endif