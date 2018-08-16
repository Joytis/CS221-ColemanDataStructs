//=============================================================================
// Programming Assignment 1
// File: main.cpp
// This program is a test procedure for BookRecord.
//
// Author: Clark Chamebrs
// History:
//      (September 4th, 2016): Created
//=============================================================================

#include <iostream>
#include <cstdio>

#include "dbg.hpp"
#include "BookRecord.h"

// I really, REALLY hate you microsoft

#define DBG_MAIN        DEBUG_ON

#define TEST_PRINT          // NOTE(clark): Working
#define TEST_GETSET         // NOTE(clark): Working
#define TEST_MISC           // NOTE(clark): Working

int main(int argc, char **args)
{
    // Tests constructors to make sure they're functional.
    char s[128];
    char s2[] = "Who would fard thus the and morthy take with make contumely, and, by a sleep of thus and end scorns of outrageous that pith may consients thance of us all; and arms makes, what fled of regardels we hue of? To bear to sleep; not the question. There's that fly to sleep: perchance dreams and name opposing after 'tis hear the ill, must a sleep: perchan fled of deat sleep: perchance dreat is he under death when hear to troubler retus resolution: who would by of? Ther beart-ache us mortal shuffer a wear t"; // Filled with garbage.
    char dude_bro[] = "Dude, bro";
    br_strncpy(s, dude_bro, sizeof(s)); // Kind of redundant and silly. Just trint out strncpy

    BookRecord br;
    BookRecord br2(s, 1001, 10, 3.45); // testing normal case
    BookRecord br3(NULL, 1, 1, 1); // testing null case.
    BookRecord br4(s2, 1, 1, 1);   // testing overflow case

    //
    // Test the printRecord Method
    //====================================
#ifdef TEST_PRINT

    // NOTE(clark): Works correctly
    br.printRecord();
    br2.printRecord();
    br3.printRecord();
    br4.printRecord();

#endif //TEST_PRINT

    //
    // Tests all the Getter and setter Methods.
    //====================================
#ifdef TEST_GETSET

    char temp[128];
    char temp4[] = "Testing out the name setting! Nice!";

    debug(DBG_MAIN, "%s", temp4);

    // NOTE(clark): Works correctly
    //getName/setName
    br.getName(temp);   // Gets m_sName
    debug(DBG_MAIN, "br.getName: %s", temp);
    br.setName(temp4);   // Sets m_sName
    br.getName(temp);   // Gets m_sName
    debug(DBG_MAIN, "br.getName: %s", temp);
    br.setName(NULL);   // NULL case
    br.getName(temp);   // Gets m_sName
    debug(DBG_MAIN, "br.getName: %s", temp);

    // NOTE(clark): Works correctly
    //setStock/getStockNum
    br.setStockNum(7890789078907890);  // Sets m_lStockNum
    debug(DBG_MAIN, "br.getStorkNum: %ld", br.getStockNum());
    br.setStockNum(404040404);
    debug(DBG_MAIN, "br.getStorkNum: %ld", br.getStockNum());

    // NOTE(clark): Works correctly
    // get/setClassification();
    int classi = 5;
    debug(DBG_MAIN, "classy: %i", classi);
    br.setClassification(10);     // sets m_iClassification
    br.getClassification(classi);    // gets m_iClassification
    debug(DBG_MAIN, "classy: %i", classi);

    // NOTE(clark): Works correctly
    // get/setCost
    double pr = 0;
    debug(DBG_MAIN, "pr: %f", pr);
    br.setCost(3.45);     // Sets m_dCost
    br.getCost(&pr);    // Gets m_dCost
    debug(DBG_MAIN, "pr: %f", pr);


    // NOTE(clark): Works correctly
    // get/setNumberInStock
    br.setNumberInStock(12);   // sets m_iCount
    debug(DBG_MAIN, "stock: %i", br.getNumberInStock());
    br.setNumberInStock(14);
    debug(DBG_MAIN, "stock: %i", br.getNumberInStock());

    // NOTE(clark(: Works Correctly
    br.printRecord();
#endif //TEST_GETSET

#ifdef TEST_MISC
#endif //TEST_MISC

	std::cin.ignore();

    return 0;
}