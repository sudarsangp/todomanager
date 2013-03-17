//@author A0086671W

#ifndef LOGIC_TESTER_H
#define LOGIC_TESTER_H

#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include <string>
#include <sstream>
#include "UI.h"

using namespace std;

// @author A0086671W
class LogicTester : public testing::Test {
public:
	// Objects declared here can be used by all tests in the test case for Foo.
	UI _ui;

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		_ui.readUserInput("add task one");
		_ui.readUserInput("add task two 20 Nov 2012");
		_ui.readUserInput("add task three from 21 nov, 12 to 21 nov, 16");
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).

		// clear all tasks to work with original setup above
		_ui.readUserInput("clear YES");
	}
};

const string TASK_ONE = "1. task one done: 0, start:not-a-date-time end: not-a-date-time";
const string TASK_ONE_EDITED_END = "1. task one done: 0, start:not-a-date-time end: 2012-Dec-01 13:00:00";
const string TASK_ONE_RENAME = "1. NEWTASKNAME done: 0, start:not-a-date-time end: not-a-date-time";
const string TASK_ONE_DONE = "task one done: 1, start:not-a-date-time end: not-a-date-time";
const string TASK_TWO = "2. task two done: 0, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_TWO_DONE = "2. task two done: 1, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_TWO_EDITED_END_TIME = "2. task two done: 0, start:not-a-date-time end: 2012-Nov-20 20:00:00";
const string TASK_TWO_EDITED_END_DATE = "2. task two done: 0, start:not-a-date-time end: 2012-Nov-30 13:00:00";
const string TASK_TWO_EDITED_START_DATE = "2. task two done: 0, start:2012-Nov-17 13:00:00 end: 2012-Nov-20 23:59:00";
const string TASK_TWO_LIST_DATE = "1. task two done: 0, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_TWO_LIST_MONTH = "1. task two done: 0, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_TWO_SORT_A = "3. task two done: 0, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_TWO_SORT_D = "1. task two done: 1, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_THREE = "3. task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 16:00:00";
const string TASK_THREE_SORT_A = "2. task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 16:00:00";
const string TASK_THREE_EDIT_START_TIME = "3. task three done: 0, start:2012-Nov-21 01:00:00 end: 2012-Nov-21 16:00:00";
const string TASK_THREE_EDIT_START_DATE = "3. task three done: 0, start:2012-Nov-19 00:00:00 end: 2012-Nov-21 16:00:00";
const string TASK_THREE_EDIT_END_DATE = "3. task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-22 10:00:00";
const string TASK_THREE_LIST_MONTH = "2. task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 16:00:00";
const string TASK_FOUR = "4. task four done: 0, start:2012-Nov-22 09:00:00 end: 2012-Nov-22 20:00:00";
const string TASK_FIVE = "5. task five done: 0, start:not-a-date-time end: not-a-date-time";
const string TASK_FIVE_DONE = "1. task five done: 1, start:not-a-date-time end: not-a-date-time";
const string TASK_FOUR_CLASH = "task four done: 0, start:2012-Nov-18 10:00:00 end: 2012-Nov-19 23:59:00";

const string TASK_ONE_BARE = "task one done: 0, start:not-a-date-time end: not-a-date-time";
const string TASK_TWO_BARE = "task two done: 0, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_THREE_BARE = "task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 16:00:00";

const string TASK_ONE_DONE_ON_DP = "task one done: 1, start:not-a-date-time end: not-a-date-time";
const string TASK_TWO_DONE_ON_DP = "task two done: 1, start:not-a-date-time end: 2012-Nov-20 23:59:00";
const string TASK_THREE_DONE_ON_DP = "task three done: 1, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 16:00:00";

const string DEF_START_TIME = "00:00:00";
const string DEF_END_TIME = "23:59:00";
const string START_DATE_TIMED = "2012-Nov-10 00:00:00";
const string END_DATE_TIMED = "2012-Dec-10 23:59:00";
const string END_DATE_DEADLINE = "2012-Nov-12 23:59:00";
const string FLOATING_TASK_FORMAT = "done: 0, start:not-a-date-time end: not-a-date-time";
const string UNDONE_FORMAT = "done: 0, ";
const string DONE_FORMAT = "done: 1, ";
const string DEADLINE_TASK_FORMAT = "done: 0, start:not-a-date-time end: ";
const string END_TIME_FORMAT = " end: ";
const string TIMED_TASK_FORMAT = "done: 0, start:";
const string NOT_A_DATE_TIME = "not-a-date-time";

