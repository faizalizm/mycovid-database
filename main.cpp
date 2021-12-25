/*
		|------------------------------------------------------------------
		| Program Developed and Maintained w/ ❤  :-
		| DeadLine Chasers | DLC
		|------------------------------------------------------------------
		| Works Best on the IDE :-
		| Replit.com
		|------------------------------------------------------------------
*/	

#include "myCovid.h"

int main() {
	Malaysia* my = new Malaysia(); // create instance of struct
	MyCovid mcd(my); // create class object, pass the struct instance for class constructer
	vector<State> StateList;
	State s;
	int choice;

	// header
	cout << "\n====================================================  ❤\n"
		<< "\n-= Welcome to Malaysia's Covid-19 Record Database =-\n"
		<< "\n====================================================  ❤\n"
		<< "\n  Legend :-"
		<< "\n  -----------------------------------------------"
		<< "\n  ->\t\t\t\t\tdenotes an Input/Output"
		<< "\n  -----------------------------------------------"
		<< "\n  [1][2][3][4]\t\t\tdenotes Number Choices"
		<< "\n  -----------------------------------------------"
		<< "\n  -= !! Msg !! =-\t\tdenotes a Notice"
		<< "\n  -----------------------------------------------\n"
		<< "\n====================================================  ❤";
	
	do {
		choice = mcd.menu();
		
		switch (choice) {
		  case 1 : {
				Record* aRec = new Record();
				mcd.newRecord(my, aRec);
				break;
			}
    	case 2 :
				mcd.report(my);
				break;
			case 3 :
				cout << "\n\t-= !! Entering Analyzation Menu !! =-\n";
				mcd.analysis(&StateList, s, my);
				break;
			case 4 :
				cout << "\n\t-= !! Exiting !! =-\n";
				break;
		}
		
		if (choice > 4 || choice < 1)
			cout << "\n\t-= !! Error : Value Out of Bound !! =-";
			
	} while (choice != 4);

	// footer
	cout << "\n====================================================  ❤"
		<< "\n\n Thank you and remember to keep social distancing !   \n"
		<< "\n            _o_        6 feet        _o_                  "
		<< "\n             |      <---------->      |                   "
		<< "\n             /\\                       /\\              \n"
		<< "\n====================================================  ❤\n"
		<< "\n    © 2021 MyCovid Database All Rights Reserved           "
		<< "\n      -----------------------------------------           "
		<< "\n      Program Developed and Maintained w/ ❤  :-          "
		<< "\n      DeadLine Chasers | DLC \n                           "
		<< "\n====================================================  ❤\n";

  return 0;
}
