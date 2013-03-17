//@author A0002927L

#include "ParserFlag.h"

const string ParserFlag::regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";

const string ParserFlag::regexArgsFlagTaskID = "\\s*([0-9]+)\\s*";
const string ParserFlag::regexArgsFlagSearchTerm = "\\s*(\\S.*?)\\s*";

const string ParserFlag::regexInstructionFlag = "(flag|mark)";
const string ParserFlag::ERROR_FORMAT_BAD = "Flag format: flag <task index>, flag <task name>, flag listed";

ParserFlag::ParserFlag(ParserBase* _nextParser) : ParserBase(_nextParser) {
}

CommandBase* ParserFlag::tryParse(string userCommand){
	
	string instruction;
	string arguments;
	
	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}
	
	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseFlag(arguments);
}

bool ParserFlag::getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments) {
	regex rgx(regexInstructionAndArguments, regex_constants::icase);
	smatch matchResults;

	if (!regex_match(userCommand, matchResults, rgx)) {

		return false;
	}

	assert(matchResults.size () > ARGS_POS);
	instruction = matchResults[INSTRUCTION_POS];
	arguments = matchResults[ARGS_POS];


	return true;
}

bool ParserFlag::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionFlag,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserFlag::parseFlag(const string& arguments) {
	smatch matchResults;

	if (regex_match(arguments, matchResults, 
			regex(regexArgsFlagTaskID))) {
		try {
			int taskIndex = getTaskIDFromArgument(matchResults[ARG_POS_FLAG_TASKID]);
			return new CommandFlag(taskIndex);
		}catch (range_error&) {
			throw (ParserException(ERROR_FORMAT_BAD));
		}
	}else if (regex_match(arguments, matchResults, 
		regex(regexArgsListed, tr1::regex_constants::icase))) {
		return new CommandFlag(CommandFlag::FLAG_ALL);
	}else if (regex_match(arguments, matchResults, 
		regex(regexArgsFlagSearchTerm, tr1::regex_constants::icase))) {
		return new CommandFlag(matchResults[ARG_POS_FLAG_SEARCHTERM]);
	}else {
		throw (ParserException(ERROR_FORMAT_BAD));
	}
}
