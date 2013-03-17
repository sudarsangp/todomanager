//@author A0092076A

#include "gtest/gtest.h" //include to use Google Unit test's stuff
#include "UI.h"
#include "Display.h"
/************************************************************************/

/* We write test cases here */

/************************************************************************/
const string fileName = "schedulerPP.txt";
const string taskAdded = "Task added:";
const string invalidAdd = "\nPlease Enter a Valid Date. Example: 8 Jan 2013\n";
const string invalidTaskNumber = "\nInvalid Task Number\n";
const string invalidTaskIndex = "\nInvalid task index.\n";
const string taskCleared = "\nAll tasks cleared.\n";
const string fileEmpty = "\nNo tasks exists.\n";
const string taskDeleted = "Task deleted:";
const string deleteDone = "\nAll Completed Tasks Deleted\n";
const string deleteFormat = "\nDelete format: delete <task index>, delete <task name>\n";
const string editFormat = "\nEdit format: edit 2 rename New Name, edit 2 end 2300\n";
const string invalidSyntax = "\nThat was an invalid syntax. Please try again with the following syntax.";
const string markedDone = "Task marked done:";
const string markedUndone = "Task marked undone:";
const string doneFormat = "\nDone format: done <task index>, done <task name>, done listed\n";
const string listAllTasks = "\nListed all tasks.\n";
const string listedTasks = "\nList Completed\n";
const string undoSuccess = "\nUndo successful.\n";
const string undoFailure = "\nUnable to undo further.\n";
const string sortByAlpha = "\nSorted by alphabetical order.\n";
const string sortByDone = "\nSorted by completed tasks on top.\n";
const string sortByTime = "\nSorted by date and time.\n";
const string sortFormat = "\nSort format: sort a[lphabet], sort t[ime], sort f[lagged], sort d[one]\n";
const string invalidCommand = "\nInvalid Command\n";
const string undoFormat = "\nUndo format: undo. There is no need for any extra arguments behind.\n";
const string noMatch = "\nNo matches containing:";
const string taskNotFound = "\nTask cannot be found.\n";

UI ui;
Writer w( fileName );

TEST(basictest0_undocheck, undotest ) {
	
	string feedback = ui.readUserInput("undo"); 
	vector<Task> fileTasks;
		w.read(fileTasks);
		stringstream displayString;
		for(unsigned int i=0; i<fileTasks.size(); i++) {
			displayString << i+1 << ". " << fileTasks.at(i).getTaskName() <<" done: "<<fileTasks.at(i).getDone()<< ", start:" 
				<< fileTasks.at(i).getStartDateTime() << " end: " << fileTasks.at(i).getEndDateTime() << endl;
		}

		string fileContents = displayString.str();
		size_t check = fileContents.find("Unable to undo further");
	if(check != string::npos || feedback == undoFailure)
		
		ASSERT_EQ( fileContents + undoFailure, feedback );
	else{
		ASSERT_EQ( fileContents + undoSuccess ,feedback);
		
	}

}

TEST(basictest1_clearcheck, forgtestchecking ) {

	string feedback = ui.readUserInput("  clear YES   ");
	if ( feedback == fileEmpty )
		ASSERT_EQ( fileEmpty, feedback );
	else
		ASSERT_EQ( taskCleared , feedback );

}

TEST(basictest2_add1, add_floatingtask){

	string feedback = ui.readUserInput("	add         cs2103 task		");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" cs2103 task\n",feedback);

}

TEST(basictest3_add2, add_deadlinetask) {

	string feedback = ui.readUserInput("	add	 quiz cs2103	 >		30     october     2013	,	2359	");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. quiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\n"+taskAdded+" quiz cs2103 By 2013-Oct-30\n",feedback);

}

TEST(basictest4_add3, add_timedtask) {

	string feedback = ui.readUserInput("	add		movie Batman	 >	31 aug	 2013,	2100	to 31	 aug 2013	,	2359");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. quiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n3. movie Batman done: 0, start:2013-Aug-31 21:00:00 end: 2013-Aug-31 23:59:00\n\n"+taskAdded+" movie Batman From 2013-Aug-31 To 2013-Aug-31\n",feedback);

}
 
TEST(basictest5_delete, deletebyindex ) {

	string feedback = ui.readUserInput("	delete		3	");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. quiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\n"+taskDeleted+" movie Batman\n",feedback);

}

