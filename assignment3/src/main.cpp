
#include <iostream>
#include "Book_Database.h"
#include "BookRecord.h"
#include "dbg.hpp"

//using namespace std;

// Test Main
int main(int argc, char* argv[]) {

	// test Initializer
	debug(true, "TESTING INITIALIZER");
	Book_Database db;
	db.PrintAll();

	// Test Read Database / print all
	debug(true, "TESTING LOAD AND PRINT");
	db.readDatabase("./inventory/BookData.txt");
	db.PrintAll();

	// Testing remove
	debug(true, "TESTING REMOVE");
	db.removeBook(456);
	db.PrintAll();
	debug(true, "-----------------");
	db.removeBook(234);
	db.PrintAll();
	debug(true, "-----------------");
	db.removeBook(123);
	db.PrintAll();
	debug(true, "-----------------");
	db.removeBook(876);
	db.PrintAll();
	debug(true, "-----------------");
	db.removeBook(567);
	db.PrintAll();
	debug(true, "-----------------");
	db.removeBook(0);
	db.PrintAll();


	// Tests the ClearList
	// test Initializer
	debug(true, "TESTING CLEAR");
	Book_Database* db2 = new Book_Database();
	db2->readDatabase("./inventory/BookData.txt");
	db2->PrintAll();
	delete db2;
	db2 = nullptr;

	// Testing Search by Stock Num
	debug(true, "TESTING SEARCHBYSTOCKRECORD");
	db2 = new Book_Database();
	db2->readDatabase("./inventory/BookData.txt");
	db2->searchByStockNumber(456)->printRecord();
	db2->searchByStockNumber(123)->printRecord();
	db2->searchByStockNumber(567)->printRecord();

	// Testing GetNum in stock
	debug(true, "TESTING GetNumInStock");
	printf("Num IN Stock: %d", db2->getNumInStock(456));

	// Testing searchByClassification
	debug(true, "TESTING searchByClassification");
	db2->searchByClassification(613);
	debug(true, "--------------------------");
	db2->searchByClassification(316);

	// Testing searchByCost
	debug(true, "TESTING searchByCost");
	db2->searchByCost(30.0, 40.0);
	debug(true, "--------------------------");
	db2->searchByCost(40.0, 50.0);
	debug(true, "--------------------------");
	db2->searchByCost(50.0, 60.0);
	debug(true, "--------------------------");
	db2->searchByCost(0.0, 100.0);

	delete db2;
	return 0;
}




