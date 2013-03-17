#include "LogicBase.h"

// @author A0086671W
Data* LogicBase::_data = NULL;
Writer* LogicBase::_writer = NULL;
Display LogicBase::_display;

void LogicBase::updateFileContents( vector<Task>& tasks ) 
{
	_data->getAll(tasks);
	try {
		_writer->write(tasks);
	}catch (WriterException& e){
		throw(e);
	}
}

bool LogicBase::isOutOfBounds(int index, int size) {
	bool outOfBounds;

	if( index <= 0 ) {
		outOfBounds = true;
	} else if( index > size ) {
		outOfBounds = true;
	} else if( index == 0 ) {
		outOfBounds = true;
	} else {
		outOfBounds = false;
	}

	return outOfBounds;
}

bool LogicBase::isMultipleMatches(int size) {
	
	bool multipleMatches;
	
	if( size == 1 ) {
		multipleMatches = false;
	} else if( size > 1 ) {
		multipleMatches = true;
	} else {
		multipleMatches = false;
	}

	return multipleMatches;
}

Display LogicBase::getDisplay() {
	return _display;
}

//LogicBase::LogicBase() {}

void LogicBase::initialize(Data* data, Writer* writer) {
	_data = data;
	_writer = writer;
}

boost::posix_time::ptime LogicBase::getCurrentDateTime()
{
	return second_clock::local_time();
}

bool LogicBase::isDatePast( ptime datetime )
{
	bool isPast;
	ptime currentDateTime = getCurrentDateTime();

	if( datetime < currentDateTime ) {
		isPast = true;
	} else {
		isPast = false;
	}

	return isPast;
}

// returns true if clash
// returns false if no clash
bool LogicBase::isDateClash( ptime startTime, ptime endTime, int taskID )
{

	bool isClash;
	string taskName;
	Data::DataFeedback dataFeedback;
	vector<Task> tasks;

	dataFeedback = _data->getAll(tasks);

	isClash = false;
	if( startTime == not_a_date_time || endTime == not_a_date_time ) {
		return isClash;
	}

	for ( unsigned int i=0; i<tasks.size(); i++ ) {
		if( tasks[i].getTaskID() != taskID ) {
			if ( tasks[i].getTaskType() == Task::TIMED ) {
				if( endTime>tasks[i].getStartDateTime() && startTime<tasks[i].getEndDateTime() ) {
					// |---------|
					//    |---|
					isClash = true;
					break;
				} else if ( endTime>tasks[i].getStartDateTime() && startTime<tasks[i].getStartDateTime() ) {
					//    |---------|
					// |---|
					isClash = true;
					break;
				} else if( endTime>tasks[i].getEndDateTime() && startTime<tasks[i].getEndDateTime() ) {
					// |---------|
					//          |---|
					isClash = true;
					break;
				}
			}
		}
	}

	return isClash;
}

bool LogicBase::isDateCorrectFormat(ptime startTime, ptime endTime) {
	bool correct;
	
	// second condition is for deadline tasks without start time
	if( (startTime <= endTime) || startTime.is_not_a_date_time()) {
		correct = true;
	} else {
		correct = false;
	}

	return correct;
}

bool LogicBase::isTimeCorrectFormat( time_duration start, time_duration end )
{
	bool correct;

	// second condition is for deadline tasks without start time
	if( (start < end) || start.is_not_a_date_time() ) {
		correct = true;
	} else {
		correct = false;
	}

	return correct;
}

void LogicBase::logDataErrors( string errorString )
{
	fstream log;
	log.open(DATA_LOG_FILE_NAME, fstream::in | fstream::app);

	log << errorString << second_clock::local_time() << endl;

	log.close();
}

const string LogicBase::RESET_STATUS = "";
const string LogicBase::ERROR_LOG_CONCAT = "|";
const string LogicBase::ERROR_DATE_PAST_MESSAGE = "The entered date or time is past. Please enter a current date or time.";
const string LogicBase::ERROR_DATE_START_END_MESSAGE = "Please ensure start time is before end time.";
const string LogicBase::ERROR_NO_COMPLETED_TASKS_MESSAGE = "No completed tasks found.";
const string LogicBase::ERROR_NO_MATCHES_FOUND_MESSAGE = "No matches containing: ";
const string LogicBase::MULTIPLE_MATCHES_FOUND = "Found multiple matches containing: ";
const string LogicBase::PROMPT_ENTER_INDEX = ". Please enter an index.";
const string LogicBase::DISPLAY_EMPTY = "No tasks on display. Try listing. e.g. list.";
const string LogicBase::ERROR_NOT_FOUND_MESSAGE = "Task cannot be found.";
const string LogicBase::ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE = "Invalid task index.";
const string LogicBase::FILE_EMPTY = "No tasks exists.";
const string LogicBase::DATA_LOG_FILE_NAME = "datalog.txt";