//@author A0002927L

#ifndef _TESTER_H_
#define _TESTER_H_

#include "../gtest-1.6.0/include/gtest/gtest.h"
#include "Parser.h"
#include "ParserDateTime.h"
/************************************************************************/
// Testing for the parser, as well as date time parser
/************************************************************************/

//**********************************************************************
// DATE AND TIME TEST
// Remarks: all date_time tests are labeled by dt_abxx
// The numbers refer to the type of test being conducted
// a: the class of the test, eg. parsing date, parsing time, parsing both
// b: 0 if the test is a failing case, 1 if the test is a passing case
//**********************************************************************

// dt_1xxx refers to full date, without the time

TEST(ParserDateTime, dt_1001) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("0 jAn 2012");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1002) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("-1 jAn 2012");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1003) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("32 jAn 2012");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1005) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1 - Jun / 999");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1006) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1 - Jun - 100");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1007) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1 - Jun - 20.12");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1008) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1.1.1.1");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1009) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("10.10.10.10");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1010) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1.1.1 1");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1011) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1rd Jan 12");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1012) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("2td Jan 12");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1013) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("4st Jan 12");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_1101) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1 jAn 12");
	ASSERT_EQ(time, ptime(date(2012,1,1), pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1102) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("28- feB 11");
	ASSERT_EQ(time, ptime(date(2011,2,28), pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1103) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30 - maR / 10");
	ASSERT_EQ(time, ptime(date(2010,3,30), pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1104) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30 - apr / 09");
	ASSERT_EQ(time, ptime(date(2009,4,30),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1105) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30 - May / 8");
	ASSERT_EQ(time, ptime(date(2008,5,30),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1106) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1 - Jun / 99");
	ASSERT_EQ(time, ptime(date(2099,06,1),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1107) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("31 - Jul / 00");
	ASSERT_EQ(time, ptime(date(2000,07,31),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1108) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("31 - Aug / 1990");
	ASSERT_EQ(time, ptime(date(1990,8,31),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1109) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("4th - Sept / 2099");
	ASSERT_EQ(time, ptime(date(2099,9,4),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1110) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("3rd - October / 2050");
	ASSERT_EQ(time, ptime(date(2050,10,3), pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1111) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30 - November / 2013");
	ASSERT_EQ(time, ptime(date(2013,11,30),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1112) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("31 - December / 2014");
	ASSERT_EQ(time, ptime(date(2014,12,31),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_1113) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("June 1 2013");
	ASSERT_EQ(time, ptime(date(2013, 6, 1), pdt.getLatestPossibleTime()));
}

// Ensure that if day-month-year fails, month-day-year kicks in
TEST(ParserDateTime, dt_1114) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("12 13 2013", true);
	ASSERT_EQ(time, ptime(date(2013, 12, 13)));
}

// Ensure that day-month-year takes precedence over month-day-year
TEST(ParserDateTime, dt_1115) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("6 7 2013", true);
	ASSERT_EQ(time, ptime(date(2013, 7, 6)));
}

// dt_2xxx refers to date-only, without the year

TEST(ParserDateTime, dt_2001) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("32-jan");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_2002) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("-30-Dec");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_2101) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("2nd-jan");
	ASSERT_EQ(time, ptime(date(2013,1,2),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_2102) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30th-Dec");
	ASSERT_EQ(time, ptime(date(2012,12,30),pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_2103) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1st-Dec", true);
	ASSERT_EQ(time, ptime(date(2012,12,1),pdt.getEarliestPossibleTime()));
}

// dt_4xxx refers to time parsing only

TEST(ParserDateTime, dt_4001) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("15::13");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4002) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("15:13:01");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4003) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("24:00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4004) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("2400");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4005) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("25:00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4006) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("2500");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4007) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:60");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4008) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:-1");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4009) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:61");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4010) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:123456789123");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4011) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("313231313121244234:00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4012) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23a:00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4013) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("a23:00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4014) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:00a");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4015) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:a00");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4016) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23:");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4017) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime(":23");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4018) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime(":");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4019) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23a59");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4020) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("23 59");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4021) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1299");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4101) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1513");
	ASSERT_EQ(time, time_duration(15, 13, 0, 0));
}

TEST(ParserDateTime, dt_4150) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("15:13");
	ASSERT_EQ(time, time_duration(15, 13, 0, 0));
}

TEST(ParserDateTime, dt_4151) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("0:13");
	ASSERT_EQ(time, time_duration(0, 13, 0, 0));
}

TEST(ParserDateTime, dt_4152) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("0:1");
	ASSERT_EQ(time, time_duration(0, 1, 0, 0));
}

