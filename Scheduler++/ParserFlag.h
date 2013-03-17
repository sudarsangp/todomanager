//@author A0002927L

#ifndef PARSER_FLAG_H
#define PARSER_FLAG_H

#include "ParserBase.h"
#include "CommandFlag.h"

/**
 * Handler for "Flag" commands. 
 * 
 * Reads in either a task index, or a search term. 
 * 
 * Since there is no observable way of identifying whether a request is a
 * search term or a task index when the argument is just a number, 
 * returning a task index (if possible) takes priority.
 @author Ling Chun Kai
*/

class ParserFlag : public ParserBase {
public:
	ParserFlag(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};
	enum CommandType {DONE_TASKID, DONE_SEARCHTERM, INVALID};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	static const string regexInstructionFlag;
	
	static const string regexArgsFlagTaskID;
	static const string regexArgsFlagSearchTerm;

	// The following are the locations for parsed segments for the expressions
	static const int ARG_POS_FLAG_TASKID = 1;
	static const int ARG_POS_FLAG_SEARCHTERM = 1;

	// Error messages for parsing
	static const string ERROR_FORMAT_BAD;

	CommandBase* tryParse(string userCommand);

	bool getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments);

	// This method checks that the instruction is of the type 'flag'
	bool checkInstruction(const string& instruction);

	// This method finds out what kind of "flag" command the user entered
	CommandType categorizeDoneCommand(const string& arguments, smatch& matchingArgs);

	CommandBase* parseFlag(const string& arguments);
};

#endif