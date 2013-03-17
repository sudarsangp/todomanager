#include "LogicTutorial.h"

// @author A0086671W
LogicTutorial* LogicTutorial::_oneLogicTutorial = NULL;

LogicTutorial* LogicTutorial::getInstance() {
	if( _oneLogicTutorial == NULL ) {
		_oneLogicTutorial = new LogicTutorial();
	}

	return _oneLogicTutorial;
}

Display LogicTutorial::startTutorial()
{
	tutorialState = INIT_STATE;

	_commandBase = NULL;
	_commandAddSpecific = NULL;
	_commandDelSpecific = NULL;
	_commandDoneSpecific = NULL;
	_commandListSpecific = NULL;
	_commandUndoSpecific = NULL;

	vector<Task> view;

	// show welcome message
	_display = LogicBase::getDisplay();
	view = _display.getTaskList();
	_display = Display(WELCOME_MSG, view);
	tutorialState = LIST_STATE;
	return _display;
}

Display LogicTutorial::executeTutorial( string text )
{
	Task _task;
	vector<Task> view;
	string errorFeedback;

	if( (int)text.length() > MAX_STRING_SIZE ) {
		vector<Task> view;
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
		errorFeedback = e.getParsingError();

		vector<Task> view;
		view = _display.getTaskList();
		_display = Display(errorFeedback, view );
		return _display;
	}
	catch (...) {
		vector<Task> view;
		view = _display.getTaskList();
		_display = Display(ERROR_UNABLE_TO_PROCESS, view );
		return _display;
	}

	// determine whether user entered appropriate command
	if( _commandBase != NULL ) {
		_commandAddSpecific = dynamic_cast<CommandAdd*>(_commandBase);
		_commandDelSpecific = dynamic_cast<CommandDelete*>(_commandBase);
		_commandDoneSpecific = dynamic_cast<CommandDone*>(_commandBase);
		_commandListSpecific = dynamic_cast<CommandList*>(_commandBase);
		_commandUndoSpecific = dynamic_cast<CommandUndo*>(_commandBase);
	}

	// update state based on whether command is succeeded
	if( _commandListSpecific != NULL && tutorialState == LIST_STATE ) {
		if( _commandListSpecific->getListType() == CommandList::LIST_ALL ) {
			_commandListSpecific->execute();
			updateDisplay(SUCCESS_TUTORIAL_LIST_MSG);
			tutorialState = ADD_STATE;
		} else {
			updateDisplay(errorFeedback);
		}
	} else if( _commandAddSpecific != NULL && tutorialState == ADD_STATE ) {
		if( _commandAddSpecific->getAddType() == CommandAdd::ADD_FLOATING_TASK ) {
			_commandAddSpecific->execute();
			updateDisplay(SUCCESS_TUTORIAL_ADD_MSG);
			tutorialState = ADD_TIME_STATE;
		} else {
			updateDisplay(errorFeedback);
		}
	} else if( _commandAddSpecific != NULL && tutorialState == ADD_TIME_STATE ) {
		if( _commandAddSpecific->getAddType() == CommandAdd::ADD_DEADLINE_TASK || _commandAddSpecific->getAddType() == CommandAdd::ADD_TIMED_TASK ) {
			_commandAddSpecific->execute();
			updateDisplay(SUCCESS_TUTORIAL_ADD_TIME_MSG);
			tutorialState = DONE_STATE;
		} else {
			updateDisplay(ERROR_TUTORIAL_ADD_TIMED_MSG);
		}
	} else if( _commandDoneSpecific != NULL && tutorialState == DONE_STATE ) {
		int size;
		vector<Task> display;
		display = _display.getTaskList();
		size = display.size();

		if( _commandDoneSpecific->getDoneIndex() > size || _commandDoneSpecific->getDoneIndex() <= 0 ) {
			updateDisplay(ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE);
		} else {
			if( _commandDoneSpecific->getDoneType() == CommandDone::DONE_INDEX ) {
				_commandDoneSpecific->execute();
				updateDisplay(SUCCESS_TUTORIAL_DONE_MSG);
				tutorialState = DELETE_DONE_STATE;
			} else {
				updateDisplay(errorFeedback);
			}
		}
	} else if( _commandDelSpecific != NULL && tutorialState == DELETE_DONE_STATE ) {
		_commandDelSpecific->execute();
		// ensure user types "delete done" command
		if( _commandDelSpecific->getDeleteType() == CommandDelete::DELETE_DONE ) {
			updateDisplay(SUCCESS_TUTORIAL_DELETE_DONE_MSG);
			tutorialState = DELETE_INDEX_STATE;
		} else {
			updateDisplay(errorFeedback);
		}

		// ensure list is not empty, otherwise will be stuck in this state
		vector<Task> display;
		display = _display.getTaskList();
		if( display.empty() ) {
			addExtraTasks();
			updateDisplay(ADDED_NEW_TASKS_MSG);
		}
	} else if( _commandDelSpecific != NULL && tutorialState == DELETE_INDEX_STATE ) {
		int size;
		vector<Task> display;
		display = _display.getTaskList();
		size = display.size();

		if( _commandDelSpecific->getDeleteIndex() > size || _commandDelSpecific->getDeleteIndex() <= 0 ) {
			updateDisplay(ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE);
		} else {
			if( _commandDelSpecific->getDeleteType() == CommandDelete::DELETE_INDEX ) {
				_commandDelSpecific->execute();
				updateDisplay(SUCCESS_TUTORIAL_DELETE_MSG);
				tutorialState = UNDO_STATE;
			} else {
				updateDisplay(errorFeedback);
			}
		}
	} else if( _commandUndoSpecific != NULL && tutorialState == UNDO_STATE ) {
		if( _commandUndoSpecific->getUndoType() == CommandUndo::UNDO_ACTION ) {
			_commandUndoSpecific->execute();
			updateDisplay(END_TUTORIAL_MSG);
			tutorialState = END_STATE;
		} else {
			updateDisplay(errorFeedback);
		}
	} else if( tutorialState == END_STATE ) {
		updateDisplay(COMPLETED_TUTORIAL_MSG);
	} else {
		_display = LogicBase::getDisplay();
		view = _display.getTaskList();
		string helpStatus;
		helpStatus = showHelpStatus(tutorialState);
		_display = Display(helpStatus, view);
	}

	delete _commandBase;

	return _display;
}

