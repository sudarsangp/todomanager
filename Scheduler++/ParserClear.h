//@author A0002927L

#ifndef PARSER_CLEAR_H
#define PARSER_CLEAR_H

#include "ParserBase.h"
#include "CommandClear.h"

/**
 * This is the handler for "clear" commands. 
 *
 * Formats supporter: clear YES
 * Note: This command is case sensitive!
 *
*/

class ParserClear : public ParserBase {
public:
	ParserClear(ParserBase *_nextParser);
private: 
	static const string CLEAR_KEYWORD;
	static const string ERROR_FORMAT_BAD;
	static const string CLEAR_CONFIRMATION;
	CommandBase* tryParse(string userCommand);
};

#endif