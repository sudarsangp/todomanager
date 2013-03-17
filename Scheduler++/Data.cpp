//@author A0092076A

#include "Data.h"

Data::Data() {

	_currentTaskID = 0;
	
}

Data::~Data() {

}

Data::DataFeedback Data::executeAdd( Task taskToAdd ) {
	
	_currentTaskID++;
	taskToAdd.setTaskID(_currentTaskID);
	
	_list.push_back(taskToAdd);
	return SUCCESS;
	
}

Data::DataFeedback Data::executeDeleteTaskID( int taskID ) {

	bool deleted = false;

	if( _list.empty() ) {

		return EMPTY;

	}

	for(unsigned int i = 0 ; i < _list.size() ; i++ ) {

		if( _list[i].getTaskID() == taskID ) {

			_list.erase(_list.begin()+i);
			deleted = true;

		}

	}

	if(  deleted == true ) {

		return SUCCESS;

	}
	else {
	
		return FAILURE;

	}

}

Data::DataFeedback Data::executeClear() {

	_list.clear();

	_currentTaskID = 0;

	if( _list.size() == 0 ) {
	
		return SUCCESS;

	}

	else {
		
		return FAILURE;

	}

}

Data::DataFeedback Data::executeEdit( Task taskToEdit ) {

	if( _list.empty() ) {

		return EMPTY;

	}

	else {

		for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {

			if( _list.at(i).getTaskID() == taskToEdit.getTaskID() ) {

				_list.at(i) = taskToEdit;

			}

		}

		return SUCCESS;

	}
	
}

Data::DataFeedback Data::getAll( vector<Task>& tasks ) {

	if( _list.empty() ) {

		return EMPTY;
	
	}

	else {

		for( unsigned int i = 0 ; i < _list.size() ; i++ ) {

			tasks.push_back( _list.at(i) );
		}
	
	return SUCCESS;

	}

}

Data::DataFeedback Data::getByName( vector<Task>& tasks, string taskName ) {

	if( _list.empty() ) {

		return EMPTY;
	
	}

	tasks.clear();

	for( int i = 0 ; i < (int)_list.size() ; i ++ ) {

		if( _list.at(i).getTaskName() == taskName ) {
			
			tasks.push_back( _list.at(i) );

		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}

}

Data::DataFeedback Data::getByID( vector<Task>& tasks, int taskId ) {

	if( _list.empty() ) {

		return EMPTY;
	
	}

	tasks.clear();

	for( int i = 0 ; i < (int)_list.size() ; i ++ ) {

		if( _list.at(i).getTaskID() == taskId ) {
			
			tasks.push_back( _list.at(i) );

		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}
		
}

Data::DataFeedback Data::getBySearchTerm ( vector<Task>& tasks, string searchTerm ) { 

	if( _list.empty() ) {

		return EMPTY;
	
	}

	tasks.clear();

	size_t found;

	for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {

		string taskName =_list.at(i).getTaskName();
		string searchString =searchTerm;
		
		transform( taskName.begin(),taskName.end(),taskName.begin(),(int(*)(int))tolower);
		transform( searchString.begin(),searchString.end(),searchString.begin(),(int(*)(int))tolower);
		
		found = taskName.find( searchString );

		if( found != string::npos ) {
		
			tasks.push_back(_list[i]);
		
		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}
	
}

Data::DataFeedback Data::getByTime (  vector<Task>& tasks, ptime dateTime ) {

	if( _list.empty() ) {

		return EMPTY;
	
	}

	tasks.clear();

	for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {

		if( _list[i].getStartDateTime() >= dateTime && _list[i].getEndDateTime() <= dateTime ) {

			tasks.push_back( _list[i] );
			
		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}

	return FAILURE;

}

Data::DataFeedback Data::getByTimePeriod(vector<Task>& tasks, ptime startTime, ptime endTime) {
	
	if( _list.empty() ) {
	
		return EMPTY;
	
	}

	tasks.clear();

	for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {
	
		if( _list[i].getEndDateTime() >= startTime && _list[i].getEndDateTime() <= endTime) {
		
			tasks.push_back( _list[i] );
		
		}
	
	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}
	
	

}

Data::DataFeedback Data::getByDone( vector<Task>& tasks ) {

	if( _list.empty() ) {
	
		return EMPTY;
	
	}

	tasks.clear();

	for( int i = 0 ; i < (int)_list.size() ; i ++ ) {

		if( _list.at(i).getDone() == true ) {
			
			tasks.push_back( _list.at(i) );

		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}
		
}

Data::DataFeedback Data::getByUndone( vector<Task>& tasks ) {

	if( _list.empty() ) {
	
		return EMPTY;
	
	}

	tasks.clear();

	for( int i = 0 ; i < (int)_list.size() ; i ++ ) {

		if( _list.at(i).getDone() == false ) {
			
			tasks.push_back( _list.at(i) );

		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}
		
}

Data::DataFeedback Data::getByPriority( vector<Task>& tasks, int flag ) {

	
	if( _list.empty() ) {

		return EMPTY;

	}

	tasks.clear();

	for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {

		if( _list.at(i).getPriority() == flag ) {
			
			tasks.push_back( _list.at(i) );

		}

	}

	if( tasks.empty() ) {
	
		return NOT_FOUND;
	
	}
	
	else {
	
		return SUCCESS;
	
	}

	return FAILURE;

}

Data::DataFeedback Data::getByOverdue( vector<Task>& tasks ) {

	if( _list.empty() ) {
	
		return EMPTY;
	
	}

	tasks.clear();

	ptime currentTime = second_clock::local_time();
	
	for( unsigned int i = 0 ; i < _list.size() ; i ++ ) {
		
		if( _list.at(i).getEndDateTime() < currentTime ) {

			tasks.push_back( _list.at(i) );

		}

	}

	
	if( tasks.empty() ) {
		return NOT_FOUND;
	} else {
		return SUCCESS;
	}

	return FAILURE;
}

Data::DataFeedback Data::executeLoad( vector<Task> list ) {

	_list.clear();

	if( list.empty() ) { 

		return SUCCESS;

	}
	
	else {

	for( int i = 0 ; i < (int)list.size() ; i ++ ) {

		_list.push_back( list.at(i) );
	
	}

	_currentTaskID = highestTaskID( list );

	return SUCCESS;
	
	}

}

int Data::getCurrentTaskID() {

	return _currentTaskID;

}

int Data::getCapacity() {

	return _list.size();

}

int Data::highestTaskID( vector<Task> tasks ) {

	int max = 0;

	for ( int i = 0 ; i < (int)tasks.size() ; i ++ ) {

		if( max < tasks.at(i).getTaskID() ) {

			max = tasks.at(i).getTaskID();

		}

	}

	return max;

}