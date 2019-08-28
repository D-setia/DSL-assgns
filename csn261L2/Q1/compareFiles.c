#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE* original = fopen("tc1.txt", "r");
	FILE* decrypted = fopen("decryptedOutputfile.txt", "r");

	char* inputData = (char*) calloc(1000, sizeof(char)); //! The input data in the form of string
	char* inputData2 = (char*) calloc(1000, sizeof(char));
	char* inputData3 = (char*) calloc(1000, sizeof(char));
	// fgets(inputData, 1000, inputFile);
	while(fgets(inputData, 1000, original)){
		inputData2 = strcat(inputData2, inputData);

	} 
	
	for(int i = 0; i < strlen(inputData2) - 1; i++){
		inputData3[i] =  inputData2[i];
	}
	char* decryptedData = (char*) calloc(1000, sizeof(char));//! The decrypted data in the form of string
	char* decryptedData2 = (char*) calloc(1000, sizeof(char));
	char* decryptedData3 = (char*) calloc(1000, sizeof(char));
	// fgets(decryptedData, 1000, inputFile);
	while(fgets(decryptedData, 1000, decrypted)){
		decryptedData2 = strcat(decryptedData2, decryptedData);

	} 
	
	// for(int i = 0; i < strlen(decryptedData2) - 1; i++){
	// 	decryptedData3[i] =  decryptedData2[i];
	// }

	// fgets(inputData, 1000, original);
	// fgets(decryptedData, 1000, decrypted);

	//! Remove the default carriage return at the end of the files
	// strtok(inputData, "\n\n");
	// strtok(decryptedData, "\n\n");

	printf("Input: %s\n", inputData3);
	printf("Output: %s\n", decryptedData2);

	//! Checking if the input and decrypted data are same
	if(strcmp(inputData3, decryptedData2) == 0){
		printf("The strings are the same!");
	}else{
		printf("The strings are NOT SAME!");
	}
	return 0;
}
