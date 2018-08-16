//=============================================================================
// Programming Assignment 1
// File: BookRecord.cpp
// This program is a test procedure for BookRecord.
//
// Author: Clark Chambers
// History:
//      (September 4th, 2016): Created
//=============================================================================

#include <iostream>
#include <cstring>

#include "BookRecord.h"

// Basic constructor for BookRecord
BookRecord::BookRecord()
{
    strcpy(m_sName, "");
    m_lStockNum = 0;
    m_iClassification = 0;
    m_dCost = 0.0;
    m_iCount = 0;
}

// Exnapded Constructor for BookRecord
BookRecord::BookRecord(char *name, long sn, int cl, double cost)
{
    if(name == NULL)    // Passing NULL pointers? Not on my watch!
    {
        printf("BR: Null pointer passed. Setting m_sName to blank string!\n");
        // Handled by copying NULL string into m_sName
        strcpy(m_sName, "");
    }
    else
    {
        strncpy(m_sName, name, sizeof(m_sName)); // Only copies first 128 characters
    }

    // Sets all private members to respective arguments.
    m_lStockNum = sn;       // stock number
    m_iClassification = cl; // Classification
    m_dCost = cost;         // Cost
    m_iCount = 1;           // Initialize count to 1
}

// Blank Placeholder Destructor
BookRecord::~BookRecord() {}

// Gets the name array copies it into passed array.
void BookRecord::getName(char *name) // Can't do error checking on sizeof(name) without length passed in
{
    if(name == NULL)
    {
        printf("BR: Null pointer passed. Please don't do this :c\n"); // <- Sassy code
    }
    else
    {
        strncpy(name, m_sName, SNAME_SIZE); // Safe copy
    }
}

// Copies the character array into name?
void BookRecord::setName(char *name)
{
    if(name == NULL)
    {
        printf("BR: Null pointer passed. Doing nothing!\n");
    }
    else
    {
        strncpy(m_sName, name, sizeof(m_sName)); // Safe string copy into m_sNames
    }
}

// returns the number in stock
long BookRecord::getStockNum()
{
    return m_lStockNum;
}

// Sets the stock number
void BookRecord::setStockNum(long sn)
{
    m_lStockNum = sn; // sets Stock number equal to argument.
}

// Gets class of book
void BookRecord::getClassification(int& cl)
{
    cl = m_iClassification; // Copies Classification information into cl
}

// Sets class of book
void BookRecord::setClassification(int cl)
{
    m_iClassification = cl; // Sets classification to arg
}

// Returns the cost of the book
void BookRecord::getCost(double *c)
{
    if(c == NULL) // NULL pointer error checking
    {
        printf("BR: Null pointer passed. Please don't do this :c\n");
    }
    else
    {
        *c = m_dCost; // Copies cost into c. Weird.
    }
}

// Sets the cost of the book.
void BookRecord::setCost(double c)
{
    m_dCost = c;
}

// Gets number in stock
int BookRecord::getNumberInStock()
{
    return m_iCount;
}

// sets number in stock
void BookRecord::setNumberInStock(int count)
{
    m_iCount = count;
}

// Print out stuff about the book.
void BookRecord::printRecord()
{
//    m_sName[SNAME_SIZE];
//    long    m_lStockNum;
//    int     m_iClassification;
//    int     m_iCount;
//    double  m_dCost;
    printf("<%s>: StockNum: %ld | Classification: %d | #InStock: %d | Cost: %.2f \n",
           m_sName,
           m_lStockNum,
           m_iClassification,
           m_iCount,
           m_dCost);
}