void LogicTutorial::updateDisplay( string message )
{
	vector<Task> view;

	_display = LogicBase::getDisplay();
	view = _display.getTaskList();
	_display = Display(message, view);
}

LogicTutorial::LogicTutorial()
{
	Task _task;
	_parser = new Parser();
	_data = new Data();
	_writer = new Writer(FILE_NAME);
	LogicBase::initialize(_data, _writer);
	initTutorial();

	vector<Task> tasks;
	_data->getAll(tasks);
	if( tasks.empty() ) {
		addSampleTasks();
	}
}

void LogicTutorial::initTutorial() {
	vector<Task> initVector;

	try {
		_writer->read(initVector);
		_data->executeLoad(initVector);
	}catch(WriterException& e) {
		_display = Display(e.getMessage(), vector<Task>());
		initVector.clear();
		_data->executeLoad(initVector);
		_writer->write(initVector);
		LogicUndo::getInstance().undoStackPush(*_data);
		throw (SchedulerPPException(e.getMessage() + "Reloaded file with no tasks."));
	}
}

LogicTutorial::~LogicTutorial() {
	delete _parser;
	delete _data;
	delete _writer;
}

string LogicTutorial::showHelpStatus( States currentState )
{
	stringstream helpStatus;

	switch (currentState) {
	case LIST_STATE: // list
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " e.g. list";
		break;
	case ADD_STATE: // add
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " e.g. add John's birthday";
		break;
	case ADD_TIME_STATE:
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " e.g. add walk the dog from 6pm to 615pm";
		break;
	case DONE_STATE: // done
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " You may try entering the index of the task. It is reflected under the index column.";
		helpStatus << " e.g. done 3 OR e.g. done errands";
		break;
	case DELETE_DONE_STATE:
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " DELETE DONE clears all your completed tasks so they don't clutter up the display.";
		helpStatus << " e.g. delete done";
		break;
	case DELETE_INDEX_STATE: // delete
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " You may try entering the index of the task. It is reflected under the index column.";
		helpStatus << " e.g. delete 3 OR e.g. delete todo";
		break;
	case UNDO_STATE: // undo
		helpStatus << ERROR_INVALID_COMMAND_MESSAGE;
		helpStatus << ERROR_TRY_AGAIN_MESSAGE;
		helpStatus << " e.g. undo";
		break;
	default:
		break;
	}

	return helpStatus.str();
}

void LogicTutorial::addSampleTasks()
{
	Task _task;
	ptime today;
	ptime deadline;
	ptime start;
	ptime end;
	today = second_clock::local_time();
	// add a floating task
	_task = Task("Tidy Room", 0, Task::FLOATING, false, 0, not_a_date_time, not_a_date_time);
	_data->executeAdd(_task);

	// add a deadline task
	days d3(3);
	deadline = ptime(today.date(), time_duration(21, 0, 0)); // deadline task @ 9pm
	deadline += days(3);
	_task = Task("Report Submission", 0, Task::DEADLINE, false, 0, not_a_date_time, deadline);
	_data->executeAdd(_task);

	// add a timing task
	start = ptime(today.date(), time_duration(18, 0, 0)); // start time @ 6pm
	start += days(4);
	end = ptime(today.date(), time_duration(20, 0, 0)); // end time @ 8pm
	end += days(4);
	_task = Task("Dinner with Client", 0, Task::DEADLINE, false, 1, start, end);
	_data->executeAdd(_task);
}

