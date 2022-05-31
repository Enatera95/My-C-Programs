/*
	This program writes the English alphabet to an array, prints the array, then
	converts the array to lowercase characters and then prints it again.
	
	Every step of the process is documented with the use of comments except for obvious ones.
*/

#include<stdio.h>

void main()
{
	
	//Reserving space for char array of 26 bytes
	char a[26];
	
	//Initializing ap with the address of a[0]	
	char * ap = &a[0];
	
	//Initializing ap2 with the contents of ap which is the address of a[0]
	char * ap2 = ap;
	
	//Writing the 65 to the location of the address held by ap
	//65 is the decimal ASCII code for "A".
	*ap = 65;
	
	//Declaring the iterator varible, i
	int i;
	
	//Proceeding to write B, C, D,..., Z to the array.
	//The for loop starts at i = 1, to avoid overwriting the contents of a[0]
	for(i = 1; i < 26; i++)
	{
		//Moving the pointer to the next byte
		ap++;
		//Initializing the ap with the contents of address located in ap2 + 0, 1, 2,...,26
		*ap = *ap2 + i;
	}
	
	//Printing individual subscript variables of char array, a.
	for(i = 0; i < 26; i++)
	{
		printf("%c  ", a[i]);	
	}
	
	//Printing 2 new lines for the sake of readability.
	printf("\n");
	printf("\n");
	
	//We aim to convert the array of Uppercase characters in a to lowercase.
	
	//Initializing the p1 with the address of a[0]
	char * p1 = &a[0];
	
	
	//Adding 32 to all the locations of a
	for(i = 0; i < 26; i++)
	{
		*p1 = *p1 + 32;
		p1++;
	}
	//Writing contents of all locations of a to stdout for the vdu to read and display.
	for(i = 0; i < 26; i++)
	{
		printf("%c  ", a[i]);	
	}
	
	//Printing one more new line for the sake of readability.
	printf("\n");
}

