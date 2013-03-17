//@author A0002927L

#ifndef COMMAND_UNDO_H
#define COMMAND_UNDO_H

#include <string>

#include "LogicUndo.h"
#include "CommandBase.h"

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class CommandUndo : public CommandBase {
public:
	enum UndoType{UNDO_ACTION};

	CommandUndo(UndoType undoType);
	void execute();
	UndoType getUndoType();

private:
	UndoType _undoType;
	LogicUndo* _logicUndo;
};
#endif