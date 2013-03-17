//@author A0002927L

#ifndef PARSER_DATETIME_H
#define PARSER_DATETIME_H

#include <string>
#include <regex>
#include <map>
#include <array>
#include <boost\algorithm\string.hpp>
#include <boost\date_time.hpp>

#include "PairDateTime.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

//@author A0002927L
/**
 * This utility class handles the parsing of dates and times.
 * 
 * The client calls parseDateTime, parseTime, and parseDate, and parseTimePeriod.
 *
 * In addition, there are less useful methods, parseMonth, parseYear 
 * and ParseDay, which return integers. Will throw an 
 * invalid_argument exception if parsing has
 * failed.
 * 
 * parseDateTime() returns a ptime object. It contains both date and time.
 * If the format does not contain a date, it is taken as the current date.
 * Use this method unless you are sure that you need a date or a 
 * time specifically
 * 
 * parseTime() returns a time_duration. The string is taken to be a time ONLY
 * returns not_a_date_time if there is no proper format of a time
 *
 * parseDate() returns a date. The string is taken to be a date ONLY
 * returns not_a_date if there is no proper format of a date
 *
 * parseTimePeriod() returns a boost time period. This returns a
 * PairDateTime structure, with first beng the start and second being the end
 * datetime.
 * If parsing was unsuccessful, a nullTimePeriod will be returned.
 *
 * There are two additional constants - EarliestPossibleTime and LatestPossibleTime
 * EarliestPossibleTime: The starting time of the day.
 * LatestPossibleTime: The latest time of the day - for example: 23:59
 * These constants are used for the determination of start and end times when
 * the dates is entered, but the time is not
 *
*/

class ParserDateTime {
public:
	
	// Parses a given date time. Takes into account partial dates, shorthands
	// and various other formats.
	// - Use earliest = true if we want to assume shorthand dates to be 
	// be set to the earliest possible time, false if we want it to be 
	// the latest possible time.
	// - Use strictSyntax = true if you do not want
	// commonly used fragments eg. relatively common numbers like "2000" to 
	// affect possible parsing. For example, "2000", or "15" will no longer 
	// be regarded as DateTimes. 
	// - Use favourPassed if, in the case of 2 possible dates/times returned,
	// the date/time which is passed will be favoured over the nearest date
	// which has not passed
	// Returns not_a_date_time if the method was unable to parse the given
	// time.
	ptime parseDateTime(string input, 
						bool earliest = false, 
						bool strictSyntax = false,
						bool favourPassed = false);

	// Parsing of time only. Takes into account partial times. 
	// Examples of supported formats: 23:59, 2359, 10 (10AM), 22(10PM).
	// - Use strictSyntax = false if we do not want simple numeric dates
	// like 2100 to be parsed as a time. 
	time_duration parseTime(string input, 
							bool strictSyntax = false);

	// Parsing of a date. If the year is not stated, it is taken
	// as the coming year (after the current date), or this year(if it
	// is after the current date)
	// Examples of supported formats: 1-Jan, 1-Jan-2012, 1 Jan 2012,
	// 1/Jan/2012. 2012/01/01. Also supports specil dates like "Monday",
	// "Mon", "Tue", etc.
	date parseDate(string input, bool favourPassed = false);

	// Parsing of a time period. Takes a time period and parses it into 
	// a pair of ptimes. 
	// *NOTE* does not do any checking for validity of the time period.
	// EG. start time is allowed to be > end time.
	// Examples of supported formats: from 1 Jan to 5 May, 
	// 1 Jan to 5 May, 2359, from 2 Apr 2013, 2359 till 3 Apr.
	PairDateTime parseTimePeriod(string input, bool favourPassed = false);

	// These methods take a given month/day/year and parse them into their
	// integer equivalents. 
	// Throws: invalid argument if parsing was unsuccessful.
	// Parses a month - January = 1, December = 12.
	int parseMonth(string input);
	// Parses an integer day. Supports Ordinals, eg 1st, 2nd, 3rd, etc.
	// This does NOT check for invalid days, eg 50, 50th, etc. This does not
	// include Monday, Tuesday, Wednesday, etc
	int parseDay(string input);
	// Parses a year, eg. 4 digit year. Also supports shorthand like 12 (2012),
	// or 15(2015).
	int parseYear(string input);

