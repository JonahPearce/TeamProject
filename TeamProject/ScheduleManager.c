#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "ScheduleManager.h"
#include "FileManager.h"

bool Exit = false;
char* MenuOutput = "";

const char* MonthNames[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void ScheduleManager() {
    SCHEDULE Scheduler = (SCHEDULE)malloc(sizeof(Schedule) + 1);
    Scheduler->CurrentDate = GetCurrentDate();

    for (int YEAR = 0; YEAR < (MAX_YEARS); YEAR++) {
        Scheduler->Year[YEAR].YearID = Scheduler->CurrentDate.Year + YEAR;
        for (int MONTH = 0; MONTH < (MAX_MONTHS); MONTH++) {
            for (int DAY = 0; DAY < (MAX_DAYS); DAY++) {
                Scheduler->Year[YEAR].Month[MONTH].Day[DAY].Time = 0;
                strcpy(Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName, "");
            }
        }
    }
    while (Exit == false) {

        system("@cls||clear");
        DisplayMenu(Scheduler);

        MenuOutput = "";
        char Input = MenuInput("abcd");

        switch (Input) {
        case 'a':
            AddEvent(Scheduler);
            break;
        case 'b':
            DeleteEvent(Scheduler);
            break;
        case 'c':
            EditEvent(Scheduler);
            break;
        case 'd':
            Exit = true;
            break;
        }
    }

    return 0;
}

void DisplayMenu(SCHEDULE Scheduler) {
    printf("Schedule Manager\n");
    printf("###############################\n");
    printf("List of commands:\n");
    printf("a) Add a new Event\n");
    printf("b) Delete an Event\n");
    printf("c) Edit an Event\n");
    printf("d) Exit\n");
    printf("###############################\n");
    printf("CurrentDate: %s %d, %d\n", MonthNames[Scheduler->CurrentDate.Month - 1], Scheduler->CurrentDate.Day, Scheduler->CurrentDate.Year);
    printf("###############################\n");
    for (int YEAR = 0; YEAR < (MAX_YEARS); YEAR++) {
        for (int MONTH = 0; MONTH < (MAX_MONTHS); MONTH++) {
            for (int DAY = 0; DAY < (MAX_DAYS); DAY++) {
                if (strcmp("", Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName) != 0) {
                    printf("%s: %s %d, %d\n", Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName, MonthNames[MONTH], DAY + 1, Scheduler->Year[YEAR].YearID);
                }
            }
        }
    }
    printf("###############################\n");
    printf("\n%s\n", MenuOutput);
    printf("\nEnter Option: ");
}

void AddEvent(SCHEDULE Scheduler) {
    int YEAR, MONTH, DAY, TIME;
    YEAR = AddYear(Scheduler);
    MONTH = AddMonth(Scheduler);
    DAY = AddDay(Scheduler, MONTH);
    TIME = AddTime(Scheduler);
    char* Input = ValidInput("\nPlease enter a name for the Event: ");
    strcpy(Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName, Input);
    Scheduler->Year[YEAR].Month[MONTH].Day[DAY].Time = TIME;
    MenuOutput = "Created Event!";
}

int AddYear(SCHEDULE Scheduler) {
    int YEAR;
    bool Valid = false;
    while (Valid == false) {
        YEAR = atoi(ValidInput("\nPlease enter the year: "));
        if (YEAR >= Scheduler->CurrentDate.Year && YEAR < (Scheduler->CurrentDate.Year + MAX_YEARS)) {
            Valid = true;
        }
    }
    return YEAR - Scheduler->CurrentDate.Year;
}

int AddMonth(SCHEDULE Scheduler) {
    int MONTH;
    bool Valid = false;
    while (Valid == false) {
        MONTH = atoi(ValidInput("\nPlease enter the number of the month: "));
        if (MONTH > 0 && MONTH < (1 + MAX_MONTHS)) {
            Valid = true;
            MONTH -= 1;
        }
    }
    return MONTH;
}

int AddDay(SCHEDULE Scheduler, int MONTH) {
    int DAY;
    bool Valid = false;
    while (Valid == false) {
        DAY = atoi(ValidInput("\nPlease enter the day: "));
        if (DAY > 0 && DAY < (MonthDays[MONTH] + 1)) {
            Valid = true;
            DAY -= 1;
        }
    }
    return DAY;
}

int AddTime(SCHEDULE Scheduler) {
    int TIME;
    bool Valid = false;
    while (Valid == false) {
        printf("\n1. Morning");
        printf("\n2. Afternoon");
        printf("\n3. Evening");
        TIME = atoi(ValidInput("\nPlease enter one of the options number: "));
        if (TIME > 0 && TIME < 4) {
            Valid = true;
        }
    }
    return TIME;
}

void DeleteEvent(SCHEDULE Scheduler) {
    char* Delete = ValidInput("\nPlease enter the name of the Event you want to delete: ");
    MenuOutput = "No event found with that name!";
    for (int YEAR = 0; YEAR < (MAX_YEARS); YEAR++) {
        for (int MONTH = 0; MONTH < (MAX_MONTHS); MONTH++) {
            for (int DAY = 0; DAY < (MAX_DAYS); DAY++) {
                if (strcmp(Delete, Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName) == 0) {
                    strcpy(Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName, "");
                    Scheduler->Year[YEAR].Month[MONTH].Day[DAY].Time = 0;
                    MenuOutput = "Deleted an Event!";
                }
            }
        }
    }
}

void EditEvent(SCHEDULE Scheduler) {
    char* Edit = ValidInput("\nPlease enter the name of the Event you want to edit: ");
    MenuOutput = "No event found with that name!";
    for (int YEAR = 0; YEAR < (MAX_YEARS); YEAR++) {
        for (int MONTH = 0; MONTH < (MAX_MONTHS); MONTH++) {
            for (int DAY = 0; DAY < (MAX_DAYS); DAY++) {
                if (strcmp(Edit, Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName) == 0) {

                    int Year = YEAR;
                    int Month = MONTH;
                    int Day = DAY;
                    int Time = Scheduler->Year[YEAR].Month[MONTH].Day[DAY].Time;
                    char Name[MAX_INPUT];
                    strcpy(Name, Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName);
                    strcpy(Scheduler->Year[YEAR].Month[MONTH].Day[DAY].EventName, "");
                    Scheduler->Year[YEAR].Month[MONTH].Day[DAY].Time = 0;
                    bool ExitEditor = false;
                    while (ExitEditor == false) {

                        printf("\na) Edit Year");
                        printf("\na) Edit Month");
                        printf("\na) Edit Day");
                        printf("\na) Edit Time");
                        printf("\na) Exit Editor\n\n");

                        char Input = MenuInput("abcde");
                        switch (Input) {
                        case 'a':
                            Year = AddYear(Scheduler);
                            break;
                        case 'b':
                            Month = AddMonth(Scheduler);
                            break;
                        case 'c':
                            Day = AddDay(Scheduler, Month);
                            break;
                        case 'd':
                            Time = AddTime(Scheduler);
                            break;
                        case 'e':
                            strcpy(Scheduler->Year[Year].Month[Month].Day[Day].EventName, Name);
                            Scheduler->Year[Year].Month[Month].Day[Day].Time = Name;
                            Exit = true;
                            break;
                        }
                    }
                    MenuOutput = "Event Edited!";
                }
            }
        }
    }
}


Date GetCurrentDate() {
    time_t Timer;
    struct tm* TimeInfo;
    char Day[MAX_INPUT], Month[MAX_INPUT], Year[MAX_INPUT];

    time(&Timer);
    TimeInfo = localtime(&Timer);

    strftime(Day, 3, "%d", TimeInfo);
    strftime(Month, 3, "%m", TimeInfo);
    strftime(Year, 5, "%Y", TimeInfo);

    Date CurrentDate;
    CurrentDate.Day = atoi(Day);
    CurrentDate.Month = atoi(Month);
    CurrentDate.Year = atoi(Year);

    return CurrentDate;
}

char* ValidInput(char* Text) {
    static char Input[MAX_INPUT];
    printf("\n%s", Text);
    gets(Input);
    return Input;
}