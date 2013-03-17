//@author A0002927L

#ifndef PARSER_BASE_H
#define PARSER_BASE_H

#include <string>
#include <regex>
#include <boost\algorithm\string.hpp>
#include <boost\date_time.hpp>
#include <stdexcept>
#include "ParserDateTime.h"
#include "CommandBase.h"
#include "ParsingException.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::algorithm;
using namespace boost::gregorian;

/**
 * This forms the base class of the parser. Commands are entered fed into
 * objects of this class. If this class cannot parse the command, it will 
 * pass the request on to the next class in the chain of responsibility.
 *
 * This class also contains many helpful utility methods that many subclasses
 * may find helpful when parsing user commands. In particular, it contains 
 * several date and time parsing methods.
 *
 @author Ling Chun Kai
*/
class ParserBase {
public:
	// Constructs an instance of the ParserBase class. Sets the sucessor
	// of this instance to be _nextParser
	ParserBase(ParserBase* _nextParser);
	
	// Returns a command of type commandBase containing the parsed information.
	virtual CommandBase* parseUserCommand(string userCommand);

	// The next handler to have a shot at parsing this command should this
	// instance of parser fail to accurately parse the given command
	ParserBase* nextParser;

protected:
	static const string EMPTY_STRING;
	static const char SPACE = ' ';
	
	// Expression for "listed/displayed" tasks. Used frequently by many 
	// Parser derived classes.
	static const string regexArgsListed;

	// This method attempts to parse the user command, and returns true
	// if successful. It also reads fills the parsedCommand reference with
	// relevenat data if and only if the parsing was successful.
	virtual CommandBase* tryParse(string userCommand) = 0;

	// *****************************************************************
	//				HELPER METHODS COMMONLY USED BY ALL PARSERS
	// *****************************************************************

	// Date/Time parser. This method reads in a single string.
	// Returns a boost::date_time::posix_time coressponding to the string input
	// The input may or may not include the time.
	ptime parseDateTime(const string& timeStr, bool earliest = false);

	// This method parses a string containing the time. 
	// Returns a time_duration object coressponding to that time. The time passed
	// should be < 24 hours. It will return not_a_date_time if there is
	// an unrecognized syntax, or if the time parsed is >= 24 hrs.
	time_duration parseTime(const string& timeStr);

	// This method parses a date, without the time. 
	// Returns: a ptime object containing the date, with time set to 23:59.
	// Returns not_a_date_time if parsing was unsuccessful.
	ptime parseDate(const string& timeStr);

	// This method parses a time period
	// Returns: a PairDateTime containing the start and end time
	// Returns a null period if parsing was unsuccessful.
	PairDateTime parseTimePeriod(const string& periodStr);

	// Given a string input, finds if there is any date/time/datetime/time 
	// period within which gives us a valid parsed date time. The string 
	// must either begin at the start, or ends at the end of the string provided
	// Returns: On the successful finding of a date/time/datetime,
	// a ptime object containing the date/time parsed.
	// In addition, the contents of output ar also filled with the portion
	// of the string which does not contain the parsed date time.
	// In the event that multiple possible matches are found. Priority is given
	// to the string where the date/time is located at the back. The longest
	// possible valid date/time is then used
	// When finding of a date and time is not successful, not_a_date_time
	// is returned. Output will be filled with an empty string.
	ptime extractDateTime(string input, 
						  string& output, 
						  vector<string>& prefixes = vector<string>());
	PairDateTime extractTimePeriod(string input, string& output);
	// Helper methods for the above extraction methods
	ptime extractDateTimeBack(string input,
							  string& output,
							  vector<string>& prefixes);
	ptime extractDateTimeFront(string input, string& output);
	PairDateTime extractTimePeriodBack(string input, string& output);
	PairDateTime extractTimePeriodFront(string input, string& output);
	
	// This method aids in extracting a task ID from a particular field
	// from matching arguments. 
	// Returns the extracted taskID. This will raise an ASSERTION 
	// if the matchingArgument is NOT a valid number
	int getTaskIDFromArgument(string argument);

	// These methods return the last/first day of the week/month containing the 
	// given datetime.
	ptime getLastOfWeek(ptime curDateTime);
	ptime getLastOfMonth(ptime curDateTime);
	ptime getLastOfDay(ptime curDateTime);
	ptime getFirstOfMonth(ptime curDateTime);
	ptime getFirstOfWeek(ptime curDateTime);
	ptime getFirstOfDay(ptime curDateTime);

	// This method returns an integer representation of the month entered
	int parseMonth(const string& monthStr);

	// Utility string management methods
	string stripWhiteSpaces(string input);
	string removePrefixes(string input, vector<string>& prefixes);
private:
	static const int NUM_HOURS_IN_DAY = 24;
	static ParserDateTime parserDateTime;
};

#endif