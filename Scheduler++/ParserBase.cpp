//@author A0002927L

#include "ParserBase.h"

ParserDateTime ParserBase::parserDateTime;

const string ParserBase::EMPTY_STRING = "";
const string ParserBase::regexArgsListed = "\\s*(listed|shown|displayed)\\s*";

CommandBase* ParserBase::parseUserCommand(string userCommand){
	
	CommandBase* parsedCommand = tryParse(userCommand);
	bool result = (parsedCommand != NULL);
	
	if (result == true) {
		return parsedCommand;
	}

	if (nextParser != NULL) {
		return nextParser->parseUserCommand(userCommand);
	}else {
		throw ("No parser exists to parse this command!");
	}
	
}

ParserBase::ParserBase(ParserBase* _nextParser) :nextParser(_nextParser) {
}

ptime ParserBase::extractDateTime(string input, string& output, vector<string>& prefixes) {
	if (input == EMPTY_STRING) {
		output = EMPTY_STRING;
		return not_a_date_time;
	}

	ptime finalDateTime = not_a_date_time;
	finalDateTime = extractDateTimeBack(input, output, prefixes);
	if (!finalDateTime.is_not_a_date_time()) {
		return finalDateTime;
	}

	finalDateTime = extractDateTimeFront(input, output);

	if (!finalDateTime.is_not_a_date_time()){
		return finalDateTime;
	}else{
		output = EMPTY_STRING;
		return not_a_date_time;
	}
}

PairDateTime ParserBase::extractTimePeriod(string input, string& output) {
	if (input == EMPTY_STRING) {
		output = EMPTY_STRING;
		return parserDateTime.makeNullPeriod();
	}

	PairDateTime finalTimePeriod = parserDateTime.makeNullPeriod();

	finalTimePeriod = extractTimePeriodBack(input, output);
	if (!finalTimePeriod.isNull()){
		return finalTimePeriod;
	}

	finalTimePeriod = extractTimePeriodFront(input, output);
	
	if (!finalTimePeriod.isNull()){
		return finalTimePeriod;
	}else{
		output = EMPTY_STRING;
		return parserDateTime.makeNullPeriod();
	}
}

ptime ParserBase::extractDateTimeBack(string input,
							  string& output,
							  vector<string>& prefixes) {
	assert(input != EMPTY_STRING);
	ptime extractedDateTime = not_a_date_time;
	// search from the back (date/time is in the back)
	for (string::iterator i = input.begin(); i != input.end(); i++) {
		// This cannot be a datetime fragment if prev char is not a space.
		if (*(i) != SPACE) {
			continue;
		}

		// substring before trimming
		string bareSubStr = string(i+1, input.end()); 
		bool isSame = false;
		string subStr = removePrefixes(bareSubStr, prefixes);
		if (subStr == bareSubStr) {
			isSame = true;
		}

		// If there was trimming done, then the instruction by the user must
		// be explitiy - no need for strict syntax
		ptime parsedDateTime = parserDateTime.parseDateTime(subStr, false, isSame);
		
		// Found a date time fragment, exit
		if (!parsedDateTime.is_not_a_date_time()){
			extractedDateTime = parsedDateTime;
			output = string(input.begin(), i);
			break;
		}	
	}
	
	return extractedDateTime;
}
ptime ParserBase::extractDateTimeFront(string input, string& output) {
	assert(input != EMPTY_STRING);
	ptime extractedDateTime = not_a_date_time;
	// search from the front (date/time is in the front)
	for (string::iterator i = input.end() - 1; i != input.begin(); i--) {
		// This cannot be a date time fragment if this char is not a space.
		if ((*i) != SPACE) {
			continue;
		}

		string subStr = string(input.begin(), i);

		ptime parsedDateTime = parseDateTime(subStr);
		// store longest valid date/time we have found
		if (!parsedDateTime.is_not_a_date_time()){
			extractedDateTime = parsedDateTime;
			output = string(i, input.end());
			break;
		}
	}
	return extractedDateTime;
}
PairDateTime ParserBase::extractTimePeriodBack(string input, string& output) {
	assert(input != EMPTY_STRING);
	PairDateTime extractedTimePeriod = parserDateTime.makeNullPeriod();
	// search from the back (time duration is at the back)
	for (string::iterator i = input.begin(); i != input.end(); i++) {
		// This cannot be a valid time period fragment if this 
		// character is not a space
		if (*(i) != SPACE) {
			continue;
		}

		string subStr = string(i+1, input.end());

		PairDateTime parsedTimePeriod = parserDateTime.parseTimePeriod(subStr);
		// found a match, return
		if (!parsedTimePeriod.isNull()) {
			extractedTimePeriod = parsedTimePeriod;
			output = string(input.begin(), i);
			break;
		}
	}

	return extractedTimePeriod;
}
PairDateTime ParserBase::extractTimePeriodFront(string input, string& output) {
	assert(input != EMPTY_STRING);
	PairDateTime extractedTimePeriod = parserDateTime.makeNullPeriod();
	// search from the front (date/time is in the front)
	for (string::iterator i = input.end()-1; i != input.begin(); i--) {
		// This cannot be a valid time period fragment if this 
		// character is not a space
		if (*(i) != SPACE) {
			continue;
		}

		string subStr = string(input.begin(), i);

		PairDateTime parsedTimePeriod = parserDateTime.parseTimePeriod(subStr);
		// store longest valid date/time we have found
		if (!parsedTimePeriod.isNull()) {
			extractedTimePeriod = parsedTimePeriod;
			output = string(i, input.end());
			break;
		}
	}

	return extractedTimePeriod;
}

