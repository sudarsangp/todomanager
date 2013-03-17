//@author A0002927L

#ifndef PARSER_EXCEPTION
#define PARSER_EXCEPTION

#include <string>

using namespace std;

class ParserException {
protected:
	string _errMsg;
public:
	ParserException(string errMsg);
	string getParsingError();
};

class ParserExceptionBadDate : public ParserException{
private:
	static const string BAD_DATE_MSG;
public:
	ParserExceptionBadDate();
};

#endif