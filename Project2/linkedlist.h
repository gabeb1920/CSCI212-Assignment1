/* Name: Gabriel Beedles (4197665)
* Assignment: 1
* Filename: linkedlist.h
* Date Modified: 21/03/2015
*
* Purpose: Contains the definition for the following classes and structs:
* - struct Time
* - class Process
* - class User
* - class UserNode
* - class LinkedList
*
*/

#include <string>
#include <iostream>

#ifndef _Time_
#define _Time_
struct Time
{
	int minutes;
	int seconds;
}; // struct Time
#endif

#ifndef _Process_
#define _Process_
class Process {
private:
	std::string pid;
	std::string cmd;
	int cmdLength;
	Time cpuTime;
public:
	// Constructors
	Process();

	// Destructor
	~Process() {}

	// Set Functions
	void setPid(std::string newPid) { pid = newPid; }
	void setCmd(std::string newCmd);
	void setcpuTime(Time newCpuTime) { cpuTime = newCpuTime; }
	
	// Get Functions
	std::string getPid() { return pid; }
	std::string getCmd() { return cmd; }
	int getCmdLength() { return cmdLength; }
	Time getCpuTime() { return cpuTime; }

	// Other Functions
	void clear();
	
	// Overloaded Operators
	friend std::ostream& operator<<(std::ostream& out, Process rhs);
};
#endif

#ifndef _User_
#define _User_
class User {
private:
	std::string userName;
	int procNum;
	Time totalTime;
	Process longestProc;
public:
	// Constructors
	User();

	// Destructor
	~User() {}

	// Get Functions
	std::string getUserName() { return userName; }
	int getProcNum() { return procNum; }
	Time getTotalTime() { return totalTime; }
	Process getLongestProc() { return longestProc; }

	// Set Functions
	void setUserName(std::string newUserName) { userName = newUserName; }

	// Other Functions
	void addProc(Process newProc);
	void clear();

	// Overloaded Operators
	friend std::ostream& operator<<(std::ostream& out, User rhs);
}; // class User
#endif

#ifndef _UserNode_
#define _UserNode_
class UserNode {
private:
	User data;
	UserNode * next;
public:
	// Constructors
	UserNode() { next = NULL; }
	
	// Destructor
	~UserNode() {}
	
	// Get Functions
	UserNode * getNext() { return next; }
	User getData() { return data; }
	
	// Set Functions
	void setData(User newData) { data = newData; }
	void setNext(UserNode * newNext) { next = newNext; }

};
#endif

#ifndef _LinkedList_
#define _LinkedList_
class LinkedList {
private:
	UserNode * head;
public:
	// Constructors
	LinkedList() { head = NULL; }
	LinkedList(const LinkedList & newLL); // Copy constructor
	
	// Destructor
	~LinkedList();
	
	// Get Functions
	UserNode * getHead() { return head; }

	// Other functions
	void insert(const User & newData);
	UserNode * exists(std::string userName);

	// Overloaded Operators
	friend std::ostream& operator<<(std::ostream& out, LinkedList rhs);
	void operator=(const LinkedList rhs);
};
#endif