// PM, AM requirements, 4170+

// Failing test cases for PM, AM requirements

TEST(ParserDateTime, dt_4070) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("13aM");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4071) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1060aM");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4072) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1259pM");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4073) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("12aM");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4074) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1 0000aM");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_4075) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("10000aM");
	ASSERT_EQ(time, not_a_date_time);
}

// 1 - 2 digit variants

TEST(ParserDateTime, dt_4171) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("0aM");
	ASSERT_EQ(time, time_duration(0, 0, 0, 0));
}

TEST(ParserDateTime, dt_4172) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("1Pm");
	ASSERT_EQ(time, time_duration(13, 0, 0, 0));
}

// 3-4 Digit numbers should be interpreted accordingly
TEST(ParserDateTime, dt_4180) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("130aM");
	ASSERT_EQ(time, time_duration(1, 30, 0, 0));
}

TEST(ParserDateTime, dt_4181) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("159pM");
	ASSERT_EQ(time, time_duration(13, 59, 0, 0));
}

// Special times
TEST(ParserDateTime, dt_4182) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("12  nOOn");
	ASSERT_EQ(time, time_duration(12, 0, 0, 0));
}

TEST(ParserDateTime, dt_4183) {
	ParserDateTime pdt;
	time_duration time = pdt.parseTime("midnight");
	ASSERT_EQ(time, time_duration(0, 0, 0, 0));
}


// dt_7xxx refers to datetimes which have both the date and time component

TEST(ParserDateTime, dt_7001) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec , 2400");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_7002) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec , -1");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_7003) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec , -0");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_7004) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec , ");
	ASSERT_EQ(time, not_a_date_time);
}

TEST(ParserDateTime, dt_7101) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec at 1513");
	ASSERT_EQ(time, ptime(date(2012,12,30))+time_duration(15, 13, 0, 0));
}

TEST(ParserDateTime, dt_7102) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("1-Jan @ 1513");
	ASSERT_EQ(time, ptime(date(2013,1,1))+time_duration(15, 13, 0, 0));
}

TEST(ParserDateTime, dt_7103) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime("30-Dec , 1");
	ASSERT_EQ(time, ptime(date(2012,12,30))+time_duration(1, 0, 0, 0));
}

// dt_8xxx refers to special date and times
TEST(ParserDateTime, dt_8101) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Monday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime("monday");
	ASSERT_EQ(time, ptime(curDate, pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_8102) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Tuesday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime("tue");
	ASSERT_EQ(time, ptime(curDate, pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_8103) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Wednesday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime("wednesday");
	ASSERT_EQ(time, ptime(curDate, pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_8104) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Thursday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime("thUrsday ");
	ASSERT_EQ(time, ptime(curDate, pdt.getLatestPossibleTime()));
}

TEST(ParserDateTime, dt_8105) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Friday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime(" friday , 1200");
	ASSERT_EQ(time, ptime(curDate)+time_duration(12, 0, 0, 0));
}

TEST(ParserDateTime, dt_8106) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Saturday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime(" sat , 2359");
	ASSERT_EQ(time, ptime(curDate)+time_duration(23, 59, 0, 0));
}

TEST(ParserDateTime, dt_8107) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	while (curDate.day_of_week() != Sunday) {
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime(" sunday , 0000");
	ASSERT_EQ(time, ptime(curDate)+time_duration(0, 0, 0, 0));
}

TEST(ParserDateTime, dt_8108) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	ptime time = pdt.parseDateTime(" tOmmoroW");
	ASSERT_EQ(time, ptime(curDate)+days(1)+time_duration(23, 59, 0, 0));
}

TEST(ParserDateTime, dt_8109) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	ptime time = pdt.parseDateTime(" today");
	ASSERT_EQ(time, ptime(curDate)+time_duration(23, 59, 0, 0));
}

TEST(ParserDateTime, dt_8110) {
	ParserDateTime pdt;
	date curDate = second_clock::local_time().date();
	bool passedSunday = false;
	while (curDate.day_of_week() != Wednesday || !passedSunday) {
		if (curDate.day_of_week() == Sunday) {
			passedSunday = true;
		}
		curDate += days(1);
	}
	ptime time = pdt.parseDateTime("next wednesday , 0000");
	ASSERT_EQ(time, ptime(curDate)+time_duration(0, 0, 0, 0));
}

