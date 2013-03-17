//@author A0081136M

#pragma once

using namespace System;
using namespace System::Drawing;

public ref class Item
{
private:
	Int32 index;
	Boolean done;
	String^ taskName;
	Int32 priority;
	String^ dateFrom;
	String^ dateTo;
	Int32 taskID;

public: 

	Item(Int32 _taskID, Int32 _index, Boolean _done, String^ _taskName, Int32 _priority, String^ _dateFrom, String^ _dateTo);

	Int32 getTaskID();

	property Int32 INDEX
	{
		Int32 get() { return index; }
		void set(Int32 value) { index = value; }
	}

	property Boolean DONE
	{
		Boolean get() {return done;}
		void set(Boolean value) { done = value; }
	}

	property String^ TASKNAME
	{
		String^ get() { return taskName; }
		void set(String^ value) { taskName = value; }
	}

	property Int32 PRIORITY
	{
		Int32 get() { return priority; }
		void set(Int32 value) { priority = value; }
	}

	property String^ DATEFROM
	{
		String^ get() { return dateFrom; }
		void set(String^ value) { dateFrom = value; }
	} 

	property String^ DATETO
	{
		String^ get() { return dateTo; }
		void set(String^ value) { dateTo = value; }
	} 

	property Int32 TASKID
	{
		Int32 get() { return taskID; }
		void set(Int32 value) { taskID = value; }
	}

};
