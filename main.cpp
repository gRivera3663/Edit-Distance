/*
Name: Gabriel Rivera
Last 4 Digits of CWID: 2136
-------------------------------------
This is the main.cpp source file for my edit distance program. Once
the program starts it will ask for the first and second strings you'd
like to insert into the function. For each type the word and press enter.
After the second word enter, the program will run and at the end it will
ask you to press enter again to continue. Once that is pressed the program will end.

I used Visual Studio 2019 Community to run my program. There are no extra add ons needed
for this file to properly complie. All libraries are available with C++.
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>

using namespace std;

void printHeader(string first);
int min(int x, int y, int z);
int determineNumberForSpace(char fromFirst, char fromSecond, int topLeft, int topRight, int bottomLeft);

int main() {
		string first;
		string second;

		// Grab two strings from user
		cout << "Enter a start string: ";
		cin >> first;
		cout << "Enter an second string: ";
		cin >> second;

		// Adding extra space for chart purposes
		first = " " + first;
		second = " " + second;

		// Forming first row and column of chart
		int editChart[50][50];
		for (int i = 0; i < first.length(); i++)
		{
			editChart[0][i] = i;
		}
		for (int i = 0; i < second.length(); i++)
		{
			editChart[i][0] = i;
		}

		int rowTracker = 0;
		int colTracker = 0;

		// Beginning of the table printing
		for (string::iterator it = second.begin(); it != second.end(); it++) {
				
				// Function runs once to print chart header
				if (it == second.begin()) {
						printHeader(first);
				}

				// Loop to create columns/remaining rows
				for (string::iterator eh = first.begin(); eh != first.end(); eh++) {
					int whatToPut;
					if (eh == first.begin()) {
						cout << setw(3) << *it << " " << "|";
					}

					if (rowTracker == 0) {
						whatToPut = editChart[0][colTracker];
					}
					else if (colTracker == 0 && rowTracker != 0) {
						whatToPut = editChart[rowTracker][0];
					}
					else if (rowTracker != 0 && colTracker != 0) {
						whatToPut = determineNumberForSpace(*eh, *it, editChart[rowTracker - 1][colTracker - 1], editChart[rowTracker - 1][colTracker], editChart[rowTracker][colTracker - 1]);
					}

					cout << setw(3) << whatToPut << " ";
					editChart[rowTracker][colTracker] = whatToPut;
					colTracker++;
				}
				cout << endl;
				rowTracker++;
				colTracker = 0;
		}

		// Uses last number from chart as the edit distance
		cout << endl;
		cout << "The edit distance is " << editChart[second.length()-1][first.length()-1] << "." << endl;

		// String allignment
		int max;
		bool isFIrstBigger = false;
		if (first.length() == second.length()) {
			cout << endl << "Allignment:" << endl;
			cout << first << endl << second << endl;
			return 0;
		}
		else if (first.length() > second.length()) {
			max = first.length();
			isFIrstBigger = true;
		}
		else {
			max = second.length();
		}

		// Reads from the chart to determine where the allignment occurs.
		// This is based mainly on whether the first or second string obtained
		// is the larger one, and the chart positioning based on that is where
		// we get the location for our allignment.
		int marker = 1;
		if (isFIrstBigger == true) {
			for (int i = 1; i < max-1; i++) {
				if (editChart[i][i] == 0) {
					marker = i;
				}
				else if (editChart[i][i] != 0) {
					if (editChart[i][i] == editChart[i][i + 1]) {
						marker = i;
						break;
					}
				}
			}

			second.insert(marker, "_");

			cout << endl << "Allignment:" << endl;
			cout << first << endl << second << endl;
		}
		else {
			for (int i = 1; i < max-1; i++) {
				if (editChart[i][i] == 0) {
					marker = i;
				}
				else if (editChart[i][i] != 0) {
					if (editChart[i][i] == editChart[i + 1][i]) {
						marker = i;
						break;
					}
				}
			}

			first.insert(marker, "_");

			cout << endl << "Allignment:" << endl;
			cout << first << endl << second << endl;
		}

		cout << endl;
		system("pause");

		return 0;
}

// Determines which number is placed into a certain spot
// in the chart based on the 3 numbers around it, and whether
// the two current strings being compared are the same or not.
int determineNumberForSpace(char fromFirst, char fromSecond, int topLeft, int topRight, int bottomLeft) {
	if (fromFirst == fromSecond) {
		return min(topLeft, topRight, bottomLeft);
	}
	else {
		return 1 + min(topLeft, topRight, bottomLeft);
	}

}

// Creates the header and the first dividing line for the table
void printHeader(string first) {

	// Prints lead space and then the first sring
	cout << setw(4) << " ";
	for (string::iterator it = first.begin(); it != first.end(); it++) {
		cout << setw(3) << *it << " ";
	}
	cout << endl;

	// Prints the top dividing line
	cout << setw(4) << " ";
	for (string::iterator it = first.begin(); it != first.end(); it++) {
		cout << "----";
	}
	cout << endl;
}

// Returns the lowest number between 3 numbers
int min(int x, int y, int z){
	return min(min(x, y), z);
}