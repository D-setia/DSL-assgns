#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE* original = fopen("Sample_testcase_1.txt", "r");
	FILE* decrypted = fopen("decryptedOutputfile.txt", "r");

	char* inputData = (char*) calloc(1000, sizeof(char)); //! The input data in the form of string
	char* decryptedData = (char*) calloc(1000, sizeof(char));//! The decrypted data in the form of string

	fgets(inputData, 1000, original);
	fgets(decryptedData, 1000, decrypted);

	//! Remove the default carriage return at the end of the files
	strtok(inputData, "\n\n");
	strtok(decryptedData, "\n\n");

	printf("Input: %s\n", inputData);
	printf("Output: %s\n", decryptedData);

	//! Checking if the input and decrypted data are same
	if(strcmp(inputData, decryptedData) == 0){
		printf("The strings are the same!");
	}else{
		printf("The strings are NOT SAME!");
	}
	return 0;
}
