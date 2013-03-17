//@author A0086671W

#ifndef LOGIC_TUTORIAL_H
#define LOGIC_TUTORIAL_H

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

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicTutorial{
private:
	// the states determine the current state the user is at.
	enum States {
		INIT_STATE,
		ADD_STATE,
		ADD_TIME_STATE,
		DELETE_INDEX_STATE,
		DELETE_DONE_STATE,
		LIST_STATE,
		DONE_STATE,
		END_STATE,
		UNDO_STATE
	};

public:
	static LogicTutorial* getInstance();
	Display startTutorial();
	Display executeTutorial( string userInput );

private:
	void addSampleTasks();
	void addExtraTasks();
	void initTutorial();
	string showHelpStatus( States currentState );
	void updateDisplay( string message );

	static LogicTutorial* _oneLogicTutorial;

	States tutorialState;

	LogicTutorial();
	~LogicTutorial();

	Parser* _parser;
	Data* _data;
	Writer* _writer;

	CommandAdd *_commandAddSpecific;
	CommandDelete * _commandDelSpecific;
	CommandDone * _commandDoneSpecific;
	CommandList * _commandListSpecific;
	CommandUndo * _commandUndoSpecific;

	CommandBase* _commandBase;

	Display _display;

	static const string WELCOME_MSG;
	static const string SUCCESS_TUTORIAL_ADD_MSG;
	static const string SUCCESS_TUTORIAL_ADD_TIME_MSG;
	static const string SUCCESS_TUTORIAL_DELETE_MSG;
	static const string SUCCESS_TUTORIAL_DELETE_DONE_MSG;
	static const string SUCCESS_TUTORIAL_DONE_MSG;
	static const string SUCCESS_TUTORIAL_LIST_MSG;
	static const string END_TUTORIAL_MSG;
	static const string COMPLETED_TUTORIAL_MSG;

	static const string ADDED_NEW_TASKS_MSG;
	static const string ERROR_TUTORIAL_ADD_TIMED_MSG;

	static const int MAX_STRING_SIZE;
	static const string ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	static const string ERROR_STRING_LENGTH_EXCEEDED;
	static const string ERROR_INVALID_COMMAND_MESSAGE;
	static const string ERROR_TRY_AGAIN_MESSAGE;
	static const string ERROR_UNABLE_TO_PROCESS;
	static const string EMPTY_STATUS;
	static const string FILE_NAME;
};

#endif