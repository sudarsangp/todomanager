#include "CommandUndo.h"

CommandUndo::CommandUndo(UndoType undoType) : _undoType(undoType) {
}

CommandUndo::UndoType CommandUndo::getUndoType() {
	return _undoType;
}

void CommandUndo::execute() {
	if(_undoType == UNDO_ACTION) {
		LogicUndo::getInstance().undo();
	}
}