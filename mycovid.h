#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct State {
	string Name;
	int New;
	int Recovered;
	int Active;
};

struct Record {
		string State;
		int New;
		int Import;
		int Recovered;
		int Active;
		int Child;
		int Adolescent;
		int Adult;
		int Elderly;
		string Status = "Unavailable";
		Record *next;
};

struct Malaysia {
	int totalState;
	Record *head, *tail;
};

class MyCovid {
	public :
	MyCovid(Malaysia* my) {	
		my->head = my->tail = NULL;
		my->totalState = 0;
	}
	
	int menu() {
		int choice;
		cout << "\n\n\tMain Menu :-"
			<< "\n\t[1] Create Record"
			<< "\n\t[2] Display Report"
			<< "\n\t[3] Analyze Report"
			<< "\n\t[4] Exit Program"
			<< "\n->\tEnter Choice : ";
		cin >> choice;
		
		// error checking for if a user entered string instead of int
		while (cin.fail()) {
			cin.clear(); // clear the error flag on cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore characters in input buffer until \n is found
			cout << "\n\t-= !! Error : Entered String Value !! =-\n"
				<< "\n->\tEnter Choice : ";
			cin >> choice;
		}

		return choice;
	}

	void newRecord(Malaysia* my, Record* aRec) {
		cout << "\n\t-= !! Record Creation Begins !! =-\n";
		cout << "\n->\tEnter State : ";
		cin >> ws;
		getline(cin, aRec->State);
		cout << "->\tEnter New Case(s) : ";
		cin >> aRec->New;
		cout << "->\tEnter Import Case(s) : ";
		cin >> aRec->Import;
		cout << "->\tEnter Recoveries : ";
		cin >> aRec->Recovered;
		cout << "->\tEnter Active Case(s) : ";
		cin >> aRec->Active;
		cout << "->\tEnter Number of Child Case(s) : ";
		cin >> aRec->Child;
		cout << "->\tEnter Number of Adolescent Case(s) : ";
		cin >> aRec->Adolescent;
		cout << "->\tEnter Number of Adult Case(s) : ";
		cin >> aRec->Adult;
		cout << "->\tEnter Number of Elderly Case(s) : ";
		cin >> aRec->Elderly;
		progress(aRec);
		aRec->next = NULL;

		// error checking for negative or string value on input
		if (aRec->New >= 0 && aRec->Import >= 0 && aRec->Recovered >= 0 && aRec->Active >= 0 &&
		    aRec->Child >= 0 && aRec->Adolescent >= 0 && aRec->Adult >= 0 && aRec->Elderly >= 0)
		{
			insert(my, aRec); 
			my->totalState++;
			cout << "\n\t-= !! Record Sucessfully Logged !! =-\n";
		}
		else {
			if (cin.fail())
				cout << "\n\n\t-= !! Error : Entered String Value on Input !! =-";
			else
				cout << "\n\t-= !! Error : Entered Negative Value on Input(s) !! =-";

			cout	<< "\n\t-= !! Current Record is Deleted !! =-"
				<< "\n\t-= !! Returning to Main Menu !! =-\n";
		}
		
		cout << "\n====================================================  ❤";
	}

	void insert(Malaysia* my, Record* aRec) { // called in line 89
		if (my->head == NULL)
			my->head = my->tail = aRec;
		else {
			my->tail->next = aRec;
			my->tail = aRec;
		}
	}

	void progress(Record* aRec) { // called in line 82
	 	// if both are 0, OR if recovered > new , set as "Good"
		if ((aRec->Recovered == 0 && aRec->New == 0) || aRec->Recovered > aRec->New)
			aRec->Status = "Good";
		else if (aRec->Recovered <= aRec->New)
			aRec->Status = "Bad";
	}

