#define _DEFAULT_SOURCE
#define _BSD_SOURCE			// Need to be before stdio.h. Used for popen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#define DEBUG 0 		// For copyUniLet ()
#define DEBUG2 0		// For findKey ()

char * copyUniLet (char * input);

char * createEncrypt (char * inputDict);

char * encryptInput (char * input, char * inputDict, char * encrpytDict);

void findKey (char * inputDict, char * encryptStr, int myRank);

char * decryptInput (char * encryptStr, char * inputDict, char * decryptKey);

void checkGrep (char * decryptStr, int myRank);