TEST(ParserDateTime, dt_8111) {
	ParserDateTime pdt;
	ptime time = pdt.parseDateTime(" 1pm, 15 Jan 2050");
	ASSERT_EQ(time, ptime(date(2050, 1, 15))+time_duration(13, 0, 0, 0));
	time = pdt.parseDateTime(" 1pm oN 15 Jan 2050");
	ASSERT_EQ(time, ptime(date(2050, 1, 15))+time_duration(13, 0, 0, 0));
}

// dt_9xxx refers to time period parsing

// start time < end time.
// Note: PairDateTime WILL allow invalid times like these
TEST(ParserDateTime, dt_9001) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("12 Jan 2013, 2359 to 12 Jan 2013, 1159");
	ASSERT_EQ(tp.isNull(), false);
}

// start time == end time
TEST(ParserDateTime, dt_9002) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("12 Jan 2013, 2359 to 12 Jan 2013, 2359");
	ASSERT_EQ(tp.isNull(), false);
}

// start time is invalid
TEST(ParserDateTime, dt_9003) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("32 Jan 2013, 2359 to 12 Jan 2013, 1159");
	ASSERT_EQ(tp.isNull(), true);
}

// end time is invalid
TEST(ParserDateTime, dt_9004) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("12 Jan 2013, 2359 to 32 Jan 2013, 1159");
	ASSERT_EQ(tp.isNull(), true);
}

TEST(ParserDateTime, dt_9101) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("12 Jan 2013, 2359 tO 14 Jan 2013, 1159");
	ASSERT_EQ(tp.begin(), ptime(date(2013, 1, 12)) + time_duration(23,59,0,0));
	ASSERT_EQ(tp.end(), ptime(date(2013, 1, 14)) + time_duration(11,59,0,0));
}

TEST(ParserDateTime, dt_9102) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("12 Jan 2013, 2359 tIlL   14 Jan 2013, 1159");
	ASSERT_EQ(tp.begin(), ptime(date(2013, 1, 12)) + time_duration(23,59,0,0));
	ASSERT_EQ(tp.end(), ptime(date(2013, 1, 14)) + time_duration(11,59,0,0));
}

TEST(ParserDateTime, dt_9103) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("from 12 Jan 2013, 2359 until   13 Jan 2013");
	ASSERT_EQ(tp.begin(), ptime(date(2013, 1, 12)) + time_duration(23,59,0,0));
	ASSERT_EQ(tp.end(), ptime(date(2013, 1, 13)) + time_duration(23,59,0,0));
}

TEST(ParserDateTime, dt_9104) {
	ParserDateTime pdt;
	
	PairDateTime tp = pdt.parseTimePeriod("from 30 Dec 2013, 2359 untill   1 Jan 2014, 0000");
	ASSERT_EQ(tp.begin(), ptime(date(2013, 12, 30)) + time_duration(23,59,0,0));
	ASSERT_EQ(tp.end(), ptime(date(2014, 1, 1)) + time_duration(0,0,0,0));
}

//*****************************
// GENERAL TESTS
//*****************************

TEST(GeneralTests, empty_input) {
	Parser p;
	CommandBase* cmd;
	
	cmd = p.parseUserCommand("  ");
	ASSERT_EQ(NULL, cmd);
}

TEST(GeneralTests, garbage_input) {
	Parser p;
	CommandBase* cmd;

	cmd = p.parseUserCommand("you are an idiot!");
	ASSERT_EQ(NULL, cmd);
}

TEST(GeneralTests, numeric_only_input) {
	Parser p;
	CommandBase* cmd;

	cmd = p.parseUserCommand("1");
	ASSERT_EQ(NULL, cmd);
}

TEST(GeneralTests, numeric_only_input_negative) {
	Parser p;
	CommandBase* cmd;

	cmd = p.parseUserCommand("-1");
	ASSERT_EQ(NULL, cmd);
}

class ParserTester : public testing::Test {
public:
	CommandBase* cmd;
	Parser p;
	virtual void SetUp() {
		cmd = NULL;
	}
	// clean up memory to prevent memory leak
	virtual void TearDown() {
		if (cmd != NULL) {
			delete cmd;
		}
	}
};


//*****************************
// GENERAL ADD TESTS
//*****************************

TEST_F(ParserTester, add_task_all_spaces_for_name) {
	ASSERT_THROW(p.parseUserCommand("add    "), ParserException);
}

TEST_F(ParserTester, add_task_no_name) {
	ASSERT_THROW(p.parseUserCommand("add"), ParserException);
}

TEST_F(ParserTester, add_task_bad_syntax_with_delimiters) {
	ASSERT_THROW(p.parseUserCommand("add >"), ParserExceptionBadDate);
}

