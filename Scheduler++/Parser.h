//@author A0002927L

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <regex>
#include <boost\algorithm\string.hpp>
#include <boost\date_time.hpp>

#include "ParserBase.h"
#include "ParserEdit.h"
#include "ParserAdd.h"
#include "ParserList.h"
#include "ParserSort.h"
#include "ParserCatchAll.h"
#include "ParserDelete.h"
#include "ParserDone.h"
#include "ParserClear.h"
#include "ParserUndo.h"
#include "ParserFlag.h"

using namespace std;
using namespace boost::posix_time;

/**
 * The purpose of the Parser is to read and parse line(s) of input. 
 * The required data is then return to the driver function via the 
 * CommandBase pointer. Polymorphism is used to return the proper 
 * Command type.
 
 * Glossary: For the purpose of this class, the following definitions are used

 1) ParsedCommand - A class containing the packaged information vital to
 accurately describe the contents of a command. Depending on the derived
 type of the command, different information may be stored in the command.
 ref. CommandBase

 2) Command - In the context of the Parser, this also refers to 
 the entire string(line) which needs to be parsed

 3) CommandType - The final nature of the entire command after being parsed.
 Usually, this refers to the subtype of the instruction. For example, under
 add, some examples are: ADD_FLOATING_TASK, ADD_DEADLINE_TASK.

 4) Instruction - The type of command which the user types. Some examples are
	a) ADD
	b) DELETE
	c) EDIT
	...
 This corressponds with what the user "thinks" he will be doing.
 The definition of Instruction will only be used within this class (Parser).

 5) Arguments - The part of the command which does not contain the instruction
For example, in the command "add CS2103 > 10 Dec to 15 Dec", the string
"CS2103 > 10 Dec to 15 Dec" is considered the argument of the command.

 * Usage: There only API from which a user may access this class is the
 parseUserComand() method. See below for additional details.
 
 6) The entire parser is created based on the chain of responsibiity architecture
 This class serves as the "head" of the chain of responsibility - it does 
 not do any actual parsing, it merely creates and instantiates all the 
 children class, and fixes the successor chain accordingly

 */

class Parser : public ParserBase {
public:
	Parser();
	~Parser();
private:
	
	CommandBase* tryParse(string userCommand);

	// Pointers to specific parsers
	ParserBase *parserAdd;
	ParserBase *parserList;
	ParserBase *parserSort;
	ParserBase *parserCatchAll;
	ParserBase *parserEdit;
	ParserBase *parserDelete;
	ParserBase *parserDone;
	ParserBase *parserClear;
	ParserBase *parserUndo;
	ParserBase *parserFlag;
};

#endif