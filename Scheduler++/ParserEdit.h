//@author A0002927L

#ifndef PARSER_EDIT_H
#define PARSER_EDIT_H

#include "ParserBase.h"
#include "CommandEdit.h"

/**
 * Handles edit commands 
 *
 * The following are handled in accordance with the priority
 * Assume argument is a datetime
 * Assume argument is a time (only)
 *
 * Examples of edit commands:
 * edit 4 end 1 Jan
 * edit 3 start 1 Jan 2012, 2359

 @author Ling Chun Kai

*/

using namespace std;
using namespace boost::posix_time;

class ParserEdit : public ParserBase {
public:
	ParserEdit(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};
	enum EditSubType {EDIT_START, EDIT_END, EDIT_NAME, INVALID_SUBTYPE};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	static const string regexArgsEditStart;
	static const string regexArgsEditEnd;
	static const string regexArgsEditRename;

	// These are the keywords allowed for instructions
	static const string regexInstructionEdit;
	
	// These are the positions of the extracted arguments in the smatch
	// structure after extracting arguments.
	static const int ARG_POS_EDIT_TASKID = 1;
	
	static const int ARG_POS_EDIT_NEW_NAME = 2;
	static const int ARG_POS_EDIT_NEW_START = 2;
	static const int ARG_POS_EDIT_NEW_END = 2;

	// Parsing error messages
	static const string ERROR_FORMAT_BAD;
	static const string ERROR_BAD_TASK_INDEX;
	static const string ERROR_FORMAT_BAD_START_DATE;
	static const string ERROR_FORMAT_BAD_END_DATE;

	CommandBase* tryParse(string userCommand);

	// This method takes a user command and splits it into the instruction and 
	// argument components
	bool getInstructionAndArguments(const string& userCommand, 
									string& instruction, 
									string& arguments);

	// This method checks that the instruction is of the type 'edit'
	bool checkInstruction(const string& instruction);

	// This method parses the arguments provided to an edit Instruction
	// and stores them in the PARSED_COMMAND struct passed.
	CommandBase* parseEdit(const string& arguments);

	// The following method categorize the actual CommandType based on the arguments provided.
	// It returns the appropriate command type. matchingArgs will be 
	// filled up with the relevant details upon successful completion
	EditSubType categorizeEditCommand(const string& arguments, smatch& matchingArgs);

	// This method fills a PARSED_COMMAND struct with information indicating that
	// there was an error in syntax within - eg. it did couldn't be classified 
	// as any one of the subtypes defined.
	CommandBase* ParserEdit::makeCmdEditErrorSyntax(smatch& matchingArgs);
	// This method parses and fills up a PARSED_COMMAND struct based
	// on the subtype of the command edit idenfitied.
	CommandBase* ParserEdit::makeCmdEditRename(smatch& matchingArgs);
	CommandBase* ParserEdit::makeCmdEditStart(smatch& matchingArgs);
	CommandBase* ParserEdit::makeCmdEditEnd(smatch& matchingArgs);

};

#endif