//@author A0002927L

#ifndef PARSER_LIST_H
#define PARSER_LIST_H

#include "ParserBase.h"
#include "CommandList.h"
/**
 * This class handles all list commands.
 *
 * It currently does not support specific operations like "list next month"
 * or "list next week" or "list <date>"
 *
 * This is to be added in future edits.
 @author Ling Chun Kai
*/

using namespace std;
using namespace boost::posix_time;

class ParserList : public ParserBase {
public:
	ParserList(ParserBase* _nextParser);
private:
	enum {INSTRUCTION_POS = 1, 
		 ARGS_POS, 
		 NUM_MAJOR_SEGMENTS};

	enum CommandType{LIST_ALL, 
					 LIST_DAY, 
					 LIST_WEEK, 
					 LIST_MONTH, 
					 LIST_STRING,
					 LIST_DONE,
					 LIST_NOT_DONE,
					 LIST_OVERDUE,
					 INVALID};

	// The following are regex constants used for parsing
	static const string regexInstructionAndArguments;

	static const string regexArgsListAll;
	static const string regexArgsListMonth;
	static const string regexArgsListWeek;
	static const string regexArgsListDay;
	static const string regexArgsListDone;
	static const string regexArgsListNotDone;
	static const string regexArgsListOverdue;
	// The string could be either a date, or a search term
	static const string regexArgsListString;

	static const int ARG_POS_LIST_STRING = 1;

	// The following are the keywords allowed for instructions
	static const string regexInstructionList;
	
	CommandBase* tryParse(string userCommand);

	// This method takes a user command and splits it into the instruction and 
	// argument components
	bool getInstructionAndArguments(const string& userCommand, 
									string& instruction, 
									string& arguments);

	// This method checks that the instruction is of the type 'list'
	bool checkInstruction(const string& instruction);

	// This method parses the arguments provided to an add Instruction
	// and stores them in the CommandList object
	CommandBase* parseList(const string& arguments);

	// The following methods categorize the actual CommandType based on the arguments provided.
	// It returns the appropriate command type. matchingArgs will be 
	// filled up with the relevant details upon successful completion
	CommandType categorizeListCommand(const string& arguments, 
									  smatch& matchingArgs);

	// The following methods creates the CommandList object 
	// by reading. Additional parsing by individual methods may be required.
	// Returns true if the parsing was a success.
	CommandBase* makeCmdListAll();
	CommandBase* makeCmdListMonth();
	CommandBase* makeCmdListWeek();
	CommandBase* makeCmdListDay();
	CommandBase* makeCmdListDone();
	CommandBase* makeCmdListNotDone();
	CommandBase* makeCmdListString(string str);

	CommandBase* makeCmdListDateTime(ptime dateTime);
	CommandBase* makeCmdListPeriod(ptime startTime, ptime endTime);
	CommandBase* makeCmdListSearchTerm(string searchTerm);

	CommandBase* makeCmdListSpecificMonth(string monthStr);
	CommandBase* makeCmdListPeriod(string durationStr);
	CommandBase* makeCmdListOverdue();
};

#endif