TEST_F(ParserTester, add_task_bad_syntax_no_date_with_delimiter) {
	ASSERT_THROW(p.parseUserCommand("add CS2103 knows no deadlines   > "), ParserExceptionBadDate);
}

TEST_F(ParserTester, add_task_bad_syntax_lack_period) {
	ASSERT_THROW(p.parseUserCommand("add CS2103 knows no deadlines   > 2015-May-15 to "), ParserExceptionBadDate);
}

//*****************************
// ADD FLOATING
//*****************************

TEST_F(ParserTester, add_floating_task) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 sucks bad");
	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 sucks bad");
}

TEST_F(ParserTester, add_floating_task_spaces) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add    CS2103    sucks       bad         ");
	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103    sucks       bad");
}

TEST_F(ParserTester, add_floating_task_numbers_behind) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add task 1");
	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "task 1");
}

// Tricky case - since 2359 is too ambigous, it is taken as a task
// name instead of the time.
TEST_F(ParserTester, add_floating_task_tricky_name) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add task 2359");
	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "task 2359");
}



//*****************************
// ADD DEADLINE
//*****************************

TEST_F(ParserTester, add_deadline_task_bad_time) {
	ASSERT_THROW(p.parseUserCommand("add CS2103 knows no deadlines   > forever and ever"), ParserExceptionBadDate);
}

TEST_F(ParserTester, add_deadline_task_alphabet_bad_time_but_floating) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows no deadlines  by forever and ever");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows no deadlines  by forever and ever");
}

TEST_F(ParserTester, add_deadline_task_good_time) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   > 2015-May-15");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 15), 
			  ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_deadline_task_alphabet_good_time) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   bY 2015-May-15");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 15),
			  ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_deadline_task_shortcut_good) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines  15   May   2015 ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 15),
			  ParserDateTime::getLatestPossibleTime()));
}


TEST_F(ParserTester, add_deadline_task_shortcut_date_at_front_good) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add 15 May 2014 CS2103 knows deadlines ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2014, 5, 15),
			  ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_deadline_task_shortcut_date_at_front_bad_but) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add 15 May 2014CS2103 knows deadlines ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "2014CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2013, 5, 15),
			  ParserDateTime::getLatestPossibleTime()));
}

// Tricky cases for deadline tasks, where short date/times can
// result in difficult decisions as to whether the input is part of 
// the task name or its time
TEST_F(ParserTester, add_deadline_task_name_or_time) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add cs2103 23:59");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "cs2103");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(second_clock::local_time().date(), 
			  time_duration(23, 59, 0, 0)));
}

// Another tricky case - 2359 is interpreted as a time because the user was 
// explicit by including "by"
TEST_F(ParserTester, add_deadline_task_name_or_time2) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add cs2103 by 2359");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "cs2103");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(second_clock::local_time().date(), 
			  time_duration(23, 59, 0, 0)));
}

// This case test for the @ connector. Also tests if only valid times are
// taken (no confusion)
TEST_F(ParserTester, add_deadline_task_name_or_time3) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add cs2103 @com1 @2359");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "cs2103 @com1");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(second_clock::local_time().date(), 
			  time_duration(23, 59, 0, 0)));
}

// Test case with multipe bys
TEST_F(ParserTester, add_deadline_task_multiple_bys) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add cs2103 exam by 20 Nov 2013 by 3pm");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "cs2103 exam");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), ptime(date(2013, 11, 20),
										time_duration(15, 0, 0, 0)));
}


// Even though this looks like a timed task, it is in an invalid format
TEST_F(ParserTester, add_deadline_task_syntax_joined_keywords_bad) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("Add CS2103 from15 Jan-2050 to 17 Jan 2050");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 from15 Jan-2050 to");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2050, 1, 17), ParserDateTime::getLatestPossibleTime()));
}

//*****************************
// ADD TIMED TASK
//*****************************
TEST_F(ParserTester, add_timed_task_bad_start_time) {
	ASSERT_THROW(p.parseUserCommand("add CS2103 knows deadlines   > 2015-JUNK-15 to 2015-May-15"), ParserExceptionBadDate);
}

TEST_F(ParserTester, add_timed_task_alphabet_bad_start_time_but_deadline) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   from 2015-JUNK-15 to     2015-May-15");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines   from 2015-JUNK-15 to");
}

TEST_F(ParserTester, add_timed_task_bad_end_time) {
	ASSERT_THROW(p.parseUserCommand("add CS2103 knows deadlines   > 2015-May-15 to 2015-Junk-15"), ParserExceptionBadDate);
}

