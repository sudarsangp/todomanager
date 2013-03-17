//@author A0086671W

#ifndef TASK_H
#define TASK_H

#include <string>
#include <boost\date_time.hpp>

using namespace std;
using namespace boost::posix_time;

class Task {
public:
	enum TaskType {
		FLOATING,
		DEADLINE,
		TIMED
	};

	Task();
	Task(string taskName, int taskId, TaskType taskType, bool done, int priority, 
										ptime startDateTime, ptime endDateTime );

	void setTaskName(string taskName);
	string getTaskName();
	bool getDone();
	void setDone(bool done);
	ptime getStartDateTime();
	ptime getEndDateTime();
	void setStartTime(time_duration startTime);
	void setEndTime(time_duration endTime);
	void setStartDateTime(ptime startDateTime);
	void setEndDateTime(ptime endDateTime);
	void setTaskType(TaskType taskType);
	TaskType getTaskType();
	void setDeleteIndex(int index);
	int getDeleteIndex();
	void setPriority(int priority);
	int getPriority();
	void setTaskID( int taskID );
	int getTaskID();
private:
	string taskName_;
	TaskType taskType_;
	bool done_;
	int priority_;
	ptime startDateTime_;
	ptime endDateTime_;
	int deleteIndex_;
	int taskID_;
};
#endif