// this call adds more tasks to prevent being stuck in the delete done state
// the stuck case can happen when the user deletes all done tasks and then
// is unable to delete the task by index in the delete index state
void LogicTutorial::addExtraTasks()
{
	Task _task;
	ptime today;
	ptime deadline;
	ptime start;
	ptime end;
	today = second_clock::local_time();

	// add a deadline task
	deadline = ptime(today.date(), time_duration(19, 0, 0)); // deadline task @ 7pm
	deadline += days(1);
	_task = Task("Download Scheduler++", 0, Task::DEADLINE, false, 0, not_a_date_time, end);
	_data->executeAdd(_task);

	// add a timing task
	start = ptime(today.date(), time_duration(5, 0, 0)); // start time @ 5am
	start += days(2);
	end = ptime(today.date(), time_duration(6, 0, 0)); // end time @ 6am
	end += days(2);
	_task = Task("Catch sunrise", 0, Task::DEADLINE, false, 1, start, end);
	_data->executeAdd(_task);
}

// order of execution :
// LIST -> ADD -> ADD TIMED TASK -> MARK DONE -> DELETE COMPLETED TASKS -> DELETE TASK BY INDEX -> UNDO -> END TUTORIAL
const string LogicTutorial::WELCOME_MSG = "Welcome to Scheduler++. You may ADD, DELETE, LIST, FLAG and mark tasks DONE. We will guide you through this. You may read the status messages here. Now, enter LIST to see sample tasks.";
const string LogicTutorial::SUCCESS_TUTORIAL_LIST_MSG = "You have entered a successful command. The above are your listed tasks. You may proceed to ADD a new task. Follow the syntax of ADDING a task. e.g. : add vacation";
const string LogicTutorial::SUCCESS_TUTORIAL_ADD_MSG = "You have just completed ADDING a task! Proceed to add a task with a date or time. You can do so with the following syntax. e.g. : add purchase air tickets by 24 Dec";
const string LogicTutorial::SUCCESS_TUTORIAL_ADD_TIME_MSG = "You have added a task with a time! Proceed to mark your task DONE. You can do so with the following syntax. e.g. : done 4";
const string LogicTutorial::SUCCESS_TUTORIAL_DONE_MSG = "You have marked your task DONE! The tick beside is an indication of DONE tasks. You may FLAG tasks using the same syntax. Now, proceed to DELETE tasks marked DONE. e.g. : delete done";
const string LogicTutorial::SUCCESS_TUTORIAL_DELETE_DONE_MSG = "You have cleared your completed agenda! You may also delete tasks normally. To do this, use the same DELETE keyword followed by an INDEX. e.g. : delete 1";
const string LogicTutorial::SUCCESS_TUTORIAL_DELETE_MSG = "The task has been DELETED! To recover the task, you may UNDO the action with the following syntax. e.g. : undo";
const string LogicTutorial::END_TUTORIAL_MSG = "Congratulations! You have completed the tutorial successfully! Enjoy using Scheduler++!";
const string LogicTutorial::COMPLETED_TUTORIAL_MSG = "You have successfully completed the tutorial.";

const string LogicTutorial::ADDED_NEW_TASKS_MSG = "Wow! You have cleared all your tasks! Let's add some tasks for you to try out the other commands.";
const string LogicTutorial::ERROR_TUTORIAL_ADD_TIMED_MSG = "Try adding a task with a date or time attribute? e.g. add health checkup by 23 Dec";

const int LogicTutorial::MAX_STRING_SIZE = 100;

const string LogicTutorial::FILE_NAME = "schedulerPP.txt";
const string LogicTutorial::ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE = "Please enter an appropriate task index.";
const string LogicTutorial::EMPTY_STATUS = "";
const string LogicTutorial::ERROR_INVALID_COMMAND_MESSAGE = "That was an invalid command";
const string LogicTutorial::ERROR_TRY_AGAIN_MESSAGE = " Try entering the command again.";
const string LogicTutorial::ERROR_STRING_LENGTH_EXCEEDED = "Maximum characters allowed is 100";
const string LogicTutorial::ERROR_UNABLE_TO_PROCESS = "We are unable to process your command. Please try again.";