TEST_F(ParserTester, add_timed_task_alphabet_bad_end_time_but_floating) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   from 2015-May-15 to 2015-Junk-15");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_FLOATING_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines   from 2015-May-15 to 2015-Junk-15");
}

TEST_F(ParserTester, add_timed_task_good_time) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   > 2015-May-15 to 2015-May-16");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_TIMED_TASK);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getStartTime(), 
			  ptime(date(2015, 5, 15), ParserDateTime::getEarliestPossibleTime()));
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 16), ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_timed_task_alphabet_good_time) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines   from 2015-May-15 to 2015-May-16");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_TIMED_TASK);
	ASSERT_EQ(cmdAdd->getStartTime(), 
			  ptime(date(2015, 5, 15), ParserDateTime::getEarliestPossibleTime()));
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 16), ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_timed_task_shortcut_good) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines  2015- May -15 to 2015-May- 16  ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);

	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_TIMED_TASK);
	cmd = p.parseUserCommand("add CS2103 knows deadlines  2015- May -15 to 2015-May- 16  ");
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getStartTime(), 
			  ptime(date(2015, 5, 15), ParserDateTime::getEarliestPossibleTime()));
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 16), ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, add_timed_task_shortcut_bad_become_deadline) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("add CS2103 knows deadlines2015- May -32 to 2015-May- 16  ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines2015- May -32 to");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_DEADLINE_TASK);
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 16), ParserDateTime::getLatestPossibleTime()));
}

// This test case returns a valid timed task - parser will not report 
// anomalies like these, where start > end.
TEST_F(ParserTester, add_timed_task_end_before_start) {
	CommandAdd* cmdAdd;

	cmd = p.parseUserCommand("Add CS2103 knows deadlines 2015- May -15 to 2015-May- 14  ");

	cmdAdd = dynamic_cast<CommandAdd*>(cmd);
	ASSERT_EQ(cmdAdd == NULL, false);
	ASSERT_EQ(cmdAdd->getTaskName(), "CS2103 knows deadlines");
	ASSERT_EQ(cmdAdd->getAddType(), CommandAdd::ADD_TIMED_TASK);
	ASSERT_EQ(cmdAdd->getStartTime(), 
			  ptime(date(2015, 5, 15), ParserDateTime::getEarliestPossibleTime()));
	ASSERT_EQ(cmdAdd->getEndTime(), 
			  ptime(date(2015, 5, 14), ParserDateTime::getLatestPossibleTime()));
}


//*****************************
// GENERAL List TESTS
//*****************************

//*****************************
// LIST ALL TESTS
//*****************************
TEST_F(ParserTester, list_no_arg) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list  ");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_ALL);
}

//*****************************
// LIST DAY TESTS
//*****************************
TEST_F(ParserTester, list_day) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("List day");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
	ASSERT_EQ(cmdList->getEndTime(), 
			  ptime(second_clock::local_time().date(), 
			  ParserDateTime::getLatestPossibleTime()));
}

//*****************************
// LIST WEEK TESTS
//*****************************
TEST_F(ParserTester, list_week) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list week");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
}

TEST_F(ParserTester, list_week_this) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list this week");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
}

TEST_F(ParserTester, list_not_done) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list not   dOne");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_NOT_DONE);
}

TEST_F(ParserTester, list_no_done_alias1) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list UNDone");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_NOT_DONE);
}

//*****************************
// LIST MONTH TESTS
//*****************************
TEST_F(ParserTester, list_month) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list month");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
}

TEST_F(ParserTester, list_month_this) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list this month");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
}

TEST_F(ParserTester, list_specified_month) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list Oct");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ptime startTime = ptime(date(second_clock::local_time().date().year(), 10, 1), time_duration(0,0,0,0));
	if (startTime < second_clock::local_time()) {
		startTime += years(1);
	}
	ptime endTime(date(startTime.date().year(), 10, 31), time_duration(23,59,0,0));
	

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_PERIOD);
	ASSERT_EQ(cmdList->getEndTime(), endTime);
	ASSERT_EQ(cmdList->getStartTime(), startTime);
}

//*****************************
// LIST MONTH TESTS
//*****************************
TEST_F(ParserTester, list_done) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list  doNe  ");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_DONE);
}


//*****************************
// LIST SEARCH_TERM TESTS
//*****************************
TEST_F(ParserTester, list_search_term) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list CS2103 Project");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_SEARCH_TERM);
	ASSERT_EQ(cmdList->getSearchTerm(), "CS2103 Project");
}

TEST_F(ParserTester, list_search_term_spaces) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("search      CS2103 Project   ");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_SEARCH_TERM);
	ASSERT_EQ(cmdList->getSearchTerm(), "CS2103 Project");
}

