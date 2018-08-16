//
// Created by Clark Burton Chambers on 10/1/16.
//
// # Any line beginning with a pound sign shall be ignored as a comment line
//    # First non-comment line will give the number of books in the file
//    # Remaining lines will give the stock number, Title, classification, 
//    # cost and number in stock. Each shall be on a separate line.
//    # Example:
//    25
//    12345
//    CS221 A Programming Challenge
//    613
//    23.95
//    15
//  Title   Stock_Num   Classification    Cost   In Stock

#include <string.h>

#include "Book_Inventory.h"

Book_Inventory::Book_Inventory() : 
	 m_pHead(nullptr){}

Book_Inventory::~Book_Inventory() {
	ClearList();
	m_pHead = nullptr;
}

void Book_Inventory::ClearList() {
	BookRecord* temp = nullptr;
	while(m_pHead != nullptr){
		temp = m_pHead;
		m_pHead = m_pHead->getNext();
		delete temp;
	}
}

//--------------------------------------------
// Function: readInventory()
// Purpose: Read the inventory data file and
//		build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Inventory::readInventory(char *filename)
{
	char     line[SNAME_SIZE];
	int      numBooks;
	// define other variables here as needed

	m_InFile.open(filename, ifstream::in);
	if(!m_InFile.is_open())
	{
		// m_InFile.is_open() returns false if the file could not be found or
		//    if for some other reason the open failed.
		cout << "Unable to open file" << filename << "\nProgram terminating...\n";
		return false;
	}
	// Read number of books
	getNextLine(line, SNAME_SIZE);
	numBooks = atoi(line);
	for(int i=0; i<numBooks; i++)
	{
		// stock number, Title, classification, 
		//    # cost and number in stock

		// ------------------------------------------
		// Your code to read the inventory goes here
		// ------------------------------------------
		BookRecord* temp = new BookRecord();
		unsigned int len;

		// Stock num
	    getNextLine(line, SNAME_SIZE);
	    temp->setStockNum(atoi(line));

	    // Title
		getNextLine(line, SNAME_SIZE);

		// Some lines are shoving carrige returns at the end.
		//		 Removing them forcefully.
		len = (unsigned)strlen(line);
		if((len != 0) && (line[len - 1] == '\r')){
			line[len - 1] = 0x00;
		}

	    temp->setName(line);

	    //Classification
	    getNextLine(line, SNAME_SIZE);
	    temp->setClassification(atoi(line));

	    // Cost
	    getNextLine(line, SNAME_SIZE);
	    temp->setCost(atof(line));

	    // Num in Stock
	    getNextLine(line, SNAME_SIZE);
	    temp->setNumberInStock(atoi(line));

		// Add the book.
		addBook(temp);
	}
	m_InFile.close();
	return true;
}	

bool Book_Inventory::addBook(BookRecord *br) {
	BookRecord* temp = m_pHead;

	if(br == nullptr){
		printf("Don't pass nullptrs please!\n");
		return false;
	}

	long stocknum = br->getStockNum();
	if(temp == nullptr){		// Check the null case
		m_pHead = br;			// Set to the passed book
		return true;			// Everything is cool now.
	}
	while(temp != nullptr){ 	// Check if it exissts already
		if(stocknum == temp->getStockNum()){	// ^
			printf("A book record with stock number <%ld> already exists.\n", stocknum);
			return false; // Everything not cool anymore.
		}
		temp = temp->getNext();
	}

	// Insertion loop.
	temp = m_pHead;
	BookRecord* prev = m_pHead;

	// Check if ths first entry is big
	if(temp->getStockNum() > stocknum){
		br->setNext(m_pHead);
		m_pHead = br;
		return true;
	}

	// Insertion loop. Will return
	while(true){
		if(temp == nullptr){ // Stock number greater than all
			prev->setNext(br);
			return true;
		}
		if(temp->getStockNum() > stocknum){ // Stock somwehere in the middle
			br->setNext(temp);
			prev->setNext(br);
			return true;
		}

		prev = temp;
		temp = temp->getNext();
	}
}

BookRecord *Book_Inventory::removeBook(long stockNum) {
	BookRecord* prev = nullptr;
	BookRecord* temp = m_pHead;

	// Check if the head isn't cool.
	if(temp == nullptr){
		printf("BI: Head is empty, returning nullptr\n");
		return nullptr;
	}

	// Check if the head isn't cool
	if(temp->getStockNum() == stockNum){
		m_pHead = temp->getNext();
		return temp;
	}

	prev = temp;
	temp = temp->getNext();

	while(temp != nullptr){
		if(temp->getStockNum() == stockNum){
			// printf("BI: could not find the book you're looking for.\n");
			prev->setNext(temp->getNext());
			return temp;
		}
		prev = temp;
		temp = temp->getNext();
	}

	printf("BI: could not find the book you're looking for.\n");
	return nullptr;

}

BookRecord *Book_Inventory::searchByStockNumber(long stockNum) {
	BookRecord* temp = m_pHead;

	// Itterate through list.
	while(temp != nullptr){
		if(temp->getStockNum() == stockNum)
			return temp;
		temp = temp->getNext();
	}

	// COuldn't find book :c
	printf("BI: Couldn't find the book you're looking for.\n");
	return nullptr;
}

void Book_Inventory::searchByClassification(int cl) {
	BookRecord* temp = m_pHead;
	while(temp != nullptr){
		if(temp->getClassification() == cl){
			//  Title   Stock_Num   Classification    Cost   In Stock
			temp->printRecord();
		}
		temp = temp->getNext();
	}
}

void Book_Inventory::searchByCost(double min, double max) {
	BookRecord* temp = m_pHead;
	while(temp != nullptr){
		if(max >= temp->getCost() && temp->getCost() >= min){
			//  Title   Stock_Num   Classification    Cost   In Stock
			temp->printRecord();
		}
		temp = temp->getNext();
	}
}

int Book_Inventory::getNumberInStock(long sn) {
	BookRecord* temp = m_pHead;
	while(temp != nullptr){
		if(temp->getStockNum() == sn){
			//  Title   Stock_Num   Classification    Cost   In Stock
			printf("Number in Stock: %11d\n",
				temp->getNumberInStock());
			return temp->getNumberInStock();
		}
		temp = temp->getNext();
	}

	printf("BI: Could not find the book you're looking for.\n");
	return 0;
}

void Book_Inventory::printAll() {
	BookRecord* temp = m_pHead;
	char tname[SNAME_SIZE];
	while(temp != nullptr){
		//  Title   Stock_Num   Classification    Cost   In Stock
		temp->printRecord();
		temp = temp->getNext();
	}
}

//--------------------------------------------
// Function: getNextLine()
// Purpose:  Read a line from a data file.
//   The next non-comment line read from file
//   is stored in line char array.
//   An empty string is stored if the end of
//   file is reached.
// Returns: bool - true if a valid line was
//   read, false if end of file is reached.
//--------------------------------------------
bool Book_Inventory::getNextLine(char *line, int lineLen)
{
	while(true)
	{
		m_InFile.getline(line, lineLen);

		if(m_InFile.good())    // If a line was successfully read
		{
			if(strlen(line) == 0)  // Skip any blank lines
				continue;
			else if(line[0] == '#')  // Skip any comment lines
				continue;
			else return true;    // Got a valid data line so return with this line
		}
		else // No valid line read, meaning we reached the end of file
		{
			strcpy(line, ""); // Copy empty string into line as sentinal value
			return false;
		}
	} // end while
	return false; // Cannot reach this point but include a return to avoid compiler warning
	//   that not all paths return a value.
}



