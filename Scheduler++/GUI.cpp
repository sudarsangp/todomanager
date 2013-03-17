//@author A0081136M

#include "GUI.h"

//Handles event when GUI loads
System::Void Scheduler::GUI::GUI_Load(System::Object^  sender, System::EventArgs^  e) 
{
	CommandBase* command = new CommandList(CommandList::LIST_ALL);
	Display display = logic->executeShortCutCommand(command);
	updateObjectListView(display.getTaskList());
}

//Handles event when textBox is focused
System::Void Scheduler::GUI::textBox_Enter(System::Object^  sender, System::EventArgs^  e) 
{
	if(textBox->ForeColor == System::Drawing::Color::Silver)
	{
		//Clear default message
		textBox->Clear();
		//Change text colour to green
		textBox->ForeColor = System::Drawing::Color::Green;
	}
}

//Handles event when textBox is unfocused
System::Void Scheduler::GUI::textBox_Leave(System::Object^  sender, System::EventArgs^  e) 
{
	if(textBox->TextLength == 0)
	{
		//change text colour to silver
		textBox->ForeColor = System::Drawing::Color::Silver;
		//append default message
		textBox->Text = TEXTBOX_DEFAULT_MESSAGE;
	}
}

//Handles events from textBox
System::Void Scheduler::GUI::textBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
	//Event when user enters a command
	if(e->KeyChar == (char)Keys::Enter)
	{
		//Initialize user command
		string userCommand = convertSysStringToStdString(textBox->Text);

		//Save user's command
		commandList->Add(textBox->Text);
		previousCommand = PREVIOUSCOMMAND_RESET;

		Display display;

		if(tutorialMode)
			//Call LogicTutorial API
			display = logicTutorial->executeTutorial(userCommand);
		else
			//Call Logic API
			display = logic->executeTextCommand(userCommand);

		updateAllDisplay(display.getTaskList(), display.getStatus());

		//Ensures that the new added task is visible
		Int32 newPage = objectListView->Items->Count - 1;//Constant, not a magic number
		checkPageWithinLimit(newPage);
		updatePage(newPage);

		textBox->Clear();
		e->Handled = true;
	}

	//Event when user presss the escape key
	else if(e->KeyChar == (char)Keys::Escape)
	{
		e->Handled = true;
		this->Close();
	}
}

//Handles events from textBox
System::Void Scheduler::GUI::textBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
{
	//Event when user presses Control with Z key		 
	if(e->KeyData == (Keys::Control | Keys::Z)) 
	{
		//Undo previous command
		CommandBase* command = new CommandUndo(CommandUndo::UNDO_ACTION);
		Display display = logic->executeShortCutCommand(command);
		updateAllDisplay(display.getTaskList(), display.getStatus());
		eventHandled(e);
	}
	//Event when user presses the F1 key
	if(e->KeyData == Keys::F1)
	{
		//Start or stop tutorial
		toggleTutorial();
		eventHandled(e);
	}
	//Event when user presses Page Up
	if(e->KeyData == Keys::PageDown)
	{
		//Scroll the list up
		Int32 newPage = page + PAGE_SIZE;
		checkPageWithinLimit(newPage);
		updatePage(newPage);
		page = newPage;
	}
	//Event when user presses Page Down
	if(e->KeyData == Keys::PageUp)
	{
		//Scroll the list down
		Int32 newPage = page - PAGE_SIZE;
		checkPageWithinLimit(newPage);
		updatePage(newPage);
		page = newPage;
	}
	//Event when user presses the Up arrow
	if(e->KeyData == Keys::Up)
	{
		//Retrieve/Scroll previous command
		Int32 index = ++previousCommand;
		checkIndexWithinLimit(index);
		updateTextBox(index);
		previousCommand = index;
	}
	//Event when user presses the Down arrow
	if(e->KeyData == Keys::Down)
	{
		//Retrieve/Scroll previous command
		Int32 index = --previousCommand;
		checkIndexWithinLimit(index);
		updateTextBox(index);
		previousCommand = index;
	}
}

