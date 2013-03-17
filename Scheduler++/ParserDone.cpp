//@author A0002927L

#include "ParserDone.h"

const string ParserDone::regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";

const string ParserDone::regexArgsDoneTaskID = "\\s*([0-9]+)\\s*";
const string ParserDone::regexArgsDoneSearchTerm = "\\s*(\\S.*?)\\s*";
const string ParserDone::regexInstructionDone = "(do|done|did|finish(ed)?|complete(d)?)";

const string ParserDone::ERROR_FORMAT_BAD = "Done format: done <task index>, done <task name>, done listed";

ParserDone::ParserDone(ParserBase* _nextParser) : ParserBase(_nextParser) {
}

CommandBase* ParserDone::tryParse(string userCommand){
	
	string instruction;
	string arguments;

	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}
	
	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseDone(arguments);
}

bool ParserDone::getInstructionAndArguments(const string& userCommand, 
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

bool ParserDone::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionDone,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserDone::parseDone(const string& arguments) {
	CommandBase* returnedCommand;
	returnedCommand = parseByIndex(arguments);
	if (returnedCommand) {
		return returnedCommand;
	}

	returnedCommand = parseByListed(arguments);
	if (returnedCommand) {
		return returnedCommand;
	}

	returnedCommand = parseBySearchTerm(arguments);
	if (returnedCommand) {
		return returnedCommand;
	}

	throw(ParserException(ERROR_FORMAT_BAD));
}

CommandBase* ParserDone::parseByIndex(const string& arguments) {
	smatch matchResults;
	if (regex_match(arguments, matchResults, 
			regex(regexArgsDoneTaskID))) {

		try {
			int taskIndex = getTaskIDFromArgument(matchResults[ARG_POS_DONE_TASKID]);
			return new CommandDone(taskIndex);
		}catch (range_error&) {
			throw(ParserException(ERROR_FORMAT_BAD));
		}
	}

	return NULL;
}
CommandBase* ParserDone::parseByListed(const string& arguments) {
	smatch matchResults;
	if (regex_match(arguments, matchResults,
		regex(regexArgsListed, tr1::regex_constants::icase))) {
			return new CommandDone(CommandDone::DONE_ALL);
	}
	return NULL;
}
CommandBase* ParserDone::parseBySearchTerm(const string& arguments) {
	smatch matchResults;
	if (regex_match(arguments, matchResults, 
		regex(regexArgsDoneSearchTerm, tr1::regex_constants::icase))) {
		
		return new CommandDone(matchResults[ARG_POS_DONE_SEARCHTERM]);
	}
	return NULL;
}