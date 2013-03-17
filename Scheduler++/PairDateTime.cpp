//@author A0002927L

#include "PairDateTime.h"

ptime PairDateTime::begin() {
	return _startTime;
}
ptime PairDateTime::end() {
	return _endTime;
}

PairDateTime::PairDateTime(ptime startTime, ptime endTime) 
	: _startTime(startTime), _endTime(endTime) {

}
bool PairDateTime::isNull() {
	return (_startTime.is_not_a_date_time() && _endTime.is_not_a_date_time());
}

