//@author A0092976A

#ifndef LOGIC_UNDO_H
#define LOGIC_UNDO_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "Data.h"
#include "Task.h"
#include "Writer.h"
#include "LogicBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class LogicUndo : public LogicBase {
public:
	static LogicUndo& getInstance();

	Display undo();
	void undoStackPush( Data stackData );

private:
	static LogicUndo* _logicUndo;

	stack<Data> undoStackData;

	static const string SUCCESS_UNDO_MESSAGE;

	static const string ERROR_UNDO_MESSAGE;
};
#endif