//@author A0002927L

#ifndef PARSER_UNDO_H
#define PARSER_UNDO_H

#include "ParserBase.h"
#include "CommandUndo.h"

/**
 * This is the handler for Undo
 *
 @author Ling Chun Kai
*/

class ParserUndo : public ParserBase {
public:
	ParserUndo(ParserBase *_nextParser);
private: 
	static const string undoKeyword;
	static const string ERROR_FORMAT_BAD;
	CommandBase* tryParse(string userCommand);
};

#endif