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
This function takes in the data of the encrypted file as a string
and decrypts it according to the values of n, a and b given by the user
@param n	Value of n used for encryption
@param a	Value of a used for encryption
@param b	Value of b used for encryption
@param input	The input string
@return char* 	The decrypted string
 */
char* decrypt(int n, int a, int b, char* encrypted){
	char* add = " ";
	int j = 0;
	int a1 = 0;
	int b1 = 0;
	int k = 0;
	char* decrypted = (char*) calloc(1000, sizeof(char));

	while(strlen(encrypted)%n != 0){
		strcat(encrypted, add);
	}

	if(a>0){
		for(int i = 1; i < n; i++){
			if((i*a)%n == 1){
				a1 = i;
				break;
			}
		}
	}else{
		for(int i = -1; i > -n; i--){
			if((i*a)%n == 1){
				a1 = i;
				break;
			}
		}
	}

	for(int i = 1; i < n; i++){
		if((a1*b + i)%n == 0){
			b1 = i;
			break;
		}
	}

	for(int l = 0; l < strlen(encrypted)/n; l++){
		for(int i = 0; i < n; i++){
			j = (i*a + b)%n;
			if(j < 0) j += n;
			k = (j*a1 + b1)%n;
			if(k < 0) k += n;
			decrypted[l*n+j] = encrypted[l*n+k];
		}
	}

	return decrypted;	
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

	FILE* inputFile = fopen("outputfile.txt", "r");
	FILE* inputFile2 = fopen("outputfile.txt", "r");
	
	char* fileData = (char*) calloc(1000, sizeof(char));
	char* fileData2 = (char*) calloc(1000, sizeof(char));
	char* fileData3 = (char*) calloc(1000, sizeof(char));
	// fgets(fileData, 1000, inputFile);
	while(fgets(fileData, 1000, inputFile)){
		fileData2 = strcat(fileData2, fileData);

	} 
	
	// for(int i = 0; i < strlen(fileData2) - 1; i++){
	// 	fileData3[i] =  fileData2[i];
	// }

	FILE* opFile = fopen("decryptedOutputfile.txt", "w");
	char* opData;
	
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

	if((a == 0)||(gcd(abs(a),n) != 1)){
		printf("ERROR: Encryption is not possible.\nChoose appropriate a and b\n");
		return 0;
	}

	opData = decrypt(n, a, b, fileData2);

	printf("%s\n", fileData2);
	printf("%s\n", opData);
	
	strtok(opData, "_");
	// opData = strcat(opData, "\n");

	fprintf(opFile,"%s",opData);

	return 0;
}
