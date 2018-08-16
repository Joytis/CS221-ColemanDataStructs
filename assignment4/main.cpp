//=============================================================================
// Programming Assignment 4
// File: main.cpp
// This program is a test procedure for a bunch of hashing stuff
//
// Author: Clark Chambers
// History:
//      (October 30th, 2016): Created
//=============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#ifdef _MSC_VER
// Pragma workaround. Stop complaining, Microsoft.
#pragma warning(disable: 4996) // Disables microsoft's warnings about unsafe memory editing
#include <conio.h>
#endif
#include <string>

#define TABLESIZE     (100)
#define KEYSIZE       (4)
#define EMPTYKEY      ("----")
#define DATAFILE      ("P4DATA.TXT")

#define MD5_SIGNATURE_SIZE   16   /* 16 bytes in a MD5 message digest */


typedef unsigned int UINT;
typedef unsigned char BYTE;

// MD5.h
/* typedef a 32 bit type */
typedef unsigned int UINT4;

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
  UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
  UINT4 buf[4];                                    /* scratch buffer */
  unsigned char in[64];                              /* input buffer */
  unsigned char digest[16];     /* actual digest after MD5Final call */
} MD5_CTX;



void MD5Init (MD5_CTX* mdContext);
void MD5Update (MD5_CTX* mdContext, BYTE* inBuf, UINT inLen);
void MD5Final (MD5_CTX* mdContext);

// NOTE(clark): Grabbed an Md5 function from some of my work source.

/* -- include the following line if the md5.h header file is separate -- */
/* forward declaration */
static void Transform ();