	void report(Malaysia* my) {
		int sumNew = 0, sumRecovered = 0, sumActive = 0;

		// loop to total up all the numbers
		for (Record* traverse = my->head; traverse != NULL; traverse = traverse->next) {
				sumNew += traverse->New;
				sumRecovered += traverse->Recovered;
				sumActive += traverse->Active;
		}
		
		cout << "\n\tSummmary of Cases Today :-" // on 15 November 2021
			<< "\n->\tTotal States : " << my->totalState
			<< "\n->\tTotal New Cases : " << sumNew
			<< "\n->\tTotal Recoveries : " << sumRecovered
			<< "\n->\tTotal Active Cases : " << sumActive << endl;

		// bool to check if there's state(s) displayed, else display "no record"
		bool flag = 0; 
		
		cout << "\n\tList of State(s) with Good Progress :-";	
		for (Record* prog = my->head; prog != NULL; prog = prog->next) {
			if (prog->Status == "Good") {
				cout << "\n->\t" << prog->State << " :-"
					<< "\n\tNew Cases : " << prog->New
					<< "\n\tRecoveries : " << prog->Recovered << "\n";
				flag = 1; // found record(s)
			}
		}

		if (!flag)
			cout << "\n->\t-= !! No Record Yet !! =-\n";
		
		flag = 0; // reinitialize flag to check for next list

		cout << "\n\tList of State(s) with Bad Progress :-";
		for (Record* prog = my->head; prog != NULL; prog = prog->next) {
			if (prog->Status == "Bad" ) {
				cout << "\n->\t" << prog->State << " :-"
					<< "\n\tNew Cases : " << prog->New
					<< "\n\tRecoveries : " << prog->Recovered << "\n";
				flag = 1; // found record(s)
			}
		}

		if (!flag)
			cout << "\n->\t-= !! No Record Yet !! =-\n";

		cout << "\n====================================================  ❤";
	}

	void dataExtraction(vector<State>* sl, State s, Malaysia* my) {
		for (Record* ext = my->head; ext != NULL; ext = ext->next) {
			s.Name = ext->State;
			s.New = ext->New;
			s.Recovered = ext->Recovered;
			s.Active = ext->Active;
			sl->push_back(s);
		}
	}

