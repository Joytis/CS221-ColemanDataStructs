//=============================================================================
// Programming Assignment 1
// File: BookRecord.h
// This program is a test procedure for BookRecord.
//
// Author: Clark Chambers
// History:
//      (September 4th, 2016): Created
//=============================================================================

#ifndef __BookRecord_H_
#define __BookRecord_H_

#define SNAME_SIZE          (128)            // Book name maximum size

#ifdef _MSC_VER
// Pragma workaround. Stop complaining, Microsoft.
	#pragma warning(disable: 4996) // Disables microsoft's warnings about unsafe memory editing
#endif

class BookRecord
{
private:
	// Next node in the Book record linked list.
	BookRecord* 	m_pNext;

    char   			m_sName[SNAME_SIZE];    // Book name member variable array
    long   			m_lStockNum;            // Unique Stock number of the Book
    int    			m_iClassification;      // Code-specific classifiction number
    double 			m_dCost;                // Cost of the Book
    int    			m_iCount;               // Number of Books currently in inventory

public:
    BookRecord();   // Default constructor
    BookRecord(char *name, long sn, int cl, double cost);   // Overloaded Constructor

    ~BookRecord();  // Default (Blank and placeholder) Destructor

    void getName(char *name);   // Gets m_sName
    void setName(char *name);   // Sets m_sName
    long getStockNum();         // Gets m_lStockNum
    void setStockNum(long sn);  // Sets m_lStockNum
	int getClassification();			// just returns the classification number.
    void setClassification(int cl);     // sets m_iClassification
    //void getClassification(int& cl);  // gets m_iClassification (DEPRECATED)
	double getCost();			// just returns the normal cost.
    void setCost(double c);     // Sets m_dCost
    //void getCost(double *c);  // Gets m_dCost (DEPRECATED)
    int getNumberInStock();             // Gets m_iCound
    void setNumberInStock(int count);   // sets m_iCount
	BookRecord *getNext();				// Gets the node next
	void setNext(BookRecord *next);		// Sets the node next
    void printRecord();
};


#endif //__BookRecord_H_
