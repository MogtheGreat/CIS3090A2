#include "encryptDecrypt.h"

//	Records the number of unique letters in a string.
//	Input:
//		input 		- a pointer to an array of char that is the user input
//		count 		- a pointer to an int that is the number of unique letters
//		letters 	- a pointer to an array of int that represent the alphabet
//	Output:
//		N/A
//
static void countLetters (char * input, int * count, int * letters)
{
	int i = 0;

	while (input[i] != '\0')
	{
		if (input[i] >= 'a' && input [i] <= 'z')
		{
			if (letters[input[i] - 'a'] == 0)
				*count += 1;
			letters[(input[i] - 'a')]++;
		}
		i++;
	}
} // end of countLetters

/*
		Used in copyUniLet. Checks to make sure each letter from
		input is counted and only once to total.
		Input:
			letters 		- an array of int that represents the alphabet
			count 			- A pointer to an int that represents the number of unique letters counted
		Output:
			N/A
*/
static void debugOne (int * letters, int * count)
{
	int i = 0;

	if (DEBUG)
	{
		for (i = 0; i < 26; i++)
		{
			printf ("%d: %d\n", i, letters[i]);
		}
		printf ("Count is %d\n", *count);
	}
} // End of debugOne

// Seaches through the input and copies all unique letters to a string
// in the order of first appeared in the input
// Input:
//		input 		- a pointer to an array of char that is the user input
// Output:
//		A pointer that an array of char that represents the unique letters of a user input
//
char * copyUniLet (char * input)
{
	char * temp = NULL;
	int letters [26];
	int count = 0;
	int i = 0;
	int k = 0;

	for (i = 0; i < 26; i++)
	{
		letters[i] = 0;
	}

	countLetters (input, &count, letters);		// Gets the total number of unique letters in input
	debugOne (letters, &count);
	temp = malloc (sizeof (char) * count+1);

	for (i = 0; i < 26; i++)
	{
		letters[i] = 0;
	}

	// Copies all unique letters to temp variable
	for (i = 0; i < strlen (input); i++)
	{
		// Checks to see char is a letter
		if (input[i] >= 'a' && input [i] <= 'z')
		{
			// Checks to see if been recorded already
			if (letters[input[i] - 'a'] == 0)
			{
				temp[k] = input[i];
				letters[input[i] - 'a'] = 1;
				k++;
			}
		}
	}

	temp [k] = 0;

	return temp;
} // end of copyUniLet ()

// Swaps the location of two chars in a string
// Input:
//		encrpytDict		- A pointer to an array of char that is the encryption key
//		loc1			- an int that represents the first location in the string
//		loc2			- an int that represents the second location in the string
static void swap (char * encrpytDict, int loc1, int loc2)
{
	char temp = encrpytDict[loc1];
	encrpytDict[loc1] = encrpytDict[loc2];
	encrpytDict[loc2] = temp;
} // end of swap

//	Creates an encryption key by randomly rearranging the letters
//	 of the input Dictionary
//
//	Input:
//		inputDict	- a pointer that an array of char that represents the unique letters of a user input
//	Output:
// A pointer to an array of char that is the encryption key
//
char * createEncrypt (char * inputDict)
{
	char * encrpytDict = NULL;
	int len = 0;
	int loc1 = 0;
	int loc2 = 0;
	int i = 0;

	len = strlen (inputDict);
	encrpytDict = malloc (sizeof (char) * len + 1);
	strcpy (encrpytDict, inputDict);
	srand(time(NULL));

	// randomly swaps the char in the string around
	for (i = 0; i < 100; i++)
	{
		loc1 = rand() % len;
		loc2 = rand() % len;
		swap (encrpytDict, loc1, loc2);
	}

	return encrpytDict;
} // end of createEncrypt ()

/*
	Goes through the input and changes a char to another based on a target char.
	Input:
		input 		- a pointer to an array of char that is the user input
		encryptStr	- a pointer to an array of char that is an encrypted string
		lenInput 	- a int that represents the length of the input
		target		- a char that represent the targeted char to change/encrypt
		key 		- a char that represent the encrypted char
		changed 	- An array of ints that represents whatever a section of the encryptStr has been encrypted
	Output:
		N/A

*/
static void replaceChar (char * input, char * encryptStr, int lenInput, char target, char key, int * changed)
{
	int i = 0;

	for (i = 0; i < lenInput; i++)
	{
		// Checks to see if the char in the input is the target and hasn't been encrypted yet.
		if ((input[i] == target) && (changed[i] == 0))
		{
			encryptStr[i] = key;
			changed[i] = 1;
		}
	}
} // replaceChar