//Handles events when objectListView is focused
System::Void Scheduler::GUI::objectListView_Enter(System::Object^  sender, System::EventArgs^  e) 
{
	//Select top item when no current item is selected and objectListView is not empty
	if(objectListView->SelectedIndex == NO_SELECTED_INDEX && objectListView->Items->Count != EMPTY)
	{
		objectListView->TopItem->Selected = true;
		objectListView->FocusedItem = objectListView->GetItem(objectListView->SelectedItem->Index);
	}
}

//Handles events from objectListView
System::Void Scheduler::GUI::objectListView_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
	//When user presses the Escape Key
	if(e->KeyChar == (char)Keys::Escape)
	{
		e->Handled = true;
		//Exit the application
		this->Close();
	}
}

//Handles events from objectListView
System::Void Scheduler::GUI::objectListView_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
{
	//Event when user presses Control with Z key
	if(e->KeyData == (Keys::Control | Keys::Z)) 
	{
		//Undo previous command
		CommandBase* command = new CommandUndo(CommandUndo::UNDO_ACTION);
		Display display = logic->executeShortCutCommand(command);
		updateAllDisplay(display.getTaskList(), display.getStatus());
		objectListView->TopItem->Selected = true;
		eventHandled(e);
	}			 

	//When user presses the Delete Key
	else if(e->KeyData == Keys::Delete)
	{
		deleteSelectedItem();
		eventHandled(e);
	}

	//Event when user presses D key
	else if(e->KeyData == Keys::D) 
	{
		toggleSelectedItemDone();
		eventHandled(e);
	}

	//Event when user presses E key
	else if(e->KeyData == Keys::E)
	{
		//Start rename of item
		this->objectListView->StartCellEdit(this->objectListView->SelectedItem, (int)COLUMN::TASKNAME_INDEX);
		eventHandled(e);
	}

	//Event when user presses F key
	else if(e->KeyData == Keys::F)
	{
		toggleSelectedItemFlag();
		eventHandled(e);
	}

	//Event when user presses the R key
	else if(e->KeyData == Keys::R)
	{
		//Start editing item from date/time
		this->objectListView->StartCellEdit(this->objectListView->SelectedItem, (int)COLUMN::DATEFROM_INDEX);
		eventHandled(e);
	}

	//Event when user presses the T key
	else if(e->KeyData == Keys::T)
	{
		//Stat editing item to date/time
		this->objectListView->StartCellEdit(this->objectListView->SelectedItem, (int)COLUMN::DATETO_INDEX);
		eventHandled(e);
	}

	//Event when user presses the F1 key
	else if(e->KeyData == Keys::F1)
	{
		toggleTutorial();
		eventHandled(e);
	}
}

//Handles event when user starts editing a cell
System::Void Scheduler::GUI::objectListView_CellEditStarting(System::Object^  sender, BrightIdeasSoftware::CellEditEventArgs^  e) 
{

	//Stores the initial value of the cell
	if(e->Column->AspectName == DONE)
		initialCellBooleanValue = (System::Boolean)e->Value;

	else if(e->Column->AspectName ==  TASKNAME || e->Column->AspectName == DATEFROM || e->Column->AspectName == DATETO)
		initialCellStringValue = (System::String^)e->Value;

	else if(e->Column->AspectName == PRIORITY)
		initialCellIntValue = (System::Int32)e->Value;
}

//Handles event when user finish editing a cell
System::Void Scheduler::GUI::objectListView_CellEditFinishing(System::Object^  sender, BrightIdeasSoftware::CellEditEventArgs^  e) 
{		 
	//Determine if cell was edited
	if(e->Column->AspectName == DONE)
		checkDoneChange(e);

	else if(e->Column->AspectName == TASKNAME)
		checkTaskNameChange(e);

	else if(e->Column->AspectName == PRIORITY)
		checkPriorityChange(e);

	else if(e->Column->AspectName == DATEFROM)
		checkDateTimeChange(e, true);

	else if(e->Column->AspectName == DATETO)
		checkDateTimeChange(e, false);
}

//Converts std:string to System:String^
String^ Scheduler::GUI::convertStdStringToSysString(std::string stdstring)
{
	string Model(stdstring);
	String^ sysString = gcnew String(Model.c_str());
	return sysString;
}

