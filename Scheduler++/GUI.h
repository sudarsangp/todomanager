//@author A0081136M

#pragma once

#include "Logic.h"
#include "LogicTutorial.h"
#include <msclr\marshal_cppstd.h>
#include <boost\date_time.hpp>
#include "Item.h"
#include "CommandBase.h"
#include "Task.h"
#include "Display.h"
#include "ParserDateTime.h"
#include <string>
#include <vector>
#include "SchedulerPPException.h"

namespace Scheduler {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace boost::posix_time;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		Logic* logic;
		LogicTutorial* logicTutorial;
		GUI()
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			try
			{
				logic = Logic::getInstance();
			}
			catch(SchedulerPPException& e)
			{
				updateStatus(e.getMessage());
				logic = Logic::getInstance();
			}

			try
			{
				logicTutorial = LogicTutorial::getInstance();
			}
			catch(SchedulerPPException& e)
			{
				updateStatus(e.getMessage());
				logicTutorial = LogicTutorial::getInstance();
			}
		}

		

		static ArrayList^ commandList = gcnew ArrayList;
		static Int32 previousCommand = 0;
		static Int32 PREVIOUSCOMMAND_RESET = 0;
		static Int32 PREVIOUSCOMMAND_MINIMUM = 1;

		static String^ TEXTBOX_DEFAULT_MESSAGE = "Type your command here: Add, Delete, Edit, List, Clear, Done, Flag";
		
		static String^ LIST_DEFAULT_DATE_TIME = "";
		static String^ NOT_A_DATE_TIME = "not-a-date-time";

		static String^ STATUS_INVALID_DATE_TIME = "Invalid date time format";
		static String^ STATUS_INVALID_TASK_DESCRIPTION = "Invalid task description";
		static String^ STATUS_INVALID_TASK_TYPE = "Invalid edit for task type";

		static String^ DONE = "DONE";
		static String^ TASKNAME = "TASKNAME";
		static String^ PRIORITY = "PRIORITY";
		static String^ DATEFROM = "DATEFROM";
		static String^ DATETO = "DATETO";
		static String^ EMPTY_STRING = "";
		static String^ TUTORIAL_EXITED = "Tutorial Exited";

		static String^ OVERLAY_EMPTY = "LIST IS EMPTY";
		static String^ OVERLAY_TUTORIAL = "PRESS F1 TO EXIT TUTORIAL";

		static Int32 INITIAL_SORT_COLUMN = 0;
		static Int32 NO_SELECTED_INDEX = -1;
		static Int32 PAGE_SIZE = 20;
		static Int32 EMPTY = 0;

		static String^ initialCellStringValue;
		static Boolean initialCellBooleanValue;
		static Int32 initialCellIntValue;

		static Boolean tutorialMode = false;
		static Int32 page = 0;
		static Int32 PAGE_MINIMUM = 0;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	public: 

	public: 
		static String^ dateTime;

		enum class COLUMN {INDEX_INDEX, DONE_INDEX, TASKNAME_INDEX, PRIORITY_INDEX, DATEFROM_INDEX, DATETO_INDEX};

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: bool Checkinout;

	private: System::Windows::Forms::TextBox^  textBox;

	private: System::Windows::Forms::Label^  status;

	private: BrightIdeasSoftware::MultiImageRenderer^  multiImageRenderer1;
	private: BrightIdeasSoftware::ObjectListView^  objectListView;
	private: BrightIdeasSoftware::OLVColumn^  index;
	private: BrightIdeasSoftware::OLVColumn^  done;

	private: BrightIdeasSoftware::OLVColumn^  taskName;
	private: BrightIdeasSoftware::OLVColumn^  priority;
	private: BrightIdeasSoftware::OLVColumn^  dateFrom;
	private: BrightIdeasSoftware::OLVColumn^  dateTo;
	private: System::Windows::Forms::ImageList^  imageList;
	private: BrightIdeasSoftware::MultiImageRenderer^  multiImageRenderer2;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->textBox = (gcnew System::Windows::Forms::TextBox());
			this->status = (gcnew System::Windows::Forms::Label());
			this->imageList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->multiImageRenderer1 = (gcnew BrightIdeasSoftware::MultiImageRenderer());
			this->objectListView = (gcnew BrightIdeasSoftware::ObjectListView());
			this->index = (gcnew BrightIdeasSoftware::OLVColumn());
			this->done = (gcnew BrightIdeasSoftware::OLVColumn());
			this->multiImageRenderer2 = (gcnew BrightIdeasSoftware::MultiImageRenderer());
			this->taskName = (gcnew BrightIdeasSoftware::OLVColumn());
			this->priority = (gcnew BrightIdeasSoftware::OLVColumn());
			this->dateFrom = (gcnew BrightIdeasSoftware::OLVColumn());
			this->dateTo = (gcnew BrightIdeasSoftware::OLVColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->objectListView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox
			// 
			this->textBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(1) {L"Type your command here"});
			this->textBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->textBox->BackColor = System::Drawing::Color::White;
			this->textBox->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox->ForeColor = System::Drawing::Color::Silver;
			this->textBox->Location = System::Drawing::Point(12, 359);
			this->textBox->Name = L"textBox";
			this->textBox->Size = System::Drawing::Size(670, 26);
			this->textBox->TabIndex = 1;
			this->textBox->Text = L"Type your command here";
			this->textBox->Enter += gcnew System::EventHandler(this, &GUI::textBox_Enter);
			this->textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::textBox_KeyDown);
			this->textBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::textBox_KeyPress);
			this->textBox->Leave += gcnew System::EventHandler(this, &GUI::textBox_Leave);
			// 
			// status
			// 
			this->status->AutoEllipsis = true;
			this->status->BackColor = System::Drawing::Color::Transparent;
			this->status->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->status->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->status->Location = System::Drawing::Point(8, 317);
			this->status->Name = L"status";
			this->status->Size = System::Drawing::Size(670, 39);
			this->status->TabIndex = 4;
			this->status->Text = L"Welcome to Scheduler++! Press F1 to start tutorial.";
			this->status->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			// 
			// imageList
			// 
			this->imageList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList.ImageStream")));
			this->imageList->TransparentColor = System::Drawing::Color::Black;
			this->imageList->Images->SetKeyName(0, L"Flag-green.ico");
			this->imageList->Images->SetKeyName(1, L"tick.ico");
			// 
			// multiImageRenderer1
			// 
			this->multiImageRenderer1->ImageIndex = 0;
			this->multiImageRenderer1->ImageList = this->imageList;
			this->multiImageRenderer1->MaximumValue = 1;
			this->multiImageRenderer1->MaxNumberImages = 1;
			// 
			// objectListView
			// 
			this->objectListView->AllColumns->Add(this->index);
			this->objectListView->AllColumns->Add(this->done);
			this->objectListView->AllColumns->Add(this->taskName);
			this->objectListView->AllColumns->Add(this->priority);
			this->objectListView->AllColumns->Add(this->dateFrom);
			this->objectListView->AllColumns->Add(this->dateTo);
			this->objectListView->AllowColumnReorder = true;
			this->objectListView->AlternateRowBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->objectListView->AutoArrange = false;
			this->objectListView->BackColor = System::Drawing::Color::White;
			this->objectListView->CellEditActivation = BrightIdeasSoftware::ObjectListView::CellEditActivateMode::DoubleClick;
			this->objectListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->index, this->done, 
				this->taskName, this->priority, this->dateFrom, this->dateTo});
			this->objectListView->Cursor = System::Windows::Forms::Cursors::Default;
			this->objectListView->EmptyListMsg = L"";
			this->objectListView->EmptyListMsgFont = (gcnew System::Drawing::Font(L"Brush Script MT", 20.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->objectListView->Font = (gcnew System::Drawing::Font(L"Calibri", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->objectListView->ForeColor = System::Drawing::Color::Green;
			this->objectListView->FullRowSelect = true;
			this->objectListView->HideSelection = false;
			this->objectListView->HighlightBackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->objectListView->HighlightForegroundColor = System::Drawing::Color::White;
			this->objectListView->Location = System::Drawing::Point(-2, 64);
			this->objectListView->MultiSelect = false;
			this->objectListView->Name = L"objectListView";
			this->objectListView->OverlayImage->Alignment = System::Drawing::ContentAlignment::MiddleCenter;
			this->objectListView->OverlayImage->InsetX = 0;
			this->objectListView->OverlayImage->InsetY = 0;
			this->objectListView->OverlayImage->ShrinkToWidth = true;
			this->objectListView->OverlayText->Alignment = System::Drawing::ContentAlignment::BottomCenter;
			this->objectListView->OverlayText->BorderColor = System::Drawing::Color::Transparent;
			this->objectListView->OverlayText->Font = (gcnew System::Drawing::Font(L"Garamond", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->objectListView->OverlayText->Text = L"";
			this->objectListView->OverlayText->TextColor = System::Drawing::Color::Green;
			this->objectListView->OverlayText->Wrap = false;
			this->objectListView->OwnerDraw = true;
			this->objectListView->SelectedColumnTint = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->objectListView->ShowGroups = false;
			this->objectListView->Size = System::Drawing::Size(698, 250);
			this->objectListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->objectListView->TabIndex = 6;
			this->objectListView->TintSortColumn = true;
			this->objectListView->UnfocusedHighlightBackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->objectListView->UnfocusedHighlightForegroundColor = System::Drawing::Color::White;
			this->objectListView->UseCompatibleStateImageBehavior = false;
			this->objectListView->UseCustomSelectionColors = true;
			this->objectListView->View = System::Windows::Forms::View::Details;
			this->objectListView->CellEditFinishing += gcnew BrightIdeasSoftware::CellEditEventHandler(this, &GUI::objectListView_CellEditFinishing);
			this->objectListView->CellEditStarting += gcnew BrightIdeasSoftware::CellEditEventHandler(this, &GUI::objectListView_CellEditStarting);
			this->objectListView->Enter += gcnew System::EventHandler(this, &GUI::objectListView_Enter);
			this->objectListView->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::objectListView_KeyDown);
			this->objectListView->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GUI::objectListView_KeyPress);
			// 
			// index
			// 
			this->index->AspectName = L"INDEX";
			this->index->IsEditable = false;
			this->index->Text = L"Index";
			this->index->Width = 48;
			// 
			// done
			// 
			this->done->AspectName = L"DONE";
			this->done->HeaderTextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->done->ImageAspectName = L"DONE";
			this->done->IsEditable = false;
			this->done->Renderer = this->multiImageRenderer2;
			this->done->Text = L"Done (D)";
			this->done->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->done->Width = 65;
			// 
			// multiImageRenderer2
			// 
			this->multiImageRenderer2->ImageIndex = 1;
			this->multiImageRenderer2->ImageList = this->imageList;
			this->multiImageRenderer2->MaximumValue = 1;
			this->multiImageRenderer2->MaxNumberImages = 1;
			// 
			// taskName
			// 
			this->taskName->AspectName = L"TASKNAME";
			this->taskName->Text = L"Description (E)";
			this->taskName->Width = 273;
			// 
			// priority
			// 
			this->priority->AspectName = L"PRIORITY";
			this->priority->AspectToStringFormat = L"";
			this->priority->HeaderTextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->priority->ImageAspectName = L"PRIORITY";
			this->priority->IsEditable = false;
			this->priority->Renderer = this->multiImageRenderer1;
			this->priority->Text = L"Flag (F)";
			this->priority->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->priority->Width = 56;
			// 
			// dateFrom
			// 
			this->dateFrom->AspectName = L"DATEFROM";
			this->dateFrom->Text = L"From (R)";
			this->dateFrom->Width = 125;
			// 
			// dateTo
			// 
			this->dateTo->AspectName = L"DATETO";
			this->dateTo->Text = L"To (T)";
			this->dateTo->Width = 125;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Brush Script MT", 27.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Green;
			this->label1->Location = System::Drawing::Point(68, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(200, 46);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Scheduler++";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(12, 8);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(50, 50);
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(694, 393);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->objectListView);
			this->Controls->Add(this->status);
			this->Controls->Add(this->textBox);
			this->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"GUI";
			this->Text = L"Scheduler++";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->objectListView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		private: 
			System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e);
			System::Void textBox_Enter(System::Object^  sender, System::EventArgs^  e);
			System::Void textBox_Leave(System::Object^  sender, System::EventArgs^  e);
			System::Void textBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
			System::Void textBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			System::Void objectListView_Enter(System::Object^  sender, System::EventArgs^  e);
			System::Void objectListView_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
			System::Void objectListView_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			System::Void objectListView_CellEditStarting(System::Object^  sender, BrightIdeasSoftware::CellEditEventArgs^  e);
			System::Void objectListView_CellEditFinishing(System::Object^  sender, BrightIdeasSoftware::CellEditEventArgs^  e);


			String^ convertStdStringToSysString(std::string stdstring);
			std::string convertSysStringToStdString(String^ sysString);

			void updateObjectListView(vector<Task> displayVector);
			void updateStatus(string statusMessage);
			void updateAllDisplay(vector<Task> displayVector, string statusMessage);
			Object^ initializeItem(int i, Task task);

			void checkPageWithinLimit(int& newPage);
			void updatePage(int page);

			void checkIndexWithinLimit(int& previousCommand);
			void updateTextBox(int previousCommand);

			void deleteSelectedItem();
			void toggleSelectedItemDone();
			void toggleSelectedItemFlag();

			void checkDoneChange(BrightIdeasSoftware::CellEditEventArgs^  e);
			void checkTaskNameChange(BrightIdeasSoftware::CellEditEventArgs^  e);
			void checkPriorityChange(BrightIdeasSoftware::CellEditEventArgs^  e);
			void checkDateTimeChange(BrightIdeasSoftware::CellEditEventArgs^  e, Boolean startDateTime);
			void checkNewDateTimeValidity(ptime newDateTime, BrightIdeasSoftware::CellEditEventArgs^  e, Boolean startDateTime);
			void changeDateTime(ptime newDateTime, Boolean startDateTime);
			bool editingFloatingTaskStartDateTime(bool startDateTime);

			int getSelectedItemIndex();
			void eventHandled(System::Windows::Forms::KeyEventArgs^  e);
			String^ trimSeconds(String^ dateTime);
			void toggleTutorial();

/*
	private: void loadSampleItems()
			 {
				 ptime empty;
				 ptime start(second_clock::local_time());
				 days delay(1);
				 ptime endTemp(second_clock::local_time());
				 ptime end = endTemp + delay;


				 vector<Task> sampleDisplay;

				 Task sampleTask1 = Task("Sample Task 1", 0, Task::FLOATING, true, 1, empty, empty);
				 Task sampleTask2 = Task("Sample Task 2", 1, Task::DEADLINE, false, 0, empty, end);
				 Task sampleTask3 = Task("Sample Task 3", 2, Task::TIMED, false, 1, start, end);

				 sampleDisplay.push_back(sampleTask1);
				 sampleDisplay.push_back(sampleTask2);
				 sampleDisplay.push_back(sampleTask3);

				 updateObjectListView(sampleDisplay);

				 this->objectListView->UseOverlays = true;
			 }
*/




};
};