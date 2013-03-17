//@author A0081136M

#include "Writer.h"

const string Writer::EMPTY_STRING = "";

const string Writer::STRING_TRUE = "true";
const string Writer::STRING_FALSE = "false";

const string Writer::NOT_A_DATE_TIME = "not-a-date-time";

const string Writer::FILE_CORRUPT = "FILE_CORRUPT";



Writer::Writer()
{}


Writer::Writer(string _filename)
{
	filename = _filename;

	fstream fileStr;
	fileStr.open(filename, fstream::in);
	fileStr << EMPTY_STRING;
	fileStr.close();

	errorMessage = false;
}

//Write to file
bool Writer::write(vector<Task> taskList)
{
	try
	{
		//assertion
		assert(filename != EMPTY_STRING);
		ofstream file;
		file.open (filename, fstream::trunc);
	
		//Writes individual task attributes to file
		for(unsigned int i=0; i<taskList.size(); i++)
		{
			file << convertIntToStr(taskList[i].getTaskID()) << endl;
			file << taskList[i].getTaskName() << endl;
			file << boolalpha << taskList[i].getDone() << endl;
			file << convertIntToStr(taskList[i].getTaskType()) << endl;
			file << convertIntToStr(taskList[i].getPriority()) << endl;
			file << to_simple_string(taskList[i].getStartDateTime()) << endl;
			file << to_simple_string(taskList[i].getEndDateTime()) << endl;
		}

		file.close();
		return true;
	}
	catch(...)
	{
		return false;
	}
}

//Convert integer to string
string Writer::convertIntToStr(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

//Convert string to integer
int Writer::convertStrToNum(string number)
{
	stringstream ss(number);//create a stringstream
	int taskID = -1;
	ss >> taskID; //add number to the stream
	ss >> ws;
	// invalid input
	if (taskID < 0 || !ss.eof() || ss.fail()) {
		throw(range_error(FILE_CORRUPT));
	}
	return taskID;//return a string with the contents of the stream
}

//Read from file
bool Writer::read(vector<Task>& taskList)
{

	ifstream file (filename);
	if (file.is_open())
	{
		if(parseData(file, taskList))
		{
			file.close();
			return true;
		}
		else 
			return false;
	}
	else
		return false;
}

//Parse file contents

bool Writer::parseData(ifstream& file, vector<Task>& taskList)
{
	string line;

	//Get individual task attributes
	while (file.good())
	{
		Task task;
		errorMessage = false;
		getline(file,line);

		if(line == EMPTY_STRING)
			break;
		
		try {
			
			task.setTaskID(convertStrToNum(line.c_str()));

			getline(file, line);
			task.setTaskName(line);

			getline(file, line);
			task.setDone(convertToBool(line));

			getline(file, line);
			task.setTaskType(convertToTaskType(line));

			getline(file, line);
			task.setPriority(convertStrToNum(line.c_str()));

			getline(file, line);
			setStartDateTime(task, line);

			getline(file, line);
			setEndDateTime(task, line);

			taskList.push_back(task);
		}catch (range_error){
			throw (WriterException(FILE_CORRUPT));
		}catch (ios_base::failure) {
			throw (WriterException(FILE_CORRUPT));
		}

		if (file.fail()) {
			throw(WriterException(FILE_CORRUPT));
		}
		
	}

	if(errorMessage)
	{
		throw WriterException(FILE_CORRUPT);
	}
	else {
		return true;
	}
}

//Convert string to bool
bool Writer::convertToBool(string line)
{
	if(line == STRING_TRUE)
		return true;
	else if(line == STRING_FALSE)
		return false;
	else
		throw(WriterException(FILE_CORRUPT));
}

//convert string to TaskType
Task::TaskType Writer::convertToTaskType(string line)
{
	if(line == convertIntToStr(Task::FLOATING))
		return Task::FLOATING;
	else if(line == convertIntToStr(Task::DEADLINE))
		return Task::DEADLINE;
	else  if(line == convertIntToStr(Task::TIMED))
		return Task::TIMED;
	else
		throw(WriterException(FILE_CORRUPT));
}

//Set the StartDateTime
void Writer::setStartDateTime(Task& task, string line)
{
	if(line != NOT_A_DATE_TIME)
	{
		try
		{
			task.setStartDateTime(time_from_string(line));
		}
		catch(...)
		{
			errorMessage = true;
		}
	}
}

//St the EndDateTime
void Writer::setEndDateTime(Task& task, string line)
{
	if(line != NOT_A_DATE_TIME)
	{
		try
		{
			task.setEndDateTime(time_from_string(line));
		}
		catch(...)
		{
			errorMessage = true;
		}
	}
}