	// This is a helper method to create a null-PairDateTime.
	PairDateTime makeNullPeriod();

	// Accessors for constants defined in this parser.
	static time_duration getLatestPossibleTime();
	static time_duration getEarliestPossibleTime();
private:
	// Standard calender constant
	static const int NUM_MONTHS = 12;
	static const int NUM_HOURS = 24;
	static const int NUM_MINUTES = 60;
	static const int NUM_DAYS_IN_WEEK = 7;

	// This is the cutoff year used for short representations of years
	// Eg. 12 == 2012
	static const int CUTOFF_REF_YEAR = 2000;

	// Minimum allowed year
	static const int MIN_YEAR = 0;

	// Maximum allowed value of shortened year
	static const int MAX_SHORTENED_YEAR = 100;

	// MAXIMUM allowed year
	static const int MAX_YEAR = 2099;

	static const string EMPTY_STRING;

	// Format for a time period
	static const string TIME_PERIOD_FORMAT;
	static const string DELIMITERS_TIME_PERIOD;
	static const int TIME_PERIOD_POS_EARLIER = 1;
	static const int TIME_PERIOD_POS_LATER = 2;

	// Delimiters between month/day/years
	static const string DELIMITERS;

	// Delimiters between the date and time
	static const string DATE_TIME_FORMAT;
	static const string DELIMITERS_DATE_TIME;
	static const int DATE_TIME_POS_DATE = 1;
	static const int DATE_TIME_POS_TIME = 2;
	static const int DATE_TIME_POS_SWAPPED_DATE = 2;
	static const int DATE_TIME_POS_SWAPPED_TIME = 1;

	// Delimiters between date and time for the swapped format
	static const string DELIMITERS_DATE_TIME_SWAPPED;
	static const string DATE_TIME_SWAPPED_FORMAT;

	// Full date format includes the year
	static const string DELIMITED_FULL_DATE_FORMAT;
	static const int NUM_DELIMITED_FULL_DATE_FORMATS = 3;
	// used for formats day-month-year
	static const int DELIMITED_FULL_DATE_POS_YEAR[NUM_DELIMITED_FULL_DATE_FORMATS];
	static const int DELIMITED_FULL_DATE_POS_MONTH[NUM_DELIMITED_FULL_DATE_FORMATS];
	static const int DELIMITED_FULL_DATE_POS_DAY[NUM_DELIMITED_FULL_DATE_FORMATS];

	// Partial date format 
	static const string DELIMITED_PARTIAL_DATE_FORMAT;
	static const int NUM_DELIMITED_PARTIAL_DATE_FORMATS = 2;
	static const int DELIMITED_PARTIAL_DATE_POS_MONTH[NUM_DELIMITED_PARTIAL_DATE_FORMATS];
	static const int DELIMITED_PARTIAL_DATE_POS_DAY[NUM_DELIMITED_PARTIAL_DATE_FORMATS];

	// Allowable formats for months
	static const string MONTH_FORMATS[NUM_MONTHS];

	// Separate date from time (if applicable). Returns true if there is a 
	// possible time in the input
	bool separateDateFromTime(string input, string& date, string& time);

	// Name of days
	enum Days {SUN = 0, MON, TUE, WED, THURS, FRI, SAT};
	static const int BOOST_DAYS[NUM_DAYS_IN_WEEK];
	static const string DAY_FORMATS[NUM_DAYS_IN_WEEK];

	// Constant strings for some special dates
	static const string TODAY_FORMATS;
	static const string TOMMOROW_FORMATS;

	// Ordinals for days
	static const array <string, 5> ORDINALS;

	// Latest possible time
	static const time_duration LATEST_POSSIBLE_TIME;
	static const time_duration EARLIEST_POSSIBLE_TIME;

