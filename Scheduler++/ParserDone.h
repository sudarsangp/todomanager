//@author A0002927L

#ifndef PARSER_DONE_H
#define PARSER_DONE_H

#include "ParserBase.h"
#include "CommandDone.h"

/**
 * Handler for "done" commands. 
 * 
 * Reads in either a task index, or a search term. 
 * 
 * Since there is no observable way of identifying whether a request is a
 * search term or a task index when the argument is just a number, 
 * returning a task index (if possible) takes priority.
 @author Ling Chun Kai
*/

class ParserDone : public ParserBase {
public:
	ParserDone(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};
	enum CommandType {DONE_TASKID, DONE_SEARCHTERM, INVALID};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	// Regex for checking if the instruction typed by the user is done
	static const string regexInstructionDone;
	
	// Regex for each done subtype
	static const string regexArgsDoneTaskID;
	static const string regexArgsDoneSearchTerm;
	static const string regexArgsDoneListed;

	// The following are the locations for parsed segments for the expressions
	static const int ARG_POS_DONE_TASKID = 1;
	static const int ARG_POS_DONE_SEARCHTERM = 1;

	// Error messages for parsing
	static const string ERROR_FORMAT_BAD;

	CommandBase* tryParse(string userCommand);

	bool getInstructionAndArguments(const string& userCommand, 
									string& instruction, 
									string& arguments);

	// This method checks that the instruction is of the type 'done'
	bool checkInstruction(const string& instruction);

	// This method finds out what kind of "done" command the user entered
	CommandType categorizeDoneCommand(const string& arguments, 
									  smatch& matchingArgs);

	// Returns a CommandDone object, and NULL otherwise. This is done based
	// on the arguments passed
	CommandBase* parseDone(const string& arguments);
	// Helper methods for parsing arguments
	CommandBase* parseByIndex(const string& arguments);
	CommandBase* parseByListed(const string& arguments);
	CommandBase* parseBySearchTerm(const string& arguments);

};

#endif