/* Name: Gabriel Beedles (4197665)
* Assignment: 1
* Filename: hashtable.h
* Date Modified: 21/03/2015
*
* Purpose: Contains the definition for the Hashtable class
*
*/

#include "linkedlist.h"
#include <iostream>

#ifndef _Hashtable_
#define _Hashtable_
class Hashtable {
private:
	LinkedList * table;
	int size;
	// Statistical variables
	int totalProcesses;
	User mostProcesses, leastProcesses, longestProc;
	Time averageTime;
public:
	// Constructors
	Hashtable();
	Hashtable(const Hashtable & newHT); //  Copy constructor
	Hashtable(int tableSize); // Used when size is known

	// Destructor
	~Hashtable();

	// Other Functions
	void insert(User & newData);
	int hash(const std::string userName);
	UserNode * exists(const std::string userName);
	void setLeastProc();

	// Overloaded Operators
	friend std::ostream& operator<<(std::ostream& out, Hashtable rhs);
};
#endif
