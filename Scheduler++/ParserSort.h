//@author A0002927L

#ifndef PARSER_SORT_H
#define PARSER_SORT_H

#include "ParserBase.h"
#include "CommandSort.h"

/**
 * This is the handler for sort commands
 *
 * Supports sort by alphabet, completed, time, and flagged 
 *
 @author Ling Chun Kai
*/

class ParserSort : public ParserBase {
public:
	ParserSort(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};
	enum CommandType {SORT_ALPHABET, SORT_COMPLETED, SORT_TIME, SORT_FLAG};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	static const string regexInstructionSort;

	static const string regexArgsSortAlphabet;
	static const string regexArgsSortTime;
	static const string regexArgsSortCompleted;
	static const string regexArgsSortFlag;

	// Error Messages for parsing
	static const string ERROR_FORMAT_BAD;

	CommandBase* tryParse(string userCommand);

	bool getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments);

	// This method checks that the instruction is of the type 'list'
	bool checkInstruction(const string& instruction);

	// This method finds out what kind of "sort" command the user entered
	CommandType categorizeSortCommand(const string& arguments, 
									  smatch& matchingArgs);

	CommandBase* parseSort(const string& arguments);

};

#endif