/*
	Encrypts the user input by using the inputDict and the encryptDict. Switches
	the order of the char using the encryptDict as a key.
	Input:
		input 		- a pointer to an array of char that is the user input
		inputDict	- a pointer that an array of char that represents the unique letters of a user input
		encryptDict - A pointer to an array of char that is the encryption key
	Output:
		a pointer to an array of char that is an encrypted string.
*/
char * encryptInput (char * input, char * inputDict, char * encrpytDict)
{
	char * encryptStr = NULL;
	int lenInDict = 0;			// length of input dictionary
	int lenInput = 0;			// length of input
	int i = 0;
	int * changed = NULL;

	lenInput = strlen(input);
	encryptStr = malloc (sizeof (char) * lenInput + 1);
	strcpy (encryptStr, input);
	lenInDict = strlen (inputDict);
	changed = malloc (sizeof (int) * lenInput);

	for (i = 0; i < lenInput; i++)
		changed [i] = 0;

	// Goes through the input dictionary and change each char in the encrypted string to its corresponding key
	for (i = 0; i < lenInDict; i++)
	{
		replaceChar (input, encryptStr, lenInput, inputDict[i], encrpytDict[i], changed);
	}

	free (changed);

	return encryptStr;
} // end of encryptInput


/*
	Creates an array  of int that represents the number of chars
	and position within input dictionary.
	Input:
		myRank		- an int that represents the rank of the process
		len 		- an int that represents the length of inputDict
	Output:
	an array of int that represents the number of chars and position within input dictionary.
*/
static int * createPermutate (int myRank, int len)
{
	int i;
	int * permutate;

	permutate = malloc (sizeof(int) * len);
	permutate[0] = myRank;

	for (i = 1; i < len; i++)
	{
		permutate[i] = 0;
	}

	return permutate;
} // end of createPermutate

/*
	Sets the decryption key to the next pemutatin of the input dictionary.

	Input:
		inputDict	- a pointer that an array of char that represents the unique letters of a user input
		permutate 	- an array of int that represents the number of chars and position within input dictionary.
		len 		- a int that represents the length of the input dictionary
	Output:
		A pointer to an array of chars that represents a decryption key.
*/
static char * setDecrypt (char * inputDict, int * permutate, int len)
{
	int i;
	char * decryptKey = NULL;

	decryptKey = calloc (len+1, sizeof(char));

	for (i = 0; i < len; i++)
	{
		decryptKey[i] = inputDict[permutate[i]];
	}

	return decryptKey;
} // end of setDecrypt

/*
	Checks to see if all permutation of input dictionary has been found.
	Input:
		len 		-	an int that represents the length of the permutation array
		permutate 	-	a pointer to an array of ints that represents the permutation
	Output:
		0 if there is still another permutation
		1 if all found.
*/
static int allFoundPer (int len, int * permutate)
{
	int i;
	// NOTE: the length of the input Dictionary is the same as the number of unique chars.

	// ignores the first slot of the array. Divided amongst processes.
	for (i = 1; i < len; i++)
	{
		// check to see if any slot in the array has yet to reached the end of all available char
		// Don't remember why have minus one, but without causes infinite loop
		if (permutate[i] % (len-1) != 0)
		{
			return 0;
		}
		if (permutate[i] == 0)
		{
			return 0;
		}
	}
	return 1;
} // end of allFoundPer

/*
	Goes through the permutation array and checks to see if a slot has reached end of
	available char. If so resets it to zero and incremennt the next slot.
	Input:
		len 		-	an int that represents the length of the permutation array
		permutate 	-	a pointer to an array of ints that represents the permutation
	Output:
		N/A
*/
void checkArray (int len, int * permutate)
{
	int i;
	int carry = 0;

	for (i = (len-1); i >= 1; i--)
	{
		// Reached the end of available chars. Reset to beginning.
		if (permutate[i] > (len-1))
		{
			permutate[i] = 0;
			carry = 1;
		}
		// Next slot can be incremented.
		else if ((carry == 1) && (permutate[i] != (len-1)))
		{
			permutate[i] += carry;
			carry = 0;
		}
		// Next slot has also reached the end of available chars.
		else if ((carry == 1) && (permutate[i] == (len-1)))
		{
			permutate[i] = 0;
		}
	}
} // end of checkArray

/*
	Used in findKey. Used to ensure ALL permutation has been created.
	input:
		permutate 	- an array of int that represents the number of chars and position within input dictionary.
		len 		- a int that represents the length of the input dictionary		
	output:
		N/A
*/
static void debugTwo (int * permutate, int len)
{
	int i;

	if (DEBUG2)
	{
		for (i = 0; i < len; i++)
			printf ("%d",permutate[i]);
		printf("\n");
	}
} // end of debugTwos

/*
	checks to see if all chars in the decrypted key is unique.
	input:
		target 	-	A pointer to an array of chars that contains all unique chars
		test 	- 	A pointer to an array of chars that is being tested.
	 Output:
	 	0 if test contains duplicates chars
	 	1 if test contains all unique char
*/
static int allUniChar (char * target, char * test)
{
	int i;
	int k;
	int len;
	int inStr;
	int checked;

	len = strlen (target);
	inStr = 0;
	checked = 0;

	for (i = 0; i < len; i++)
	{
		for (k = 0; k < len; k++)
		{
			// first finding of char in test is recorded only
			if ((target[i] == test [k]) && (checked == 0))
			{
				inStr += 1;
				checked = 1;
			}
		}
		checked = 0;
	}

	// the number of chars found should match the length of target which is equal
	// to the number of unique chars.
	if (inStr == len)
		return 1;
	else
		return 0;
} // end of allUniChar

