//@author A0002927L

#ifndef PARSER_CATCH_ALL_H
#define PARSER_CATCH_ALL_H

#include "ParserBase.h"

/**
 * This class is a "catch-all" class. It handles all instructions 
 * which has not been parsed by the time it reaches to this handler.
 *
 * It simply returns a null command pointer without doing any form of parsing
 *
*/

class ParserCatchAll : public ParserBase {
public:
	ParserCatchAll();
	CommandBase* parseUserCommand(string userCommand);
private:
	CommandBase* tryParse(string userCommand);

};

#endif