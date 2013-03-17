//@author A0081136M

#ifndef WRITER_H
#define WRITER_H

#define BUFFER_SIZE 33

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <boost\date_time.hpp>
#include <iostream>
#include <typeinfo> 
#include <stdexcept>

#include "Task.h"
#include "Writer.h"
#include "WriterException.h"

using namespace std;
using namespace boost::posix_time;

class Writer {
private:
	string filename;
	char buffer [BUFFER_SIZE];
	bool errorMessage;

	bool parseData(ifstream& file, vector<Task>& taskList);
	bool convertToBool(string line);
	Task::TaskType convertToTaskType(string line);
	string convertIntToStr(int number);
	int convertStrToNum(string str);
	void setStartDateTime(Task& task, string line);
	void setEndDateTime(Task& task, string line);

	static const string EMPTY_STRING;
	
	static const string STRING_TRUE;
	static const string STRING_FALSE;

	static const string NOT_A_DATE_TIME;

	static const string FILE_CORRUPT;

public:
	Writer(string _filename);

	Writer();

	bool write(vector<Task> taskList);
	bool read(vector<Task>& taskList);

};

#endif