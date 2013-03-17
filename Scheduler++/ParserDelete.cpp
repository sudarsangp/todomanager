//@author A0002927L

#include "ParserDelete.h"

const string ParserDelete::regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";
const string ParserDelete::regexArgsDeleteSearchTerm = "\\s*(.+?)\\s*";
const string ParserDelete::regexArgsDeleteTaskID = "\\s*([0-9]+)\\s*";
const string ParserDelete::regexArgsDeleteDone = "\\s*done\\s*";

const string ParserDelete::regexInstructionDelete = "(del|delete|remove|erase|kill)";
const string ParserDelete::ERROR_FORMAT_BAD = "Delete format: delete <task index>, delete <task name>";

ParserDelete::ParserDelete(ParserBase* _nextParser) : ParserBase(_nextParser) {
}

CommandBase* ParserDelete::tryParse(string userCommand) {
	
	string instruction;
	string arguments;
	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}

	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseDelete(arguments);
}

bool ParserDelete::getInstructionAndArguments(const string& userCommand, 
										string& instruction, 
										string& arguments) {
	regex deleteFormat(regexInstructionAndArguments,
						regex_constants::icase);
	smatch matchResults;

	if (!regex_match(userCommand, matchResults, deleteFormat)) {
		return false;
	}
	
	assert(matchResults.size() > ARGS_POS);
	instruction = matchResults[INSTRUCTION_POS];
	arguments = matchResults[ARGS_POS];
	
	return true;
}

bool ParserDelete::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionDelete,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserDelete::parseDelete(const string& arguments) {
	smatch matches;

	if (regex_match(arguments, 
					regex(regexArgsDeleteDone, regex_constants::icase))) {
		return makeCmdDeleteDone();
	}else if (regex_match(arguments, 
						  matches, 
						  regex(regexArgsDeleteTaskID, regex_constants::icase))) {
		return makeCmdDeleteTaskID(matches);
	}else if (regex_match(arguments,
						  regex(regexArgsListed, regex_constants::icase))) {
		return makeCmdDeleteListed();
	}else if (regex_match(arguments, 
						  matches, 
						  regex(regexArgsDeleteSearchTerm, regex_constants::icase))) {
		return makeCmdDeleteSearchTerm(matches);
	}else {
		// There has not been any matching format
		throw(ParserException(ERROR_FORMAT_BAD));
	}
}

CommandBase* ParserDelete::makeCmdDeleteSearchTerm(smatch& matchingArgs) {

	return new CommandDelete(CommandDelete::DELETE_SEARCHTERM,
						matchingArgs[ARG_POS_DELETE_SEARCHTERM]);
}
CommandBase* ParserDelete::makeCmdDeleteTaskID(smatch& matchingArgs) {
	CommandBase* parsedCommand;

	try {
		parsedCommand = new CommandDelete(CommandDelete::DELETE_INDEX, 
			getTaskIDFromArgument(matchingArgs[ARG_POS_DELETE_TASKID]));
	}catch (range_error&) {
		throw (ParserException(ERROR_FORMAT_BAD));
	}

	return parsedCommand;
}

CommandBase* ParserDelete::makeCmdDeleteDone() {
	return new CommandDelete(CommandDelete::DELETE_DONE, true);
}

CommandBase* ParserDelete::makeCmdDeleteListed() {
	return new CommandDelete(CommandDelete::DELETE_LISTED, true);
}