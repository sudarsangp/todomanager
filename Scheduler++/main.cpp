#include <iostream>
#include <string>

#include "UI.h"
// unit tests. comment out to disable
#include "ParserTester.h"
#include "LogicTester.h"
#include "Tester.h"
#include "TutorialTester.h"

using namespace std;

int main(int argument_count, char** argument_vars) {
	runTest(argument_count, argument_vars); //run unit test. comment out to disable
	UI ui;
	string userInput;
	string feedback;

	while(1) {
		cout << "Command: ";

		getline(cin, userInput);
		feedback = ui.readUserInput(userInput);

		if( userInput == "quit" ) {
			exit(1);
		}

		cout << "Status: " << endl << feedback;
	}

	return 0;
}
