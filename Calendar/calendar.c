#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<windows.h>

void display(int, int, int, int[]);
void calendar(int, int);

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

char* month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char* week[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

int main()
{
    int nmonth, nyr, ch;
enteryear:
    while (1)
    {
        printf("Enter year and month (ex: 1923 01):");
        scanf("%d%d", &nyr, &nmonth);
        if (nyr < 1923)
        {
            printf("\n\t Enter a year above 1923\n");
            continue;
        }
        else
        {
            calendar(nyr, nmonth);
        }
        while (1)
        {
            gotoxy(20, 20); printf("Use LEFT, RIGHT, UP and DOWN arrows for navigation");
            gotoxy(20, 22); printf("Press Y to change the date");
            gotoxy(20, 24); printf("Press Esc to exit");
            switch (_getch())
            {
            case 72: //Up
                if (nmonth == 1)
                {
                    nyr--;
                    nmonth = 12;
                }
                else
                    nmonth--;
                calendar(nyr, nmonth);
                break;
            case 75: //Left
                if (nyr == 1923)
                {
                    gotoxy(15, 2); printf("Year below 1923 not available");
                }
                else
                {
                    nyr--;
                    calendar(nyr, nmonth);
                }
                break;
            case 77: //Right
                nyr++;
                calendar(nyr, nmonth);
                break;
            case 80: //Down
                if (nmonth == 12)
                {
                    nmonth = 1;
                    nyr++;
                }
                else
                {
                    nmonth++;
                }
                calendar(nyr, nmonth);
                break;
            case 27: //Esc
                system("cls");
                exit(0);
            case 121: //y
                system("cls");
                goto enteryear;
            }
        }
        break;

    }
    _getch();
    return 0;
}


void display(int nyr, int nmonth, int tdays, int days[])
{
    int i, j, pos;
    SetColor(12);
    gotoxy(56, 6); printf("%s %d", month[nmonth - 1], nyr);
    SetColor(10);
    for (i = 0, pos = 30; i < 7; i++, pos += 10)
    {
        gotoxy(pos, 8); printf("%s", week[i]);
    }

    SetColor(15);
    tdays++;
    switch (tdays)
    {
    case 0:
    case 7: pos = 91;
        break;
    case 1: pos = 31;
        break;
    case 2: pos = 41;
        break;
    case 3: pos = 51;
        break;
    case 4: pos = 61;
        break;
    case 5: pos = 71;
        break;
    case 6: pos = 81;
        break;
    }

    SetColor(7);
    for (i = 0, j = 10, pos; i < days[nmonth - 1]; i++, pos += 10)
    {
        gotoxy(pos, j); printf("%d", i + 1);
        if (pos == 91)
        {
            pos = 21;
            j++;
        }
    }

    SetColor(5);

    for (i = 22; i < 102; i++)
    {
        gotoxy(i, 4); printf("%c", 196);
        gotoxy(i, 17); printf("%c", 196);
    }

    gotoxy(21, 4); printf("%c", 218);
    gotoxy(102, 4); printf("%c", 191);
    gotoxy(21, 17); printf("%c", 192);
    gotoxy(102, 17); printf("%c", 217);

    for (i = 5; i < 17; i++)
    {
        gotoxy(21, i); printf("%c", 179);
        gotoxy(102, i); printf("%c", 179);
    }
}

void calendar(int nyr, int nmonth)
{
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int tdays = 0, k, myear;
    system("cls");
    myear = nyr - 1;
    if (myear >= 1923)
    {
        for (k = 1923; k <= myear; k++)
        {
            if (k % 4 == 0)
                tdays = tdays + 366;
            else
                tdays = tdays + 365;
        }
    }

    if (nyr % 4 == 0)
        days[1] = 29;
    else
        days[1] = 28;

    for (k = 0; k < (nmonth - 1); k++)
    {
        tdays = tdays + days[k];
    }

    tdays = tdays % 7;
    display(nyr, nmonth, tdays, days);
}