//Converts System:String^ to std:string
std::string Scheduler::GUI::convertSysStringToStdString(String^ sysString)
{
	msclr::interop::marshal_context context;
	string stdString = context.marshal_as<string>(sysString);
	return stdString;
}

//Updates objectListView
void Scheduler::GUI::updateObjectListView(vector<Task> displayVector)
{
	//Clear all objects from objectListView
	objectListView->ClearObjects();

	ptime currentTime(second_clock::local_time());

	for(unsigned int i=0; i<displayVector.size(); i++)
	{
		//Create item from displayVector
		Object^ item = initializeItem(i, displayVector[i]);

		//Add item to objectListView
		objectListView->AddObject(item);

		ptime itemDeadline = displayVector[i].getEndDateTime();
		if(itemDeadline < currentTime)
		{
			objectListView->Items[i]->BackColor = System::Drawing::Color::LightSalmon;
		}
	}

	//Ensures that objects are sorted according to index when first displayed
	objectListView->Sort(INITIAL_SORT_COLUMN);

	//Display Overlays if objectListView is empty or in tutorial mode
	this->objectListView->HideOverlays();
	this->objectListView->UseOverlays = false;
	this->objectListView->UseOverlays = true;

	if(tutorialMode)
		this->objectListView->OverlayText->Text = OVERLAY_TUTORIAL;

	else if(objectListView->Items->Count == 0)
		this->objectListView->OverlayText->Text = OVERLAY_EMPTY;

	else
		this->objectListView->OverlayText->Text = EMPTY_STRING;

	objectListView->Refresh();
}

//Updates status message
void Scheduler::GUI::updateStatus(string statusMessage)
{
	status->Text = convertStdStringToSysString(statusMessage);
}

//Updates all display components
void Scheduler::GUI::updateAllDisplay(vector<Task> displayVector, string statusMessage)
{
	updateObjectListView(displayVector);
	updateStatus(statusMessage);
}

//Initialize and returns an item object from a task object
Object^ Scheduler::GUI::initializeItem(int i, Task task)
{
	int taskID = task.getTaskID();

	bool done = task.getDone();

	String^ taskName = convertStdStringToSysString(task.getTaskName());
	//Assertion
	assert(taskName != EMPTY_STRING);

	int priority = task.getPriority();

	string stdStartTime = to_simple_string(task.getStartDateTime());
	String^ sysStartTime;
	//Determine if start time is valid
	if(stdStartTime == convertSysStringToStdString(NOT_A_DATE_TIME))
		sysStartTime = LIST_DEFAULT_DATE_TIME;
	else
		sysStartTime = trimSeconds(convertStdStringToSysString(stdStartTime));

	string stdEndTime = to_simple_string(task.getEndDateTime());
	String^ sysEndTime;
	//Determine if end time is valid
	if(stdEndTime == convertSysStringToStdString(NOT_A_DATE_TIME))
		sysEndTime = LIST_DEFAULT_DATE_TIME;
	else
		sysEndTime = trimSeconds(convertStdStringToSysString(stdEndTime));

	//Create Item object
	Object^ item = gcnew Item(taskID, i+1, done, taskName, priority, sysStartTime, sysEndTime);

	return item;
}

//Check and set new page to be within page limit
void Scheduler::GUI::checkPageWithinLimit(int& newPage)
{
	if(newPage < PAGE_MINIMUM)
		newPage = PAGE_MINIMUM;
	else if(newPage > (objectListView->Items->Count - 1))
		newPage = objectListView->Items->Count - 1;//Constant, not a magic number
}

//Update view of list
void Scheduler::GUI::updatePage(int page)
{
	if(objectListView->Items->Count != EMPTY)
		objectListView->Items[page]->EnsureVisible();
}

//Check and set index of previous command to be within limit
void Scheduler::GUI::checkIndexWithinLimit(int& previousCommand)
{
	if(previousCommand < PREVIOUSCOMMAND_MINIMUM)
		previousCommand = PREVIOUSCOMMAND_MINIMUM;
	else if(previousCommand > commandList->Count)
		previousCommand = commandList->Count;
}