/*
	Goes through the encrypted string and changes the char based on the decryption key.

	input:
		encryptStr	- a pointer to an array of char that is an encrypted string
		inputDict	- a pointer to an array of char that represents the unique letters of a user input
		decryptKey	- a pointer to an array of char that represents the decryption key.
	output:
		A pointer to an array of char that represents a decrypted string.
*/
char * decryptInput (char * encryptStr, char * inputDict, char * decryptKey)
{
	char * temp = NULL;
	int lenInDict = 0;			// length of input dictionary
	int lenEncrypt = 0;			// length of encrypted string
	int i = 0;
	int * changed = NULL;

	lenEncrypt = strlen(encryptStr);
	temp = malloc (sizeof (char) * lenEncrypt + 1);
	strcpy (temp, encryptStr);
	lenInDict = strlen (inputDict);
	changed = malloc (sizeof (int) * lenEncrypt);

	for (i = 0; i < lenEncrypt; i++)
		changed[i] = 0;

	// Goes through the input dictionary and change each char in the encrypted string to its corresponding key
	for (i = 0; i < lenInDict; i++)
	{
		replaceChar (encryptStr, temp, lenEncrypt, inputDict[i], decryptKey[i], changed);
	}

	free (changed);

	return temp;
} // end of decryptInput


/*
	Creates a string that contains the command for the computer 
	that will search for a target word in dictionary.
	Input:
		target -	A pointer to an array of chars that represents a word? to searched in dictionary.
	Ouput:
		A point to an array of chars that represents the command to computer to search for a suppose
		word in dictionary.
*/
static char * createCom (char * target)
{
	char grep [] = "grep ^";
	char dictWords [] = "$ /usr/share/dict/words";
	char * allToGet = NULL;
	int len1 = 0;
	int len2 = 0;
	int len3 = 0;

	len1 = strlen (grep);
	len2 = strlen (target);
	len3 = strlen (dictWords);

	allToGet = malloc (sizeof(char) * (len1 + len2 + len3) +1);
	allToGet[0] = 0;
	strcat (allToGet, grep);
	strcat (allToGet, target);
	strcat (allToGet, dictWords);

	return allToGet;
} // end of createCom

/*
	Searches the dictonary in /usr/share/dict/words for the
	word(s) in decrypted string. Prints to screen if found.
	Input:
		decryptStr - 	A pointer to an array of char that represents a decrypted string.
		myRank - 		An int that represents the rank of the process
	Output:
		N/A		
*/
void checkGrep (char * decryptStr, int myRank)
{
	FILE * cmd;
	char target [2500];
	char * rest = NULL;
	char result [1024];
	char * command = NULL;
	char * token = NULL;
	int countTok = 0;
	int countRes = 0;

	strcpy (target, decryptStr);
	rest = target;

	// breaks the decrypt string up.
	while ((token = strtok_r (rest, " \t", &rest)))
	{
		command = createCom (token); 		// Creates the command to search for part of the decrypt string
		countTok++;
		cmd = popen (command, "r");
		
		if (cmd == NULL)
		{
			return;
		}

		// Counts the number of success.
		while (fgets (result, sizeof(result), cmd))
		{
			countRes++;
		}

		pclose (cmd);
		free (command);
	}

	// If the number of successful finds equal the number of suppose word(s) in the decrypted string
	// then decryption was successful.
	if (countRes == countTok)
	{
		printf ("Rank %d: %s\n", myRank, decryptStr);
	}

	return;
} // end of checkGrep

/*
		Decrypts the string by brute force. Finds every possible
		combination of the input dictionary to find the key.
	Input:
		inputDict 	- A pointer that an array of char that represents the unique letters of a user input
		encryptStr 	- a pointer to an array of char that is an encrypted string.
		myRank 		- An int that represents the rank of the process
	Output:
		N/A
*/
void findKey (char * inputDict, char * encryptStr, int myRank)
{
	int len;
	int * permutate;
	char * decryptKey = NULL;
	char * decryptStr = NULL;

	len = strlen (inputDict);
	permutate = createPermutate (myRank, len);		// creates an array of int that represents the permutation of the input Dictionary

	// Continue why all permutation has not been found.
	while (!(allFoundPer (len, permutate)))
	{
		decryptKey = setDecrypt (inputDict, permutate, len);	// Set decrypt key to the next permutation

		if (allUniChar(inputDict, decryptKey))
		{
			decryptStr = decryptInput (encryptStr, inputDict, decryptKey);
			checkGrep (decryptStr, myRank);		// Check result to see if properly decrypted
		}
		
		debugTwo (permutate, len);		// Used to see if going through all permutations
		permutate[len-1] +=1;

		//  if last slot of permutation has reached the end of the available chars.
		if (permutate[len-1] > (len-1))
		{
			checkArray (len, permutate);
		}
		free (decryptKey);

		if (decryptStr != NULL)
		{
			free (decryptStr);
			decryptStr = NULL;
		}
	}

	free (permutate);
	return;
} // end of findKey
