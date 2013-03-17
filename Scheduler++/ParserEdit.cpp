//@author A0002927L

#include "ParserEdit.h"

const string ParserEdit::
	regexInstructionAndArguments = "\\s*([a-zA-Z]+)\\s*(.*)";

const string ParserEdit::
	regexArgsEditEnd = "\\s*([0-9]+)\\s+end\\s+(\\S.*?)\\s*";
const string ParserEdit::
	regexArgsEditStart = "\\s*([0-9]+)\\s+start\\s+(\\S.*?)\\s*";
const string ParserEdit::
	regexArgsEditRename = "\\s*([0-9]+)\\s+rename\\s+(\\S.*?)\\s*";

const string ParserEdit::regexInstructionEdit = "(edit|change|modify|update)";

const string ParserEdit::ERROR_FORMAT_BAD = "Edit format: edit 2 rename New Name, edit 2 end 2300";
const string ParserEdit::ERROR_BAD_TASK_INDEX = "Task index should be 1 or greater";
const string ParserEdit::ERROR_FORMAT_BAD_START_DATE = "Please enter a valid start date/time.";
const string ParserEdit::ERROR_FORMAT_BAD_END_DATE = "Please enter a valid start date/time.";

ParserEdit::ParserEdit(ParserBase* _nextParser) : ParserBase(_nextParser) {}

CommandBase* ParserEdit::tryParse(string userCommand){
	
	string instruction;
	string arguments;
	
	if (!getInstructionAndArguments(userCommand, instruction, arguments)) {
		return NULL;
	}

	if (!checkInstruction(instruction)) {
		return NULL;
	}

	return parseEdit(arguments);
}

bool ParserEdit::getInstructionAndArguments(const string& userCommand, 
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

// Checks if the instruction is "edit"
bool ParserEdit::checkInstruction(const string& instruction) {
	if (regex_match(instruction, regex(regexInstructionEdit,
									   tr1::regex_constants::icase))) {
		return true;
	}

	return false;
}

CommandBase* ParserEdit::parseEdit(const string& arguments) {	
	smatch matchResults;

	EditSubType editSubType = categorizeEditCommand(arguments, matchResults);

	switch (editSubType) {
	case EDIT_END:
		return makeCmdEditEnd(matchResults);
		break;
	case EDIT_START:
		return makeCmdEditStart(matchResults);
		break;
	case EDIT_NAME:
		return makeCmdEditRename(matchResults);
		break;
	case INVALID_SUBTYPE:
		return makeCmdEditErrorSyntax(matchResults);
		break;
	default:
		assert(false && "Unexpected invalid edit subtype!");
		break;
	}

	return NULL;
}

ParserEdit::EditSubType ParserEdit::categorizeEditCommand(const string& arguments, 
												 smatch& matchingResults) {
	EditSubType returnedSubType;

	if (regex_match(arguments, 
					matchingResults, 
					regex(regexArgsEditEnd, regex::icase))) {

		returnedSubType = EDIT_END;

	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsEditStart, regex::icase))) {

		returnedSubType = EDIT_START;

	}else if (regex_match(arguments, 
						  matchingResults, 
						  regex(regexArgsEditRename, regex::icase))) {

		returnedSubType = EDIT_NAME;

	}else {
		returnedSubType = INVALID_SUBTYPE;
	}
		
	return returnedSubType;
}

CommandBase* ParserEdit::makeCmdEditErrorSyntax(smatch& matchingArgs) {
	throw (ParserException(ERROR_FORMAT_BAD));
}

CommandBase* ParserEdit::makeCmdEditStart(smatch& matchingArgs) {

	int editTaskID;
	try {
		editTaskID = 
			getTaskIDFromArgument(matchingArgs[ARG_POS_EDIT_TASKID]);
	}catch (range_error&) {
		throw(ParserException(ERROR_BAD_TASK_INDEX));
	}
	
	// Extract date and time.
	ptime parsedDateTime = 
		parseDateTime(matchingArgs[ARG_POS_EDIT_NEW_START], true);
	time_duration parsedTime = 
		parseTime(matchingArgs[ARG_POS_EDIT_NEW_START]);

	if (!parsedTime.is_not_a_date_time()) {	 // check if user only entered time

		return new CommandEdit(CommandEdit::EDIT_START_TIME, 
										editTaskID, 
										parsedTime);

	}else if (!parsedDateTime.is_not_a_date_time()) {// check if user entered date+time

		return new CommandEdit(CommandEdit::EDIT_START_DATETIME,
										editTaskID,
										parsedDateTime);

	}else {										
		throw (ParserException(ERROR_FORMAT_BAD_START_DATE));
	}	
}

CommandBase* ParserEdit::makeCmdEditEnd(smatch& matchingArgs) {
	int editTaskID; 
	try {
		editTaskID = 
			getTaskIDFromArgument(matchingArgs[ARG_POS_EDIT_TASKID]);
	}catch (range_error&) {
		throw(ParserException(ERROR_BAD_TASK_INDEX));
	}

	ptime parsedDateTime = 
		parseDateTime(matchingArgs[ARG_POS_EDIT_NEW_END]);
	time_duration parsedTime = 
		parseTime(matchingArgs[ARG_POS_EDIT_NEW_END]);

	if (!parsedTime.is_not_a_date_time()) {			// check if user only entered time
		return new CommandEdit(CommandEdit::EDIT_END_TIME, 
										editTaskID, 
										parsedTime);
	}else if (!parsedDateTime.is_not_a_date_time()) {// check if user entered date+time
		return new CommandEdit(CommandEdit::EDIT_END_DATETIME,
										editTaskID,
										parsedDateTime);
	}else {
		throw(ParserExceptionBadDate());
	}
}

CommandBase* ParserEdit::makeCmdEditRename(smatch& matchingArgs) {

	int editTaskID; 
	try {
		editTaskID = 
			getTaskIDFromArgument(matchingArgs[ARG_POS_EDIT_TASKID]);
	}catch (range_error&) {
		throw(ParserException(ERROR_BAD_TASK_INDEX));
	}
	string editTaskName; 
	editTaskName = matchingArgs[ARG_POS_EDIT_NEW_NAME];
	return new CommandEdit(CommandEdit::EDIT_RENAME, 
									editTaskID, 
									editTaskName);
}
