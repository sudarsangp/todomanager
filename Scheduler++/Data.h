//@author A0092076A

#ifndef DATA_H
#define DATA_H

// this is a container class
// populates tasks to internal vector

#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include <boost\date_time.hpp>
#include "Task.h"

using namespace std;
using namespace boost::posix_time;

class Data {
private:
	
	vector<Task> _list;
	int _currentTaskID;
	
	int highestTaskID( vector<Task> tasks ) ;

public:

	enum DataFeedback {
		SUCCESS,
		FAILURE,
		NOT_FOUND,
		EMPTY
	};

	Data();
	~Data();

	DataFeedback executeAdd( Task task );

	DataFeedback executeDeleteTaskID( int taskID );

	DataFeedback executeClear();

	DataFeedback getAll( vector<Task>& tasks );
	DataFeedback getByTime( vector<Task>& tasks, ptime dateTime );
	DataFeedback getBySearchTerm( vector<Task>& tasks, string searchTerm );
	DataFeedback getByName( vector<Task>& tasks, string taskName );
	DataFeedback getByID( vector<Task>& tasks, int taskId );
	DataFeedback getByDone( vector<Task>& tasks );
	DataFeedback getByUndone( vector<Task>& tasks );
	DataFeedback getByPriority( vector<Task>& tasks, int flag );
	DataFeedback getByOverdue( vector<Task>& tasks );
	// Populates the tasks vector with tasks with end date lying within
	// the time period stated
	DataFeedback getByTimePeriod(vector<Task>& tasks, ptime startTime, ptime endTime);

	DataFeedback executeEdit( Task taskToEdit );
	
	DataFeedback executeLoad( vector<Task> list );

	int getCurrentTaskID();

	int getCapacity();
};

#endif