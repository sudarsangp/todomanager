#include "ParsingException.h"

const string ParserExceptionBadDate::BAD_DATE_MSG = 
	"Please enter a valid date or time. Eg. 1 Jan 2014";

ParserException::ParserException(string errMsg) : _errMsg(errMsg) {
}

string ParserException::getParsingError() {
	return _errMsg;
}

ParserExceptionBadDate::ParserExceptionBadDate() : ParserException(BAD_DATE_MSG){
	
}