TEST(basictest6_edit, edit_rename ) {

	string feedback = ui.readUserInput("	edit      2		  rename       postlecturequiz cs2103");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\nTask renamed:  From: quiz cs2103 To: postlecturequiz cs2103\n",feedback);

}

TEST(basictest7_done, markasdone ) {

	string feedback = ui.readUserInput("	done	1	");
	ASSERT_EQ("1. cs2103 task done: 1, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\n"+markedDone+" cs2103 task\n",feedback);

}

TEST(basictest8_list, listalltasks ) {

	string feedback = ui.readUserInput("	list	");
	ASSERT_EQ("1. cs2103 task done: 1, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n"+listAllTasks,feedback);

}

TEST(basictest9_clear, clearcommand ) {

	string feedback = ui.readUserInput("	clear YES	");
	ASSERT_EQ( taskCleared,feedback );

}

TEST(basictest10_undo, undocommand ) {

	string feedback = ui.readUserInput("		undo	");
	ASSERT_EQ("1. cs2103 task done: 1, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n"+undoSuccess ,feedback);

}

TEST(add_test11, addpastdate ) {

	string feedback = ui.readUserInput("	add	 cs1231exam		>	 22		sep		2011	");
	ASSERT_EQ("1. cs2103 task done: 1, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\nThe entered date or time is past. Please enter a current date or time.\n" ,feedback);

}

TEST(basictest12_listforundo, listalltasksforundone ) {

	string feedback = ui.readUserInput("		list	");
	ASSERT_EQ("1. cs2103 task done: 1, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n"+listAllTasks,feedback);

}

TEST(basictest13_undone, markasnotdone ) {

	string feedback = ui.readUserInput("done 1");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\n"+markedUndone+" cs2103 task\n",feedback);

}
  
TEST(basictest14_add4, deadlinetask ) {

	string feedback = ui.readUserInput("add AI Competition > 22:11:12");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n3. AI Competition done: 0, start:not-a-date-time end: 2012-Nov-22 23:59:00\n\n"+taskAdded+" AI Competition By 2012-Nov-22\n",feedback);

}

TEST(basictest15_sort, alphabetical) {

	string feedback = ui.readUserInput("sort a");
	ASSERT_EQ("1. AI Competition done: 0, start:not-a-date-time end: 2012-Nov-22 23:59:00\n2. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n3. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n"+sortByAlpha ,feedback);

}

TEST(basictest16_editendtime, endtime ) {

	string feedback = ui.readUserInput(" edit 1 end 10 feb 2013");
	ASSERT_EQ("1. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n2. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n3. postlecturequiz cs2103 done: 0, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\nTask edited: AI Competition End date updated From: 2012-Nov-22 23:59:00 To: 2013-Feb-10 23:59:00\n",feedback);

}

TEST(basictest17_done, forchecksortdone ) {

	string feedback = ui.readUserInput("done 3");
	ASSERT_EQ("1. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n2. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n3. postlecturequiz cs2103 done: 1, start:not-a-date-time end: 2013-Oct-30 23:59:00\n\n"+ markedDone +" postlecturequiz cs2103\n",feedback);

}

TEST(basictest18_sortdone, sortbydone ) {

	string feedback = ui.readUserInput("sort d");
	ASSERT_EQ("1. postlecturequiz cs2103 done: 1, start:not-a-date-time end: 2013-Oct-30 23:59:00\n2. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n3. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n"+sortByDone ,feedback);

}

TEST(basictest19_sorttime, sortbytime ) {

	string feedback = ui.readUserInput("sort t");
	ASSERT_EQ("1. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n2. postlecturequiz cs2103 done: 1, start:not-a-date-time end: 2013-Oct-30 23:59:00\n3. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n"+sortByTime ,feedback);

}

TEST(basictest20_deletedone, deletedonetasks ) {

	string feedback = ui.readUserInput("delete done");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n\n"+taskDeleted+" postlecturequiz cs2103\n" ,feedback);

}

TEST(basictest21_addtimedtask, addtimedtask ) {

	string feedback = ui.readUserInput("add cs2103lecture > 28-2-2013,200 to 28 2 2013,16");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. AI Competition done: 0, start:not-a-date-time end: 2013-Feb-10 23:59:00\n3. cs2103lecture done: 0, start:2013-Feb-28 02:00:00 end: 2013-Feb-28 16:00:00\n\n"+taskAdded+" cs2103lecture From 2013-Feb-28 To 2013-Feb-28\n",feedback);

}

