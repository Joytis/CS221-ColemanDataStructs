#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream> 

#include "Book_Database.h"


Book_Database::Book_Database() :
	m_pRoot(nullptr){}

Book_Database::~Book_Database() {
	ClearList(m_pRoot);
	m_pRoot = nullptr;
}

//--------------------------------------------
// Function: readDatabase()
// Purpose: Read the inventory data file and
//		build the list.
//--------------------------------------------
bool Book_Database::readDatabase(char *filename)
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
		if((len != 0) && (line[len - 1] == '\r')) {
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

bool Book_Database::addBook(BookRecord *br) {
	if(br == nullptr){
		printf("Please don't pass nullptr :c\n");
		return false;
	}

	BookRecord* prev;
	BookRecord* next;
	long stocknum = br->getStockNum();
	long psnum;

	// Handle null case.
	if(m_pRoot == nullptr) {
		m_pRoot = br;
		return true;
	}

	next = m_pRoot;
	prev = next;

	while(true)
	{	
		psnum = prev->getStockNum();

				// Check if book already exists. 
		if(prev->getStockNum() == stocknum){
			printf("Book Record for that stock number already exists! %ld\n", br->getStockNum());
			return false;
		}
		else if(stocknum > psnum){	// Right side is gerater than
			next = prev->getRight();

			// Check the next pointer for null
			if(next == nullptr){
				// Add the book here. 
				prev->setRight(br);
				return true;
			}
		}
		else{						// Left side is less than
			next = prev->getLeft();

			// Check the next pointer for null
			if(next == nullptr){
				// Add the book here. 
				prev->setLeft(br);
				return true;
			}
		}
		// Move the list onwards.
		prev = next;
	}

}

BookRecord *Book_Database::removeBook(long stockNum) {
	BookRecord* node;
	BookRecord* prev;
	BookRecord* next;
	BookRecord* right;
	BookRecord* left;
	bool 		flag;

	// Handle null case.
	if(m_pRoot == nullptr) {
		printf("Tree root is empty!\n");
		return nullptr;
	}

	// if m_pRoot is the book, things get weird.
	if(m_pRoot->getStockNum() == stockNum){
		node = m_pRoot;
		right = node->getRight();
		left = node->getLeft();

		// Clear the node pointers
		node->setLeft(nullptr);
		node->setRight(nullptr);

		if(right != nullptr){
			m_pRoot = right;
			next = right->getLeft();
			prev = right;
			while(next != nullptr){
				prev = next;
				next = next->getLeft();
			}

			prev->setLeft(left);
		}
		else
			m_pRoot = left;
		return node;
	}

	next = m_pRoot;
	prev = next;

	while(true){
		prev = next;

		// Toggle is true if right and false if left
		if(stockNum > prev->getStockNum()){	// Less than on the left
			next = prev->getRight();
			flag = true;
		}
		else{								// Greater than on the right
			next = prev->getLeft();
			flag = false;
		}

		// Check the next pointer for null
		if(next == nullptr){
			// Add the book here. 
			printf("The book you're looking for doens't exist!\n");
			return nullptr;
		}

		// Default case
		if(next->getStockNum() == stockNum){
			node = next;
			right = node->getRight();
			left = node->getLeft();

			// Clear the node pointers
			node->setLeft(nullptr);
			node->setRight(nullptr);

			if(right != nullptr){
				if(flag)
					prev->setRight(right);
				else
					prev->setLeft(right);

				next = right->getLeft();
				prev = right;
				while(next != nullptr){
					prev = next;
					next = next->getLeft();
				}

				prev->setLeft(left);
			}
			else{
				if(flag)
					prev->setRight(left);
				else
					prev->setLeft(left);
			}
			return node;
		}
	}
}

BookRecord *Book_Database::searchByStockNumber(long stockNum) {
	BookRecord* next = m_pRoot;
	long snum;

	if(m_pRoot == nullptr){
		printf("The tree is currently empty!\n");
		return nullptr;
	}

	while(next != nullptr){
		snum = next->getStockNum();
		if(snum == stockNum)
			return next;
		if(stockNum > snum)
			next = next->getRight();
		else
			next = next->getLeft();

	}

	return nullptr;
}

int Book_Database::getNumInStock(long sn) {
	BookRecord* next = m_pRoot;
	long snum;

	if(m_pRoot == nullptr){
		printf("The tree is currently empty!\n");
		return 0;
	}

	while(next != nullptr){
		snum = next->getStockNum();
		if(snum == sn)
			return next->getNumberInStock();
		if(sn > snum)
			next = next->getRight();
		else
			next = next->getLeft();

	}

	return 0;
}

void Book_Database::ClearList(BookRecord *rt) {
	// Recursion time!
	if(rt != nullptr){
		// Variables
		BookRecord* left;
		BookRecord* right;

		left = rt->getLeft();
		right = rt->getRight();

		ClearList(left);

		rt->setLeft(nullptr);
		rt->setRight(nullptr);
		delete rt;

		ClearList(right);
	}
	// return
}


//-------------------------------------------------
// getNextLine() 
// Read a line from a data file.  
// Note: The second argument is of type size_t.
//       This is just an int but the compiler
//       will give you a warning if you use 
//       int instead of this #defined name
//       Another confusing example of Micro-soft
//       at work.
//-------------------------------------------------
bool Book_Database::getNextLine(char *line, int lineLen)
{
    while(true){
        m_InFile.getline(line, 128);
        
        if(m_InFile.good()){    // If a line was successfully read
            if(strlen(line) == 0)  // Skip any blank lines
                continue;
            else if(line[0] == '\r') // Skip any carrige return lines
            	continue;
            else if(line[0] == '#')  // Skip any comment lines
                continue;
            else return true;    // Got a valid data line so return with this line
        }
        else {
            strcpy(line, "");	// Reached the end of the file
            return false;
        }
    } // end while
    return false;  // You can never get here but include the return anyway to keep the
                   // compiler from warning you that not all paths return a value.
}

void Book_Database::searchByClassification(int cl) {
	searchByClassification(cl, m_pRoot);
}

void Book_Database::searchByClassification(int cl, BookRecord *rt) {
	// Recursion time!
	if(rt != nullptr){
		// Variables
		BookRecord* left;
		BookRecord* right;

		left = rt->getLeft();
		right = rt->getRight();

		// Left (always less than)
		searchByClassification(cl, left);
		// Us (always greater than left)
		if(rt->getClassification() == cl)
			rt->printRecord();
		// Right (Always greater than us)
		searchByClassification(cl, right);
	}
	// return
}

void Book_Database::searchByCost(double min, double max) {
	searchByCost(min, max, m_pRoot);
}

void Book_Database::searchByCost(double min, double max, BookRecord *rt) {
	// Recursion time!
	if(rt != nullptr){
		// Variables
		BookRecord* left;
		BookRecord* right;

		left = rt->getLeft();
		right = rt->getRight();

		// Left (always less than)
		searchByCost(min, max, left);
		// Us (always greater than left)
		if(max > rt->getCost() && rt->getCost() > min)
			rt->printRecord();
		// Right (Always greater than us)
		searchByCost(min, max, right);
	}
	// return
}

void Book_Database::PrintAll() {
	if(m_pRoot == nullptr){
		printf("The tree is currently empty!\n");
	}
	PrintAll(m_pRoot);
}

void Book_Database::PrintAll(BookRecord *rt) {

	// Recursion time!
	if(rt != nullptr){
		// Variables
		BookRecord* left;
		BookRecord* right;

		left = rt->getLeft();
		right = rt->getRight();

		// Left (always less than)
		PrintAll(left);
		// Us (always greater than left)
		rt->printRecord();
		// Right (Always greater than us)
		PrintAll(right);
	}
	// return
}


