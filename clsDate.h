#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<vector>
using namespace std;

class clsDate
{
    short day = 1;
    short month = 1;
    short year = 2000;

public:
    clsDate() {
        time_t t = time(0);
        tm* now = localtime(&t);
        day = now->tm_mday;
        month = now->tm_mon + 1;
        year = now->tm_year + 1900;
    }
    clsDate(string sDate) {
        vector<string> vDate;
        vDate = clsDate::Split(sDate, ",");
       
            day = stoi(vDate[0]);
            month = stoi(vDate[1]);
            year = stoi(vDate[2]);
        
    }
    clsDate(short day, short month, short year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    clsDate(short dateOrderInYear, short _year) {
        //This will construct a date by date order in year
        clsDate Date1 = GetDateFromDayOrderInYear(dateOrderInYear, _year);
        day = Date1.day; 
        month = Date1.month; 
        year = Date1.year;
    }
    void SetDay(short d) {
        day = d;
    }
    short getDay() {
        return day;
    }
    __declspec(property(get = GetDay, put = SetDay))short Day;

    void SetMonth(short m) {
        month = m;
    }
    short GetMonth() {
        return month;
    }
    __declspec(property(get = GetMonth, put = SetMonth))short Month;

    void SetYear(short y) {
        year = y;
    }
    short GetYear() {
        return year;
    }
    __declspec(property(get = GetYear, put = SetYear))short year;

     static short DayOfWeekOrder(short _day, short _month, short _year) {
        short a, y, m;
        a = (14 - _month) / 12;
        y = _year - a;
        m = _month + (12 * a) - 2;
        return (_day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

     short DayOfWeekOrder() {
         return DayOfWeekOrder(day, month, year);
     }

    void Print() {
        cout << DateToString() << endl;
    }

  static  string DateToString(clsDate date ) {
        return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
    }

    string DateToString() {
        return DateToString(*this);
    }

  static  string DayShortName(short _day) {
        string arr[] = { "sun","mon","tue","wednes","thures","fri","sat" };
        return arr[_day - 1];
    }

  string DayShortName() {
      string arr[] = { "sun","mon","tue","wednes","thures","fri","sat" };
      return DayShortName(DayOfweekOrder(day,month,year));
  }

  static string DayShortName(short _day, short _month, short _year) {
      string arr[] = { "sun","mon","tue","wednes","thures","fri","sat" };
      return arr[DayOfWeekOrder(_day, _month, _year)];
  }
  
   static string MonthName(short _month) {
        string arrMonth[12] = { "Jan","Feb","March","April","May","June","Jully","Aug","Sep","Oct","Nov","Des" };
        return arrMonth[_month - 1];
    }

   string MonthName() {
       return MonthName(month);
   }

   static void PrintMonthCaledar(short _month, short _year) {
        int numberOfDays;
        int currentDay = DayOfWeekOrder(1, _month, _year);
        numberOfDays = NumberOfDaysInMonth(_month, _year);
        printf("__________________________%s_________________________\n\n", MonthName(_month).c_str());
        printf("  sun  mon  tue  wed  thu  fri  sat\n ");
        int i;
        for (i = 0; i < currentDay; i++)
            printf("     ");
        for (int j = 1; j <= numberOfDays; j++) {
            printf("%5d", j);
            if (++i == 7) {
                i = 0;
                printf("\n");
            }
        }
        printf("\n _______________________________________________________________\n");
    }

   void AddDays(short days) {
       short RemainingDate = days + NumberOfDaysFromBeginingOfYear(day, month, year);
       short MonthDays = 0;
       month = 1;
       while (1) {
           MonthDays = NumberOfDaysInMonth(month, year);
           if (RemainingDate > MonthDays) {
               RemainingDate -= MonthDays;
               month++;
               if (month > 12) {
                   month = 1;
                   year++; 
               }
           }
           else {
               day = RemainingDate;
               break;

           }
       }
   }


   void PrintMonthCaledar() {
       PrintMonthCaledar(month, year);
   }

   static void PrintYearCalendar(short _year) {
       printf("\n_________________________________________________________________\n\n");
       printf("        Calendar_ %d\n", _year);
        cout << "---------------------------------------------------------------------\n";

        for (int i = 1; i <= 12; i++) {
           PrintMonthCaledar(i, _year);
        }
        return;
    }

   void PrintYearCalendar() {
       PrintYearCalendar(year);
   }

  static short NumberOfDaysFromBeginingOfYear(short _day, short _month, short _year) {
        short totalDays = 0;
        for (int i = 1; i <= _month - 1; i++) {
            totalDays += NumberOfDaysInMonth(i, _year);
        }
        totalDays += _day;
        return totalDays;
    }

  short NumberOfDaysFromBeginingOfYear() {
      return NumberOfDaysFromBeginingOfYear(day, month, year);
  }

   static clsDate GetDateFromDayOrderInYear(short DateOrder, short year) {
        clsDate date;
        short RemainingYear = DateOrder;
        date.year = year;
        date.month = 1;
        while (1) {
            short Monthdayes = NumberOfDaysInMonth(date.month, year);
            if (RemainingYear > Monthdayes) {
                RemainingYear -= Monthdayes;
                date.month++;
            }
            else {
                date.day = RemainingYear;
                break;
            }
        }
        return date;
    }

  static  bool IsDate1BeforeDate2(clsDate date1, clsDate date2) {
        return (date1.year < date2.year) ? true : ((date1.year == date2.year) ? ((date1.month < date2.month) ? true :
            ((date1.month == date2.month) ? (date1.day < date2.day) : false)) : false);
    }

  // note :*This means the current date

  bool UsDate1BeforeDate2(clsDate date2) {
      return IsDate1BeforeDate2(*this, date2);
  }

  static  bool DatesAreEquals(clsDate d1, clsDate d2) {
        return (d1.year == d2.year) ? ((d1.month == d2.month) ? ((d1.day == d2.day) ? true : false) : false) : false;
    }

  bool DatesAreEquals(clsDate date2) {
      return DatesAreEquals(*this, date2);
  }

  static  bool IsLastDayInMonth(clsDate d) {
        return (d.day == NumberOfDaysInMonth(d.month, d.year));
    }

  bool IsLastDayInMonth() {
      return IsLastDayInMonth(*this);
  }
   static bool IsLastMonthInYear(short month) {
        return (month == 12);
    }

   bool IsLastMonthInYear() {
       return IsLastMonthInYear(month);
   }

  static  clsDate AddOneDay(clsDate date) {
        if (IsLastDayInMonth(date)) {
            if (IsLastMonthInYear(date.month)) {
                date.day = 1;
                date.month = 1;
                date.year++;
            }
            else {
                date.day = 1;
                date.month++;
            }
        }
        else {
            date.day++;
        }
        return date;
    }

  void AddOneDay() {
      *this = AddOneDay(*this);
  }

    int GetDifferenceInTwoDates(clsDate d1, clsDate d2){
         int days = 0;
         while (IsDate1BeforeDate2(d1, d2)) {
             days++;
             d1 = AddOneDay(d1);
         }
         return days;
 }
  static  clsDate GetSystemDate() {
        //System date
        time_t t = time(0);
        tm* now = localtime(&t);
        short _day, _month, _year;
        _year = now->tm_year + 1900;
        _month = now->tm_mon + 1;
        _day = now->tm_mday;
        return clsDate(_day,_month,_year);
    }

  static void SwapTwoDates(clsDate& d1, clsDate& d2) {
      clsDate temp;
      temp = d1;
      d1 = d2;
      d2 = temp;
  }

   void SwapTwoDates(clsDate d2) {
       SwapTwoDates(*this, d2); 
   }

  static  int GetDifferenceInDays(clsDate d1, clsDate d2, bool IncludeEndDay=false) {
      //This will Take care of neative diff
        int days = 0;
        int swapflag = 1;
        if (!IsDate1BeforeDate2(d1, d2)) {
            //swap days
            SwapTwoDates(d1, d2);
            swapflag = -1;
        }
        while (IsDate1BeforeDate2(d1, d2)) {
            days++;
            d1 = AddOneDay(d1);
        }
        return IncludeEndDay ? ++days * swapflag : days * swapflag;
    }

  int GetDifferenceInDays(clsDate d2, bool IncludeEndDay = false) {
      return GetDifferenceInDays(*this, d2, IncludeEndDay);
  }

  static short CalCulateMyAgeInDays(clsDate dateOfBirth) {
      return GetDifferenceInDays( dateOfBirth,clsDate::GetSystemDate(),true);
  }

   static clsDate AddingXdays(clsDate d, short number) {
        for (short i = 1; i <= number; i++) {
            d = AddOneDay(d);
        }
        return d;
    }

   void AddingXdays(short days) {
      *this= AddingXdays(*this,days);
   }
   static clsDate AddingOneWeek(clsDate d) {
        for (short i = 1; i <= 7; i++) {
            d = AddOneDay(d);
        }
        return d;
    }

   void addingOneWeek() {
      *this= AddingOneWeek(*this);
   }

   static clsDate IncreaseXweeks(short weeks, clsDate date) {
       for (short i = 1; i <= weeks; i++) {
           date = AddingOneWeek(date);
       }
       return date;
  }
   void IncreaseXweeks(short weeks) {
       *this = IncreaseXweeks(weeks, *this);
   }

  static  clsDate AddingOneMonth(clsDate d) { 
        if (d.month == 12) {
            d.year++;
            d.month = 1;
        }
        else {
            d.month++;
        }
        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(d.month, d.year);
        if (d.day > NumberOfDaysInCurrentMonth) {
            d.day = NumberOfDaysInCurrentMonth;
        }
        return d;
    }

  void AddingOneMonth() {
     *this= AddingOneMonth(*this);
  }

  static  clsDate AddingXMonth(clsDate d, short months) {
        for (short i = 1; i <= months; i++) {
            d = AddingOneMonth(d);
        }
        return d;
    }
  void AddingXMonth(short months) {
     *this= AddingXMonth(*this, months);
  }
  static  clsDate AddingOneYear(clsDate d) {
        d.year++;
        return d;
    }

  void AddingOneYear() {
      *this = AddingOneYear(*this);
  }
   static clsDate AddingXYears(clsDate d, short years) {
        for (short i = 1; i <= years; i++) {
            d = AddingOneYear(d);
        }
    }

   void AddingXYears(short years) {
       *this = AddingXYears(*this, years);
   }
  static  clsDate AddingOneDecade(clsDate d) {
        d = AddingXYears(d, 10);
        return d;
    }

  void AddingOneDecade() {
      *this = AddingOneDecade(*this);
  }

   static clsDate AddingXDecades(clsDate d, short decades) {
        for (short i = 1; i <= decades; i++) {
            d = AddingOneDecade(d);
        }
        return d;
    }

   void AddingXDecades(short decades) {
       *this = AddingXDecades(*this, decades);
   }
   static clsDate AddingOneCentury(clsDate d) {
        d = AddingXDecades(d, 10);
        return d;
    }

   void AddingOneCentury() {
       *this = AddingOneCentury(*this);
   }
  static  clsDate AddingXCentury(clsDate d, short century) {
        for (short i = 1; i <= century; i++) {
            d = AddingOneCentury(d);
        }
        return d;
    }

  void Addingxcentury(short century) {
      *this = AddingXCentury(*this, century);
  }
   static clsDate AddingOneMillenium(clsDate d) {
        d = AddingXCentury(d, 10);
        return d;
    }

   void AddingOneMillenium() {
       *this = AddingOneMillenium(*this);
   }
   static clsDate DecreaseOneDay(clsDate date) {
        if (date.day == 1) {
            if (date.month == 1) {
                date.day = 31;
                date.month = 12;
                date.year--;
            }
            else {
                date.month--;
                date.day = NumberOfDaysInMonth(date.month, date.year);
            }
        }
        else {
            date.day--;
        }
        return date;
    }

   void DecreaseOneDay() {
       *this = DecreaseOneDay(*this);
   }
  static  clsDate DecreaseXdays(short days, clsDate date) {
        for (short i = 1; i <= days; i++) {
            date = DecreaseOneDay(date);
        }
        return date;
    }

  void DecreaseXdays(short days) {
      *this = DecreaseXdays(days, *this);
  }
   static clsDate DecreaseOneWeek(clsDate date) {
        for (short i = 1; i <= 7; i++) {
            date = DecreaseOneDay(date);
        }
        return date;
    }

   void DecreaseOneWeek() {
       *this = DecreaseOneWeek(*this);
   }
  static  clsDate DecreaseXWeeks(short weeks, clsDate date) {
        for (short i= 1; i <= weeks; i++) {
            date = DecreaseOneWeek(date);
        }
        return date;
    }

  void DecreaseXweeks(short weeks) {
      *this = DecreaseXWeeks(weeks, *this);
  }
  static  clsDate DecreaseOneMonth(clsDate date) {
        if (date.month == 1) {
            date.month = 12;
            date.year--;
        }
        if (IsLastDayInMonth(date)) {
            date.month--;
            date.day = NumberOfDaysInMonth(date.month, date.year);
        }
        else {
            date.month--;
        }
        return date;
    }

  void DecreaseOneMonth() {
      *this = DecreaseOneMonth(*this);
  }
 static  clsDate DecreaseXMonth(short months, clsDate date) {
        for (short i = 1; i <= months; i++) {
            date = DecreaseOneMonth(date);
        }
        return date;
    }

 void DecreaseXmonth(short months) {
     *this = DecreaseXMonth(months, *this);
 }
    static clsDate DecreaseOneYear(clsDate date) {
        date.year--;
        return date;
    }

    void DecreaseOneYear() {
        *this = DecreaseOneYear(* this);
    }
   static clsDate DecreaseXYears(short years, clsDate date) {
        date.year -= years;
        return date;
    }

   void DecreaseXyears(short years) {
       *this = DecreaseXYears(years, *this);
   }
  static  clsDate DecreaseOneDecade(clsDate date) {
        date.year -= 10;
        return date;
    }

  void DecreaseOneDecade() {
      *this = DecreaseOneDecade(*this);
  }
  static   clsDate DecreaseXDecades(short decades, clsDate date) {
        date.year -= (decades * 10);
        return date;
    }

  void DecreaseXDecades(short decades) {
      *this = DecreaseXDecades(decades, *this);
  }
  static   clsDate DecreaseOneCentury(clsDate date) {
        date.year -= 100;
        return date;
    }

  void DecreaseOneCentury() {
      *this = DecreaseOneCentury(*this);
  }
  static  clsDate DecreaseOneMillinum(clsDate date) {
        date.year -= 1000;
        return date;
    }

  void DecreaseOneMillinum() {
      *this = DecreaseOneMillinum(*this);
  }
   static short DayOfweekOrder(short day, short month, short year) {
        short a, y, m;
        a = (14 - month) / 12;
        y = year - a;
        m = month + (12 * a) - 2;
        return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder(clsDate date) {
        return DayOfWeekOrder(date.day, date.month, date.year);
    }
   
   static bool IsEndOfWeek(clsDate date) {
        return DayOfWeekOrder(date.day,date.month,date.year) == 6;
    }

   bool IsEndOfWeek() {
       return IsEndOfWeek(*this);
   }

  static  bool IsWeekEnd(clsDate date) {
        short dayIndex = DayOfWeekOrder(date.day,date.month,date.year);
        return (dayIndex == 5 || dayIndex == 6);
    }

  bool IsWeekEnd() {
      return IsWeekEnd(*this);
  }
  static  bool IsBussinusDay(clsDate date) {
        return (!IsWeekEnd(date));
    }

  bool IsBussinusDay() {
      return IsBussinusDay(*this);
  }
   static short DayUntilTheWeekEnd(clsDate date) {
        return 6 - DayOfWeekOrder(date.day,date.month,date.year);
    }

   short DayUntilTheWeekEnd() {
       return DayUntilTheWeekEnd(*this);
   }

   static short DayUntilTheEndOfMonth(clsDate date) {
       clsDate EndOfMonthDate;
       EndOfMonthDate.day = NumberOfDaysInMonth( date.month, date.year);
       EndOfMonthDate.month = date.month;
       EndOfMonthDate.year = date.year;
       return GetDifferenceInDays(date, EndOfMonthDate,true);
   }
    short DayUntilTheEndOfMonth() {
        return DayUntilTheEndOfMonth(*this);
    }

  static  short DayUntilEndOfYear(clsDate date) {
        clsDate yearDate;
        yearDate.day = 31;
        yearDate.month = 12;
        yearDate.year = date.year;
        return GetDifferenceInDays(yearDate, date);
    }

  short DayUntilEnfOfYear() {
      return DayUntilEndOfYear(*this);
  }

  //Calculate Business days between 2 days
  static short CalculateBusinessDays(clsDate d1, clsDate d2) {
      short days = 0;
      while (IsDate1BeforeDate2(d1, d2)) {
          if (IsBussinusDay(d1))
              days++;
          d1 = AddOneDay(d1);
      }
      return days;
  }

  short CalculateBusinessDays(clsDate d) {
      return CalculateBusinessDays(*this, d);
 }

   static short CalculateVacasionDays(clsDate d1, clsDate d2) {
        short count = 0;
        while (IsDate1BeforeDate2(d1, d2)) {
            if (IsBussinusDay(d1)) {
                count++;
                d1 = AddOneDay(d1);
            }
        }
        return count;
    }

   short CalculateVacasionDays(clsDate d) {
       return CalculateVacasionDays(*this, d);
   }

   static  clsDate CalculateVacasionReturnDate(clsDate date, short number) {
       short weekendcount = 0;
       while (IsWeekEnd(date)) {
           date = AddOneDay(date);
       }
       for (short i = 1; i <= number + weekendcount; i++) {
           if (IsWeekEnd(date))
               weekendcount++;
           date = AddOneDay(date);
       }
       while (IsWeekEnd(date)) {
           date = AddOneDay(date);
       }
       return date;
   }

  static  bool IsDate1AfterDate2(clsDate d1, clsDate d2) {
        return (!IsDate1BeforeDate2(d1, d2) && !DatesAreEquals(d1, d2));
    }

  bool IsDate1AfterDate2(clsDate d) {
      return IsDate1AfterDate2(*this, d);
  }

    enum enNumber { before = -1, equal = 0, after = 1 };

  static  enNumber CompareTwoDates(clsDate d1, clsDate d2) {
        if (IsDate1BeforeDate2(d1, d2))
            return enNumber::before;
        else if (IsDate1AfterDate2(d1, d2))
            return enNumber::after;
        else
            return enNumber::equal;
    }

  enNumber CompareTwoDates(clsDate d) {
      return CompareTwoDates(*this, d);
  }

  static  bool IsvalidateDate(clsDate date) {
        if (date.day < 1 || date.day>31)
            return false;
        if (date.month < 1 || date.month>12)
            return false;
        if (date.month == 2) {
            if (IsLeapYear(date.year)) {
                if (date.day < 1 || date.day>29)
                    return false;
            }
            else {
                if (date.day < 1 || date.day>28)
                    return false;
            }
        }
        if (date.day > NumberOfDaysInMonth(date.month, date.year))
            return false;
        return true;
    }

  bool IsValidDate() {
      return IsvalidateDate(*this);
  }

  static  short NumberOfDaysInMonth(short _month, short _year) {
        if (_month == 2)
            return IsLeapYear(_year) ? 29 : 28;
        short arr[] = {1,3,5,7,8,10,12};
        for (int i = 0; i <7; i++) {
            if (_month == arr[i])
                return 31;
        }
        return 30;
    }

  short NumberOfDaysInMonth() {
      return NumberOfDaysInMonth(month, year);
  }

  static short NumberOfHoursInMonth(short _month, short _year) {
      return NumberOfDaysInMonth(_month, _year) * 24;
  }

  short NumberOfHoursInMonth() {
      return NumberOfHoursInMonth(month, year);
  }

  static int NumberOfMinutesInMonth(short _month, short _year) {
      return NumberOfHoursInMonth(_month, _year) * 60;
  }

  int NumberOfMinutesInMonth() {
          return NumberOfMinutesInMonth(month, year);
  }

  static int NumberOfSecondsInMonth(short _month, short _year) {
      return NumberOfMinutesInMonth(_month, _year) * 60;
  }

  int NumberOfSecondsInMonth() {
      return NumberOfSecondsInMonth(month, year);
  }
  
  static  bool IsLeapYear(short _year) {
        return (_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0);
    }

  bool IsLeapYear() {
      return IsLeapYear(year);
 }

  static short NumberOfDaysInYear(short _year) {
      return IsLeapYear(_year) ? 365 : 364;
  }

  short NumberOfDaysInYear() {
      return NumberOfDaysInYear(year);
  }

  static short NumberOfHoursInYear(short _year) {
      return NumberOfDaysInYear(_year) * 24;
  }

  short NumberOfHoursInYear() {
      return NumberOfDaysInYear(year);
  }

  static int NumberOfMinutesInYear(short year) {
      return NumberOfHoursInYear(year) * 60;
  }

  int NumberOfMinutesInYear() {
      return NumberOfMinutesInYear(year);
  }

  static int NumberOfSecondsInYear(short _year) {
      return NumberOfMinutesInYear(_year) * 60;
  }

  int NumberOfseconds() {
      return NumberOfSecondsInYear(year);
  }

 static vector<string> Split(string s, string sep) {
      vector<string> vDate;
      int pos = 0;
      string s1 = "";

      while ((pos = s.find(sep)) != std::string::npos) {
       s1 =  s.substr(0, pos);
          if (s1 != "") {
              vDate.push_back(s1);
          }
       s = s.erase(0, pos + sep.length());
      }
      if (s != "")
          vDate.push_back(s);
      return vDate;
  }

};