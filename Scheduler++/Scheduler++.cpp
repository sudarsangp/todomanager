// Scheduler++.cpp : main project file.

#include "Logic.h"
#include "GUI.h"


using namespace Scheduler;

[STAThreadAttribute]
int main()
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 



	// Create the main window and run it
	Application::Run(gcnew GUI());
	return 0;
}