// flag messages
const string SUCCESS_FLAG_MESSAGE = "Task flagged: ";
const string SUCCESS_UNFLAG_MESSAGE = "Task unflagged: ";
const string SUCCESS_FLAG_ALL_MESSAGE = "All tasks listed flagged.";
const string SUCCESS_FLAG_SOME_MESSAGE = "Tasks listed flagged.";
const string SUCCESS_UNFLAG_ALL_MESSAGE = "All tasks listed unflagged.";
const string ERROR_FLAG_MESSAGE = "Unable to flag.";
const string ERROR_UNFLAG_MESSAGE = "Unable to unflag.";
// edit messages
const string PROMPT_EDIT_FLOATING_START_DATE_MESSAGE = "Please enter an end date for floating task.";
const string PROMPT_EDIT_FLOATING_END_DATE_MESSAGE = "Please enter a date for floating task.";
const string ERROR_EDIT_DATE_START_END_MESSAGE = "Please ensure start time is before end time.";
const string ERROR_EDIT_CLASH_MESSAGE = " [CLASH]";
const string PROMPT_EDIT_DEADLINE_START_TIME_MESSAGE = " Deadline task start time edited";
const string ERROR_EDIT_FLOAT_TASK_TIME_MESSAGE = "Cannot edit floating task start time";
const string SUCCESS_EDIT_MESSAGE = "Task edited: ";
const string SUCCESS_EDIT_RENAME = "Task renamed: ";
const string SUCCESS_EDIT_START_TIME = " Start time updated";
const string SUCCESS_EDIT_END_TIME = " End time updated";
const string SUCCESS_EDIT_START_DATE = " Start date updated";
const string SUCCESS_EDIT_END_DATE = " End date updated";
const string EDIT_FROM_CONNECTOR = " From: ";
const string EDIT_TO_CONNECTOR = " To: ";
const string NA_DATE_TIME = "N.A.";
const string ERROR_EDIT_MESSAGE = "Unable to edit.";
const string ERROR_EDIT_NO_CHANGES_MESSAGE = "No changes have been made.";
// done messages
const string SUCCESS_DONE_MESSAGE = "Task marked done: ";
const string SUCCESS_UNDONE_MESSAGE = "Task marked undone: ";
const string SUCCESS_DONE_ALL_MESSAGE = "All tasks listed marked done.";
const string SUCCESS_UNDONE_ALL_MESSAGE = "All tasks listed marked undone.";
const string ERROR_DONE_MESSAGE = "Unable to mark done.";
// delete messages
const string SUCCESS_DELETE_MESSAGE = "Task deleted: ";
const string SUCCESS_DELETE_DONE_MESSAGE = "All completed tasks deleted.";
const string ERROR_DELETE_MESSAGE = "Unable to delete.";
// clear messages
const string SUCCESS_CLEAR_MESSAGE = "All tasks cleared.";
const string ERROR_CLEAR_MESSAGE = "Unable to clear tasks. Data failure.";
// add messages
const string SUCCESS_ADD_MESSAGE = "Task added: ";
const string ADD_DEADLINE_BY_CONNECTOR = " By ";
const string ADD_TIMED_FROM_CONNECTOR = " From ";
const string ADD_TIMED_TO_CONNECTOR = " To ";
const string ERROR_ADD_CLASH_MESSAGE = " [CLASH]";
const string ERROR_ADD_MESSAGE = "Unable to add";
// sort messages
const string SUCCESS_SORT_MESSAGE = "Sort completed.";
const string SUCCESS_SORT_ALPHA_MESSAGE = "Sorted by alphabetical order.";
const string SUCCESS_SORT_DONE_MESSAGE = "Sorted by completed tasks on top.";
const string SUCCESS_SORT_FLAG_MESSAGE = "Sorted by flagged tasks on top.";
const string SUCCESS_SORT_DATE_TIME_MESSAGE = "Sorted by date and time.";
const string SORT_EMPTY_DISPLAY = "No tasks on display to sort.";
const string ERROR_SORT_MESSAGE = "Unable to sort.";
const string ERROR_SORT_FLAG_MESSAGE = "Unable to sort by flagged tasks.";
const string ERROR_SORT_DATE_TIME_MESSAGE = "Unable to sort by date time.";
const string ERROR_SORT_DONE_MESSAGE = "Unable to sort by completed tasks.";
// undo messages
const string SUCCESS_UNDO_MESSAGE = "Undo successful.";
const string ERROR_UNDO_MESSAGE = "Unable to undo further.";
// list messages
const string SUCCESS_LIST_OVERDUE = "Listed overdue tasks.";
const string SUCCESS_LIST_NO_OVERDUE = "No overdue tasks.";
const string SUCCESS_LIST_DONE = "Listed completed tasks.";
const string SUCCESS_LIST_TO_CONNECTOR = " To: ";
const string SUCCESS_LIST_DAY_DATE = "Listed tasks from: ";
const string SUCCESS_LIST_WEEK = "Listed tasks from: ";
const string SUCCESS_LIST_MONTH = "Listed tasks in: ";
const string ERROR_LIST_NO_COMPLETED_TASKS = "No tasks marked done.";
const string SUCCESS_LIST_ALL_MESSAGE = "Listed all tasks.";
const string SUCCESS_LIST_SEARCHTERM = "Listed tasks containing: ";
const string SUCCESS_LIST_MESSAGE = "List completed.";
const string SUCCESS_LIST_UNDONE = "Listed uncompleted tasks.";
const string ERROR_LIST_NO_TASKS = "No tasks to list.";
const string ERROR_LIST_MESSAGE = "Unable to list.";
// invalid messages
const string RESET_STATUS = "";
const string ERROR_LOG_CONCAT = "$";
const string ERROR_DATE_PAST_MESSAGE = "The entered date or time is past. Please enter a current date or time.";
const string ERROR_DATE_START_END_MESSAGE = "Please ensure start time is before end time.";
const string ERROR_NO_COMPLETED_TASKS_MESSAGE = "No completed tasks found.";
const string ERROR_NO_MATCHES_FOUND_MESSAGE = "No matches containing: ";
const string MULTIPLE_MATCHES_FOUND = "Found multiple matches containing: ";
const string PROMPT_ENTER_INDEX = ". Please enter an index.";
const string DISPLAY_EMPTY = "No tasks on display. Try listing. e.g. list.";
const string ERROR_NOT_FOUND_MESSAGE = "Task cannot be found.";
const string ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE = "Invalid task index.";
const string FILE_EMPTY = "No tasks exists.";
const string ERROR_LOG_FILE_NAME = "log.txt";
const string ERROR_STRING_LENGTH_EXCEEDED = "Maximum characters allowed is 100.";
const string ERROR_INVALID_SYNTAX = "That was an invalid syntax. Please try again with the following syntax.";
const string ERROR_BLANK_COMMAND = "Aw...That was an invalid command. Please try again.";
const string ERROR_UNABLE_TO_PROCESS = "We are unable to process your command. Please try again.";
const string FILE_NAME = "schedulerPP.txt";