// Tricky case- this should be taken as a searchterm rather than
// a month
TEST_F(ParserTester, list_bad_month_connecter) {
	CommandList* cmdList;

	cmd = p.parseUserCommand("list  thismonth");

	cmdList = dynamic_cast<CommandList*>(cmd);
	ASSERT_EQ(cmdList == NULL, false);

	ASSERT_EQ(cmdList->getListType(), CommandList::LIST_SEARCH_TERM);
	ASSERT_EQ(cmdList->getSearchTerm(), "thismonth");
}

//*****************************
// SORTING TESTS
//*****************************
TEST_F(ParserTester, sort_invalid) {
	ASSERT_THROW(p.parseUserCommand("Sort some junk"), ParserException);
}

TEST_F(ParserTester, sort_empty) {
	ASSERT_THROW(cmd = p.parseUserCommand("sort  ");, ParserException);
}

TEST_F(ParserTester, sort_time) {
	CommandSort* cmdSort;

	cmd = p.parseUserCommand("sort t");

	cmdSort = dynamic_cast<CommandSort*>(cmd);
	ASSERT_EQ(cmdSort == NULL, false);

	ASSERT_EQ(cmdSort->getSortType(), CommandSort::SORT_TIME);
}

TEST_F(ParserTester, sort_flagged) {
	CommandSort* cmdSort;

	cmd = p.parseUserCommand("sort f");

	cmdSort = dynamic_cast<CommandSort*>(cmd);
	ASSERT_EQ(cmdSort == NULL, false);

	ASSERT_EQ(cmdSort->getSortType(), CommandSort::SORT_FLAG);
}

TEST_F(ParserTester, sort_completed) {
	CommandSort* cmdSort;

	cmd = p.parseUserCommand("sort d");

	cmdSort = dynamic_cast<CommandSort*>(cmd);
	ASSERT_EQ(cmdSort == NULL, false);

	ASSERT_EQ(cmdSort->getSortType(), CommandSort::SORT_COMPLETED);
}

TEST_F(ParserTester, sort_alphabetical) {
	CommandSort* cmdSort;

	cmd = p.parseUserCommand("sort a");

	cmdSort = dynamic_cast<CommandSort*>(cmd);
	ASSERT_EQ(cmdSort == NULL, false);

	ASSERT_EQ(cmdSort->getSortType(), CommandSort::SORT_ALPHABET);
}

TEST_F(ParserTester, sort_alphabetical_full) {
	CommandSort* cmdSort;

	cmd = p.parseUserCommand("sort alphabet");

	cmdSort = dynamic_cast<CommandSort*>(cmd);
	ASSERT_EQ(cmdSort == NULL, false);

	ASSERT_EQ(cmdSort->getSortType(), CommandSort::SORT_ALPHABET);
}

//*****************************
// EDIT_GENERAL_TESTS
//*****************************

TEST_F(ParserTester, edit_no_args) {
	ASSERT_THROW(p.parseUserCommand("edit "), ParserException);
}

TEST_F(ParserTester, edit_no_subtype) {
	ASSERT_THROW(p.parseUserCommand("edit 412 "), ParserException);
}

TEST_F(ParserTester, edit_bad_taskid) {
	ASSERT_THROW(p.parseUserCommand("edit 412a start 2012-May-15"), ParserException);
}

TEST_F(ParserTester, edit_bad_no_taskid) {
	ASSERT_THROW(p.parseUserCommand("edit start 2012-May-15"), ParserException);
}

//*****************************
// EDIT_START
//*****************************

TEST_F(ParserTester, edit_good_startdate) {
	CommandEdit* cmdEdit;

	cmd = p.parseUserCommand("edit 412 start 2012-May-15");

	cmdEdit = dynamic_cast<CommandEdit*>(cmd);
	ASSERT_EQ(cmdEdit == NULL, false);

	ASSERT_EQ(cmdEdit->getEditType(), CommandEdit::EDIT_START_DATETIME);
	ASSERT_EQ(cmdEdit->getDateTime(), 
			  ptime(date(2012, 5, 15), ParserDateTime::getEarliestPossibleTime()));
}

TEST_F(ParserTester, edit_bad_startdate) {
	ASSERT_THROW(p.parseUserCommand("edit 412 start 2012-May-32"), ParserException);
}

