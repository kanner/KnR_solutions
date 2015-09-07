/**
 * Exercise 5-8, page 93
 * Упражнение 5.8, страница 123
 * 
 * There is no error checking in day_of_year or month_day. Remedy this defect.
 *
 * В функциях day_of_year и month_day нет никакого контроля ошибок в данных.
 * Устраните эту недоработку
 */

#include <stdio.h>

#define WRONG_MONTH_YEAR_OR_DAY	-1
#define WRONG_DAY	-2

static char daytab [2] [13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
	int i, leap;

	/** if we got wrong month or day - return */
	if (month < 1 || month > 12 || day < 1 || year < 0)
		return WRONG_MONTH_YEAR_OR_DAY;

	leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	/** if we got more than real days in that month - return */
	if (day > daytab [leap] [month])
		return WRONG_DAY;
	
	for (i = 1; i < month; i++)
		day += daytab [leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	if ((yearday > (leap == 0 ? 365 : 366)) || yearday < 1 || year < 0)
		return;
	
	for (i = 1; yearday > daytab [leap] [i]; i++)
		yearday -= daytab [leap] [i];

	*pmonth = i;
	*pday = yearday;
}

int main (void) {
	int year = 2015;
	/** leap */
//	int year = 2016;
	int month = 3;
	/** should be 67 or 68 day of year */
	int day = 8;

	int yearday = 67;
	int pmonth = 0;
	int pday = 0;

	printf("day (%d) month (%d) of year (%d) = %d\n", day, month, year, day_of_year(year, month, day));
	
	month_day(year, yearday, &pmonth, &pday);
	printf("yearday (%d) of year (%d) = %d day %d month\n", yearday, year, pday, pmonth);

	return 0;
}
