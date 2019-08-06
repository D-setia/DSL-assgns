#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*!
This function takes in two positive numbers and give their GCD
@param smaller	The smaller of the two numbers
@param greater	The greater of the two numbers
@return int 	The GCD of the two numbers
 */
int gcd(int smaller, int greater){
	
	if(greater%smaller != 0) return gcd(greater%smaller, smaller);
	
	else return smaller;
}

/*!
This functin converts a valid string to int
@param string	A string with numbers for each char
@return int 	The int form of the string
 */
int charToInt(char* string){
	int n = 0;
	
	for(int i = 0; i < strlen(string); i++){
		n = n*10 + string[i] - '0';
	}

	return n;
}

/*!
This function takes in the data of the input file as a string
and encrypts it according to the values of n, a and b given by the user
@param n	Value of n used for encryption
@param a	Value of a used for encryption
@param b	Value of b used for encryption
@param input	The input string
@return char* 	The encrypted string
 */
char* encrypt(int n, int a, int b, char* input){
	char* sp = "_";
	int j = 0;
	char* encrypted = (char*) calloc(1000, sizeof(char));

	while(strlen(input)%n != 0){
		strcat(input, sp);
	}
	
	for(int l = 0; l < strlen(input)/n; l++){
		for(int i = 0; i < n; i++){
			j = (i*a + b)%n;
			if(j < 0) j += n;
			encrypted[l*n+i] = input[l*n+j];
		}
	}

	return encrypted;	
}

/*!
The file reading and writing takes place in the main function
 */
int main(){
	int n;
	char* n_string;
	int a;
	char* a_string;
	int b;
	char* b_string;

	FILE* opFile = fopen("outputfile.txt", "w");
	char* opData = (char*) calloc(1000, sizeof(char));

	char* fileData = (char*) calloc(1000, sizeof(char));
	
	printf("Give the values of n, a and b in the format:\nn a b\n");

	char* inputs = (char*) calloc(200, sizeof(char));
	fgets(inputs, 200, stdin);

	char* args;
	args = strtok(inputs, " ");
	
	if(args){
		n_string = args;
		n = charToInt(n_string);
		args = strtok(NULL, " ");
	}else{
		printf("\nPlease enter the arguments correctly\n");
		return 0;
	}

	if(args){
		a_string = args;
		a = charToInt(a_string);
		args = strtok(NULL, " ");
	}else{
		printf("\nPlease enter the arguments correctly\n");
		return 0;
	}

	if(args){
		b_string = args;
		b = charToInt(b_string);
		args = strtok(NULL, " ");
	}else{
		printf("\nPlease enter the arguments correctly\n");	
		return 0;
	}
	
	if(args){
		printf("Error: more than 3 arguments found");	
		return 0;
	}

	FILE* inputFile = fopen("inputfile.txt", "r");
	fgets(fileData, 1000, inputFile);
	strtok(fileData, "\n\n");

	if((a == 0)||(gcd(abs(a),n) != 1)){
		printf("ERROR: Encryption is not possible.\nChoose appropriate a and b\n");
		return 0;
	}
	
	opData = encrypt(n, a, b, fileData);

	printf("%s\n", fileData);
	printf("%s\n", opData);

	fprintf(opFile,"%s",opData);


	return 0;
}
