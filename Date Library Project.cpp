// Date Library Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"clsDate.h";
using namespace std;
int main()
{
	clsDate Date1;
	Date1.Print();

	clsDate Date2("26,5,2005");
	Date2.Print();

	clsDate Date3(20, 12, 2020);
	Date3.Print();
   
	clsDate Date4(40, 2020);
	Date4.Print();

	Date1.AddingOneMonth();
	Date1.Print();

	Date3.PrintYearCalendar();
	//cout << Date2.IsValidDate() << endl;

	cout << "My Age InDays :" << clsDate::CalCulateMyAgeInDays(clsDate(26, 5, 2005)) << endl;


	//You Can Try any method at your own...

	system("pause>0");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
