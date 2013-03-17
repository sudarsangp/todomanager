#include "Logic.h"

// @author A0086671W
Logic* Logic::_oneLogic = NULL;

Logic* Logic::getInstance() {
	if( _oneLogic == NULL ) {
		_oneLogic = new Logic();
	}

	return _oneLogic;
}

Display Logic::executeTextCommand( string text ) {
	stringstream errorFeedback;
	vector<Task> view;
	logAllActions(text);

	if( (int)text.length() > MAX_STRING_SIZE ) {
		view = _display.getTaskList();
		_display = Display(ERROR_STRING_LENGTH_EXCEEDED, view );
		return _display;
	}

	try
	{
		_commandBase = _parser->parseUserCommand( text );
	}
	catch (ParserException& e)
	{
		errorFeedback << ERROR_INVALID_SYNTAX;
		errorFeedback << endl;
		errorFeedback << e.getParsingError();

		stringstream errorString;
		errorString << text << USER_LOG_CONCAT << errorFeedback << endl;
		logUserErrorActions(text);

		vector<Task> view;
		view = _display.getTaskList();
		_display = Display(errorFeedback.str(), view );
		return _display;
	}
	catch (...) {
		stringstream errorString;
		errorString << text << USER_LOG_CONCAT << ERROR_UNABLE_TO_PROCESS << endl;
		logUserErrorActions(text);

		vector<Task> view;
		view = _display.getTaskList();
		_display = Display(ERROR_UNABLE_TO_PROCESS, view );
		return _display;
	}

	if ( _commandBase == NULL ) {
		view = _display.getTaskList();
		_display = Display(ERROR_BLANK_COMMAND, view );
		return _display;
	} else {
		view = _display.getTaskList();
		_display = Display(RESET_STATUS, view );
		_commandBase->execute();
		_display = LogicBase::getDisplay();

		stringstream errorString;
		errorString << text << USER_LOG_CONCAT << _display.getStatus() << endl;
		logUserErrorActions(text);

		delete _commandBase;
	}

	return _display;
}

Display Logic::executeShortCutCommand( CommandBase* commandClass )
{
	if (commandClass != NULL) {
		commandClass->execute();
		_display = LogicBase::getDisplay();

		delete commandClass;
	} else {
		vector<Task> view;
		view = _display.getTaskList();
		_display = Display(ERROR_BLANK_COMMAND, view);
	}

	return _display;
}

// read and store in Data
void Logic::populateData() {
	vector<Task> initVector;

	try {
		_writer->read(initVector);
		_data->executeLoad(initVector);
	}catch (WriterException& e) {
		_display = Display(e.getMessage(), vector<Task>());
		initVector.clear();
		_data->executeLoad(initVector);
		_writer->write(initVector);
		LogicUndo::getInstance().undoStackPush(*_data);
		throw (SchedulerPPException(e.getMessage() + "Reloaded file with no tasks."));
	}
}

// sets up the program before user begins using it
// populates the internal vector with tasks from files
Logic::Logic() {
	setupParser();
	setupData();
	setupWriter();
	populateData();
	LogicBase::initialize(_data, _writer);
	LogicUndo::getInstance();
}

Logic::~Logic() {
	logUserErrorActions(USER_LOG_SEPARATOR);
	delete _parser;
	delete _data;
	delete _writer;
}

void Logic::setupParser() {
	_parser = new Parser();
}

void Logic::setupData() {
	_data = new Data();
}

void Logic::setupWriter() {
	_writer = new Writer(MAIN_FILE_NAME);
}

void Logic::logUserErrorActions( string errorString )
{
	fstream log;
	log.open(USER_LOG_FILE_NAME, fstream::in | fstream::app);

	log << errorString << USER_LOG_CONCAT << second_clock::local_time() << endl;

	log.close();
}

void Logic::logAllActions( string text )
{
	fstream log;
	log.open(USER_LOG_FILE_NAME, fstream::in | fstream::app);

	log << USER_LOG_ALL << text << USER_LOG_CONCAT << second_clock::local_time() << endl;

	log.close();
}

const int Logic::MAX_STRING_SIZE = 100;

const string Logic::ERROR_STRING_LENGTH_EXCEEDED = "Maximum characters allowed is 100.";

const string Logic::ERROR_INVALID_SYNTAX = "That was an invalid syntax. Please try again with the following syntax.";
const string Logic::ERROR_UNABLE_TO_PROCESS = "We are unable to process your command. Please try again.";
const string Logic::USER_LOG_FILE_NAME = "userlog.txt";
const string Logic::USER_LOG_CONCAT = "|";
const string Logic::USER_LOG_SEPARATOR = ">>>>>>>>> Time Program Closed >>>>>>>>> ";
const string Logic::USER_LOG_ALL = ">>> Logging all user actions >>> ";
const string Logic::ERROR_BLANK_COMMAND = "Aw...That was an invalid command. Please try again.";
const string Logic::RESET_STATUS = "";

const string Logic::MAIN_FILE_NAME = "schedulerPP.txt";