//@author A0002927L

#ifndef PARSER_ADD_H
#define PARSER_ADD_H

#include <string>
#include <regex>
#include <boost\algorithm\string.hpp>
#include <boost\date_time.hpp>

#include "ParserBase.h"
#include "CommandAdd.h"

using namespace std;
using namespace boost::posix_time;

/**
 * This is the handler for "add" commands. 
 * This class handles all "add" commands, including those from different
 * subtypes - floating, deadline and timed.
 *
 * Note to developer: Parsing here is done with the aid of regular expressions
 * You may wish to modify the constant strings in the CPP file in order to allow
 * a larger range of commands
 *
 * Formats: Note - date/date time/time period simplifications are done by 
 * ParserDateTime
 *
 * NORMAL FORMATS
 * -- <add alias> <task> <time period>
 * -- <add alias> <task> [optional: deadline keywords] <time period>
 *
 * ESCAPE SEQUENCES
 * '>' is used as an escape character to handle tricky cases.
 * -- <add alias> <task> '>' <time period>
 * -- <add alias> <task> '>' <date time>
 * 
 * SWAPPED FORMATS
 * The positions of the time and task name are swapped
 * -- <add alias> <time period> <task name>
 *
*/ 

class ParserAdd : public ParserBase {
public:
	ParserAdd(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, ARGS_POS, NUM_MAJOR_SEGMENTS};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;
	
	static const string regexArgsEscape;
	static const array <string, 5> deadlineTaskKeywords;

	// The following are the locations for parsed segments for the expressions
	static const int ARG_POS_NAME = 1;
	static const int ARG_POS_TIME = 2;

	// The following are the keywords allowed for instructions
	static const string regexInstructionAdd;

	// This method tries to parse the command as an add instruction	
	CommandBase* tryParse(string userCommand);

	// Parsing error messages
	static const string ERROR_MISSING_NAME;
	static const string ERROR_FORMAT_BAD;

	// This method takes a user command and splits it into the instruction and 
	// argument components
	bool getInstructionAndArguments(const string& userCommand, 
									string& instruction, 
									string& arguments);

	// This method checks that the instruction is of the type 'add'
	bool checkInstruction(const string& instruction);

	// These 2 methods parse the arguments provided to an add Instruction //
	// and stores the pointer to the created CommandBase object created   //
	// This method parses the cases where the time periods/date times 
	// are in the front or at the back of the argument.
	// This method will only handle SOME deadline and timed tasks when
	// they are entered in shortened form, ie, no delimiters.
	CommandBase* parseAddQuick(const string& arguments);
	// This method only takes into account the special escape sequences
	// defined. ParsedCommand will be NULL if it was unable to parse
	// using the escape sequences
	CommandBase* parseAddEscape(const string& arguments);

	// These methods actually create (allocate memory) to the command
	// created
	CommandAdd* makeCommandAdd(string name);
	CommandAdd* makeCommandAdd(string name, ptime endTime);
	CommandAdd* makeCommandAdd(string name, ptime startTime, ptime endTime);
};

#endif