TEST(basictest22_done, markdoneusingtermintaskname ) {

	string feedback = ui.readUserInput(" done ompe ");
	ASSERT_EQ("1. cs2103 task done: 0, start:not-a-date-time end: not-a-date-time\n2. AI Competition done: 1, start:not-a-date-time end: 2013-Feb-10 23:59:00\n3. cs2103lecture done: 0, start:2013-Feb-28 02:00:00 end: 2013-Feb-28 16:00:00\n\n"+markedDone+" AI Competition\n",feedback);

}

TEST(basictest23_deletesearchterm, deletebysearchterm ) {

	string feedback = ui.readUserInput("delete as");
	ASSERT_EQ("1. AI Competition done: 1, start:not-a-date-time end: 2013-Feb-10 23:59:00\n2. cs2103lecture done: 0, start:2013-Feb-28 02:00:00 end: 2013-Feb-28 16:00:00\n\n"+taskDeleted+" cs2103 task\n",feedback);

}

TEST(basictest24_listterms, listbysearchterms ) {

	string feedback = ui.readUserInput("list tit");
	ASSERT_EQ("1. AI Competition done: 1, start:not-a-date-time end: 2013-Feb-10 23:59:00\n\nListed tasks containing: tit\n" ,feedback);

}

TEST(complex1_comb, casesensitivitysortalpha ) {

	string feedback = ui.readUserInput("list");
	ASSERT_EQ("1. AI Competition done: 1, start:not-a-date-time end: 2013-Feb-10 23:59:00\n2. cs2103lecture done: 0, start:2013-Feb-28 02:00:00 end: 2013-Feb-28 16:00:00\n"+listAllTasks,feedback );
	
	feedback = ui.readUserInput("clear YES");
	if ( feedback == fileEmpty )
		ASSERT_EQ( fileEmpty, feedback );
	else
		ASSERT_EQ( taskCleared , feedback );
	
	feedback = ui.readUserInput("add cS2103");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" cS2103\n" ,feedback);
	
	feedback = ui.readUserInput("add cs2103");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n2. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" cs2103\n" ,feedback);

	feedback = ui.readUserInput("add CS2103");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n2. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n3. CS2103 done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" CS2103\n" ,feedback);

	feedback = ui.readUserInput("add Cs2103");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n2. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n3. CS2103 done: 0, start:not-a-date-time end: not-a-date-time\n4. Cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" Cs2103\n" ,feedback);

	feedback = ui.readUserInput("add Android Programming ");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n2. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n3. CS2103 done: 0, start:not-a-date-time end: not-a-date-time\n4. Cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n5. Android Programming done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" Android Programming\n" ,feedback);

	feedback = ui.readUserInput("add ANDROID Coding ");
	ASSERT_EQ("1. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n2. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n3. CS2103 done: 0, start:not-a-date-time end: not-a-date-time\n4. Cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n5. Android Programming done: 0, start:not-a-date-time end: not-a-date-time\n6. ANDROID Coding done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" ANDROID Coding\n" ,feedback);

	feedback = ui.readUserInput("sort a");
	ASSERT_EQ("1. ANDROID Coding done: 0, start:not-a-date-time end: not-a-date-time\n2. Android Programming done: 0, start:not-a-date-time end: not-a-date-time\n3. CS2103 done: 0, start:not-a-date-time end: not-a-date-time\n4. Cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n5. cS2103 done: 0, start:not-a-date-time end: not-a-date-time\n6. cs2103 done: 0, start:not-a-date-time end: not-a-date-time\n"+sortByAlpha ,feedback );

}

