//@author A0002927L

#include "ParserList.h"

const string ParserList::
	regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";

const string ParserList::regexArgsListMonth = "\\s*((this[ ]+)?month)\\s*";
const string ParserList::regexArgsListWeek = "\\s*((this[ ]+)?week)\\s*";
const string ParserList::regexArgsListDay = "\\s*(day|today)\\s*";
const string ParserList::regexArgsListDone = "\\s*(done)\\s*";
const string ParserList::regexArgsListNotDone = "\\s*(undone|not\\s+done)\\s*";
const string ParserList::regexArgsListOverdue = "\\s*(overdue)\\s*";
const string ParserList::regexArgsListAll = "([\\s]*)";
const string ParserList::regexArgsListString = "\\s*(.+?)\\s*";

const string ParserList::regexInstructionList = "(list|display|show|search)";

ParserList::ParserList(ParserBase* _nextParser) : ParserBase(_nextParser) {	
}

CommandBase* ParserList::tryParse(string userCommand){
	
	string instruction;
	string arguments;
	
	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}
	
	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseList(arguments);
}

bool ParserList::getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments) {
	regex rgx(regexInstructionAndArguments, regex_constants::icase);
	smatch matchResults;

	if (!regex_match(userCommand, matchResults, rgx)) {

		return false;
	}

	assert(matchResults.size() > ARGS_POS);
	instruction = matchResults[INSTRUCTION_POS];
	arguments = matchResults[ARGS_POS];

	return true;
}

bool ParserList::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionList,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserList::parseList(const string& arguments) {
	smatch matchResults;

	CommandType commandType = categorizeListCommand(arguments, matchResults);

	switch (commandType) {
	case LIST_ALL:
		return makeCmdListAll();
		break;
	case LIST_DAY:
		return makeCmdListDay();
		break;
	case LIST_MONTH:
		return makeCmdListMonth();
		break;
	case LIST_WEEK:
		return makeCmdListWeek();
		break;
	case LIST_STRING:
		return makeCmdListString(matchResults[ARG_POS_LIST_STRING]);
		break;
	case LIST_DONE:
		return makeCmdListDone();
		break;
	case LIST_NOT_DONE:
		return makeCmdListNotDone();
		break;
	case LIST_OVERDUE:
		return makeCmdListOverdue();
		break;
	default:
		assert(false && "Unexpected commandType for 'list' instruction");
		break;
	}
	return NULL;
}

ParserList::CommandType ParserList::categorizeListCommand(const string& arguments, 
												 smatch& matchingResults) {
	CommandType returnedCommandType;

	if (regex_match(arguments, 
					matchingResults, 
					regex(regexArgsListAll, 
						  tr1::regex_constants::icase))) {
		returnedCommandType = LIST_ALL;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListMonth, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_MONTH;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListWeek, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_WEEK;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListDay, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_DAY;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListDone, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_DONE;
	}else if (regex_match(arguments,
						  matchingResults,
						  regex(regexArgsListNotDone,
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_NOT_DONE;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListOverdue, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_OVERDUE;
	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsListString, 
								tr1::regex_constants::icase))) {
		returnedCommandType = LIST_STRING;
	}else{
		returnedCommandType = INVALID;
	}

	return returnedCommandType;
}

CommandBase* ParserList::makeCmdListAll() {
	return new CommandList(CommandList::LIST_ALL);
}

CommandBase* ParserList::makeCmdListWeek() {
	ptime curDateTime = second_clock::local_time();
	return new CommandList(getFirstOfWeek(curDateTime),
						   getLastOfWeek(curDateTime));
}

CommandBase* ParserList::makeCmdListMonth() {

	ptime curDateTime = second_clock::local_time();
	return new CommandList(getFirstOfMonth(curDateTime),
						   getLastOfMonth(curDateTime));
}

CommandBase* ParserList::makeCmdListDone() {

	return new CommandList(CommandList::LIST_DONE);
}

CommandBase* ParserList::makeCmdListDay() {
	
	ptime curDateTime = second_clock::local_time();
	return new CommandList(getFirstOfDay(curDateTime), 
						   getLastOfDay(curDateTime));
}

CommandBase* ParserList::makeCmdListString(string str) {
	ptime parsedDateTime = parseDateTime(str);	
	if (!parsedDateTime.is_not_a_date_time()) {
		return makeCmdListDateTime(parsedDateTime);
	}
	CommandBase* parsedCommand = makeCmdListPeriod(str);
	if (parsedCommand != NULL) {
		return parsedCommand;
	}

	parsedCommand = makeCmdListSpecificMonth(str);
	if (parsedCommand != NULL) {
		return parsedCommand;
	}else{
		return makeCmdListSearchTerm(str);
	}
}

CommandBase* ParserList::makeCmdListDateTime(ptime dateTime) {
	return new CommandList(second_clock::local_time(), dateTime);
}

CommandBase* ParserList::makeCmdListPeriod(ptime startTime, ptime endTime) {
	return new CommandList(startTime, endTime);
}

CommandBase* ParserList::makeCmdListNotDone() {
	return new CommandList(CommandList::LIST_NOT_DONE);
}

CommandBase* ParserList::makeCmdListSearchTerm(string searchTerm) {
	return new CommandList(searchTerm);
}

CommandBase* ParserList::makeCmdListSpecificMonth(string monthStr) {
	int parsedMonth;
	// Parse month, if month is valid
	try {
		parsedMonth = parseMonth(monthStr);
	}catch (invalid_argument) {
		return NULL;
	}

	// Ensure that the month is the coming month, and not a month which
	// has already passed
	date currentDate = second_clock::local_time().date();
	date startDate = date(currentDate.year(), parsedMonth, 1);
	if (currentDate.month() > parsedMonth) {
		startDate += years(1);
	}

	ptime startTime = ptime(startDate);
	ptime endTime = getLastOfMonth(startTime);
	return makeCmdListPeriod(startTime, endTime);
}

CommandBase* ParserList::makeCmdListPeriod(string periodStr) {
	PairDateTime timePeriod = parseTimePeriod(periodStr);
	if (timePeriod.isNull()) {
		return NULL;
	}else {
		return new CommandList(timePeriod.begin(), timePeriod.end());
	}
}

CommandBase* ParserList::makeCmdListOverdue() {
	return new CommandList(CommandList::LIST_OVERDUE);
}
