//@author A0002927L

#include "ParserDateTime.h"

const string ParserDateTime::EMPTY_STRING = "";
const string ParserDateTime::DELIMITERS_TIME_PERIOD =
	"(?:"
	"to|till|untill|until"
	")";
const string ParserDateTime::TIME_PERIOD_FORMAT = 
	"\\s*(?:from\\s+)?(\\S.*?)" +
	DELIMITERS_TIME_PERIOD +
	"\\s+(\\S.*?)\\s*";

const string ParserDateTime::DELIMITERS_DATE_TIME = 
	"(?:,| at |@| by )";
const string ParserDateTime::DATE_TIME_FORMAT =
	"\\s*(.+?)\\s*"
	"(?:" + ParserDateTime::DELIMITERS_DATE_TIME + 
	"\\s*(.+?)\\s*)?";

const string ParserDateTime::DELIMITERS_DATE_TIME_SWAPPED =
	"(?:,| on )";
const string ParserDateTime::DATE_TIME_SWAPPED_FORMAT  = 
	"\\s*(.+?)\\s*" + 
	ParserDateTime::DELIMITERS_DATE_TIME_SWAPPED +
	"\\s*(.+?)\\s*";

const string ParserDateTime::DELIMITERS =
	"[\t:/ .-]";
const string ParserDateTime::DELIMITED_FULL_DATE_FORMAT = 
	"\\s*" 
	"([[:alnum:]]+)" +
	ParserDateTime::DELIMITERS + "+" +
	"([[:alnum:]]+)" +
	ParserDateTime::DELIMITERS + "+" +
	"([[:alnum:]]+)" +
	"\\s*";
const string ParserDateTime::MONTH_FORMATS[NUM_MONTHS] = { 
	"january|jan|01|1", 
	"febuary|feb|02|2", 
	"march|mar|03|3", 
    "april|apr|04|4", 
	"may|may|05|5", 
	"june|jun|06|6", 
    "july|jul|07|7", 
	"august|aug|08|8", 
	"september|sep|sept|09|9", 
    "october|oct|10", 
	"november|nov|11", 
	"december|dec|12" 
};

