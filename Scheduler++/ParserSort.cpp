//@author A0002927L

#include "ParserSort.h"

const string ParserSort::
	regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";
const string ParserSort::regexArgsSortAlphabet = "\\s*(a(lpha(bet)?)?)\\s*";
const string ParserSort::regexArgsSortCompleted = "\\s*(d(one)?)\\s*";
const string ParserSort::regexArgsSortTime = "\\s*((t(ime)?)|date)\\s*";
const string ParserSort::regexArgsSortFlag = "\\s*(f(lag(ged)?)?)\\s*";
const string ParserSort::regexInstructionSort = "(sort)";

const string ParserSort::ERROR_FORMAT_BAD = 
	"Sort format: sort a[lphabet], sort t[ime], sort f[lagged], sort d[one]";

ParserSort::ParserSort(ParserBase* _nextParser) : ParserBase(_nextParser) {
}

CommandBase* ParserSort::tryParse(string userCommand) {
	
	string instruction;
	string arguments;

	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}

	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseSort(arguments);
}

bool ParserSort::getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments) {
	regex sortFormat(regexInstructionAndArguments, regex_constants::icase);
	smatch matchResults;

	if (!regex_match(userCommand, matchResults, sortFormat)) {

		return false;
	}

	assert(matchResults.size() > ARGS_POS);
	instruction = matchResults[INSTRUCTION_POS];
	arguments = matchResults[ARGS_POS];
	

	return true;
}

bool ParserSort::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionSort,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserSort::parseSort(const string& arguments) {
	smatch matchingResults;

	if (regex_match(arguments, 
					matchingResults, 
					regex(regexArgsSortAlphabet, regex_constants::icase))) {

		return new CommandSort(CommandSort::SORT_ALPHABET);

	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsSortCompleted, regex_constants::icase))) {

		return new CommandSort(CommandSort::SORT_COMPLETED);

	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsSortFlag, regex_constants::icase))) {

		return new CommandSort(CommandSort::SORT_FLAG);

	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsSortTime, regex_constants::icase))) {

		return new CommandSort(CommandSort::SORT_TIME);

	}else {
		throw (ParserException(ERROR_FORMAT_BAD));
	}

	return NULL;
}