static unsigned char PADDING[64] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* F, G and H are basic MD5 functions: selection, majority, parity */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z))) 

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) \
  {(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }

/* Basic MD5 step. Transform buf based on in.
 */
static void Transform (UINT4* buf,UINT4* in)
{
  UINT4 a = buf[0], b = buf[1], c = buf[2], d = buf[3];

  /* Round 1 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
  FF ( a, b, c, d, in[ 0], S11, 3614090360); /* 1 */
  FF ( d, a, b, c, in[ 1], S12, 3905402710); /* 2 */
  FF ( c, d, a, b, in[ 2], S13,  606105819); /* 3 */
  FF ( b, c, d, a, in[ 3], S14, 3250441966); /* 4 */
  FF ( a, b, c, d, in[ 4], S11, 4118548399); /* 5 */
  FF ( d, a, b, c, in[ 5], S12, 1200080426); /* 6 */
  FF ( c, d, a, b, in[ 6], S13, 2821735955); /* 7 */
  FF ( b, c, d, a, in[ 7], S14, 4249261313); /* 8 */
  FF ( a, b, c, d, in[ 8], S11, 1770035416); /* 9 */
  FF ( d, a, b, c, in[ 9], S12, 2336552879); /* 10 */
  FF ( c, d, a, b, in[10], S13, 4294925233); /* 11 */
  FF ( b, c, d, a, in[11], S14, 2304563134); /* 12 */
  FF ( a, b, c, d, in[12], S11, 1804603682); /* 13 */
  FF ( d, a, b, c, in[13], S12, 4254626195); /* 14 */
  FF ( c, d, a, b, in[14], S13, 2792965006); /* 15 */
  FF ( b, c, d, a, in[15], S14, 1236535329); /* 16 */

  /* Round 2 */
#define S21 5
#define S22 9
#define S23 14
#define S24 20
  GG ( a, b, c, d, in[ 1], S21, 4129170786); /* 17 */
  GG ( d, a, b, c, in[ 6], S22, 3225465664); /* 18 */
  GG ( c, d, a, b, in[11], S23,  643717713); /* 19 */
  GG ( b, c, d, a, in[ 0], S24, 3921069994); /* 20 */
  GG ( a, b, c, d, in[ 5], S21, 3593408605); /* 21 */
  GG ( d, a, b, c, in[10], S22,   38016083); /* 22 */
  GG ( c, d, a, b, in[15], S23, 3634488961); /* 23 */
  GG ( b, c, d, a, in[ 4], S24, 3889429448); /* 24 */
  GG ( a, b, c, d, in[ 9], S21,  568446438); /* 25 */
  GG ( d, a, b, c, in[14], S22, 3275163606); /* 26 */
  GG ( c, d, a, b, in[ 3], S23, 4107603335); /* 27 */
  GG ( b, c, d, a, in[ 8], S24, 1163531501); /* 28 */
  GG ( a, b, c, d, in[13], S21, 2850285829); /* 29 */
  GG ( d, a, b, c, in[ 2], S22, 4243563512); /* 30 */
  GG ( c, d, a, b, in[ 7], S23, 1735328473); /* 31 */
  GG ( b, c, d, a, in[12], S24, 2368359562); /* 32 */

  /* Round 3 */
#define S31 4
#define S32 11
#define S33 16
#define S34 23
  HH ( a, b, c, d, in[ 5], S31, 4294588738); /* 33 */
  HH ( d, a, b, c, in[ 8], S32, 2272392833); /* 34 */
  HH ( c, d, a, b, in[11], S33, 1839030562); /* 35 */
  HH ( b, c, d, a, in[14], S34, 4259657740); /* 36 */
  HH ( a, b, c, d, in[ 1], S31, 2763975236); /* 37 */
  HH ( d, a, b, c, in[ 4], S32, 1272893353); /* 38 */
  HH ( c, d, a, b, in[ 7], S33, 4139469664); /* 39 */
  HH ( b, c, d, a, in[10], S34, 3200236656); /* 40 */
  HH ( a, b, c, d, in[13], S31,  681279174); /* 41 */
  HH ( d, a, b, c, in[ 0], S32, 3936430074); /* 42 */
  HH ( c, d, a, b, in[ 3], S33, 3572445317); /* 43 */
  HH ( b, c, d, a, in[ 6], S34,   76029189); /* 44 */
  HH ( a, b, c, d, in[ 9], S31, 3654602809); /* 45 */
  HH ( d, a, b, c, in[12], S32, 3873151461); /* 46 */
  HH ( c, d, a, b, in[15], S33,  530742520); /* 47 */
  HH ( b, c, d, a, in[ 2], S34, 3299628645); /* 48 */

  /* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
  II ( a, b, c, d, in[ 0], S41, 4096336452); /* 49 */
  II ( d, a, b, c, in[ 7], S42, 1126891415); /* 50 */
  II ( c, d, a, b, in[14], S43, 2878612391); /* 51 */
  II ( b, c, d, a, in[ 5], S44, 4237533241); /* 52 */
  II ( a, b, c, d, in[12], S41, 1700485571); /* 53 */
  II ( d, a, b, c, in[ 3], S42, 2399980690); /* 54 */
  II ( c, d, a, b, in[10], S43, 4293915773); /* 55 */
  II ( b, c, d, a, in[ 1], S44, 2240044497); /* 56 */
  II ( a, b, c, d, in[ 8], S41, 1873313359); /* 57 */
  II ( d, a, b, c, in[15], S42, 4264355552); /* 58 */
  II ( c, d, a, b, in[ 6], S43, 2734768916); /* 59 */
  II ( b, c, d, a, in[13], S44, 1309151649); /* 60 */
  II ( a, b, c, d, in[ 4], S41, 4149444226); /* 61 */
  II ( d, a, b, c, in[11], S42, 3174756917); /* 62 */
  II ( c, d, a, b, in[ 2], S43,  718787259); /* 63 */
  II ( b, c, d, a, in[ 9], S44, 3951481745); /* 64 */

  buf[0] += a;
  buf[1] += b;
  buf[2] += c;
  buf[3] += d;
}


void MD5Init (MD5_CTX* mdContext)
{
  mdContext->i[0] = mdContext->i[1] = (UINT4)0;

  /* Load magic initialization constants.
   */
  mdContext->buf[0] = (UINT4)0x67452301;
  mdContext->buf[1] = (UINT4)0xefcdab89;
  mdContext->buf[2] = (UINT4)0x98badcfe;
  mdContext->buf[3] = (UINT4)0x10325476;
}

void MD5Update (MD5_CTX* mdContext, BYTE* inBuf, UINT inLen)
{
  UINT4 in[16];
  int mdi;
  unsigned int i, ii;

  /* compute number of bytes mod 64 */
  mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

  /* update number of bits */
  if ((mdContext->i[0] + ((UINT4)inLen << 3)) < mdContext->i[0])
    mdContext->i[1]++;
  mdContext->i[0] += ((UINT4)inLen << 3);
  mdContext->i[1] += ((UINT4)inLen >> 29);

  while (inLen--) {
    /* add new character to buffer, increment mdi */
    //if(*inBuf != 0) printf("%c", *inBuf);		// writting 0's as a character seems to lock up the uart for a few seconds
    mdContext->in[mdi++] = *inBuf++;

    /* transform if necessary */
    if (mdi == 0x40) {
      for (i = 0, ii = 0; i < 16; i++, ii += 4)
        in[i] = (((UINT4)mdContext->in[ii+3]) << 24) |
                (((UINT4)mdContext->in[ii+2]) << 16) |
                (((UINT4)mdContext->in[ii+1]) << 8) |
                ((UINT4)mdContext->in[ii]);
      Transform (mdContext->buf, in);
      mdi = 0;
    }
  }
}

void MD5Final (MD5_CTX* mdContext)
{
  UINT4 in[16];
  int mdi;
  unsigned int i, ii;
  unsigned int padLen;

  /* save number of bits */
  in[14] = mdContext->i[0];
  in[15] = mdContext->i[1];

  /* compute number of bytes mod 64 */
  mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

  /* pad out to 56 mod 64 */
  padLen = (mdi < 56) ? (56 - mdi) : (120 - mdi);
  MD5Update (mdContext, PADDING, padLen);

  /* append length in bits and transform */
  for (i = 0, ii = 0; i < 14; i++, ii += 4)
    in[i] = (((UINT4)mdContext->in[ii+3]) << 24) |
            (((UINT4)mdContext->in[ii+2]) << 16) |
            (((UINT4)mdContext->in[ii+1]) << 8) |
            ((UINT4)mdContext->in[ii]);
  Transform (mdContext->buf, in);

  /* store buffer in digest */
  for (i = 0, ii = 0; i < 4; i++, ii += 4) {
    mdContext->digest[ii] = (unsigned char)(mdContext->buf[i] & 0xFF);
    mdContext->digest[ii+1] =
      (unsigned char)((mdContext->buf[i] >> 8) & 0xFF);
    mdContext->digest[ii+2] =
      (unsigned char)((mdContext->buf[i] >> 16) & 0xFF);
    mdContext->digest[ii+3] =
      (unsigned char)((mdContext->buf[i] >> 24) & 0xFF);
  }
}


/*
 **********************************************************************
 ** End of md5.c                                                     **
 ******************************* (cut) ********************************
 */

/*
 **********************************************************************
 ** End of md5.h                                                     **
 ******************************* (cut) ********************************
 */

using namespace std;

// Define the structure for use in the hash table
struct HashStruct
{
		 char key[5];
		 int data;
};

void InitTable(HashStruct hashT[], int TableSize);
int HashInsert(HashStruct T[], char *key, int data, int hNum, int dhNum);

int Hash_1(char* key);
int Hash_2(char* key);
int Hash_3(char* key);
int ProbeDec_1(char* key); 
int ProbeDec_2(char* key);
int ProbeDec_3(char* key);

int main()
{
	//==============================================================================
	/* --- Snippet 1: Partial list of variables defined in main() --- */
	int          i, hashNum, dHashNum, count;
	ifstream     *inFile;
	HashStruct   T[100];  // Hash table srray of 100 data structures
	char         line[64];// Array to hold lines read from file
	char         key[5];  // Array to hold 4-character keys
	int          data;    // Integer data
	char* 		 filename = DATAFILE;

	//==============================================================================
	/* --- Snippet 2: The following code can be used to perform the 9 tests. Use 
		hashNum to increment a loop for each of 3 hash functions and 
		dHashNum to increment a nested loop for each of 3 double 
		hash functions. --- */
		
	// For each of three hash functions
	for(hashNum = 0; hashNum < 3; hashNum++)
	{
		 // For each of three double hash functions
		for(dHashNum = 0; dHashNum < 3; dHashNum++)
		{
			InitTable(T, TABLESIZE);               // Call function to initialize table to empty
			inFile = new ifstream();
			inFile->open(filename, ifstream::in);   // Open data file for this test
			if(!inFile->is_open())
			{
				cout << "Unable to open data file. Program terminating\n";
				return 0;
			}
			count = 0;     // Initialize collision counter
			for(int i = 0; i < 50; i++)
			{
				inFile->getline(line, 64, '\n');
				sscanf(line, "%s %d", key, &data);
				count += HashInsert(T, key, data, hashNum, dHashNum);
				// Note: The HashInsert() function uses the indices of hashNum and
				// dHashNum to know which hash function and double hash function to call
				// in this test.


			}
			inFile->close();    /* Close the text file */
			delete inFile;

			//==============================================================================
			/* --- Snippet 3: This code shows how to create a diagram of the results of a single
					test using one hash function and one double hash function.  The resulting
					diagram looks similar to the sample below with '|' representing a slot where
					a key hashed or double hashed to and '-' representing an empty slot:
					||-||||---|||-|-||||||||-----||-|-||---||||--|-|||...etc.  --- */
			cout << "Testing hash function " << hashNum << " using double hash " << dHashNum << ".\n";
			cout << "Total collisions = " << count << ".\n";
			// Show the form of the array
			for(int i=0; i < 100; i++)
				if(strcmp(T[i].key, EMPTYKEY)) // strcmp gives a non-zero (true) result if Key is NOT the EMPTYKEY
					cout << "|";     // Indicate an entry at this location
				else
					cout << "-";     // Indicate no entry at this location
			cout << "\n\n";
		}
	}

	return 0;		
}

//==============================================================================
/* --- Snippet 4: Initialize table function --- */
void InitTable(HashStruct hashT[], int TableSize)
{
	int i;

	for(i=0; i<TableSize; i++)
	{
		strcpy(hashT[i].key, EMPTYKEY);
		hashT[i].data = 0;
	}
}

//==============================================================================
/*--- Snippet 5: Hash Insert function testNum is a number from 0 through 8
	 indicating which test is being run.  This can be calculated 
	 from hashNum and dHashNum in snippet 2, for example:
	 testNum = (hashNum * 3) + dHashNum.  --- */

int HashInsert(HashStruct T[], char *key, int data, int hNum, int dhNum)
{
	int  testNum = (hNum * 3) + dhNum;
	int  colCount = 0;
	int  hashIndex, probeDec;

	switch(testNum)
	{
		case 0 :  // Hash function 1 -- Double hash 1 (linear probing) 
			hashIndex = Hash_1(key);
			probeDec = ProbeDec_1(key); // Function just returns 1 
			break;
		case 1 :  // Hash function 1 -- Double hash 2  
			hashIndex = Hash_1(key);
			probeDec = ProbeDec_2(key);
			break;
		case 2 :  // Hash function 1 -- Double hash 3  
			hashIndex = Hash_1(key);
			probeDec = ProbeDec_3(key);
			break;
		case 3 :  // Hash function 2 -- Double hash 1 (linear probing)  
			hashIndex = Hash_2(key);
			probeDec = ProbeDec_1(key); // Function just returns 1
			break;
		case 4 :  // Hash function 2 -- Double hash 2  
			hashIndex = Hash_2(key);
			probeDec = ProbeDec_2(key);
			break;
		case 5 :  // Hash function 2 -- Double hash 3  
			hashIndex = Hash_2(key);
			probeDec = ProbeDec_3(key);
			break;
		case 6 :  // Hash function 3 -- Double hash 1 (linear probing)  
			hashIndex = Hash_3(key);
			probeDec = ProbeDec_1(key); // Function just returns 1
			break;
		case 7 :  // Hash function 3 -- Double hash 2  
			hashIndex = Hash_3(key);
			probeDec = ProbeDec_2(key);
			break;
		case 8 :  // Hash function 3 -- Double hash 3  
			hashIndex = Hash_3(key);
			probeDec = ProbeDec_3(key);
			break;
	}

	// Find a place to insert into the table
	while(strcmp(T[hashIndex].key, EMPTYKEY) != 0)
	{
		colCount++;
		hashIndex -= probeDec;  // Decrementing was chosen you could also choose to
		if(hashIndex < 0)    //  increment and wrap back to the beginning of the table.
		hashIndex = hashIndex + TABLESIZE;
	}

	//  You must add the code to insert key and data 
	//     into the table at index hashIndex at this point and then
	//     return the collision count
	strcpy(T[hashIndex].key, key);
	T[hashIndex].data = data;

	return colCount;
}

// Some hash functions and all that. 
// Case the key as a uint_32 and mod
int Hash_1(char* key)
{
	// cout << "Hash1: Uint cast + mod" << endl;
	int retkey = 0;
	UINT* charsum = (UINT*)key;

	retkey = (*charsum) % TABLESIZE;

	return retkey;
}

// Some hash functions and all that.
// MD5! :D 
// (just casting part of the 16 BYTE digest and modding it.)
int Hash_2(char* key)
{
	// cout << "Hash2: MD5" << endl;
	MD5_CTX md5;
	int ckey = *((UINT*)key); 
	char hash[MD5_SIGNATURE_SIZE];

	MD5Init(&md5);
    MD5Update(&md5, (BYTE*)key, 4);
    MD5Final(&md5);

	return (*(UINT*)md5.digest % TABLESIZE);
}
// Some hash functions and all that. 
// Middle squaring!
int Hash_3(char* key)
{
	// cout << "Hash3: Middle squaring" << endl;
	int stuff = (key[1] + key[2]);
	stuff *= stuff;
	return  stuff % TABLESIZE;
}
// Some hash functions and all that. 
// Linear probing
int ProbeDec_1(char* key)
{
	// cout << "Probe1: Linear Probing" << endl;
	return 1;
}

// Some hash functions and all that. 
// Mod by 7 for double hashing
int ProbeDec_2(char* key)
{
	// cout << "Prob2: Uint cast + mod double hash" << endl;
	int ctret = 1;
	UINT* charsum = (UINT*)key;

	ctret = (*charsum % 7) + 1;

	return ctret;
}

// Some hash functions and all that. 
// MD5! :D 
// (just casting part of the 16 BYTE digest and modding it.)
int ProbeDec_3(char* key)
{
	// cout << "Probe3: Md5 double hash" << endl;
	MD5_CTX md5;
	int ckey = *((UINT*)key); 
	char hash[MD5_SIGNATURE_SIZE];

	MD5Init(&md5);
    MD5Update(&md5, (BYTE*)key, 4);
    MD5Final(&md5);

	return (*(UINT*)md5.digest % 7) + 1;
}
