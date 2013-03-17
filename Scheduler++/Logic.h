//@author A0086671W

#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Parser.h"
#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "Display.h"
#include "CommandBase.h"

#include "WriterException.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;
//@author A0086671W
class Logic {
public:
	Display executeTextCommand( string text );
	Display executeShortCutCommand( CommandBase* commandClass );

	static Logic* getInstance();

private:
	// SINGLETON
	static Logic* _oneLogic;
	
	Parser* _parser;
	Data* _data;
	Writer* _writer;
	Task _task;

	CommandBase* _commandBase;

	Display _display;

	Logic();
	~Logic();

	static const int MAX_STRING_SIZE;

	static const string ERROR_STRING_LENGTH_EXCEEDED;
	static const string ERROR_UNABLE_TO_PROCESS;
	static const string ERROR_INVALID_SYNTAX;
	static const string ERROR_BLANK_COMMAND;
	static const string RESET_STATUS;
	static const string MAIN_FILE_NAME;
	static const string USER_LOG_FILE_NAME;
	static const string USER_LOG_CONCAT;
	static const string USER_LOG_SEPARATOR;
	static const string USER_LOG_ALL;

	void setupWriter();
	void setupData();
	void setupParser();
	void populateData();

	void logUserErrorActions( string errorString );
	void logAllActions( string text );
};

#endif