ptime ParserBase::getLastOfWeek(ptime curDateTime) {
	// Get last day of week
	date currentDate = curDateTime.date();
	greg_weekday weekDay(Saturday);

	date nextWeekday = next_weekday(currentDate, weekDay);

	return ptime(nextWeekday, parserDateTime.getLatestPossibleTime());
}
ptime ParserBase::getLastOfMonth(ptime curDateTime) {
	// Get last day of month
	date currentDate = curDateTime.date();
	date lastDayOfMonth = currentDate.end_of_month();

	return ptime(lastDayOfMonth, parserDateTime.getLatestPossibleTime());
}

ptime ParserBase::getFirstOfMonth(ptime curDateTime) {
	// Get first day of month
	date currentDate = curDateTime.date();
	date firstDayOfMonth = date(currentDate.year(), currentDate.month(), 1);

	return ptime(firstDayOfMonth, parserDateTime.getEarliestPossibleTime());
}

ptime ParserBase::getFirstOfWeek(ptime curDateTime) {
	// Get first day of week
	date currentDate = curDateTime.date();
	greg_weekday weekDay(Sunday);

	date nextWeekday = next_weekday(currentDate - weeks(1), weekDay);

	return ptime(nextWeekday, parserDateTime.getEarliestPossibleTime());
}

ptime ParserBase::getLastOfDay(ptime curDateTime) {
	date currentDate = curDateTime.date();
	
	return ptime(currentDate, parserDateTime.getLatestPossibleTime());
}

ptime ParserBase::getFirstOfDay(ptime curDateTime) {
	date currentDate = curDateTime.date();
	
	return ptime(currentDate, parserDateTime.getEarliestPossibleTime());
}

time_duration ParserBase::parseTime(const string& timeStr) {

	return parserDateTime.parseTime(timeStr);
}

ptime ParserBase::parseDateTime(const string& timeStr, bool earliest) {
	ptime parsedTime = parserDateTime.parseDateTime(timeStr, earliest);
	return parsedTime;
}

ptime ParserBase::parseDate(const string& timeStr) {
	return ptime(parserDateTime.parseDate(timeStr));
}

int ParserBase::parseMonth(const string& monthStr) {
	return parserDateTime.parseMonth(monthStr);
}

PairDateTime ParserBase::parseTimePeriod(const string& periodStr) {
	return parserDateTime.parseTimePeriod(periodStr, true);
}

int ParserBase::getTaskIDFromArgument(string argument) {
	int extractedID;
	stringstream strStream(argument);

	strStream >> extractedID;
	strStream >> ws;

	// ensure that we indeed have a task ID, and there are no other
	// trailing characters
	if (strStream.fail() || !strStream.eof()) {
		throw (range_error("Invalid task Index!"));
	}
	
	return extractedID;
}

string ParserBase::stripWhiteSpaces(string input) {
	boost::algorithm::trim(input);
	return input;
}

string ParserBase::removePrefixes(string input, vector<string>& prefixes) {
	for (unsigned int x = 0; x < prefixes.size(); x++) {
		if (input.length() < prefixes[x].length()) {
			continue;
		}

		// could not find prefix
		if (!iequals(input.substr(0, prefixes[x].length()), prefixes[x])) {
			continue;
		}

		// return trimmed string
		return input.substr(prefixes[x].length());
	}
	// return untrimmed string
	return input;
}