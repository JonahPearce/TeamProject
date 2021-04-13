#define MAX_DAYS 31
#define MAX_MONTHS 12
#define MAX_YEARS 10
#define MAX_INPUT 100

typedef struct Day {
	int Time;
	char * EventName;
}Day,*DAY;

typedef struct Month {
	Day Day[MAX_DAYS];
}Month,*MONTH;

typedef struct Year {
	Month Month[MAX_MONTHS];
	int YearID;
}Year,*YEAR;

typedef struct Date {
	int Time;
	int Day;
	int Month;
	int Year;
}Date,*DATE;

typedef struct Schedule {
	Year Year[MAX_YEARS];
	Date CurrentDate;
}Schedule,*SCHEDULE;

const char * MonthNames[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void ScheduleManager();

void DisplayMenu(SCHEDULE);
void AddEvent(SCHEDULE);
int AddYear(SCHEDULE);
int AddMonth(SCHEDULE);
int AddDay(SCHEDULE, int);
int AddTime(SCHEDULE);
void DeleteEvent(SCHEDULE);
void EditEvent(SCHEDULE);

Date GetCurrentDate();
char* ValidInput(char*);