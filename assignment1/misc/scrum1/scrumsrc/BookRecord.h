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

class BookRecord
{
private:
    char    m_sName[SNAME_SIZE];    // Book name member variable array
    long    m_lStockNum;            // Unique Stock number of the Book
    int     m_iClassification;      // Code-specific classifiction number
    double  m_dCost;                // Cost of the Book
    int     m_iCount;               // Number of Books currently in inventory

public:
    BookRecord();   // Default constructor
    BookRecord(char *name, long sn, int cl, double cost);   // Overloaded Constructor

    ~BookRecord();  // Default (Blank and placeholder) Destructor

    void getName(char *name);   // Gets m_sName
    void setName(char *name);   // Sets m_sName

    long getStockNum();         // Gets m_lStockNum
    void setStockNum(long sn);  // Sets m_lStockNum

    void getClassification(int& cl);    // gets m_iClassification
    void setClassification(int cl);     // sets m_iClassification

    void getCost(double *c);    // Gets m_dCost
    void setCost(double c);     // Sets m_dCost

    int getNumberInStock();             // Gets m_iCound
    void setNumberInStock(int count);   // sets m_iCount

    void printRecord();
};


#endif //__BookRecord_H_
