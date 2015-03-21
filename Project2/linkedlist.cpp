/* Name: Gabriel Beedles (4197665)
* Assignment: 1
* Filename: linkedlist.cpp
* Date Modified: 21/03/2015
*
* Purpose: Contains the implementation for the following classes and structs:
* - struct Time
* - class Process
* - class User
* - class UserNode
* - class LinkedList
*
*/

#include "linkedlist.h"
#include <iostream>
using namespace std;

// Process Class Functions
// Process Class Constructors
Process::Process() {
	cmdLength = 0;
	cpuTime.minutes = 0;
	cpuTime.seconds = 0;
} // Process::Process()

// Process Class Set Functions
void Process::setCmd(string newCmd) {
	// Set the new command
	cmd = newCmd;
	// Update the command length
	for (unsigned int i = 0; i < cmd.length(); ++i) {
		if (cmd.at(i) == '/')
			cmdLength++;
	}

	//cmdLength = count(cmd.begin(), cmd.end(), '/');
} // void Process::setCmd(string newCmd)

// Process Class Other Functions
void Process::clear() {
	pid.clear();
	cmd.clear();
	cmdLength = 0;
	cpuTime.minutes = 0;
	cpuTime.seconds = 0;
} // void Process::clear()

// Process Class Overloaded Operator Functions
ostream& operator<<(ostream& out, Process rhs) {
	out << "PID: " << rhs.pid << " CPU Time: " << rhs.cpuTime.minutes;
	out << ":" << rhs.cpuTime.seconds << " Command: " << rhs.cmd;
	out << " Command Length: " << rhs.cmdLength << endl;
	return out;
} // ostream& operator<<(ostream& out, Process rhs)

// User Class Functions
// User Class Constructors
User::User() {
	procNum = 0;
	totalTime.minutes = 0;
	totalTime.seconds = 0;
} // User::User()

// User Class Other Functions
void User::addProc(Process newProc) {
	totalTime.seconds += newProc.getCpuTime().seconds;
	totalTime.minutes += newProc.getCpuTime().minutes + 
		totalTime.seconds / 60;
	totalTime.seconds = totalTime.seconds % 60;

	// Increment the number of processes the user has
	++procNum;

	// Check if newProc command is longer than current longest
	if (newProc.getCmdLength() >= longestProc.getCmdLength()) {
		longestProc = newProc;
	}
} // void User::addProc(Process newProc)

void User::clear() {
	userName.clear();
	procNum = 0;
	totalTime.minutes = 0;
	totalTime.seconds = 0;
	longestProc.clear();
} // void User::clear()

// Overloaded Operators
ostream& operator<<(ostream& out, User rhs) {
	out << "User " << rhs.userName << "\n==========\n" << endl;
	out << "User " << rhs.userName << " has a total of " << rhs.procNum;
	out << " processes." << endl;
	out << "User " << rhs.userName << " has consumed a total of ";
	out << rhs.totalTime.minutes << " minutes and ";
	out << rhs.totalTime.seconds << " seconds of CPU time." << endl;
	out << "The process id with the longest path name is pid ";
	out << rhs.longestProc.getPid() << " ";
	out << rhs.longestProc.getCmd() << "\n" << endl;
	return out;
} // ostream& operator<<(ostream& out, User rhs)

// LinkedList Class Functions
// LinkedList Class Constructors
// Copy Constructor
LinkedList::LinkedList(const LinkedList & newLL) {
	head = NULL;

	UserNode * temp = newLL.head;
	while (temp != NULL) {
		this->insert(temp->getData());
		temp = temp->getNext();
	}
} // LinkedList::LinkedList(const LinkedList & newLL)

// LinkedList Class Destructor
LinkedList::~LinkedList() {
	UserNode * current = head;
	while (current != NULL) {
		UserNode * next = current->getNext();
		delete current;
		current = next;
	}
} // LinkedList::~LinkedList()

// LinkedList Class Other functions
void LinkedList::insert(const User & newData) {
	UserNode * temp = new UserNode;
	temp->setData(newData);

	if (head == NULL)
		head = temp;
	else {
		UserNode * current = head;
		while (current->getNext() != NULL)
			current = current->getNext();
		current->setNext(temp);
	}
} // void LinkedList::insert(const User & newData)

UserNode * LinkedList::exists(string userName) {
	UserNode * currentNode = head;
	if (currentNode != NULL) {
		// Step through the list until we reach the end or find a
		// node that matches
		User currentUser = currentNode->getData();
		while (currentUser.getUserName() != userName && currentNode
			!= NULL) {

			currentNode = currentNode->getNext();
		}
	}

	return currentNode;
	
} // UserNode * LinkedList::exists(string userName)

// LinkedList Class Overloaded Operators
ostream& operator<<(ostream& out, LinkedList rhs) {
	UserNode * current = rhs.head;
	while (current != NULL) {
		out << current->getData();
		current = current->getNext();
	}

	return out;
} // ostream& operator<<(ostream& out, LinkedList rhs)

void LinkedList::operator=(const LinkedList rhs) {
	head = NULL;

	UserNode * temp = rhs.head;
	while (temp != NULL) {
		this->insert(temp->getData());
		temp = temp->getNext();
	}
} // void LinkedList::operator=(const LinkedList rhs)