TEST_F(ParserTester, edit_good_starttime) {
	CommandEdit* cmdEdit;

	cmd = p.parseUserCommand("eDit 412 start 15:15");

	cmdEdit = dynamic_cast<CommandEdit*>(cmd);
	ASSERT_EQ(cmdEdit == NULL, false);

	ASSERT_EQ(cmdEdit->getEditType(), CommandEdit::EDIT_START_TIME);
	ASSERT_EQ(cmdEdit->getTime(), time_duration(15, 15, 0));
}

TEST_F(ParserTester, edit_bad_starttime) {
	ASSERT_THROW(p.parseUserCommand("edit 412 start 24:15"), ParserException);
}

//*****************************
// EDIT_END
//*****************************

TEST_F(ParserTester, edit_good_enddate) {
	CommandEdit* cmdEdit;

	cmd = p.parseUserCommand("update 412 end 2012-May-15");

	cmdEdit = dynamic_cast<CommandEdit*>(cmd);
	ASSERT_EQ(cmdEdit == NULL, false);

	ASSERT_EQ(cmdEdit->getEditType(), CommandEdit::EDIT_END_DATETIME);
	ASSERT_EQ(cmdEdit->getDateTime(), 
			  ptime(date(2012, 5, 15), ParserDateTime::getLatestPossibleTime()));
}

TEST_F(ParserTester, edit_bad_enddate) {
	ASSERT_THROW(p.parseUserCommand("edit 412 end 2012-May-32"), ParserExceptionBadDate);
}

TEST_F(ParserTester, edit_good_endtime) {
	CommandEdit* cmdEdit;

	cmd = p.parseUserCommand("modify 412 end 1515");

	cmdEdit = dynamic_cast<CommandEdit*>(cmd);
	ASSERT_EQ(cmdEdit == NULL, false);

	ASSERT_EQ(cmdEdit->getEditType(), CommandEdit::EDIT_END_TIME);
	ASSERT_EQ(cmdEdit->getTime(), time_duration(15, 15, 0));
}

TEST_F(ParserTester, edit_bad_endtime) {
	ASSERT_THROW(p.parseUserCommand("edit 412 end 24:15"), ParserExceptionBadDate);
}


//*****************************
// EDIT_RENAME
//*****************************
TEST_F(ParserTester, edit_rename_bad_name) {
	ASSERT_THROW(p.parseUserCommand("change 412 rename   "), ParserException);
}

TEST_F(ParserTester, edit_rename_good_name) {
	CommandEdit* cmdEdit;

	cmd = p.parseUserCommand("edit 412 rename   CS2103 project   tutorial .");

	cmdEdit = dynamic_cast<CommandEdit*>(cmd);
	ASSERT_EQ(cmdEdit == NULL, false);

	ASSERT_EQ(cmdEdit->getEditType(), CommandEdit::EDIT_RENAME);
	ASSERT_EQ(cmdEdit->getTaskName(), "CS2103 project   tutorial .");
}

//*****************************
// DELETE GENERAL
//*****************************
TEST_F(ParserTester, delete_no_args) {
	ASSERT_THROW(p.parseUserCommand("delete  "), ParserException);
}
//*****************************
// DELETE SEARCHTERM
//*****************************

TEST_F(ParserTester, delete_searchterm) {
	CommandDelete* cmdDelete;

	cmd = p.parseUserCommand("delete  abc def");

	cmdDelete = dynamic_cast<CommandDelete*>(cmd);
	ASSERT_EQ(cmdDelete == NULL, false);

	ASSERT_EQ(cmdDelete->getDeleteType(), CommandDelete::DELETE_SEARCHTERM);
	ASSERT_EQ(cmdDelete->getDeleteSearchString(), "abc def");
}

//*****************************
// DELETE TASKID
//*****************************
TEST_F(ParserTester, delete_taskid) {
	CommandDelete* cmdDelete;

	cmd = p.parseUserCommand("delete   152");

	cmdDelete = dynamic_cast<CommandDelete*>(cmd);
	ASSERT_EQ(cmdDelete == NULL, false);
	
	ASSERT_EQ(cmdDelete->getDeleteType(), CommandDelete::DELETE_INDEX);
	ASSERT_EQ(cmdDelete->getDeleteIndex(), 152);
}

//*****************************
// DELETE DONE
//*****************************
TEST_F(ParserTester, delete_bad_args) {
	CommandDelete* cmdDelete;

	cmd = p.parseUserCommand("Delete   done ");

	cmdDelete = dynamic_cast<CommandDelete*>(cmd);
	ASSERT_EQ(cmdDelete == NULL, false);

	ASSERT_EQ(cmdDelete->getDeleteType(), CommandDelete::DELETE_DONE);
}


//*****************************
// DONE
//*****************************

