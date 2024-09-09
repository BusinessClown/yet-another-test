
#include "header.h"
#include <fstream> 
#include <iostream> 
#include <string> 
#include <typeinfo>
using namespace std;

int main() {

	string menu = "";
	int amount = 0;
	int storage[150];
	int findNum, oldNum;
	string userNum;
	ifstream inputOfA1("C:\\Users\\zach0\\Downloads\\A1input.txt");
	
	if (inputOfA1.is_open()) {
		string line, word;
		//Goes through the file and stores all values in diffrent index determind by spaces
		while (inputOfA1 >> word) {
			storage[amount] = stoi(word);
			amount++;
		}

		// Close the file 
		inputOfA1.close();
	}
	else {

		// Failed to open the file 
		cout << "Error opening the file for reading." << endl;
		menu = "close";
		return 1;
	}
	//This loop is what keeps the program open as long as the user wants to do more.
	while (menu != "close") {
		//These lines are the menu and promps for the user 
		cout << "If you want to check if a number is in the array Enter:check" << endl;
		cout << "If you want to change a number in the array Enter:change" << endl;
		cout << "If you want to add a new integer to the array Enter:add" << endl;
		cout << "If you want to remove a part of the array Enter:remove" << endl;
		cout << "If you want to end program Enter:close " << endl;
		cin >> menu;
		// this option is the prompts, user input and input validation needed for checking is an integer is in the array funtion 
		if (menu == "check") {

			while (menu != "no") {
				// ask the user what integer they want to look for 
				cout << "Enter the integer you wish to check if present array. Use no letters or spaces :" << endl;
				cin >> userNum;
				menu = check(userNum);
				if (menu == "safe") {
					// convererts string to int
					findNum = stoi(userNum);
					// if the int wasn't in the array says it wasn't
					if (isNumPresent(storage, amount, findNum) == false) {
						cout << findNum << ": Is not an integer that exists in this array" << endl;
						cout << "Would you like to search for another integer:yes or no" << endl;
						menu = yesOrNo();
					}
					// if the value was present says the value and its index
					else {
						cout << "Integer " << findNum << " is in this array at index:" << isNumPresent(storage, amount, findNum) << endl;
						cout << "Would you like to search for another integer:yes or no" << endl;
						menu = yesOrNo();

					}


				}
				// if the user input was invalid says ask thme to try again
				else if (menu == "unsafe") {
					cout << "Please only enter a positive number with no spaces!" << endl;
				}
			}
		}
		// this option is the prompts, user input and input validation needed for adding a new value at the end of array funtion 
		else if (menu == "change") {
			while (menu != "no") {
				// ask the user what index they want to change and gives them valid index options 
				cout << "Enter the index you want to modify. Valid index rang from 0 to " << amount - 1 << " Use no letters or spaces (seriasly no spaces i ran out of time) and only a max of 3 digets:" << endl;
				cin >> userNum;
				menu = check(userNum);
				//makes sure is valide input had it worked into the code more but had an error with stoi that i thought was because of my exeption it was not but out of time
				try {
					if (menu == "unsafe") {
						throw false;
					}
					if (menu == "safe") {
						findNum = stoi(userNum);
						if (findNum < 0 || findNum > amount - 1) {
							throw false;
						}
					}

				}
				catch (bool unsafe) {
					menu = "unsafe";
				}
				//makes sure use input is valid
					// if the user input wasn't valid throws error and tells them to try again
				if (menu == "safe") {
					findNum = stoi(userNum);
					if (findNum < 0 || findNum > amount - 1) {
						menu = "unsafe";
					}
				}
					if (menu == "safe") {
						//ask the user if there sure this is the index and integer they want to change 
						cout << "Is index " << findNum << " contaning " << storage[findNum] << " the one you wish to modify: yes or no" << endl;
						menu = yesOrNo();

						if (menu == "yes") {

							oldNum = storage[findNum];
							// makes sure the user enters a safe new integer and then call the update function 
							while (menu != "safe") {
								cout << "Enter the integer you want to replace the old one with." << endl;
								cin >> userNum;
								menu = check(userNum);
								if (menu == "unsafe") {
									cout << "Please only enter a positive number with no spaces!" << endl;
								}
								else if (menu == "safe") {
									storage[findNum] = stoi(userNum);
									modStoredValue(storage, findNum, userNum);

								}
							}
							// tells user old value and new value and what index it was that changed
							cout << "Integer " << oldNum << " at index " << findNum << " has been replaced with " << storage[findNum] << endl;

							cout << "Would you like to modify another integer: yes or no" << endl;
							menu = yesOrNo();
						}
						else {
							menu = "";
						}


					}else if(menu == "unsafe") {
					cout << "Please only enter a valeid index and positive number with no spaces!" << endl;
				}

			}

		}
		// this option is the prompts, user input and input validation needed for adding a new value at the end of array funtion 
		else if (menu == "add") {
			while (menu != "no") {
				// makes sure array isn't full and if it is throws error "was a try block thought there was a problem with it was something else
				
				if (amount < sizeof(storage) / sizeof(int)) {




					//tells the user how many empty index are left then ask what integer they want to add
					cout << "There are " << sizeof(storage) / sizeof(int) - amount << " empty index left. Enter the integer you wish to add to the end of the array. Use no letters or spaces (seriasly no spaces i ran out of time) and only a max of 3 digets:" << endl;
					cin >> userNum;
					menu = check(userNum);

					if (menu == "safe") {
						findNum = stoi(userNum);
						cout << "Is integer " << findNum << " the one you wish to add: yes or no" << endl;
						menu = yesOrNo();

						if (menu == "yes") {
							// calls the funtion that adds the new value to the last open index and increase value that track how full the array is
							storeNewValueAtEnd(storage, amount, findNum);

							cout << "Integer " << storage[amount] << " has been added to index " << amount << endl;
							amount++;

							cout << "Would you like to modify another integer: yes or no" << endl;
							menu = yesOrNo();
						}
						else {
							menu = "";
						}

					}
					//reprompts the user if they enter invaled input
					else if (menu == "unsafe") {
						cout << "Please only enter a positive number with no spaces!" << endl;
					}

					// if the array is full tells the user so and kicks them out of add value
				}
				else if (amount >= sizeof(storage) / sizeof(int)) {
					cout << "The array is full. Remove a full index to add a new one." << endl;
					menu = "no";
				}


			}
		}
		// this option is the prompts, user input and input validation needed for the index removal funtion 
		else if (menu == "remove") {
			while (menu != "no") {
				// tells the user what indexs are valid for the user to pick from
				cout << "Enter the index you want to remove. Valid index rang from 0 to " << amount - 1 << " Use no letters or spaces (seriasly no spaces i ran out of time):" << endl;
				cin >> userNum;
				// makes sure the user entered a valid input
				menu = check(userNum);
				// makes sure input was a valid option
				//makes sure is valide input had it worked into the code more but had an error with stoi that i thought was because of my exeption it was not but out of time
				try {
					if (menu == "unsafe") {
						throw false;
					}
					if (menu == "safe") {
						findNum = stoi(userNum);
						if (findNum < 0 || findNum > amount - 1) {
							throw false;
						}
					}

				}
				catch (bool unsafe) {
					menu = "unsafe";
				}
				// if input was valid it continues
				if (menu == "safe") {
					//Shows the user what integer is in the choosen index and makes sure thats the integer they wish to remove 
					cout << "Is index " << findNum << " contaning " << storage[findNum] << " the one you wish to remove: yes or no" << endl;
					menu = yesOrNo();
					//if its the integer the user wants removed calls removal funtion and ask if the user wants to remove more
					if (menu == "yes") {
						removesIndex(storage, findNum, amount);
						//adjust total of filled indexs 
						amount--;
						cout << "Index " << findNum <<" has been removed. Would you like to remove another index: yes or no" << endl;
						menu = yesOrNo();
					}
					else {
						menu = "";
					}


				}
				//prompts the user to try again and enter a valid index
				else if (menu == "unsafe") {
					cout << "Please only enter a valeid index and positive number with no spaces!" << endl;
				}

			}

		}
		// This option is used to end the program when you are done and it does ask if you are sure or not
		else if (menu == "close") {
			cout << "Would you like to see your array:yes or no" << endl;
			menu = yesOrNo();
			if (menu == "yes") {
			for (int i = 0; i < amount; i++) {
				cout << " " << storage[i] << ", ";
			}
			}
			
			cout << endl << "Are you sure you want to exit the program:yes or no" << endl;
			menu = yesOrNo();
			if (menu == "yes") {
				cout << "Thank you for using this program " << endl;
				menu = "close";
			}
		}
		else {
			// this is if the user didn't enter one of the prompted options
			cout << "Make sure you enter a valid option" << endl;
		}

	}

	return 0;
}