//Update the text in textbox with previous command
void Scheduler::GUI::updateTextBox(int previousCommand)
{
	if(commandList->Count != EMPTY)
	{
		Int32 index = commandList->Count - previousCommand;
		textBox->Clear();
		textBox->AppendText((String^)commandList[index]);
		textBox->SelectionStart = textBox->TextLength;
	}
}

//Deletes selected item
void Scheduler::GUI::deleteSelectedItem()
{
	int index = getSelectedItemIndex();

	//Creates delete command
	CommandBase* command = new CommandDelete(CommandDelete::DELETE_INDEX, index);
	Display display = logic->executeShortCutCommand(command);

	updateAllDisplay(display.getTaskList(), display.getStatus());

	//Update selection as the top item
	if( display.getTaskList().size() > 0 ) {
		objectListView->TopItem->Selected = true;
		objectListView->FocusedItem = objectListView->TopItem;
	}
}

//Toggles the Done value of the selected item
void Scheduler::GUI::toggleSelectedItemDone()
{
	int displayIndex = getSelectedItemIndex();

	//Create done command
	CommandBase* command = new CommandDone(displayIndex);
	Display display = logic->executeShortCutCommand(command);

	updateAllDisplay(display.getTaskList(), display.getStatus());
				 
	//Refocus the selection and focus onto the selected item
	int index = displayIndex - 1;//Constant, not a magic number
	objectListView->Items[index]->Selected = true;
	objectListView->FocusedItem = objectListView->GetItem(index);
	objectListView->Items[index]->EnsureVisible();
}

//Toggles the Flag value of the selected item
void Scheduler::GUI::toggleSelectedItemFlag()
{
	int displayIndex = getSelectedItemIndex();

	//Creates flag command
	CommandBase* command = new CommandFlag(displayIndex);
	Display display = logic->executeShortCutCommand(command);

	updateAllDisplay(display.getTaskList(), display.getStatus());

	//Refocus the selection and focus onto the selected item
	objectListView->Items[displayIndex-1]->Selected = true;
	objectListView->FocusedItem = objectListView->GetItem(displayIndex-1);//Constant, not a magic number	
	objectListView->Items[page]->EnsureVisible();		 
}

//Check if the new value of done differs from the original value
void Scheduler::GUI::checkDoneChange(BrightIdeasSoftware::CellEditEventArgs^  e)
{
	//If the new value differs, create and execute a CommandDone object
	if(initialCellBooleanValue != (System::Boolean)e->NewValue)
	{
		int displayIndex = getSelectedItemIndex();

		//Creates done command
		CommandBase* command = new CommandDone(displayIndex);
		Display display = logic->executeShortCutCommand(command);

		updateStatus(display.getStatus());
	}
}

//Check if the new value of taskname differs from the original value
void Scheduler::GUI::checkTaskNameChange(BrightIdeasSoftware::CellEditEventArgs^  e)
{
	//If the new value differs and is not empty, create and execute a CommandEdit object
	if(initialCellStringValue != (System::String^)e->NewValue && (System::String^)e->NewValue != EMPTY_STRING)
	{
		int displayIndex = getSelectedItemIndex();

		//Creates edit command
		CommandBase* command = new CommandEdit(CommandEdit::EDIT_RENAME, displayIndex,  convertSysStringToStdString((System::String^)e->NewValue));
		Display display = logic->executeShortCutCommand(command);

		updateStatus(display.getStatus());
	}
	else
	{
		//Cancel the event and ignore any changes to the cell
		e->Cancel = true;
		updateStatus(convertSysStringToStdString(STATUS_INVALID_TASK_DESCRIPTION));
	}
}

//Check if the new value of priority differs from the original value
void Scheduler::GUI::checkPriorityChange(BrightIdeasSoftware::CellEditEventArgs^  e)
{
	//If the new value differs, create and execute a CommandFlag object
	if(initialCellIntValue != (System::Int32)e->NewValue)
	{
		int displayIndex = getSelectedItemIndex();

		//Create flag command
		CommandBase* command = new CommandFlag(displayIndex);
		Display display = logic->executeShortCutCommand(command);

		updateStatus(display.getStatus());
	}
}

