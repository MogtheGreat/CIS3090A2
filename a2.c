/* a2.c

Process 0 gets the input from user and encrypts. Then it divides the
work amongst all the other processes and decrypts it.

Created: 28 Oct. 2017
Author: Michael G. Oranski ID: 0557701
Contact: moranski@mail.uoguelph.ca
*/
#include "encryptDecrypt.h"

int main ()
{
	int i;
	int len1;
	int len2;
	int myRank = 0;
	int commSize;
	char str[350];
	char * inputDict = NULL;
	char * encrpytDict = NULL;
	char * encryptStr = NULL;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank (MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);

	if (myRank == 0)
	{
		printf ("Please enter a string to be encrypted.\n");
		fgets (str, 349, stdin);
		str [(strlen(str) -1)] = 0;			// Removes trailing newline char

		inputDict = copyUniLet (str);								// Finds all the unique chars in the input
		encrpytDict = createEncrypt (inputDict);					// Mixes up the chars to create a key
		encryptStr = encryptInput (str, inputDict, encrpytDict);	// Encrypts the input using the key
		len1 = strlen (encryptStr)+1;
		len2 = strlen (inputDict) + 1;

		printf ("Input Dictionary: %s\n", inputDict);
		printf ("Encryption Dictionary: %s\n", encrpytDict);
		printf ("Encrypted Input: %s\n", encryptStr);

		// Divides the work up amongst the processes
		for (i = 1; i < commSize; i++)
		{
			MPI_Send (&len1, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send (&len2, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send (encryptStr, len1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
			MPI_Send (inputDict, len2, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}

		// Decrypts the encrypted input by finding the key using brute force
		findKey (inputDict, encryptStr, myRank);
	}
	else
	{
		// Receives the length of the string to be received later
		MPI_Recv (&len1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv (&len2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		encryptStr = malloc (sizeof (char) * len1);
		inputDict = malloc (sizeof (char) * len2);

		// Receives and copies the string from process 0
		MPI_Recv (encryptStr, len1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv (inputDict, len2, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// Decrypts the encrypted input by finding the key using brute force
		findKey (inputDict, encryptStr, myRank);
	}

	if (myRank == 0)
	{
		free (inputDict);
		free (encrpytDict);
		free (encryptStr);
	}
	else
	{
		free (inputDict);
		free (encryptStr);
	}

	MPI_Finalize();
	
	return 0;
}