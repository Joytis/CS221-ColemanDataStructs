//1.0 Overview
//		The Book Worm, a privately owned business dealing in
//  		a variety of books and periodicals is in need of a program that will store inventory
// 			records on books and periodicals and provide ready access to the information.
// 			This statement of work addresses the second phase of this project. That is,
// 			to develop an application in which any number of book records can be stored in a database
// 			and information on the books and periodicals can be retrieved as needed.
//
//2.0 Requirements
//		The student shall define, develop, document, prototype, test, and modify as required the software system.
//2.1 This software system will allow the storage of information on an unlimited number of books.
//2.2 The information stored on each book record shall include: the name/title of the book, the stocknumber
// 	of the book, the classification of the book coded as an integer number, the cost of the book, and the number in stock.
//2.3 Upon startup the system shall read all data on the inventory from a text file and store the data in the inventory database.
//2.4 A user shall have the option of searching for a book by stock number, cost range,
// 	or classification. When a book or books are located that match the search criteria, all information on
// 	the book(s) shall be printed on the screen.
//2.5 A user shall also have the option of printing information on all books in the inventory.
//2.6 All requirements stated and illustrated in the excerpt from the Software Requirements Specification (see below) shall be followed.
//
//3.0 Deliverables
//		These products shall be delivered to the instructor electronically via e-mail as specified below.
//3.1 Sprint Report -- The student shall provide filled out Sprint Report form for instructor approval NLT
// 		(Not Later Than) Monday, October 17.
//3.2 Program source files -- The student shall provide fully tested electronic copies of the .cpp and
// 		.h files. These files must be submitted to the instructor via e-mail. The files shall be delivered NLT Monday, October 17.
//4.0 Period of Performance
//		The period of performance of this assignment is 28 days from the date of assignment.


#include <iostream>
#include "Book_Inventory.h"
#include "BookRecord.h"
#include "dbg.hpp"

//using namespace std;

// Test Main
int main(int argc, char* argv[]) {

	// THINGS TO TEST.
	//	int getClassification();			// just returns the classification number.
	//	double getCost();			// just returns the normal cost.
	//	BookRecord *getNext();				// Gets the node next
	//	void setNext(BookRecord *next);		// Sets the node next
	//	void printRecord();

	// getClassification();
	BookRecord* temp = new BookRecord();
	temp->setStockNum(10000);
	temp->setClassification(1010);

	debug(true, "Classification NUm: %d", temp->getClassification());

	// getClassification()
	temp->setCost(45.43);
	debug(true, "Cost: %f", temp->getCost());

	// setNext/getNext()
	BookRecord* temp2 = new BookRecord();
	debug(true, "Pointer %p", temp2);
	temp->setNext(temp2);
	debug(true, "Pointer %p", temp->getNext())
	delete temp2;

	// printRecord();
	temp->setName("Cool dudes");
	temp->printRecord();

	// delete temp
	delete temp;

	//class Book_Inventory
	//{
	//private:
	//	BookRecord     *m_pHead;                		// Pointer to the head of the list
	//	ifstream       m_InFile;                		// File containing the inventory
	//
	//public:
	//	Book_Inventory();                       		// Class constructor
	//	~Book_Inventory();                      		// Class destructor. Must free all list memory
	//	void ClearList();                       		// Remove all items from the list
	//	bool readInventory(char *filename);     		// Read inventory file and build the list
	//	bool addBook(BookRecord *br);           		// Add the given book to the list
	//	BookRecord *removeBook(long stockNum);  		// Remove a book from the list or print message if not found
	//	BookRecord *searchByStockNumber(long stockNum);		// Search by stock number return pointer to node or NULL if not found
	//	void searchByClassification(int cl);   			// Search for all books given classification, print all data
	//	void searchByCost(double min, double max);		// Search for all books within the given cost range
	//	int getNumberInStock(long sn);          		// Get number of books in stock for the given stock number
	//	void printAll();                        		// Print all information on all books in the inventory.
	//private:
	//	bool getNextLine(char *line, int lineLen);   		// read next line from a file
	//};

	// Book_Inventory();
	Book_Inventory* bi = new Book_Inventory();
	BookRecord* temp3 = new BookRecord();
	temp3->setStockNum(10020);
	temp3->setClassification(400);
	temp3->setName("Cool dudes 2");
	temp3->setCost(20.92);
	temp3->setNumberInStock(20);

	// readInventory();
	char filename[SNAME_SIZE] = "BookData.txt";
	bi->readInventory(filename);

	// printAll()
	bi->printAll();

	// clearList()
	bi->ClearList();
	debug(true, "Prints null list:");
	bi->printAll();

	// addBook()
	debug(true, "Prints newlist:");
	bi->addBook(temp3);
	bi->printAll();
	bi->addBook(nullptr);

	// removeBook
	BookRecord* temp4 = bi->removeBook(10020);
	delete temp4;
	if(bi->removeBook(0) == nullptr){
		debug(true, "Passed remove case 1");
	}

	//	BookRecord *searchByStockNumber(long stockNum);		// Search by stock number return pointer to node or NULL if not found
	//	void searchByClassification(int cl);   			// Search for all books given classification, print all data
	//	void searchByCost(double min, double max);		// Search for all books within the given cost range
	//	int getNumberInStock(long sn);          		// Get number of books in stock for the given stock number
	//	void printAll();

	// searchByStockNUmber
	bi->readInventory(filename);
	bi->printAll();
	debug(true, "SEARCH BY STOCK");
	BookRecord* temp5 = bi->searchByStockNumber(1234);
	printf("\n");
	temp5->printRecord();
	temp5 = bi->searchByStockNumber(0);
	if(temp5 == nullptr){
		debug(true, "Search case 1 passed");
	}

	// searchByClassification
	debug(true, "SEARCH BY CLASS");
	bi->searchByClassification(613);
	bi->searchByClassification(0);

	// searchByCost
	debug(true, "SEARCH BY COST");
	bi->searchByCost(25.0, 30.0);
	bi->searchByCost(0.1, 0.2);

	// getNUmberInStock;
	debug(true, "SEARCH FOR STOCK");
	bi->getNumberInStock(1234);
	bi->getNumberInStock(2345);
	bi->getNumberInStock(0);

	// printall
	debug(true, "PRINT ALL");
	bi->printAll();

	// removeBook
	debug(true, "REMOVE BOOK");
	delete bi->removeBook(1234);
	bi->printAll();

	debug(true, "REMOVE BOOK");
	delete bi->removeBook(4567);
	bi->printAll();

	debug(true, "REMOVE BOOK");
	delete bi->removeBook(9876);
	bi->printAll();

	//debug(true, "REMOVE BOOK");
	//delete bi->removeBook(20345);
	//bi->removeBook(0);
	//bi->printAll();

	bi->ClearList();

	// ~Book_Inventory()
	delete bi;

}




























