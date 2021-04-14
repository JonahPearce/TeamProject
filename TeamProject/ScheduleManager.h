#define MAX_DAYS 31
#define MAX_MONTHS 12
#define MAX_YEARS 10
#define MAX_INPUT 100

typedef struct Day {
	int Time;
	char EventName[MAX_INPUT];
}Day;

typedef struct Month {
	Day Day[MAX_DAYS];
}Month;

typedef struct Year {
	Month Month[MAX_MONTHS];
	int YearID;
}Year;

typedef struct Date {
	int Time;
	int Day;
	int Month;
	int Year;
}Date;

typedef struct Schedule {
	Year Year[MAX_YEARS];
	Date CurrentDate;
}Schedule, * SCHEDULE;

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