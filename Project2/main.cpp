/* Name: Gabriel Beedles (4197665)
* Assignment: 1
* Filename: main.cpp
* Date Modified: 21/03/2015
*
* Purpose: Recieves input from ps(1), stores the data in a hashtable and
* outputs to cout
*
*/

#include "hashtable.h"
#include "linkedlist.h"
#include <string>
#include <iostream>
using namespace std;

const int HASHTABLE_SIZE = 120; // Used to set the size of the hashtable

int main() {
	// Temp variables to hold input data
	Process tempProc;
	Time tempTime;
	User tempUser;
	string junk, tempUsername, tempPid, tempTimeMin, tempTimeSec, tempCmd;

	// Hashtable to store the final data
	Hashtable newTable(HASHTABLE_SIZE);

	cin.ignore(1024, '\n'); // Ignore the first line
	cin >> skipws;
	// Loop to read the rest of the input
	while (cin >> tempUsername) {
		// Read in the data
		cin >> tempPid;
		cin >> junk; // Ignore parent PID
		cin >> junk; // Ignore C		
		// Dealing with STIME
		junk.clear();
		cin >> junk;
		// If STIME is a date string
		if (junk.at(0) >= 'A' && junk.at(0) <= 'Z') { 
			cin >> junk;
		}
		// else it must be a time string and we have already
		// collected it entirely
		cin >> junk; // Ignore TTY
		getline(cin, tempTimeMin, ':');
		// Remove whitespace remaining after getline
		int minuteStart = tempTimeMin.find_first_not_of(' ');
		tempTimeMin = tempTimeMin.substr(minuteStart);
		cin >> tempTimeSec;
		getline(cin, tempCmd);
		// Remove whitespace remaining after getline
		int cmdStart = tempCmd.find_first_not_of(' ');
		tempCmd = tempCmd.substr(cmdStart);

		// Add the recorded time to tempTime
		tempTime.minutes = atoi(tempTimeMin.c_str());
		tempTime.seconds = atoi(tempTimeSec.c_str());

		// Add the process details
		tempProc.setPid(tempPid);
		tempProc.setCmd(tempCmd);
		tempProc.setcpuTime(tempTime);

		// Add the process to the tempUser
		tempUser.setUserName(tempUsername);
		tempUser.addProc(tempProc);

		// Add the user to the hashtable
		newTable.insert(tempUser);

		// Empty the temp variables
		junk.clear();
		tempUsername.clear();
		tempPid.clear();
		tempTimeMin.clear();
		tempTimeSec.clear();
		tempCmd.clear();
		tempUser.clear();
		tempProc.clear();
	}
	// Calculate the least process user
	newTable.setLeastProc();
	// Print both reports
	cout << newTable;

	return 0;
}
