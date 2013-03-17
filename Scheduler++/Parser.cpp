//@author A0002927L

#include "Parser.h"

Parser::Parser() : ParserBase(NULL){
	// Initializes the chain of responsibility
	parserCatchAll = new ParserCatchAll();
	parserUndo = new ParserUndo(parserCatchAll);
	parserFlag = new ParserFlag(parserUndo);
	parserClear = new ParserClear(parserFlag);
	parserDone = new ParserDone(parserClear);
	parserDelete = new ParserDelete(parserDone);
	parserEdit = new ParserEdit(parserDelete);
	parserSort = new ParserSort(parserEdit);
	parserList = new ParserList(parserSort);
	parserAdd = new ParserAdd(parserList);

	nextParser = parserAdd;
}

Parser::~Parser() {
	delete parserAdd;
	delete parserList;
	delete parserSort;
	delete parserEdit;
	delete parserDelete;
	delete parserDone;
	delete parserCatchAll;
	delete parserClear;
	delete parserUndo;
	delete parserFlag;
}

CommandBase* Parser::tryParse(string userCommand) {
	return false;
}