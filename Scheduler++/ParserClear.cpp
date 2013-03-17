//@author A0002927L

#include "ParserClear.h"

const string ParserClear::CLEAR_KEYWORD = "clear";
const string ParserClear::CLEAR_CONFIRMATION = "YES";

const string ParserClear::ERROR_FORMAT_BAD = "Clear format: clear YES";

ParserClear::ParserClear(ParserBase *_nextParser) : ParserBase (_nextParser) {
}

CommandBase* ParserClear::tryParse(string userCommand) {
	// Extract single keyword, while eliminating leading and trailing spaces
	stringstream wordExtractor(userCommand);
	string command;
	wordExtractor >> command;
	if (!boost::iequals(command, CLEAR_KEYWORD)) {
		return NULL;
	}

	string nextWord;
	wordExtractor >> nextWord;

	if (!boost::equals(nextWord, CLEAR_CONFIRMATION)) {
		throw (ParserException(ERROR_FORMAT_BAD));
	}

	return new CommandClear();
}