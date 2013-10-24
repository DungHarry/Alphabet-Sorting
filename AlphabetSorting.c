/*
	Author: Dung Harry
	Date created: 24th, October 2013
	Operating System: Ubuntu 13.04 Desktop x86_64
	Compiler: GNU compiler 4.7.3

	Description: this is the program about sorting an char* array in alphabet order in C programming language
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void vEnterNames(char*** lppNames, int numNames);
void vSwapNames(char** lppNames, int iFirstIndex, int iSecondIndex);
int iCharAt(char** lppNames, int numNames, int iNameIndex, int iCharIndex);
void vSortRange(char** lppNames, int numNames, int iIndex, int iHead, int iTail);
int iMaxLength(char** lppNames, int numNames);
void vSortAlphabet(char** lppNames, int numNames);
void vPrint(char** lppNames, int numNames);

void main(int argc, char* argv[]) {
	char **lppNames;
	int iNumNames;

	printf("Author: Dung Harry. Date created: 24th, October 2013\n\n");

	printf("Enter number of names you wanted to sort: ");
	scanf("%d", &iNumNames);

	vEnterNames(&lppNames, iNumNames);

	printf("The list of names you entered is: \n\n");
	vPrint(lppNames, iNumNames);

	printf("\nSorting follows alphabet order...\n");

	vSortAlphabet(lppNames, iNumNames);

	printf("The list of names after sorted is: \n");
	vPrint(lppNames, iNumNames);
}

void vEnterNames(char*** lppNames, int numNames) {
	int i, j;

	*lppNames = (char **) malloc(numNames * sizeof(char *));

	printf("Entering name part...\n\n");

	for(i = 0; i < numNames; i ++) {
		*(*lppNames + i) = (char *) malloc(MAX_LENGTH * sizeof(char));

		printf("Enter name %d: ", i + 1);
		scanf("%s", *(*lppNames + i));

		for(j = 0; (j < MAX_LENGTH - 1) && (*(*(*lppNames + i) + j) != '\0'); j ++);

		if(j == MAX_LENGTH - 2) {
			printf("Your name is too long. The maximum length of name is just 100\n");
		} else {
			for(; ((*(*(*lppNames + i) + j) = getc(stdin)) != '\n') && (j < MAX_LENGTH - 2); j ++);

			if(j == MAX_LENGTH - 2) {
				printf("Your name is too long. The maximum length of name is just 100\n");
			}
		}

		*(*(*lppNames + i) + j) = '\0';
	}

	printf("Finish entering names...\n\n");
}

void vSwapNames(char** lppNames, int iFirstIndex, int iSecondIndex) {
	char* temp = (char *) malloc(MAX_LENGTH * sizeof(char));

	strcpy(temp, *(lppNames + iFirstIndex));
	strcpy(*(lppNames + iFirstIndex), *(lppNames + iSecondIndex));
	strcpy(*(lppNames + iSecondIndex), temp);

	free(temp);
}

int iCharAt(char** lppNames, int numNames, int iNameIndex, int iCharIndex) {
	int iLength;
	int iResult;

	if(iNameIndex < numNames) { 
		iLength = strlen(*(lppNames + iNameIndex));

		if(iCharIndex < iLength) {
			iResult = (int) *(*(lppNames + iNameIndex) + iCharIndex);
		} else {
			iResult = 1;
		}
	} else {
		iResult = 1;
	}

	return iResult;
}

void vSortRange(char** lppNames, int numNames, int iIndex, int iHead, int iTail) {
	int i, j, k, iFirstSum, iSecondSum;

	for(i = iHead; i <= iTail; i ++) {
		for(j = i; j <= iTail; j ++) {
			if(iCharAt(lppNames, numNames, i, iIndex) > iCharAt(lppNames, numNames, j, iIndex)) {
				iFirstSum = iSecondSum = 0;

				for(k = 0; k < iIndex; k ++) {
					iFirstSum += iCharAt(lppNames, numNames, i, k);
					iSecondSum += iCharAt(lppNames, numNames, j, k);
				}

				if(iFirstSum == iSecondSum) {
					vSwapNames(lppNames, i, j);
				}
			}
		}
	}
}

int iMaxLength(char** lppNames, int numNames) {
	int i, iResult = 0;

	for(i = 0; i < numNames; i ++) {
		if(strlen(*(lppNames + i)) > iResult) {
			iResult = strlen(*(lppNames + i));
		}
	}

	return iResult;
}

void vSortAlphabet(char** lppNames, int numNames) {
	int iMax = iMaxLength(lppNames, numNames);
	int iHead, iTail, iTemp, i, j;

	vSortRange(lppNames, numNames, 0, 0, numNames - 1);

	for(j = 1; j <= iMax; j ++) {
		i = 0;
	
		while(i < numNames) {
			iHead = i;
		
			iTemp = iCharAt(lppNames, numNames, i, j - 1);
		
			while(iCharAt(lppNames, numNames, ++ i, j - 1) == iTemp) {
				if(i >= numNames - 1) {
					i ++;
			
					break;
				}
			}
		
			iTail = i - 1;

			vSortRange(lppNames, numNames, j, iHead, iTail);
		}
	}
}

void vPrint(char** lppNames, int numNames) {
	int i;

	for(i = 0; i < numNames; i ++) {
		printf("%d. %s\n", i + 1, *(lppNames + i));
	}
}
