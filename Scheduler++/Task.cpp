//@author A0086671W

#include "Task.h"

Task::Task(string taskName, int taskId, TaskType taskType, bool done, int priority, 
										ptime startDateTime, ptime endDateTime ) {
	taskName_ = taskName;
	taskID_ = taskId;
	taskType_ = taskType;
	done_ = done;
	priority_ = priority;
	startDateTime_ = startDateTime;
	endDateTime_ = endDateTime;
}

Task::Task() {
	taskName_ = "-1";
	taskID_ = -1;
	taskType_ = FLOATING;
	done_ = false;
	priority_ = -1;
	startDateTime_ = not_a_date_time;
	endDateTime_ = not_a_date_time;
}

void Task::setTaskName(string taskName) {
	taskName_ = taskName;
}

string Task::getTaskName() {
	return taskName_;
}

bool Task::getDone() {
	return done_;
}

void Task::setDone(bool done) {
	done_ = done;
}

void Task::setStartTime(time_duration startTime) {
	startDateTime_ = ptime(startDateTime_.date(), startTime);
}

void Task::setEndTime(time_duration endTime) {
	endDateTime_ = ptime(endDateTime_.date(), endTime);
}

void Task::setStartDateTime(ptime startDateTime) {
	startDateTime_ = startDateTime;
}

void Task::setEndDateTime(ptime endDateTime) {
	endDateTime_ = endDateTime;
}

ptime Task::getStartDateTime() {
	return startDateTime_;
}

ptime Task::getEndDateTime() {
	return endDateTime_;
}

void Task::setTaskType(TaskType taskType) {
	taskType_ = taskType;
}

Task::TaskType Task::getTaskType() {
	return taskType_;
}

void Task::setDeleteIndex(int index) {
	deleteIndex_ = index;
}

int Task::getDeleteIndex() {
	return deleteIndex_;
}

void Task::setPriority(int priority) {
	priority_ = priority;
}

int Task::getPriority() {
	return priority_;
}

void Task::setTaskID( int taskID ) {
	taskID_ = taskID;
}

int Task::getTaskID() {
	return taskID_;
}