//Check if the new value of date time differs from the original value
void Scheduler::GUI::checkDateTimeChange(BrightIdeasSoftware::CellEditEventArgs^  e, Boolean startDateTime)
{
	if(initialCellStringValue != (System::String^)e->NewValue && editingFloatingTaskStartDateTime(startDateTime) == false)
	{
		ParserDateTime parserDateTime;
		//parses the user input and returns a ptime type
		ptime newDateTime = parserDateTime.parseDateTime(convertSysStringToStdString((System::String^)e->NewValue), true);

		checkNewDateTimeValidity(newDateTime, e, startDateTime);
	}
	else
	{
		//Cancel the event and ignore any changes to the cell
		e->Cancel = true;
		updateStatus(convertSysStringToStdString(STATUS_INVALID_TASK_TYPE));
	}

}

//Checks if the new date time is valid
void Scheduler::GUI::checkNewDateTimeValidity(ptime newDateTime, BrightIdeasSoftware::CellEditEventArgs^  e, Boolean startDateTime)
{
	string newDateTimeString = to_simple_string(newDateTime);

	//If invalid
	if(newDateTimeString == convertSysStringToStdString(NOT_A_DATE_TIME))
	{
		//Cancel the event and ignore any changes to the cell
		e->Cancel = true;
		updateStatus(convertSysStringToStdString(STATUS_INVALID_DATE_TIME));
	}
	//If valid
	else
	{
		//Commit changes
		changeDateTime(newDateTime, startDateTime);
		e->NewValue = (Object^)convertStdStringToSysString(to_simple_string(newDateTime));
	}
}

//Changes the date time of the particular edited item
void Scheduler::GUI::changeDateTime(ptime newDateTime, Boolean startDateTime)
{
	int displayIndex = getSelectedItemIndex();
	CommandBase* command;

	//Determine if date time is from DATEFROM or DATETO and create edit command
	if(startDateTime == true)
		command = new CommandEdit(CommandEdit::EDIT_START_DATETIME, displayIndex, newDateTime);
	else
		command = new CommandEdit(CommandEdit::EDIT_END_DATETIME, displayIndex, newDateTime);

	Display display = logic->executeShortCutCommand(command);

	updateStatus(display.getStatus());
}

//Determine if user is editing a floating task's start date time
bool Scheduler::GUI::editingFloatingTaskStartDateTime(bool startDateTime)
{
	if(startDateTime == false)
		return false;
	else
	{
		if(initialCellStringValue != EMPTY_STRING)
			return false;
		else
			return true;
	}
}

//Gets the index of the selected item
int Scheduler::GUI::getSelectedItemIndex()
{
	int index = this->objectListView->SelectedItem->Index;
	int displayIndex = index + 1;//Constant, not a magic number
	return displayIndex;
}

//Event handler
void Scheduler::GUI::eventHandled(System::Windows::Forms::KeyEventArgs^  e)
{
	e->Handled = true;
	e->SuppressKeyPress = true;
}

//Trims away the seconds from date time if seconds is not present
String^ Scheduler::GUI::trimSeconds(String^ dateTime)
{
	dateTime = dateTime->TrimEnd('0');
	dateTime = dateTime->TrimEnd(':');
	return dateTime;
}

//Toggle tutorial mode and start tutorial if tutorialMode = true
void Scheduler::GUI::toggleTutorial()
{
	tutorialMode = !tutorialMode;

	if(tutorialMode == true)
	{
		//Start tutorial
		Display display = logicTutorial->startTutorial();
		//Display display = logicTutorial->executeTutorial(convertSysStringToStdString(EMPTY_STRING));

		updateAllDisplay(display.getTaskList(), display.getStatus());
	}
	else
	{
		//Exit tutorial
		updateStatus(convertSysStringToStdString(TUTORIAL_EXITED));
		//this->objectListView->OverlayText->Text = EMPTY_STRING;

		this->objectListView->HideOverlays();
		this->objectListView->UseOverlays = false;
	}
}