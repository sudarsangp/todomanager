//@author A0002927L

#include "ParserAdd.h"

const string ParserAdd::regexInstructionAndArguments = 
	"\\s*([a-zA-Z]+)\\s*(.*?)\\s*";
const string ParserAdd::regexArgsEscape = "\\s*([^>]*?)\\s*(?:>)"
											 "\\s*(.*)?\\s*";

const string ParserAdd::regexInstructionAdd = "(add|create)";
const array <string, 5> ParserAdd::deadlineTaskKeywords = 
	{{string("by "), string("@"), string("at "), string("on "), string("before ")}};

const string ParserAdd::ERROR_MISSING_NAME = 
	"Please enter a description of the task";

const string ParserAdd::ERROR_FORMAT_BAD = 
	"Add format: add [task description] from [date] to [date]";

ParserAdd::ParserAdd(ParserBase* _nextParser) : ParserBase(_nextParser) {}

CommandBase* ParserAdd::tryParse(string userCommand){
	string instruction;
	string arguments;
	getInstructionAndArguments(userCommand, instruction, arguments);
	if (!checkInstruction(instruction)) {
		return false;
	}
	CommandBase* parsedCommand;
	// Highest priority: Test for escape characters 
	parsedCommand = parseAddEscape(arguments);

	// Second Priority: Test for date/times/time periods
	if (parsedCommand == NULL) {
		parsedCommand = parseAddQuick(arguments);
	}
	
	// We only assume that this is a floating task at the end
	if (parsedCommand == NULL) {
		parsedCommand = makeCommandAdd(arguments);
	}

	if (parsedCommand != NULL) {
		return parsedCommand;
	}

	throw(ParserException(ERROR_FORMAT_BAD));
}

bool ParserAdd::getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments) {
	regex rgx(regexInstructionAndArguments,
			  regex_constants::icase);
	smatch matchResults;

	if (!regex_match(userCommand, matchResults, rgx)) {
		return false;
	}
	
	assert(matchResults.size() > ARGS_POS);
	instruction = matchResults[INSTRUCTION_POS];
	arguments = matchResults[ARGS_POS];
	
	return true;
}

bool ParserAdd::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionAdd,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserAdd::parseAddQuick(const string& arguments) {
	// Try to parsed by time period
	string remaining;
	PairDateTime parsedTimePeriod = extractTimePeriod(arguments, remaining);
	if (!parsedTimePeriod.isNull()) {
		return makeCommandAdd(stripWhiteSpaces(remaining), 
							  parsedTimePeriod.begin(), 
							  parsedTimePeriod.end());
	}

	// Try to parse by time/date only. 
	vector<string> keywords;// Consolidate keywords for the aliases of deadline
	for (unsigned int x = 0; x < deadlineTaskKeywords.size(); x++) {
		keywords.push_back(deadlineTaskKeywords[x]);
	}
	ptime parsedDateTime = extractDateTime(arguments, remaining, keywords);
	if (!parsedDateTime.is_not_a_date_time()) {
		return makeCommandAdd(stripWhiteSpaces(remaining), parsedDateTime);
	}		
	
	return NULL;
}

CommandBase* ParserAdd::parseAddEscape(const string& arguments) {	
	CommandBase* parsedCommand;
	smatch matchResults;
	if (regex_match(arguments, matchResults, regex(regexArgsEscape))) {
		// Attempt to parse individual formats.
		string timeString = matchResults[ARG_POS_TIME];
		string taskName = matchResults[ARG_POS_NAME];
		PairDateTime timePeriodParsed =	parseTimePeriod(timeString);
		ptime dateTimeParsed = parseDateTime(timeString);

		// Add by time period (both date and time)
		if (!timePeriodParsed.isNull()){
			parsedCommand = makeCommandAdd(taskName,
										   timePeriodParsed.begin(),
										   timePeriodParsed.end());
		}else if (!dateTimeParsed.is_not_a_date_time()) {
			// Add deadline task (the string can be interpreted as a datetime)
			parsedCommand = makeCommandAdd(taskName, dateTimeParsed);
		}else {
			throw(ParserExceptionBadDate());
		}		
	}else {
		parsedCommand = NULL; // Unable to parse by escape sequence
	}

	return parsedCommand;
}

CommandAdd* ParserAdd::makeCommandAdd(string name) {
	if (name == EMPTY_STRING) {
		throw (ParserException(ERROR_MISSING_NAME));
	}
	return new CommandAdd(name);
}

CommandAdd* ParserAdd::makeCommandAdd(string name, ptime endTime) {
	return new CommandAdd(name, endTime);
}

CommandAdd* ParserAdd::makeCommandAdd(string name, 
									  ptime startTime, 
									  ptime endTime) {
	return new CommandAdd(name, startTime, endTime);
}