//@author A0002927L

#include "ParserUndo.h"

const string ParserUndo::undoKeyword = "undo";
const string ParserUndo::ERROR_FORMAT_BAD = "Undo format: undo. There is no need for any extra arguments behind.";


ParserUndo::ParserUndo(ParserBase *_nextParser) : ParserBase (_nextParser) {
}

CommandBase* ParserUndo::tryParse(string userCommand) {
	// Extract single keyword, while eliminating leading and trailing spaces
	stringstream wordExtractor(userCommand);
	string command;
	wordExtractor >> command;
	if (!boost::iequals(command, undoKeyword)) {
		return NULL;
	}

	wordExtractor >> ws;

	if (!wordExtractor.eof()) {
		throw (ParserException(ERROR_FORMAT_BAD));
	}

	return new CommandUndo(CommandUndo::UNDO_ACTION);
}