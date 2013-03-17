//@author A0092076A

#ifndef WRITER_EXCEPTION_H
#define WRITER_EXCEPTION_H

#include <iostream>
#include <string>
#include <sstream>

#include "SchedulerPPException.h"

using namespace std;

class WriterException : public SchedulerPPException {
public:
	WriterException(string input) : SchedulerPPException(input) {}
private:
};

#endif