TEST(complex2_comb, casesensitivitysorttimeandalpha ) {

	string feedback = ui.readUserInput("clear YES");
	if ( feedback == fileEmpty )
		ASSERT_EQ( fileEmpty, feedback );
	else
		ASSERT_EQ( taskCleared , feedback );

	feedback = ui.readUserInput("add lquiz2103 > 3 dec ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n\n"+taskAdded+" lquiz2103 By 2012-Dec-03\n" ,feedback); 

	feedback = ui.readUserInput("add LQUIZ2103 > 3 dec ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n\n"+taskAdded+" LQUIZ2103 By 2012-Dec-03\n" ,feedback); 

	feedback = ui.readUserInput("sort t");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+sortByTime ,feedback); 

	feedback = ui.readUserInput("sort a");
	ASSERT_EQ("1. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+sortByAlpha ,feedback); 

	feedback = ui.readUserInput("sort t");
	ASSERT_EQ("1. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+sortByTime ,feedback); 

}

TEST(complex3 , outofbounds ) {

	string feedback = ui.readUserInput("   list   ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+listAllTasks ,feedback); 

	feedback = ui.readUserInput("   delete      0  ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidTaskIndex ,feedback );
	
	feedback = ui.readUserInput("   delete      0  random   entry");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+noMatch+" 0  random   entry\n" ,feedback );

	feedback = ui.readUserInput("delete -1");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+noMatch+" -1\n" ,feedback );
	
	feedback = ui.readUserInput("    delete              -1   badstuff     ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+noMatch+" -1   badstuff\n" ,feedback );
	
	feedback = ui.readUserInput("edit           0");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidSyntax+editFormat ,feedback );

	feedback = ui.readUserInput("edit           0  unwanted          details   ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidSyntax+editFormat ,feedback );

	feedback = ui.readUserInput("edit -1    badstuff");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidSyntax+editFormat ,feedback );
	
	feedback = ui.readUserInput("edit         -1 ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidSyntax+editFormat ,feedback );

	feedback = ui.readUserInput("done           0     not needed    details   " );
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+taskNotFound ,feedback );

	feedback = ui.readUserInput("done           0" );
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+invalidTaskIndex ,feedback );

	feedback = ui.readUserInput("done      -1                  badstuff");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+taskNotFound  ,feedback );

}

TEST(complex4, searchspecialsymbols ) {

	string feedback = ui.readUserInput("   list   ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+listAllTasks ,feedback); 

	feedback = ui.readUserInput("add \\~!@#$%^&*()_+{}: |:';<,.?/");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" \\~!@#$%^&*()_+{}: |:';<,.?/\n" ,feedback); 

	feedback = ui.readUserInput("   list ~  ");
	ASSERT_EQ("1. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 0, start:not-a-date-time end: not-a-date-time\n\nListed tasks containing: ~\n" ,feedback);

	feedback = ui.readUserInput("   list   \\ ");
	ASSERT_EQ("1. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 0, start:not-a-date-time end: not-a-date-time\n\nListed tasks containing: \\\n" ,feedback);
	
	feedback = ui.readUserInput("   list   ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 0, start:not-a-date-time end: not-a-date-time\n"+listAllTasks ,feedback); 

	feedback = ui.readUserInput(" done (");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 1, start:not-a-date-time end: not-a-date-time\n\n"+markedDone+" \\~!@#$%^&*()_+{}: |:';<,.?/\n" ,feedback); 
	
	feedback = ui.readUserInput("undo ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. \\~!@#$%^&*()_+{}: |:';<,.?/ done: 0, start:not-a-date-time end: not-a-date-time\n"+undoSuccess ,feedback );

}

TEST(complex5, edittimefordandftasks ) {

	string feedback = ui.readUserInput("undo ");
	ASSERT_EQ("1. lquiz2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n"+undoSuccess ,feedback); 
	
	feedback = ui.readUserInput("edit 1 start 3 dec");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n\nTask edited: lquiz2103 Start date updated From: N.A. To: 2012-Dec-03 00:00:00\n" ,feedback); 
	
	feedback = ui.readUserInput("edit 1 start 13 dec,0400");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n\nPlease ensure start time is before end time.\n" ,feedback); 
	
	feedback = ui.readUserInput("add send email");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. send email done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" send email\n" ,feedback); 

	feedback = ui.readUserInput("edit 3 end 3 dec");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. send email done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n\nTask edited: send email End date updated From: N.A. To: 2012-Dec-03 23:59:00\n" ,feedback); 
	
	feedback = ui.readUserInput("edit 3 start 2 dec");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. send email done: 0, start:2012-Dec-02 00:00:00 end: 2012-Dec-03 23:59:00\n\nTask edited: send email Start date updated From: N.A. To: 2012-Dec-02 00:00:00 [CLASH]\n" ,feedback); 

	feedback = ui.readUserInput("edit 3 end 3 dec,0900");
	ASSERT_EQ("1. lquiz2103 done: 0, start:2012-Dec-03 00:00:00 end: 2012-Dec-03 23:59:00\n2. LQUIZ2103 done: 0, start:not-a-date-time end: 2012-Dec-03 23:59:00\n3. send email done: 0, start:2012-Dec-02 00:00:00 end: 2012-Dec-03 09:00:00\n\nTask edited: send email End date updated From: 2012-Dec-03 23:59:00 To: 2012-Dec-03 09:00:00 [CLASH]\n" ,feedback); 

}

