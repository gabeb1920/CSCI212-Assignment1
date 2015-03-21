/* Name: Gabriel Beedles (4197665)
* Assignment: 1
* Filename: hashtable.cpp
* Date Modified: 21/03/2015
*
* Purpose: Contains the implementation for the Hashtable class
*
*/

#include "hashtable.h"
#include <iostream>
using namespace std;

// Hashtable Class Functions
// Hashtable Class Constructors
Hashtable::Hashtable() {
	size = 0;
	table = NULL;
	totalProcesses = 0;
	averageTime.minutes = 0;
	averageTime.seconds = 0;
} // Hashtable::Hashtable()

Hashtable::Hashtable(const Hashtable & newHT) {
	size = newHT.size;
	table = new LinkedList[size];
	totalProcesses = newHT.totalProcesses;
	averageTime.minutes = newHT.averageTime.minutes;
	averageTime.seconds = newHT.averageTime.seconds;
	mostProcesses = newHT.mostProcesses;
	leastProcesses = newHT.leastProcesses;
	longestProc = newHT.longestProc;

	for (int i = 0; i < size; ++i) {
		table[i] = newHT.table[i];
	}
} // Hashtable::Hashtable(const Hashtable & newHT)

Hashtable::Hashtable(int tableSize) {
	size = tableSize;
	table = new LinkedList[size];
	totalProcesses = 0;
	averageTime.minutes = 0;
	averageTime.seconds = 0;
} // Hashtable::Hashtable(int tableSize)

// Hashtable Class Destructor
Hashtable::~Hashtable() {
	if (table != NULL)
		delete [] table;
} // Hashtable::~Hashtable()

// Hashtable Class Other Functions
void Hashtable::insert(User & newData) {
	int hash = this->hash(newData.getUserName());

	UserNode * tempNode = table[hash].exists(newData.getUserName());
	User tempUser;
	
	if (tempNode == NULL) {
		table[hash].insert(newData);
		tempUser = newData;
	}
	else {
		tempUser = tempNode->getData();
		tempUser.addProc(newData.getLongestProc());
		tempNode->setData(tempUser);
		tempUser = tempNode->getData(); // Used to gather stats
	}

	// Update the statistical data
	++totalProcesses;
	// Update user with the most processes
	if (tempUser.getProcNum() >= mostProcesses.getProcNum())
		mostProcesses = tempUser;
	// Update the longest path
	Process tempProc = tempUser.getLongestProc();
	Process currentlongestProc = longestProc.getLongestProc();
	if (tempProc.getCmdLength() >= currentlongestProc.getCmdLength())
		longestProc = tempUser;
	// Update average CPU Time
	Time tempTime = tempUser.getTotalTime();
	int totalSeconds = averageTime.minutes * 60 + averageTime.seconds;
	totalSeconds = totalSeconds * (totalProcesses - 1);
	totalSeconds += tempTime.minutes * 60 + tempTime.seconds;
	totalSeconds = totalSeconds / totalProcesses;
	averageTime.seconds = totalSeconds % 60;
	averageTime.minutes = totalSeconds / 60;
} // void Hashtable::insert(const User & newData)

int Hashtable::hash(const string userName) {
	int hash = 0;
	char currentLetter = '\0';

	for (unsigned int i = 0; i < userName.length(); ++i) {
		currentLetter = userName.at(i);
		hash += int(currentLetter);
	}

	hash = hash % size;

	return hash;
} // int Hashtable::hash(const string userName)

UserNode * Hashtable::exists(const string userName) {
	int hash = this->hash(userName);

	return table[hash].exists(userName);
} // UserNode * Hashtable::exists(const string userName)

void Hashtable::setLeastProc() {
	for (int i = 0; i < size; ++i) {
		UserNode * tempNode = table[i].getHead();
		while (tempNode != NULL) {
			User tempUser = tempNode->getData();
			if (tempUser.getProcNum() < leastProcesses.getProcNum() ||
				leastProcesses.getProcNum() == 0)

				leastProcesses = tempUser;
			tempNode = tempNode->getNext();
		}
	}
} // void Hashtable::setLeastProc()

// Hashtable Class Overloaded Operators
ostream& operator<<(ostream& out, Hashtable rhs) {
	// Print out the user summaries
	for (int i = 0; i < rhs.size; ++i) {
		out << rhs.table[i];
	}
	// Print out the statistical summary
	out << "Statistical Summary\n============\n\n";
	out << "There are a total of " << rhs.totalProcesses << " in the ";
	cout << "process table." << endl;
	out << "User " << rhs.mostProcesses.getUserName() << " has the most ";
	out << "processes in the table (count = ";
	out << rhs.mostProcesses.getProcNum() << ")" << endl;
	out << "User " << rhs.leastProcesses.getUserName() << " has the ";
	out << "least processes in the table (count = ";
	out << rhs.leastProcesses.getProcNum() << ")" << endl;
	// Get the process out of the user place holder
	Process tempProc = rhs.longestProc.getLongestProc();
	out << "The process with the longest path name is pid ";
	out << tempProc.getPid() << " with the path name ";
	out << tempProc.getCmd() << " belonging to the user ";
	out << rhs.longestProc.getUserName() << endl;
	out << "The average CPU time used by all processes is ";
	out << rhs.averageTime.minutes << " minutes and ";
	out << rhs.averageTime.seconds << " seconds" << endl;

	return out;
} // ostream& operator<<(ostream& out, Hashtable rhs)