	// Helper methods for parsing dates and times
	ptime parseDateTimeNormal(string input, 
							  bool earliest = false, 
						      bool strictSyntax = false,
						      bool favourPassed = false);
	ptime parseDateTimeSwapped(string input, 
							   bool earliest = false, 
						       bool strictSyntax = false,
						       bool favourPassed = false);

	// Parsing functions for dates
	date parseDelimitedFullDate(string input);
	// Parses a partial date (eg. year/month was left out)
	// In case of a date that has already passed, eg 1 Jan when it is 2 Jan, 
	// the method will return a date based on whether a passed date is favoured
	date parseDelimitedPartialDate(string input, bool favourPassed = false);
	// Parsing for special dates
	date parseToday(string input);
	date parseTommorow(string input);
	date parseSpecialDate(string input);	
	date parseWeekdayDays(string input);
	date parseNextWeek(string input);
	date parseConstantDate(string input, bool favourPassed = false);
	// Constants for this monday, next monday etc.
	static const string THIS_FORMATS;
	static const string NEXT_FORMATS;
	static const string NEXT_WEEK_FORMATS;

	static const int THIS_FORMAT_DAY_POS = 1;
	static const int NEXT_FORMAT_DAY_POS = 1;

	static const int NUM_CONSTANT_DATES = 2;
	static const string CONSTANT_DATES_FORMAT[NUM_CONSTANT_DATES];
	static const int CONSTANT_DATES_MONTH[NUM_CONSTANT_DATES];
	static const int CONSTANT_DATES_DAY[NUM_CONSTANT_DATES];

	// Regex format for time represented purely in numbers
	static const string NUMERIC_TIME_FORMAT;
	static const int NUMERIC_TIME_FORMAT_POS = 1;
	// used to separate minutes and hour
	static const int NUMERIC_TIME_MODULO = 100;	

	// Parsing a time represented solely by numbers 
	time_duration parseNumericTime(string input);
	// Extract the hours and minutes in a time represented solely by numbers
	void extractHoursMinutes(int numericTime, int& hours, int& minutes);

	static const string DELIMITED_TIME_FORMAT;
	static const string DELIMITERS_TIME;
	static const int DELIMITED_TIME_FORMAT_POS_HOURS;
	static const int DELIMITED_TIME_FORMAT_POS_MINUTES;

	// Parse a time with delimiters inside it
	time_duration parseDelimitedTime(string input);

	// Parse a special time
	time_duration parseSpecialTime(string input);
	// Helper methods for parsing special dates and times
	time_duration ParserDateTime::parseByNoon(string input);
	time_duration ParserDateTime::parseByMidnight(string input);

	static const string NOON_FORMATS;
	static const string MIDNIGHT_FORMATS;

	static const time_duration NOON_TIME;
	static const time_duration MIDNIGHT_TIME;

	// Parse a time with the format including AMs/and PMs at the back
	time_duration parseAmPm(string input);
	// Helper methods for parsing Am and Pm formats
	time_duration parseTimeAm(string input);
	time_duration parseTimePm(string input);

	// This method removes the given suffix from input, and stores the result
	// in output. Returns true if the given suffix was found.
	// Remarks: String comparison for the suffix is case insensitive.
	// Returns false if the suffix is shorter than the input.
	// If suffix is not found, the value of output is undefined.
	bool removeSuffix(string input, string& output, string suffix);

	static const string AM_KEYWORD;
	static const string PM_KEYWORD;
	
	// Converts the given hours and minutes into an actual time object
	time_duration computeTime(int hours, int minutes);

	// Extracts a decimal number from a string. Extracted decimal is stored in
	// output. 
	// Returns true if successful, ie, the string is a perfect integer,
	// no other unnecessary characters contaminating it. If allowOrdinals
	// is true, 1st, 2nd, 3rd, 4th etc are also allowed.
	// output will be ZERO if extraction is unsuccessful.
	bool extractDecimalNumber(string input, 
							  int& output, 
							  bool allowOrdinals = false);
};

#endif