const int ParserDateTime::BOOST_DAYS[NUM_DAYS_IN_WEEK] = 
	{Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

const string ParserDateTime::DELIMITED_PARTIAL_DATE_FORMAT = 
	"\\s*" 
	"([[:alnum:]]+)" +
	ParserDateTime::DELIMITERS + "+" +
	"([[:alnum:]]+)" +
	"\\s*";

const string ParserDateTime::NUMERIC_TIME_FORMAT = 
	"\\s*"
	"([[:d:]]+)" 
	"\\s*";

const string ParserDateTime::DELIMITERS_TIME = "[:.]";
const string ParserDateTime::DELIMITED_TIME_FORMAT = 
	"\\s*([[:d:]]+)" + DELIMITERS_TIME + "([[:d:]]+)\\s*";

const string ParserDateTime::NOON_FORMATS = "\\s*(noon|(12\\s+noon))\\s*";
const string ParserDateTime::MIDNIGHT_FORMATS = "\\s*(midnight)\\s*";

const time_duration ParserDateTime::NOON_TIME = time_duration(12, 0, 0, 0);
const time_duration ParserDateTime::MIDNIGHT_TIME = time_duration(0, 0, 0, 0);

const int ParserDateTime::DELIMITED_TIME_FORMAT_POS_HOURS = 1;
const int ParserDateTime::DELIMITED_TIME_FORMAT_POS_MINUTES = 2;

// Full date regex positions
const int ParserDateTime::
	DELIMITED_FULL_DATE_POS_YEAR[NUM_DELIMITED_FULL_DATE_FORMATS] = {3, 1, 3};
const int ParserDateTime::
	DELIMITED_FULL_DATE_POS_MONTH[NUM_DELIMITED_FULL_DATE_FORMATS] = {2, 2, 1};
const int ParserDateTime::
	DELIMITED_FULL_DATE_POS_DAY[NUM_DELIMITED_FULL_DATE_FORMATS] = {1, 3, 2};

// Partial date regex positions
const int ParserDateTime::
	DELIMITED_PARTIAL_DATE_POS_MONTH[NUM_DELIMITED_PARTIAL_DATE_FORMATS] = {2, 1};
const int ParserDateTime::
	DELIMITED_PARTIAL_DATE_POS_DAY[NUM_DELIMITED_PARTIAL_DATE_FORMATS] = {1, 2};

const string ParserDateTime::DAY_FORMATS[NUM_DAYS_IN_WEEK] = { 
	"(sun|sunday)",
	"(mon|monday)",
	"(tues|tue|tuesday)",
	"(wed|wednesday)",
	"(thu|thur|thurs|thursday)",
	"(fri|friday)",
	"(sat|saturday)"
};

const string ParserDateTime::TODAY_FORMATS = "(today|tdy)";
const string ParserDateTime::TOMMOROW_FORMATS = "(tomorrow|tommorow|tmr|tml)";

const time_duration ParserDateTime::LATEST_POSSIBLE_TIME = time_duration(23, 59, 0, 0);
const time_duration ParserDateTime::EARLIEST_POSSIBLE_TIME = time_duration(0, 0, 0, 0);

const array <string, 5> ParserDateTime::ORDINALS = 
	{{string("th"), string("st"), string("nd"), string("rd"), string("th")}};

const string ParserDateTime::AM_KEYWORD = "am";
const string ParserDateTime::PM_KEYWORD = "pm";

const string ParserDateTime::THIS_FORMATS = "\\s*(?:this(?:\\s+coming)?)\\s+(.*)";
const string ParserDateTime::NEXT_FORMATS = "\\s*(?:next)\\s+(.*)";

const string ParserDateTime::NEXT_WEEK_FORMATS = "\\s*next\\s+week\\s*";

// Constant Date formats
const string ParserDateTime::CONSTANT_DATES_FORMAT[NUM_CONSTANT_DATES] = {
	"\\s*christmas\\s*",
	"\\s*new year\\s*"
};
const int ParserDateTime::CONSTANT_DATES_DAY[NUM_CONSTANT_DATES] = {
	25,
	1
};

const int ParserDateTime::CONSTANT_DATES_MONTH[NUM_CONSTANT_DATES] = {
	12,
	1
};

PairDateTime ParserDateTime::parseTimePeriod(string input, bool favourPassed) {
	regex timePeriodFormat(TIME_PERIOD_FORMAT, regex_constants::icase);
	smatch matchResults;
	// Attempt to match this to a recognized time period format
	if (!regex_match(input, matchResults, timePeriodFormat)) {
		return makeNullPeriod();
	}

	ptime earlier = parseDateTime(matchResults[TIME_PERIOD_POS_EARLIER], 
								  true, 
								  false, 
								  favourPassed);
	ptime later = parseDateTime(matchResults[TIME_PERIOD_POS_LATER], 
								false, 
								false, 
								favourPassed);

	// If earlier is a date and later is a time,
	// we can choose later to be the same day as earlier. 
	time_duration timeParsed = parseTime(matchResults[TIME_PERIOD_POS_LATER]);
	if (!earlier.is_not_a_date_time() && !timeParsed.is_not_a_date_time()) {
		return PairDateTime(earlier, ptime(earlier.date(), timeParsed));
	}

	// Test for earlier and later being dates/datetimes
	if (!earlier.is_not_a_date_time() && !later.is_not_a_date_time()) {
		return PairDateTime(earlier, later);
	}

	return makeNullPeriod();
}

ptime ParserDateTime::parseDateTime(string input,
									bool earliest,
									bool strictSyntax,
									bool favourPassed) {
	// Parse as standard format: <date> <time>
	ptime parsedTime = parseDateTimeNormal(input, earliest, strictSyntax, favourPassed);
	if (!parsedTime.is_not_a_date_time()) {
		return parsedTime;
	}

	// Parse as reversed format: <time> <date>
	parsedTime = parseDateTimeSwapped(input, earliest, strictSyntax, favourPassed);
	return parsedTime;
}

ptime ParserDateTime::parseDateTimeNormal(string input, 
										  bool earliest,
									      bool strictSyntax,
									      bool favourPassed) {
	ptime parsedDate;
	time_duration parsedTime = seconds(0);
	ptime combinedDateTime;

	string stringDate, stringTime;

	// Check if there is a time component available
	bool containsTime;
	containsTime = separateDateFromTime(input, stringDate, stringTime);
	
	// Parse the time first, if it was included
	if (containsTime) {
		parsedTime = parseTime(stringTime);	
		if (parsedTime.is_not_a_date_time()) {
			// directly return invalid date if what is supposed to be a time
			// is not a valid time
			return not_a_date_time;
		}
	}else if (earliest == false) {
		parsedTime = LATEST_POSSIBLE_TIME;
		// String does not contain time, defaulted to LASTEST_POSSIBLE_TIME
	}else if (earliest == true) {
		parsedTime = EARLIEST_POSSIBLE_TIME;
	}
	
	// Parse the date portion 
	parsedDate = ptime(parseDate(stringDate, favourPassed));

	if (!parsedDate.is_not_a_date_time()) {
		combinedDateTime = parsedDate + parsedTime;
	}else{
		// attempt to parse as time only - date taken as today.
		ptime timeOnly = 
			ptime(date(second_clock::local_time().date())) 
					 + parseTime(input, strictSyntax);
		if (!timeOnly.is_not_a_date_time()) {
			combinedDateTime = timeOnly;
		}else {
			combinedDateTime = not_a_date_time;
		}
	}
	
	return combinedDateTime;
}

ptime ParserDateTime::parseDateTimeSwapped(string input, 
										   bool earliest, 
										   bool strictSyntax,
										   bool favourPassed) {

	// Separate date from time in the reversed format
	regex dateTimeFormat(DATE_TIME_SWAPPED_FORMAT, regex_constants::icase);
	smatch matchingResult;

	if (!regex_match(input, matchingResult, dateTimeFormat)) {
		return not_a_date_time;
	}

	string dateString = matchingResult[DATE_TIME_POS_SWAPPED_DATE];
	string timeString = matchingResult[DATE_TIME_POS_SWAPPED_TIME];

	date parsedDate = parseDate(dateString, favourPassed);
	time_duration parsedTime = parseTime(timeString, strictSyntax);

	if (!(parsedDate.is_not_a_date() || parsedTime.is_not_a_date_time())) {
		return ptime(parsedDate, parsedTime);
	}
	return not_a_date_time;
}

bool ParserDateTime::separateDateFromTime(string input, 
										string& date, 
										string& time) {
	regex dateTimeFormat(DATE_TIME_FORMAT, regex_constants::icase);

	date = EMPTY_STRING;
	time = EMPTY_STRING;
	smatch matchingResult;

	if (!regex_match(input, matchingResult, dateTimeFormat)) {
		return false;
	}

	date = matchingResult[DATE_TIME_POS_DATE];

	if (matchingResult[DATE_TIME_POS_TIME].matched) {
		time = matchingResult[DATE_TIME_POS_TIME];
		return true;
	}

	return false;
}

time_duration ParserDateTime::parseTime(string input, bool strictSyntax) {
	time_duration timeParsed = not_a_date_time;

	// Try to parse as Numeric time, do not allow pure numeric time if
	// syntax is strict.
	timeParsed = parseNumericTime(input);
	if (timeParsed != not_a_date_time && !strictSyntax) {
		return timeParsed;
	}

	// Try to pasrse as Delimited Time
	timeParsed = parseDelimitedTime(input);
	if (timeParsed != not_a_date_time) {
		return timeParsed;
	}
	
	// Attempt to parse times in AM/PM formats
	timeParsed = parseAmPm(input);
	if (!timeParsed.is_not_a_date_time()) {
		return timeParsed;
	}

	// Attempt to parse special times
	timeParsed = parseSpecialTime(input);
	if (!timeParsed.is_pos_infinity()) {
		return timeParsed;
	}

	// Developers may add additional formats here.

	return timeParsed;
}

date ParserDateTime::parseDate(string input, bool favourPassed) {
	date returnedDate;
	//	 Try to parse as delimited full date
	returnedDate = parseDelimitedFullDate(input);
	// Try to parse as partial date
	if (returnedDate.is_not_a_date()) {
		returnedDate = parseDelimitedPartialDate(input, favourPassed);
	}
	// Try to parse as a special date
	if (returnedDate.is_not_a_date()) {
		returnedDate = parseSpecialDate(input);
	}

	// Try to parse as a constant date
	if (returnedDate.is_not_a_date()) {
		returnedDate = parseConstantDate(input, favourPassed);
	}

	// Developers may add additional date formats here

	return returnedDate;
}

time_duration ParserDateTime::getLatestPossibleTime() {
	return LATEST_POSSIBLE_TIME;
}

time_duration ParserDateTime::getEarliestPossibleTime() {
	return EARLIEST_POSSIBLE_TIME;
}

date ParserDateTime::parseDelimitedFullDate(string input) {
	date parsedDate;

	regex fullDateFormat(DELIMITED_FULL_DATE_FORMAT,
						 regex_constants::icase);
	smatch matchResults;

	// Attempt to match this to a recognized date format
	if (!regex_match(input, matchResults, fullDateFormat)) {
		return date(not_a_date_time);
	}

	for (int x = 0; x < NUM_DELIMITED_FULL_DATE_FORMATS; x++) {
		try {
		parsedDate = date(parseYear(matchResults[DELIMITED_FULL_DATE_POS_YEAR[x]]),
						parseMonth(matchResults[DELIMITED_FULL_DATE_POS_MONTH[x]]),
						parseDay(matchResults[DELIMITED_FULL_DATE_POS_DAY[x]]));
		}catch(std::exception) { // exception is thrown when date is not valid
			continue;
		}
		// break out of loop if we found a valid parsing format
		if (!parsedDate.is_not_a_date()) {
			break;
		}
	}
	
	return parsedDate;
}

date ParserDateTime::parseDelimitedPartialDate(string input, bool favourPassed) {
	date parsedDate;

	regex partialDateFormat(DELIMITED_PARTIAL_DATE_FORMAT,
							regex_constants::icase);
	smatch matchResults;

	// Attempt to match this to a partial date format
	if (!regex_match(input, matchResults, partialDateFormat)) {
		return date(not_a_date_time);
	}
	
	for (int x = 0; x < NUM_DELIMITED_PARTIAL_DATE_FORMATS; x++) {
		try {
			parsedDate = date(second_clock::local_time().date().year(),
				parseMonth(matchResults[DELIMITED_PARTIAL_DATE_POS_MONTH[x]]),
				parseDay(matchResults[DELIMITED_PARTIAL_DATE_POS_DAY[x]]));
		}catch(std::exception) { // exception is thrown when date is not valid
			parsedDate = date(not_a_date_time);
		}
	
		// return closest date/time that has not passed
		if (!parsedDate.is_not_a_date() && !favourPassed) {
			if (parsedDate < second_clock::local_time().date()) {
				parsedDate += years(1);
			}
		}
		// Break out once we find a matching partial date format
		if (!parsedDate.is_not_a_date()) {
			break;
		}
	}
	return  parsedDate;
}

date ParserDateTime::parseSpecialDate(string input) {
	// Parse Today
	date returnDate = parseToday(input);
	if (!returnDate.is_not_a_date()) {
		return returnDate;
	}

	// Parse tommorow
	returnDate = parseTommorow(input);
	if (!returnDate.is_not_a_date()) {
		return returnDate;
	}

	// Parse weekday days
	returnDate = parseWeekdayDays(input);
	if (!returnDate.is_not_a_date()) {
		return returnDate;
	}

	// Parse next week
	returnDate = parseNextWeek(input);
	if (!returnDate.is_not_a_date()) {
		return returnDate;
	}

	return date(not_a_date_time);
}

date ParserDateTime::parseToday(string input) {
	regex dayFormat(TODAY_FORMATS, regex_constants::icase);
	if (regex_match(input, dayFormat)) {
		return second_clock::local_time().date();
	}
	return date(not_a_date_time);
}

date ParserDateTime::parseTommorow(string input) {
	regex dayFormat(TOMMOROW_FORMATS, regex_constants::icase);
	if (regex_match(input, dayFormat)) {
		return second_clock::local_time().date() + days(1);
	}
	return date(not_a_date_time);
}

date ParserDateTime::parseWeekdayDays(string input) {
	bool nextWeek = false;
	string trimmedInput = input;
	smatch matchingResults;
	if (regex_match(input, matchingResults, 
					regex(THIS_FORMATS, regex_constants::icase))) {
		nextWeek = false;
		trimmedInput = matchingResults[THIS_FORMAT_DAY_POS];
	}else if(regex_match(input, matchingResults, 
						regex(NEXT_FORMATS, regex_constants::icase))) {
		nextWeek = true;
		trimmedInput = matchingResults[NEXT_FORMAT_DAY_POS];
	}

	int dayIndex = -1;
	// Parse Days in strings
	for (int  x = 0; x < NUM_DAYS_IN_WEEK; x++) {
		regex dayFormat(DAY_FORMATS[x], regex_constants::icase);
		if (regex_match(trimmedInput, dayFormat)) {
			dayIndex = x;
			break;
		}
	}
	if (dayIndex < 0) {
		return date(not_a_date_time);
	}
	
	date returnedDate;
	if (nextWeek) {
		returnedDate = next_weekday(second_clock::local_time().date(), 
								greg_weekday(boost::date_time::Sunday));
		returnedDate = next_weekday(returnedDate, 
								greg_weekday(BOOST_DAYS[dayIndex]));
	}else {
		returnedDate = next_weekday(second_clock::local_time().date(),
								greg_weekday(BOOST_DAYS[dayIndex]));
	}
	return returnedDate;

}

date ParserDateTime::parseNextWeek(string input) {
	regex dayFormat = regex(NEXT_WEEK_FORMATS, regex_constants::icase);
	if (regex_match(input, dayFormat)) {
		return second_clock::local_time().date() + days(NUM_DAYS_IN_WEEK);
	}
	return date(not_a_date_time);
}

date ParserDateTime::parseConstantDate(string input, bool favourPassed) {
	for (int i = 0; i < NUM_CONSTANT_DATES; i++) {
		regex dayFormat(CONSTANT_DATES_FORMAT[i], regex_constants::icase);
		if (regex_match(input, dayFormat)) {
			date today = second_clock::local_time().date();
			date parseDate = date(today.year(),
								  CONSTANT_DATES_MONTH[i], 
								  CONSTANT_DATES_DAY[i]);
			// Add one year if it has passed
			bool hasPassed = today > parseDate;
			if (!favourPassed && hasPassed) {
				parseDate = parseDate + years(1);
			}
			return parseDate;
		}
	}
	return date(not_a_date_time);
}

time_duration ParserDateTime::parseNumericTime(string input) {

	// Extract relevant parts of the numeric time
	regex timeFormat(NUMERIC_TIME_FORMAT,
					 regex_constants::icase);
	smatch matchResults;
	if (!regex_match(input, matchResults, timeFormat)) {
		return not_a_date_time;
	}

	int time;
	int hours;
	int minutes;

	// Extract numeric time from string
	bool successExtractNumericTime = extractDecimalNumber(input, time);
	if (!successExtractNumericTime) {
		return not_a_date_time;
	}

	// Extract hours and minutes from numbers
	extractHoursMinutes(time, hours, minutes);
	
	return computeTime(hours, minutes);
}

time_duration ParserDateTime::parseDelimitedTime(string input) {
	regex timeFormat(DELIMITED_TIME_FORMAT,
					 regex_constants::icase);
	smatch matchResults;
	if (!regex_match(input, matchResults, timeFormat)) {
		return not_a_date_time;
	}

	int hours;
	int minutes; 

	bool extractSuccess = 
		extractDecimalNumber(matchResults[DELIMITED_TIME_FORMAT_POS_HOURS], hours) && 
		extractDecimalNumber(matchResults[DELIMITED_TIME_FORMAT_POS_MINUTES], minutes);

	if (!extractSuccess) {
		return not_a_date_time;
	}

	return computeTime(hours, minutes);
}

time_duration ParserDateTime::parseSpecialTime(string input) {
	time_duration returnTime = parseByMidnight(input);
	if (!returnTime.is_not_a_date_time()) {
		return returnTime;
	}

	returnTime = parseByNoon(input);
	if (!returnTime.is_not_a_date_time()) {
		return returnTime;
	}

	// developers may add in more special times here
	return not_a_date_time;
}

time_duration ParserDateTime::parseAmPm(string input) {
	boost::algorithm::trim(input);
	if (input.length() <= 0) {
		return not_a_date_time;
	}
	assert(input.at(0) != ' ' && input.back() != ' ');

	time_duration returnedTime = parseTimeAm(input);
	if (!returnedTime.is_not_a_date_time()) {
		return returnedTime;
	}
	returnedTime = parseTimePm(input);
	if (!returnedTime.is_not_a_date_time()) {
		return returnedTime;
	}
	return not_a_date_time;
}

// Attempts to parse by special times
time_duration ParserDateTime::parseByNoon(string input) {
	regex dayFormat(NOON_FORMATS, regex_constants::icase);
	if (regex_match(input, dayFormat)) {
		return NOON_TIME;
	}
	return time_duration(not_a_date_time);
}

time_duration ParserDateTime::parseByMidnight(string input) {
	regex dayFormat(MIDNIGHT_FORMATS, regex_constants::icase);
	if (regex_match(input, dayFormat)) {
		return MIDNIGHT_TIME;
	}
	return time_duration(not_a_date_time);
}

// Attempts to parse a certain time by AM/PM formats. Assumes whitespaces
// have already been trimmed
time_duration ParserDateTime::parseTimeAm(string input) {
	string prefix;
	if (!removeSuffix(input, prefix, AM_KEYWORD)) {
		return not_a_date_time;
	}
	
	time_duration timeParsed;
	// attempt to parse as delimited format
	timeParsed = parseDelimitedTime(prefix);
	if (timeParsed.is_not_a_date_time()) {
		// attempt to parse as numeric format
		timeParsed = parseNumericTime(prefix);
	}

	if (timeParsed.is_not_a_date_time()) {
		return not_a_date_time;
	}

	// ensure that we do not have times past 12
	if (timeParsed.hours() >= NUM_HOURS/2) {
		return not_a_date_time;
	}
	return timeParsed;
}

time_duration ParserDateTime::parseTimePm(string input) {
	string prefix;
	if (!removeSuffix(input, prefix, PM_KEYWORD)) {
		return not_a_date_time;
	}
	
	time_duration timeParsed;
	// attempt to parse as delimited format
	timeParsed = parseDelimitedTime(prefix);
	if (timeParsed.is_not_a_date_time()) {
		// attempt to parse as numeric format
		timeParsed = parseNumericTime(prefix);
	}

	if (timeParsed.is_not_a_date_time()) {
		return not_a_date_time;
	}

	// special case: time is equal to 12
	if (timeParsed == time_duration(NUM_HOURS/2, 0, 0, 0)) {
		return timeParsed;
	}

	// ensure that we do not have times past 12
	if (timeParsed.hours() >= NUM_HOURS/2) {
		return not_a_date_time;
	}
	return timeParsed + hours(NUM_HOURS/2);
}

void ParserDateTime::extractHoursMinutes(int numericTime, 
										int& hours, 
										int& minutes) {
	
	if (numericTime < NUMERIC_TIME_MODULO) {
		hours = numericTime;
		minutes = 0;
	}else {
		hours = numericTime / NUMERIC_TIME_MODULO;
		minutes = numericTime % NUMERIC_TIME_MODULO;
	}
}

time_duration ParserDateTime::computeTime(int hours, int minutes) {
	// Ensure that time is a valid time
	if (hours >= NUM_HOURS || minutes >= NUM_MINUTES) {
		return not_a_date_time;
	}else {
		return time_duration(hours, minutes, 0, 0);
	}
}

int ParserDateTime::parseMonth(string input) {
	int month;
	for (int x = 0; x < NUM_MONTHS; x++) {
		regex rgx(MONTH_FORMATS[x], regex_constants::icase);
		if (regex_match(input, rgx)) {
			month = x + 1;
			return month;
		}
	}
	throw(invalid_argument("Invalid month parsed"));
}
int ParserDateTime::parseDay(string input) {
	int day;
		
	if (!extractDecimalNumber(input, day, true)) {
		throw (invalid_argument("Invalid day parsed"));
	}

	return day;
}
int ParserDateTime::parseYear(string input) {
	int year;
	if (!extractDecimalNumber(input, year) || year > MAX_YEAR) {
		throw(invalid_argument("Invalid year parsed"));
	}else {
		// handles cases where the user uses a shortened form for the year
		if (year >= MIN_YEAR && year < MAX_SHORTENED_YEAR) {
			year = year + CUTOFF_REF_YEAR;
		}
	}
	return year;
}

bool ParserDateTime::removeSuffix(string input, 
								  string& output,
								  string suffix) {
	if (input.length() < suffix.length()) {
		return false;
	}
	string extractedSuffix = 
		input.substr(input.length()-suffix.length(), suffix.length());
	if (!boost::iequals(extractedSuffix, suffix)) {
		return false;
	}

	output = input.substr(0, input.length() - suffix.length());
	return true;
}

bool ParserDateTime::extractDecimalNumber(string input, 
										  int& output, 
										  bool allowOrdinals) {
	output = 0;
	stringstream strStream(input);

	strStream >> output;
	if (strStream.fail()) {
		return false;
	}

	bool validInteger = true;
	if (allowOrdinals && output >= 0) {
		// handle ordinals - they are expected to be single words.
		int index = min(output, (int)ORDINALS.size() - 1);
		string ordinal;
		strStream >> ordinal;

		int pos = ordinal.find(ORDINALS[index]);
		if (pos != ordinal.npos) {
			strStream.str(ordinal.substr(pos, ORDINALS[index].length()));
		}else if (ordinal != EMPTY_STRING) {
			validInteger = false;
		}
	}

	// Test if there are no other characters left
	strStream >> ws;
	validInteger &= strStream.eof();

	return validInteger;
}

PairDateTime ParserDateTime::makeNullPeriod() {
	return PairDateTime(ptime(not_a_date_time), ptime(not_a_date_time));
}