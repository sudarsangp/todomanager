//@author A0092076A

#ifndef SCHEDULERPP_EXCEPTION_H
#define SCHEDULERPP_EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class SchedulerPPException {

private:

	string message;

public:

	SchedulerPPException(string input){ message = input; }
	virtual inline string getMessage() { return message; }
	
};

#endif