/************************************************************************/
/* We write test cases here */
/************************************************************************/
// <task> <ws> <-num>
TEST_F(LogicTester, add_floating_whitespaces)
{
	stringstream i;
	_ui.readUserInput("clear YES");
	string o = _ui.readUserInput("add task   -111");

	i << "1. " << "task   -111 " << FLOATING_TASK_FORMAT;
	i << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task   -111";
	i << endl;

	ASSERT_EQ(i.str(), o);

}

// <task> <from|datetime> <to|datetime>
TEST_F(LogicTester, add_clashing_task)
{
	stringstream i;
	string res = _ui.readUserInput("add Task clash from 21 Nov, 1300 to 21 Nov, 1400");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << "4. " << "Task clash " << TIMED_TASK_FORMAT << "2012-Nov-21 13:00:00 end: 2012-Nov-21 14:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "Task clash " << "From 2012-Nov-21 To 2012-Nov-21" << ERROR_ADD_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// <add> <current date> < <added date>
TEST_F(LogicTester, add_past_date) {
	stringstream i;
	string res = _ui.readUserInput("add Task past date by 1 nov 2012");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_DATE_PAST_MESSAGE << endl;

	ASSERT_EQ(i.str(), res);
}

// <add> from <date1> to <date2> where date2 < date1
TEST_F(LogicTester, add_date_start_end) {
	stringstream i;
	string res = _ui.readUserInput("add Task temp from 14 Nov, 2000 to 13 Nov, 2100");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_DATE_START_END_MESSAGE << endl;

	ASSERT_EQ(i.str(), res);
}

// edit task name GOOD
TEST_F(LogicTester, edit_task_name_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 rename NEWTASKNAME");

	i << TASK_ONE_RENAME << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_EDIT_RENAME;
	i << EDIT_FROM_CONNECTOR << "task one";
	i << EDIT_TO_CONNECTOR << "NEWTASKNAME";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time GOOD
TEST_F(LogicTester, edit_end_time_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 end 2000");

	i << TASK_ONE << endl;
	i << TASK_TWO_EDITED_END_TIME << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task two" << SUCCESS_EDIT_END_TIME;
	i << EDIT_FROM_CONNECTOR << "23:59:00";
	i << EDIT_TO_CONNECTOR << "20:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date GOOD
TEST_F(LogicTester, edit_end_date_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 end 30 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO_EDITED_END_DATE << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task two" << SUCCESS_EDIT_END_DATE;
	i << EDIT_FROM_CONNECTOR << "2012-Nov-20 23:59:00";
	i << EDIT_TO_CONNECTOR << "2012-Nov-30 13:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date BAD past date
TEST_F(LogicTester, edit_end_date_bad_past) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 end 1 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_DATE_PAST_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date BAD start>end
TEST_F(LogicTester, edit_end_date_bad_invalid) {
	stringstream i;
	_ui.readUserInput("list");
	// 21 Nov > 19 Nov
	string res = _ui.readUserInput("edit 3 end 19 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_DATE_START_END_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date GOOD
TEST_F(LogicTester, edit_start_date_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 start 17 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO_EDITED_START_DATE << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task two" << SUCCESS_EDIT_START_DATE;
	i << EDIT_FROM_CONNECTOR << "N.A.";
	i << EDIT_TO_CONNECTOR << "2012-Nov-17 13:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date BAD past date
TEST_F(LogicTester, edit_start_date_bad_past) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 start 1 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_DATE_PAST_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date BAD start>end
TEST_F(LogicTester, edit_start_date_bad_invalid) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 start 1 Dec 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_DATE_START_END_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date GOOD floating->deadline
TEST_F(LogicTester, edit_end_date_good_float_to_deadline) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 end 1 Dec 2012, 1300");

	i << TASK_ONE_EDITED_END << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task one" << SUCCESS_EDIT_END_DATE;
	i << EDIT_FROM_CONNECTOR << "N.A.";
	i << EDIT_TO_CONNECTOR << "2012-Dec-01 13:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date BAD floating->deadline
TEST_F(LogicTester, edit_end_date_bad_float_past_date) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 end 1 Nov 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_DATE_PAST_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date BAD floating->???
TEST_F(LogicTester, edit_start_date_bad_floating) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 start 1 Dec 2012, 1300");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << PROMPT_EDIT_FLOATING_START_DATE_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start time GOOD
TEST_F(LogicTester, edit_start_time_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 0100");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE_EDIT_START_TIME << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task three" << SUCCESS_EDIT_START_TIME;
	i << EDIT_FROM_CONNECTOR << "12:00:00";
	i << EDIT_TO_CONNECTOR << "01:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start time BAD start_time > end_time (same day)
TEST_F(LogicTester, edit_start_time_bad_start_more_end) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 2100");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_EDIT_DATE_START_END_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time BAD start_time > end_time (same day)
TEST_F(LogicTester, edit_end_time_bad_start_more_end) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 0100");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_EDIT_DATE_START_END_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit no clash start date GOOD
TEST_F(LogicTester, edit_start_date_good_no_clash) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 19 Nov, 0");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE_EDIT_START_DATE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task three" << SUCCESS_EDIT_START_DATE;
	i << EDIT_FROM_CONNECTOR << "2012-Nov-21 12:00:00";
	i << EDIT_TO_CONNECTOR << "2012-Nov-19 00:00:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit CLASH start date GOOD
TEST_F(LogicTester, edit_start_date_good_clash) {
	stringstream i;
	_ui.readUserInput("add task four from 18 Nov, 1000 to 19 Nov, 2359");
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 19 Nov, 0");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE_EDIT_START_DATE << endl;
	i << "4. " << TASK_FOUR_CLASH << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task three" << SUCCESS_EDIT_START_DATE;
	i << EDIT_FROM_CONNECTOR << "2012-Nov-21 12:00:00";
	i << EDIT_TO_CONNECTOR << "2012-Nov-19 00:00:00";
	i << ERROR_ADD_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit clash end date GOOD
TEST_F(LogicTester, edit_end_date_good_clash) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("add task four from 22 Nov, 0900 to 22 Nov, 2000");
	string res = _ui.readUserInput("edit 3 end 22 Nov, 1000");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE_EDIT_END_DATE << endl;
	i << TASK_FOUR << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task three" << SUCCESS_EDIT_END_DATE;
	i << EDIT_FROM_CONNECTOR << "2012-Nov-21 16:00:00";
	i << EDIT_TO_CONNECTOR << "2012-Nov-22 10:00:00";
	i << ERROR_EDIT_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time BAD floating task
TEST_F(LogicTester, edit_end_time_bad_floating_missing_date) {
	stringstream i;
	stringstream temp;
	ptime today = second_clock::local_time();
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 end 2359");

	i << "1. " << "task one done: 0, start:not-a-date-time end: " << today.date() << " 23:59:00" << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task one" << SUCCESS_EDIT_END_TIME;
	i << EDIT_FROM_CONNECTOR << "N.A.";
	i << EDIT_TO_CONNECTOR << "23:59:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start time BAD floating task
TEST_F(LogicTester, edit_start_time_bad_floating) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 start 1000");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_EDIT_FLOAT_TASK_TIME_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date GOOD
TEST_F(LogicTester, list_date_good) {
	stringstream i;
	ptime l;
	l = second_clock::local_time();
	string res = _ui.readUserInput("list 20 Nov");

	i << TASK_TWO_LIST_DATE << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << l.date() << SUCCESS_LIST_TO_CONNECTOR << "2012-Nov-20";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list done GOOD
TEST_F(LogicTester, list_done_good) {
	stringstream i;
	_ui.readUserInput("add task four");
	_ui.readUserInput("add task five");
	_ui.readUserInput("list");
	_ui.readUserInput("done 5");
	string res = _ui.readUserInput("list done");

	i << TASK_FIVE_DONE << endl;
	i << endl;
	i << SUCCESS_LIST_DONE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list done BAD no done tasks
TEST_F(LogicTester, list_date_bad_no_done) {
	stringstream i;
	string res = _ui.readUserInput("list done");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << ERROR_NOT_FOUND_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// undo as first command
TEST_F(LogicTester, undo_as_first_command) {
	stringstream i;
	string res = _ui.readUserInput("undo");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << endl;
	i << SUCCESS_UNDO_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete BAD empty file
TEST_F(LogicTester, delete_empty_file_bad) {
	stringstream i;
	_ui.readUserInput("clear YES");
	string res = _ui.readUserInput("delete 1");

	i << endl;
	i << FILE_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete task name GOOD
TEST_F(LogicTester, delete_task_name_good) {
	stringstream i;
	string res = _ui.readUserInput("delete task three");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << endl;
	i << SUCCESS_DELETE_MESSAGE << "task three";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete task name GOOD multiple match
TEST_F(LogicTester, delete_task_name_good_multiple) {
	stringstream i;
	string res = _ui.readUserInput("delete task");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << MULTIPLE_MATCHES_FOUND << "task";
	i << PROMPT_ENTER_INDEX;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete all done GOOD
TEST_F(LogicTester, delete_all_done_good) {
	stringstream i;

	_ui.readUserInput("add task four");
	_ui.readUserInput("add task five");
	_ui.readUserInput("list");
	_ui.readUserInput("done 4");
	_ui.readUserInput("done 5");
	string res = _ui.readUserInput("delete done");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_DELETE_DONE_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete single done GOOD
TEST_F(LogicTester, delete_single_done_good) {
	stringstream i;

	_ui.readUserInput("add task four");
	_ui.readUserInput("list");
	_ui.readUserInput("done 4");
	string res = _ui.readUserInput("delete done");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_DELETE_MESSAGE;
	i << "task four";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list month GOOD
TEST_F(LogicTester, list_month_good) {
	stringstream i;
	string res = _ui.readUserInput("list november");

	i << TASK_TWO_LIST_MONTH << endl;
	i << TASK_THREE_LIST_MONTH << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << "2012-Nov-01" << SUCCESS_LIST_TO_CONNECTOR << "2012-Nov-30";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list month GOOD
TEST_F(LogicTester, list_month_keyword_good) {
	stringstream i;
	string res = _ui.readUserInput("list month");

	i << TASK_TWO_LIST_MONTH << endl;
	i << TASK_THREE_LIST_MONTH << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << "2012-Nov-01" << SUCCESS_LIST_TO_CONNECTOR << "2012-Nov-30";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag index GOOD
TEST_F(LogicTester, flag_index_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag 2");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_FLAG_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// unflag GOOD
TEST_F(LogicTester, unflag_index_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("flag 2");
	string res = _ui.readUserInput("flag 2");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_UNFLAG_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// undone index GOOD
TEST_F(LogicTester, undone_index_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done 2");
	string res = _ui.readUserInput("done 2");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_UNDONE_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done index GOOD
TEST_F(LogicTester, done_index_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done 2");

	i << TASK_ONE << endl;
	i << TASK_TWO_DONE << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_DONE_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag task name GOOD
TEST_F(LogicTester, flag_task_name_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag task two");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_FLAG_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// unflag task name GOOD
TEST_F(LogicTester, unflag_task_name_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("flag task two");
	string res = _ui.readUserInput("flag task two");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_UNFLAG_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// undone task name GOOD
TEST_F(LogicTester, undone_task_name_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done task two");
	string res = _ui.readUserInput("done task two");

	i << TASK_ONE << endl;
	i << TASK_TWO << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_UNDONE_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done task name GOOD
TEST_F(LogicTester, done_task_name_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done task two");

	i << TASK_ONE << endl;
	i << TASK_TWO_DONE << endl;
	i << TASK_THREE << endl;
	i << endl;
	i << SUCCESS_DONE_MESSAGE;
	i << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort alphabetically GOOD
TEST_F(LogicTester, sort_alpha_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("sort a");

	i << TASK_ONE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << "3. " << TASK_TWO_BARE << endl;
	i << endl;
	i << SUCCESS_SORT_ALPHA_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort alphabetically BAD empty display
TEST_F(LogicTester, sort_alpha_bad_empty_display) {
	stringstream i;
	_ui.readUserInput("clear YES");
	string res = _ui.readUserInput("sort a");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort done GOOD
TEST_F(LogicTester, sort_done_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done 2");
	string res = _ui.readUserInput("sort d");

	i << TASK_TWO_SORT_D << endl;
	i << "2. " << TASK_ONE_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_SORT_DONE_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort done BAD empty display
TEST_F(LogicTester, sort_done_bad_empty_display) {
	stringstream i;
	_ui.readUserInput("clear YES");
	string res = _ui.readUserInput("sort d");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort datetime GOOD
TEST_F(LogicTester, sort_datetime_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("sort t");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << "3. " << TASK_ONE_BARE << endl;
	i << endl;
	i << SUCCESS_SORT_DATE_TIME_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort datetime BAD empty display
TEST_F(LogicTester, sort_datetime_bad_empty_display) {
	stringstream i;
	_ui.readUserInput("clear YES");
	string res = _ui.readUserInput("sort t");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort flag GOOD
TEST_F(LogicTester, sort_flag_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("flag 2");
	string res = _ui.readUserInput("sort f");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_ONE_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_SORT_FLAG_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// sort flag BAD empty display
TEST_F(LogicTester, sort_flag_bad_empty_display) {
	stringstream i;
	_ui.readUserInput("clear YES");
	string res = _ui.readUserInput("sort f");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task no clash GOOD
TEST_F(LogicTester, add_timed_task_good_no_clash) {
	stringstream i;
	string res = _ui.readUserInput("add newtask timed from 13 Nov, 1000 to 13 Nov, 1100"); // exceed 50 chars

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "newtask timed done: 0, start:2012-Nov-13 10:00:00 end: 2012-Nov-13 11:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "newtask timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-13";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-13";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task CLASH GOOD
// |---|
//    |----|
TEST_F(LogicTester, add_timed_task_good_clash_end_front) {
	stringstream i;
	string res = _ui.readUserInput("add task timed from 21 Nov, 1000 to 21 Nov, 1300");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "task timed done: 0, start:2012-Nov-21 10:00:00 end: 2012-Nov-21 13:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-21";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-21";
	i << ERROR_ADD_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task CLASH GOOD
// |----|
//     |---|
TEST_F(LogicTester, add_timed_task_good_clash_front_end) {
	stringstream i;
	string res = _ui.readUserInput("add task timed from 21 Nov, 1300 to 21 Nov, 2300");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "task timed done: 0, start:2012-Nov-21 13:00:00 end: 2012-Nov-21 23:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-21";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-21";
	i << ERROR_ADD_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task CLASH GOOD
// |---------|
//    |---|
TEST_F(LogicTester, add_timed_task_good_clash_middle) {
	stringstream i;
	string res = _ui.readUserInput("add task timed from 21 Nov, 1300 to 21 Nov, 2300");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "task timed done: 0, start:2012-Nov-21 13:00:00 end: 2012-Nov-21 23:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-21";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-21";
	i << ERROR_ADD_CLASH_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task CLASH BAD equal
// |---------|
//           |---|
TEST_F(LogicTester, add_timed_task_bad_clash_equal_end) {
	stringstream i;
	string res = _ui.readUserInput("add task timed from 21 Nov, 1600 to 21 Nov, 2300");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "task timed done: 0, start:2012-Nov-21 16:00:00 end: 2012-Nov-21 23:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-21";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-21";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add timed task CLASH BAD equal
//     |---------|
// |---|
TEST_F(LogicTester, add_timed_task_bad_clash_equal_start) {
	stringstream i;
	string res = _ui.readUserInput("add task timed from 21 Nov, 0800 to 21 Nov, 1200");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << "task timed done: 0, start:2012-Nov-21 08:00:00 end: 2012-Nov-21 12:00:00" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << "task timed";
	i << ADD_TIMED_FROM_CONNECTOR << "2012-Nov-21";
	i << ADD_TIMED_TO_CONNECTOR << "2012-Nov-21";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// mark done by search term GOOD object not in display
TEST_F(LogicTester, done_search_term_good_not_on_screen) {
	stringstream i;
	_ui.readUserInput("list two");
	string res = _ui.readUserInput("done one");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_ONE_DONE << endl;
	i << endl;
	i << SUCCESS_DONE_MESSAGE << "task one";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// mark undone by search term GOOD object not in display
TEST_F(LogicTester, done_index_good_not_on_screen) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done 1");
	_ui.readUserInput("list two");
	string res = _ui.readUserInput("done one");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_ONE_BARE << endl;
	i << endl;
	i << SUCCESS_UNDONE_MESSAGE << "task one";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_display, sort_alpha_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("sort a");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_display, sort_date_time_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("sort t");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_display, sort_done_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("sort d");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_display, sort_flag_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("sort f");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_done_bad_empty) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list done");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_datetime_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list 20 Nov");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_month_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list nov");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_search_term_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list task");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_day_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list today");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(empty_data, list_all_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("list");

	i << endl;
	i << ERROR_LIST_NO_TASKS;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete index in empty
TEST(empty_data, delete_index_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("delete 1");

	i << endl;
	i << FILE_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete search term in empty
TEST(empty_data, delete_search_term_bad) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("delete task");

	i << endl;
	i << FILE_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start time BAD no change
TEST_F(LogicTester, edit_start_time_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 1200");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time BAD no change
TEST_F(LogicTester, edit_end_time_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 1600");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time deadline BAD no change
TEST_F(LogicTester, edit_end_time_deadline_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 end 2359");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date time BAD no change
TEST_F(LogicTester, edit_start_date_time_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 21 Nov, 1200");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date BAD no change
TEST_F(LogicTester, edit_start_date_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 21 Nov, 1200");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date BAD no change
TEST_F(LogicTester, edit_end_date_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 21 Nov, 1600");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date WITHOUT time BAD no change
TEST_F(LogicTester, edit_end_date_without_time_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 21 Nov");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << "task three done: 0, start:2012-Nov-21 12:00:00 end: 2012-Nov-21 23:59:00" << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE << "task three";
	i << SUCCESS_EDIT_END_DATE << EDIT_FROM_CONNECTOR << "2012-Nov-21 16:00:00";
	i << EDIT_TO_CONNECTOR << "2012-Nov-21 23:59:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date deadline BAD no change
TEST_F(LogicTester, edit_end_date_deadline_bad_no_changes) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 2 end 20 Nov");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done index BAD out bounds
TEST_F(LogicTester, done_index_bad_out_bounds) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done 20");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done search term BAD not found
TEST_F(LogicTester, done_search_term_bad_not_found) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done tana");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NOT_FOUND_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done search term GOOD multiple matches
TEST_F(LogicTester, done_search_term_good_multiple_matches) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done task t");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << MULTIPLE_MATCHES_FOUND;
	i << "task t";
	i << PROMPT_ENTER_INDEX;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list search term GOOD
TEST_F(LogicTester, list_search_term_good) {
	stringstream i;
	string res = _ui.readUserInput("list tas");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_LIST_SEARCHTERM << "tas";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list search term BAD not found
TEST_F(LogicTester, list_search_term_bad_not_found) {
	stringstream i;
	string res = _ui.readUserInput("list tasky");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NOT_FOUND_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date time GOOD past date assumed
TEST_F(LogicTester, list_date_time_good_past_date_assumed) {
	stringstream i;
	ptime l;
	l = second_clock::local_time();
	string res = _ui.readUserInput("list 1 Nov");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << l.date() << SUCCESS_LIST_TO_CONNECTOR << "2013-Nov-01";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date time BAD past date
TEST_F(LogicTester, list_date_time_bad_past_date) {
	stringstream i;
	string res = _ui.readUserInput("list 1 Nov 2012");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_DATE_PAST_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag index BAD out of bounds
TEST_F(LogicTester, flag_index_bad_out_bounds) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag 20");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag search term BAD not found
TEST_F(LogicTester, flag_search_term_bad_not_found) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag tasky");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NO_MATCHES_FOUND_MESSAGE << "tasky";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag search term BAD multiple matches
TEST_F(LogicTester, flag_search_term_bad_multiple_matches) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag task t");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << MULTIPLE_MATCHES_FOUND << "task t";
	i << PROMPT_ENTER_INDEX;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date BAD not found
TEST_F(LogicTester, list_date_time_bad_not_found) {
	stringstream i;
	string res = _ui.readUserInput("list 17 Nov");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NOT_FOUND_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date BAD before and inclusive
TEST_F(LogicTester, list_date_time_bad_before_inclusive) {
	stringstream i;
	ptime l;
	l = second_clock::local_time();
	_ui.readUserInput("add task four 18 Nov, 2000");
	string res = _ui.readUserInput("list 20 Nov");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << "task four done: 0, start:not-a-date-time end: 2012-Nov-18 20:00:00" << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << l.date() << SUCCESS_LIST_TO_CONNECTOR << "2012-Nov-20";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list date BAD before strictly
TEST_F(LogicTester, list_date_time_bad_before_strictly) {
	stringstream i;
	ptime l;
	l = second_clock::local_time();
	string res = _ui.readUserInput("list 29 Nov");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << l.date() << SUCCESS_LIST_TO_CONNECTOR << "2012-Nov-29";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit rename BAD no change
TEST_F(LogicTester, edit_rename_bad_no_change) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 rename task one");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_EDIT_NO_CHANGES_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit rename BAD out of bounds
TEST_F(LogicTester, edit_rename_bad_out_bounds) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 4 rename task one");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit rename empty display
TEST(empty_display, edit_rename_empty_display) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 rename task one");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start time empty display
TEST(empty_display, edit_start_time_empty_display) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 1000");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit start date empty display
TEST(empty_display, edit_start_date_empty_display) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 start 20 Nov");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end time empty display
TEST(empty_display, edit_end_time_empty_display) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 1700");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit end date empty display
TEST(empty_display, edit_end_date_empty_display) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 3 end 22 Nov");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// clear BAD empty file
TEST(empty_file, clear_bad_empty_file) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("clear YES");

	i << endl;
	i << FILE_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete index GOOD twice by 1
TEST_F(LogicTester, delete_index_good_twice_1) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("delete 1");
	string res = _ui.readUserInput("delete 1");

	i << "1. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_DELETE_MESSAGE << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete search term GOOD
TEST_F(LogicTester, delete_search_term_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("delete two");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_DELETE_MESSAGE << "task two";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag index BAD empty display
TEST(empty_display, flag_index_bad_empty_display) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("flag 3");

	i << endl;
	i << DISPLAY_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete search term GOOD
TEST_F(LogicTester, delete_search_term_bad_not_found) {
	stringstream i;
	string res = _ui.readUserInput("delete hello");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NO_MATCHES_FOUND_MESSAGE;
	i << "hello";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete index BAD out of bounds
TEST_F(LogicTester, delete_index_bad_negative_search_term) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("delete -1");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_NO_MATCHES_FOUND_MESSAGE << "-1";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete index BAD zero boundary
TEST_F(LogicTester, delete_index_bad_zero_boundary) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("delete 0");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done search term BAD multiple matches
TEST_F(LogicTester, done_search_term_bad_multiple_matches) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done task");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << MULTIPLE_MATCHES_FOUND;
	i << "task";
	i << PROMPT_ENTER_INDEX;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// delete BAD invalid command
TEST(status_update_test, invalid_command) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("add");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Please enter a description of the task";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit floating start time BAD
TEST_F(LogicTester, edit_bad_start_time_floating) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("edit 1 start 1 Dec");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << PROMPT_EDIT_FLOATING_START_DATE_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

//Command: clear
//All Tasks Cleared
//Command: clear abc
//Invalid Command
//Command: clear abc
//Invalid Command
//Command: delete -1
//All Tasks Cleared
TEST_F(LogicTester, status_update_bad) {
	stringstream i;
	_ui.readUserInput("clear YES");
	_ui.readUserInput("clear abc");
	_ui.readUserInput("clear abc");
	string res = _ui.readUserInput("delete -1");

	i << endl;
	i << FILE_EMPTY;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// string length exceed BAD without tasks
TEST(input_exceed, string_length_exceed_bad_without_tasks) {
	stringstream i;
	UI _ui;
	stringstream x;
	x << "add ";
	// loop 24 times including "add " 
	for(int j=0; j<24; j++) {
		x << "abcd";
	}
	x << ".";
	string res = _ui.readUserInput(x.str());

	i << endl;
	i << ERROR_STRING_LENGTH_EXCEEDED;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// string length exceed GOOD WITH tasks
TEST_F(LogicTester, string_length_exceed_good_with_tasks) {
	stringstream i;
	stringstream x;
	stringstream y;
	x << "add ";
	// loop 24 times including "add " 
	for(int j=0; j<96; j++) {
		x << "a";
		y << "a";
	}
	string res = _ui.readUserInput(x.str());

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << "4. " << y.str() << " done: 0, start:not-a-date-time end: not-a-date-time" << endl;
	i << endl;
	i << SUCCESS_ADD_MESSAGE << y.str();
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// string length exceed BAD WITH tasks
TEST_F(LogicTester, string_length_exceed_bad_with_tasks) {
	stringstream i;
	stringstream x;
	x << "add ";
	// loop 24 times including "add " 
	for(int j=0; j<24; j++) {
		x << "abcd";
	}
	x << ".";
	string res = _ui.readUserInput(x.str());

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << ERROR_STRING_LENGTH_EXCEEDED;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// edit 2 end 1000 : check if date is present. if not, set to current date.
// edit end time only GOOD display current date with new time
TEST_F(LogicTester, edit_end_time_good_current_date_with_new_time) {
	stringstream i;
	ptime today;
	today = second_clock::local_time();
	_ui.readUserInput("list");
	string input;
	input = "edit 1 end 2359";
	string res = _ui.readUserInput(input);

	i << "1. " << "task one done: 0, start:not-a-date-time end: " << today.date() << " " << "23:59:00" << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_EDIT_MESSAGE;
	i << "task one" << SUCCESS_EDIT_END_TIME;
	i << EDIT_FROM_CONNECTOR << "N.A.";
	i << EDIT_TO_CONNECTOR << "23:59:00";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done listed on display GOOD
TEST_F(LogicTester, done_listed_on_display_good) {
	stringstream i;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("done listed");

	i << "1. " << TASK_ONE_DONE_ON_DP << endl;
	i << "2. " << TASK_TWO_DONE_ON_DP << endl;
	i << "3. " << TASK_THREE_DONE_ON_DP << endl;
	i << endl;
	i << SUCCESS_DONE_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// done listed on display BAD 1 task already marked done
TEST_F(LogicTester, done_listed_on_display_bad_1_task_already_marked_done) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done 1");
	string res = _ui.readUserInput("done listed");

	i << "1. " << TASK_ONE_DONE_ON_DP << endl;
	i << "2. " << TASK_TWO_DONE_ON_DP << endl;
	i << "3. " << TASK_THREE_DONE_ON_DP << endl;
	i << endl;
	i << SUCCESS_DONE_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// undone listed on display GOOD
TEST_F(LogicTester, undone_listed_on_display_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done listed");
	string res = _ui.readUserInput("done listed");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_UNDONE_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list undone GOOD
TEST_F(LogicTester, list_undone_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("done listed");
	_ui.readUserInput("add task four");
	string res = _ui.readUserInput("list not done");

	i << "1. " << "task four done: 0, start:not-a-date-time end: not-a-date-time" << endl;
	i << endl;
	i << SUCCESS_LIST_UNDONE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag listed GOOD
TEST_F(LogicTester, flag_listed_good) {
	stringstream i;
	_ui.readUserInput("list task t");
	string res = _ui.readUserInput("flag listed");

	i << "1. " << TASK_TWO_BARE << endl;
	i << "2. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_FLAG_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// flag listed BAD one task already flagged
TEST_F(LogicTester, flag_listed_bad_1_task_already_flagged) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("flag 1");
	_ui.readUserInput("list");
	string res = _ui.readUserInput("flag listed");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_FLAG_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// unflag listed GOOD
TEST_F(LogicTester, unflag_listed_good) {
	stringstream i;
	_ui.readUserInput("list");
	_ui.readUserInput("flag listed");
	string res = _ui.readUserInput("flag listed");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_UNFLAG_ALL_MESSAGE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list next sun GOOD
TEST_F(LogicTester, list_next_day_good) {
	stringstream i;
	ptime start;
	ptime end;
	start = second_clock::local_time();
	end = ptime(date(2012,Nov,18), time_duration(23,59,0));
	_ui.readUserInput("add task four next sunday");
	string res = _ui.readUserInput("list next sunday");

	i << "1. " << "task four done: 0, start:not-a-date-time end: " << end.date() << " " << end.time_of_day() << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << start.date() << SUCCESS_LIST_TO_CONNECTOR << end.date();
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list this monday GOOD
TEST_F(LogicTester, list_this_day_good) {
	stringstream i;
	ptime start;
	ptime end;
	start = second_clock::local_time();
	end = ptime(date(2012,Nov,12), time_duration(23,59,0));
	_ui.readUserInput("add task four this monday");
	string res = _ui.readUserInput("list this monday");

	i << "1. " << "task four done: 0, start:not-a-date-time end: " << end.date() << " " << end.time_of_day() << endl;
	i << endl;
	i << SUCCESS_LIST_DAY_DATE << start.date() << SUCCESS_LIST_TO_CONNECTOR << end.date();
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// list overdue good no overdue
TEST_F(LogicTester, list_overdue_good_no_overdue) {
	stringstream i;
	string res = _ui.readUserInput("list overdue");

	i << "1. " << TASK_ONE_BARE << endl;
	i << "2. " << TASK_TWO_BARE << endl;
	i << "3. " << TASK_THREE_BARE << endl;
	i << endl;
	i << SUCCESS_LIST_NO_OVERDUE;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// invalid command
TEST(invalid_command_test, edit_bad_empty_command) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("add temp task");
	string res = _ui.readUserInput("edit");

	i << "1. temp task done: 0, start:not-a-date-time end: not-a-date-time" << endl;
	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Edit format: edit 2 rename New Name, edit 2 end 2300";
	i << endl;

	_ui.readUserInput("clear YES");

	ASSERT_EQ(i.str(), res);
}

// parsing error feedback
// add command BAD no description
TEST(invalid_command_test, add_bad_no_description) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("add");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Please enter a description of the task";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// add > command BAD no description
TEST(invalid_command_test, add_escape_date_bad_no_description) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("add >");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Please enter a valid date or time. Eg. 1 Jan 2014";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(invalid_command_test, done_bad_empty_command) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("done");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Done format: done <task index>, done <task name>, done listed";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(invalid_command_test, flag_bad_empty_command) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("flag");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Flag format: flag <task index>, flag <task name>, flag listed";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(invalid_command_test, delete_bad_empty_command) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("delete");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Delete format: delete <task index>, delete <task name>";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(invalid_command_test, sort_bad_empty_command) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("sort");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Sort format: sort a[lphabet], sort t[ime], sort f[lagged], sort d[one]";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

TEST(invalid_command_test, undo_bad_extra_command) {
	stringstream i;
	UI _ui;
	string res = _ui.readUserInput("undo xxx");

	i << endl;
	i << ERROR_INVALID_SYNTAX;
	i << endl;
	i << "Undo format: undo. There is no need for any extra arguments behind.";
	i << endl;

	ASSERT_EQ(i.str(), res);
}

// status update BAD list then empty command
TEST(invalid_command_test, status_update_bad_list_and_empty_command) {
	stringstream i;
	UI _ui;
	_ui.readUserInput("list");
	string res = _ui.readUserInput("");

	i << endl;
	i << ERROR_BLANK_COMMAND;
	i << endl;

	ASSERT_EQ(i.str(), res);
}

/************************************************************************/
/* Test function to be called in main */
/************************************************************************/
void runTest(int argument_count, char** argument_vars)
{
	testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest
	RUN_ALL_TESTS();
	std::getchar(); //pause the program after all the testing
}

#endif