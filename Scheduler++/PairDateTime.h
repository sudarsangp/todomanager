#ifndef PAIR_DATE_TIME_H
#define PAIR_DATE_TIME_H

#include <boost\date_time.hpp>

/**
 * This utility class represents a pair of datetimes
 * 
 * Note that this class is different from Boost::time_period. This allows
 * for invalid times (end < start)
 *
 * NULL times are pairs where both the startTime and endTime are 
 * not_a_date_time
 *
 @author A0002927L
*/

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class PairDateTime {
public:
	ptime begin();
	ptime end();
	PairDateTime(ptime startTime, ptime endTime);
	bool isNull();
private:
	ptime _startTime;
	ptime _endTime;
};

#endif