TEST( complex6, miscellaneous ) {
	
	string feedback = ui.readUserInput("clear YES");
	if ( feedback == fileEmpty )
		ASSERT_EQ( fileEmpty, feedback );
	else
		ASSERT_EQ( taskCleared , feedback );

	feedback = ui.readUserInput("clear YES ");
	if ( feedback == fileEmpty )
		ASSERT_EQ( fileEmpty, feedback );
	else
		ASSERT_EQ( taskCleared , feedback );
	

	feedback = ui.readUserInput("clear");
	ASSERT_EQ(invalidSyntax+"\nClear format: clear YES\n", feedback );
		
	feedback = ui.readUserInput("add sampletask ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n\n"+taskAdded+" sampletask\n",feedback);

	feedback = ui.readUserInput("delete");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+deleteFormat,feedback );

	feedback = ui.readUserInput("delete ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+deleteFormat,feedback );

	feedback = ui.readUserInput("delete 2 ");
    ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidTaskIndex, feedback);

	feedback = ui.readUserInput("delete -9 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+noMatch+" -9\n", feedback);

	feedback = ui.readUserInput("  delete   0 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidTaskIndex, feedback);

	feedback = ui.readUserInput("delete -19 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+noMatch+" -19\n", feedback);
	
	feedback = ui.readUserInput("delete -1231110012 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+noMatch+" -1231110012\n", feedback);

	feedback = ui.readUserInput("delete 0 12 3 45 6 789 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+noMatch+" 0 12 3 45 6 789\n", feedback);

	feedback = ui.readUserInput("delete \"");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+noMatch+" \"\n", feedback);
	
	feedback = ui.readUserInput("done ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+doneFormat, feedback);

	feedback = ui.readUserInput("done");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+doneFormat, feedback);

	feedback = ui.readUserInput("done   2 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidTaskIndex , feedback);

	feedback = ui.readUserInput(" done -4 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+taskNotFound, feedback);

	feedback = ui.readUserInput("done     0 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidTaskIndex, feedback);

	feedback = ui.readUserInput("done   121131 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidTaskIndex, feedback);

	feedback = ui.readUserInput("done   -65535 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+taskNotFound, feedback);

	feedback = ui.readUserInput("done   !@4 ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+taskNotFound, feedback);

	feedback = ui.readUserInput("sort");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+sortFormat, feedback);

	feedback = ui.readUserInput("sort ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+sortFormat, feedback);
	
	feedback = ui.readUserInput("sort A randomentry ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+sortFormat, feedback);
	
	feedback = ui.readUserInput("sort T randomentry ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+sortFormat, feedback);

	feedback = ui.readUserInput("edit");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit 4");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);
	
	feedback = ui.readUserInput("edit 1 rename   ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit 1 end   ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit 1 start  ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit 9 rename   ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit -4 end   ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);

	feedback = ui.readUserInput("edit 0 start  ");
	ASSERT_EQ("1. sampletask done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+editFormat, feedback);
	
	feedback = ui.readUserInput("edit 1 RENAME abc ");
	ASSERT_EQ("1. abc done: 0, start:not-a-date-time end: not-a-date-time\n\nTask renamed:  From: sampletask To: abc\n", feedback);

	feedback = ui.readUserInput("edit 1 ReNAMe bcd ");
	ASSERT_EQ("1. bcd done: 0, start:not-a-date-time end: not-a-date-time\n\nTask renamed:  From: abc To: bcd\n", feedback);

	feedback = ui.readUserInput("undo ");
	ASSERT_EQ("1. abc done: 0, start:not-a-date-time end: not-a-date-time\n"+undoSuccess, feedback);
	
	feedback = ui.readUserInput("undo unwanted part");
	ASSERT_EQ("1. abc done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+undoFormat, feedback);

	feedback = ui.readUserInput("undo 12 ");
	ASSERT_EQ("1. abc done: 0, start:not-a-date-time end: not-a-date-time\n"+invalidSyntax+undoFormat, feedback);
	
}

//void runTest(int argument_count, char** argument_vars)
//{
//	testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest
//	RUN_ALL_TESTS();
//	std::getchar(); //pause the program after all the testing
//}