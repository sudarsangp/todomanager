//@author A0081136M

#include "Item.h"

Item::Item(Int32 _taskID, Int32 _index, Boolean _done, String^ _taskName, Int32 _priority, String^ _dateFrom, String^ _dateTo)
{
	taskID = _taskID;
	index = _index;
	done = _done;
	taskName = _taskName;
	priority = _priority;
	dateFrom = _dateFrom;
	dateTo = _dateTo;
}

Int32 Item::getTaskID()
{
	return taskID;
}