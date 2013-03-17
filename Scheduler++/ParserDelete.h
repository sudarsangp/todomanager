//@author A0002927L

#ifndef PARSER_DELETE_H
#define PARSER_DELETE_H

#include "ParserBase.h"
#include "CommandDelete.h"

/**
 * This is the handler for delete commands.
 * 
 * Developers should note that there are commands here which may be interpreted
 * in several ways - for example the command "delete done" may refer to the deletion
 * of all "done" tasks. However, it could also mean for the program to delete the 
 * task containing "done".
 *
 * In the above case - the more precise syntax will be chosen over the more relaxed
 * version - ie. delete done will delete all "done" tasks
 @author Ling Chun Kai
*/

class ParserDelete : public ParserBase {
public:
	ParserDelete(ParserBase* _nextParser);
private:
	// Constants to aid in regex parsing and deciding command types
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};
	enum CommandType {DELETE_SEARCHTERM, DELETE_TASKID};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	// Valid variants of delete instructions
	static const string regexInstructionDelete;

	// Regular expression for each type of command
	static const string regexArgsDeleteTaskID;
	static const string regexArgsDeleteSearchTerm;
	static const string regexArgsDeleteDone;

	// Argument positions in the regular expression
	static const int ARG_POS_DELETE_SEARCHTERM = 1;
	static const int ARG_POS_DELETE_DONE = 1;
	static const int ARG_POS_DELETE_TASKID = 1;

	// Error Messages while parsing
	static const string ERROR_FORMAT_BAD;

	// Try to match the command with any of the recognized formats. Returns 
	// a pointer to the command object created.
	CommandBase* tryParse(string userCommand);

	// Splits the given command into instructions and arguments.
	bool getInstructionAndArguments(const string& userCommand, 
									string& instruction, 
									string& arguments);


	// This method checks that the instruction is of the type 'delete'
	bool checkInstruction(const string& instruction);
	
	// Attempts to parse a delete instruction given the arguments
	CommandBase* parseDelete(const string& arguments);

	// This method finds out what kind of "delete" command the user entered
	CommandType categorizeDeleteCommand(const string& arguments, smatch& matchingArgs);

	// Methods used to create the CommandDelete class
	CommandBase* makeCmdDeleteSearchTerm(smatch& matchingArgs);
	CommandBase* makeCmdDeleteTaskID(smatch& matchingArgs);
	CommandBase* makeCmdDeleteDone();
	CommandBase* makeCmdDeleteListed();
};

#endif