	void analysis(vector<State>* sl, State s, Malaysia* my) {
		int option;
		int count = 0; // to hold the INDEX of the vector

		// if vector is not empty, need to clear vector, before re-extracting updated data
		if (sl->empty())
			dataExtraction(sl, s, my);
		else if (!sl->empty()) {
			sl->clear();
			dataExtraction(sl, s, my);
		}

		// keep the INDEX of vector that holds highest/lowest number
		int newH = 0, newL = 0, recH = 0, recL = 0,	actH = 0, actL = 0;

		// keep the highest/lowest NUMBER temporarily to compare with current iterator data
		int tempNewH, tempNewL, tempRecH, tempRecL,	tempActH, tempActL; 
		
		// loop to find highest/lowest NUMBER and its corresponding INDEX in the vector
		for (auto hl = sl->begin(); hl != sl->end(); hl++) {
			if (count == 0) {
				tempNewH = tempNewL = hl->New;
				tempRecH = tempRecL = hl->Recovered;
				tempActH = tempActL = hl->Active;
			}
			else {
				if (hl->New > tempNewH) {
					newH = count;
					tempNewH = hl->New;
				}
				if (hl->New < tempNewL) {
					newL = count;
					tempNewL = hl->New;
				}

				if (hl->Recovered > tempRecH) {
					recH = count;
					tempRecH = hl->Recovered;
				}
				if (hl->Recovered < tempRecL) {
					recL = count;
					tempRecL = hl->Recovered;
				}
					
				if (hl->Active > tempActH) {
					actH = count;
					tempActH = hl->Active;
				}
				if (hl->Active < tempActL) {
					actL = count;
					tempActL = hl->Active;
				}
			}
			count++;
		}

		// one way to cheat the above code is by using stl funtion max_element() with #include <algorithm>
		// auto max = *max_element (sl.begin(), sl.end(), [](const State& a, const State& b){
		// 		return a.New < b.New; 
		// }); 

		// the above for loop only keeps the first highest/lowest value
		// e.g if we have data 10 50 99 99 30 and we are finding highest
		// it will only keep the first 99 and ignore the next 99
		// code below will find multiple highest/lowest value

		count = 0; // reinitialize count
		const int SIZE = 16;
		int index = 0;
		// the array holds INDEX of vector that has multiple highest/lowest VALUE
		int newSameH[SIZE] = {0}, newSameL[SIZE] = {0},
				recSameH[SIZE] = {0}, recSameL[SIZE] = {0},
				actSameH[SIZE] = {0}, actSameL[SIZE] = {0};

		// check if there's multiple highest/lowest VALUE in vector
		if (sl->size() >= 2) { // only if theres 2 or more data
			for (auto hl = sl->begin(); hl != sl->end(); hl++) {
				if (hl->New == tempNewH && count != newH) {
					newSameH[index] = count;
					index++;
				}
				if (hl->New == tempNewL && count != newL) {
					newSameL[index] = count;
					index++;
				}

				if (hl->Recovered == tempRecH && count != recH) {
					recSameH[index] = count;
					index++;
				}
				if (hl->Recovered == tempRecL && count != recL) {
					recSameL[index] = count;
					index++;
				}

				if (hl->Active == tempActH && count != actH) {
					actSameH[index] = count;
					index++;
				}
				if (hl->Active == tempActL && count != actL) {
					actSameL[index] = count;
					index++;
				}
			
				count++;
			}
		}

		do {
			if (sl->empty()) {
				cout << "\n\t-= !! No Record Added Yet !! =-\n";
				break; // break to go outside of do...while and redisplay main menu
			}
			else {
				cout << "\n====================================================  ❤\n"
					<< "\n\tAnalyzation Menu :-"
					<< "\n\t[1] Display Highest and Lowest New Cases"
					<< "\n\t[2] Display Highest and Lowest Recoveries"
					<< "\n\t[3] Display Highest and Lowest Active Cases"
					<< "\n\t[4] Exit Analyzation Menu"
					<< "\n->\tEnter Option : ";
				cin >> option;

				// error checking for if a user entered string instead of int
				while (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n\t-= !! Error : Entered String Value !! =-\n"
						<< "\n->\tEnter option : ";
					cin >> option;
				}
				
				if (option > 0 && option < 4)
					cout << "\n\t-= !! Displaying Analyzation Result !! =-\n";

				switch (option) {
					case 1 :
						cout << "\n->\tState(s) with Highest New Cases : \n\t" << (sl->begin() + newH)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (newSameH[i] != 0)
								cout << ", " << (sl->begin() + newSameH[i])->Name;
						}
						cout << " :-" << "\n\tNew Cases : " << (sl->begin() + newH)->New<< endl;

						cout << "\n->\tState(s) with Lowest New Cases : \n\t" << (sl->begin() + newL)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (newSameL[i] != 0)
								cout << ", " << (sl->begin() + newSameL[i])->Name;
						}
						cout << " :-" << "\n\tNew Cases : " << (sl->begin() + newL)->New << endl;
						break;
					case 2 :
						cout << "\n->\tState(s) with Highest Recoveries : \n\t" << (sl->begin() + recH)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (recSameH[i] != 0)
								cout << ", " << (sl->begin() + recSameH[i])->Name;
						}
						cout << " :-" << "\n\tRecoveries : " << (sl->begin() + recH)->Recovered<< endl;

						cout << "\n->\tState(s) with Lowest Recoveries : \n\t" << (sl->begin() + recL)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (recSameL[i] != 0)
								cout << ", " << (sl->begin() + recSameL[i])->Name;
						}
						cout << " :-" << "\n\tRecoveries : " << (sl->begin() + recL)->Recovered << endl;
						break;
					case 3 :
						cout << "\n->\tState(s) with Highest Active Cases : \n\t" << (sl->begin() + actH)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (actSameH[i] != 0)
								cout << ", " << (sl->begin() + actSameH[i])->Name;
						}						
						cout << " :-" << "\n\tActive Cases : " << (sl->begin() + actH)->Active << endl;

						cout << "\n->\tState(s) with Lowest Active Cases : \n\t" << (sl->begin() + actL)->Name;
						for (int i = 0; i < SIZE ; i++) {
							if (actSameL[i] != 0)
								cout << ", " << (sl->begin() + actSameL[i])->Name;
						}						
						cout << " :-" << "\n\tActive Cases : " << (sl->begin() + actL)->Active << endl;
						break;
					case 4 :
						cout << "\n\t-= !! Exiting Analyzation Menu !! =-\n";
				}
			}

			if (option > 4 || option < 1)
				cout << "\n\t-= !! Error : Value Out of Bound !! =-\n";

		} while (option != 4);
		
		cout << "\n====================================================  ❤";
	}
};