TEST_F(ParserTester, done_bad_args) {
	ASSERT_THROW(p.parseUserCommand("done   "), ParserException);
}

TEST_F(ParserTester, done_good_taskid) {
	CommandDone* cmdDone;

	cmd = p.parseUserCommand("do   154  ");

	cmdDone = dynamic_cast<CommandDone*>(cmd);
	ASSERT_EQ(cmdDone == NULL, false);

	ASSERT_EQ(cmdDone->getDoneType(), CommandDone::DONE_INDEX);
	ASSERT_EQ(cmdDone->getDoneIndex(), 154);
}

TEST_F(ParserTester, done_good_searchterm) {
	CommandDone* cmdDone;

	cmd = p.parseUserCommand("finished  abc def     ");

	cmdDone = dynamic_cast<CommandDone*>(cmd);
	ASSERT_EQ(cmdDone == NULL, false);

	ASSERT_EQ(cmdDone->getDoneType(), CommandDone::DONE_SEARCHTERM);
	ASSERT_EQ(cmdDone->getDoneSearchTerm(), "abc def");
}

TEST_F(ParserTester, done_good_listed) {
	CommandDone* cmdDone;

	cmd = p.parseUserCommand("done  listed");

	cmdDone = dynamic_cast<CommandDone*>(cmd);
	ASSERT_EQ(cmdDone == NULL, false);

	ASSERT_EQ(cmdDone->getDoneType(), CommandDone::DONE_ALL);
}

TEST_F(ParserTester, done_good_listed_alias1) {
	CommandDone* cmdDone;

	cmd = p.parseUserCommand("did  shOwn");

	cmdDone = dynamic_cast<CommandDone*>(cmd);
	ASSERT_EQ(cmdDone == NULL, false);

	ASSERT_EQ(cmdDone->getDoneType(), CommandDone::DONE_ALL);
}

TEST_F(ParserTester, done_good_alias2) {
	CommandDone* cmdDone;

	cmd = p.parseUserCommand("completed  displAyed  ");

	cmdDone = dynamic_cast<CommandDone*>(cmd);
	ASSERT_EQ(cmdDone == NULL, false);

	ASSERT_EQ(cmdDone->getDoneType(), CommandDone::DONE_ALL);
}

//*****************************
// FLAG 
//*****************************

TEST_F(ParserTester, flag_bad) {
	ASSERT_THROW(p.parseUserCommand("flag    "), ParserException);
}

TEST_F(ParserTester, flag_good_searchterm) {
	CommandFlag* cmdFlag;

	cmd = p.parseUserCommand("flag  search term !<< ");

	cmdFlag = dynamic_cast<CommandFlag*>(cmd);
	ASSERT_EQ(cmdFlag == NULL, false);
	ASSERT_EQ(cmdFlag->getFlagType(), CommandFlag::FLAG_SEARCHTERM);
	ASSERT_EQ(cmdFlag->getFlagSearchTerm(), "search term !<<");
}

TEST_F(ParserTester, flag_good_task_index) {
	CommandFlag* cmdFlag;

	cmd = p.parseUserCommand("flag  1 ");

	cmdFlag = dynamic_cast<CommandFlag*>(cmd);
	ASSERT_EQ(cmdFlag == NULL, false);
	ASSERT_EQ(cmdFlag->getFlagType(), CommandFlag::FLAG_INDEX);
	ASSERT_EQ(cmdFlag->getFlagIndex(), 1);
}

TEST_F(ParserTester, flag_good_listed) {
	CommandFlag* cmdFlag;

	cmd = p.parseUserCommand("flag  listed ");

	cmdFlag = dynamic_cast<CommandFlag*>(cmd);
	ASSERT_EQ(cmdFlag == NULL, false);
	ASSERT_EQ(cmdFlag->getFlagType(), CommandFlag::FLAG_ALL);
}

//*****************************
// UNDO
//*****************************

TEST_F(ParserTester, undo_bad) {
	ASSERT_THROW(p.parseUserCommand("undo    qqq"), ParserException);
}

TEST_F(ParserTester, undo_good) {
	CommandUndo* cmdUndo;

	cmd = p.parseUserCommand("uNdo");

	cmdUndo = dynamic_cast<CommandUndo*>(cmd);
	ASSERT_EQ(cmdUndo == NULL, false);
	ASSERT_EQ(cmdUndo->getUndoType(), CommandUndo::UNDO_ACTION);
}

/*
void runTest(int argument_count, char** argument_vars)
{

	testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

	RUN_ALL_TESTS();

	std::getchar(); //pause the program after all the testing

}
*/
#endif