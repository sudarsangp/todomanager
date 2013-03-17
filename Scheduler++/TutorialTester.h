#ifndef TUTORIAL_TESTER_H
#define TUTORIAL_TESTER_H

#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include <string>
#include <sstream>
#include "LogicTutorial.h"

using namespace std;

// @author A0086671W
class TutorialTester : public testing::Test {
public:
	// Objects declared here can be used by all tests in the test case for Foo.

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		LogicTutorial::getInstance()->startTutorial();
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
		LogicTutorial::getInstance()->executeTutorial("clear YES");
	}
};

const string TEST_WELCOME_MSG = "Welcome to Scheduler++. You may ADD, DELETE, LIST, FLAG and mark tasks DONE. We will guide you through this. You may read the status messages here. Now, enter LIST to see sample tasks.";
const string TEST_SUCCESS_TUTORIAL_LIST_MSG = "You have entered a successful command. The above are your listed tasks. You may proceed to ADD a new task. Follow the syntax of ADDING a task. e.g. : add vacation";
const string TEST_SUCCESS_TUTORIAL_ADD_MSG = "You have just completed ADDING a task! Proceed to add a task with a date or time. You can do so with the following syntax. e.g. : add purchase air tickets by 24 Dec";
const string TEST_SUCCESS_TUTORIAL_ADD_TIME_MSG = "You have added a task with a time! Proceed to mark your task DONE. You can do so with the following syntax. e.g. : done 4";
const string TEST_SUCCESS_TUTORIAL_DONE_MSG = "You have marked your task DONE! The tick beside is an indication of DONE tasks. You may FLAG tasks using the same syntax. Now, proceed to DELETE tasks marked DONE. e.g. : delete done";
const string TEST_SUCCESS_TUTORIAL_DELETE_DONE_MSG = "You have cleared your completed agenda! You may also delete tasks normally. To do this, use the same DELETE keyword followed by an INDEX. e.g. : delete 1";
const string TEST_SUCCESS_TUTORIAL_DELETE_MSG = "The task has been DELETED! To recover the task, you may UNDO the action with the following syntax. e.g. : undo";
const string TEST_END_TUTORIAL_MSG = "Congratulations! You have completed the tutorial successfully! Enjoy using Scheduler++!";
const string TEST_COMPLETED_TUTORIAL_MSG = "You have successfully completed the tutorial.";

const string TEST_ADDED_NEW_TASKS_MSG = "Wow! You have cleared all your tasks! Let's add some tasks for you to try out the other commands.";

const int TEST_MAX_STRING_SIZE = 100;

const string TEST_FILE_NAME = "schedulerPP.txt";
const string TEST_ERROR_INDEX_OUT_OF_BOUNDS_MESSAGE = "Please enter an appropriate task index.";
const string TEST_EMPTY_STATUS = "";
const string TEST_ERROR_INVALID_COMMAND_MESSAGE = "That was an invalid command";
const string TEST_ERROR_TRY_AGAIN_MESSAGE = " Try entering the command again.";
const string TEST_ERROR_STRING_LENGTH_EXCEEDED = "Maximum characters allowed is 100";
const string TEST_ERROR_UNABLE_TO_PROCESS = "We are unable to process your command. Please try again.";

TEST_F(TutorialTester, test_start) {
	// LIST -> ADD -> ADD TIMED TASK -> MARK DONE -> DELETE COMPLETED TASKS -> DELETE TASK BY INDEX -> UNDO -> END TUTORIAL
	Display dp;
	
	dp = LogicTutorial::getInstance()->executeTutorial("list");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_LIST_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("add vacation");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_ADD_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("add go helloshop from 21 dec, 10am to 21 dec, 2pm");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_ADD_TIME_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("done 1");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_DONE_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("delete done");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_DELETE_DONE_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("delete 1");
	ASSERT_EQ(TEST_SUCCESS_TUTORIAL_DELETE_MSG, dp.getStatus());

	dp = LogicTutorial::getInstance()->executeTutorial("undo");
	ASSERT_EQ(TEST_END_TUTORIAL_MSG, dp.getStatus());
}
#endif