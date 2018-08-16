//=============================================================================
// Programming Assignment 3
// File: Book_Database.h
// This program is a test procedure for Book_Database.
//
// Author: Clark Chambers
// History:
//      (October 10th, 2016): Created
//=============================================================================

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "BookRecord.h"

#ifdef _MSC_VER
// Pragma workaround. Stop complaining, Microsoft.
   #pragma warning(disable: 4996) // Disables microsoft's warnings about unsafe memory editing
#endif

using namespace std;

class Book_Database 
{
   private:
      BookRecord *m_pRoot;                         		// Pointer to root of the tree
      ifstream   m_InFile;                         		// File containing inventory


   public:
      Book_Database ();                            		// Class constructor
      ~Book_Database ();                           		// Class destuctor
      bool readDatabase(char *filename);           		// Read database from file
      bool addBook(BookRecord *br);                		// Add the given book to the list
      BookRecord *removeBook(long stockNum);              	// Remove a book from the list
      BookRecord *searchByStockNumber(long stockNum);    	// Search for a book by stock number
      void searchByClassification(int cl);         		// Search for all books of the given classification
      void searchByCost(double min, double max);   		// Search for all books whose cost is within the given range
      int getNumInStock(long sn);				// Get number of books of given stock number in stock 
      void PrintAll();                             		// Print all items in the database

   private:
      void ClearList(BookRecord *rt);              		// Recursively remove any items from the list
      bool getNextLine(char *line, int lineLen);   		// Read next line from a file
      void searchByClassification(int cl, BookRecord *rt);	// Recursive search by classification
      void searchByCost(double min, double max, BookRecord *rt);// Recursive search by cost range
      void PrintAll(BookRecord *rt);               		// Recursive print all
};