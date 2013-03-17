#include "CommandClear.h"

void CommandClear::execute() {
	LogicClear::getInstance().clearTask();
}