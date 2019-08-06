#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*!
This is a struct of each node of the tree with
details about the data, level and leafNo of each node
 */
struct dataCell{
	int data;
	int level;
	int leafNo;
};

int leafNo = 1;
struct dataCell** dataArray;//!The array of data

/*!
This function counts the no of columns in the original array 
given in the input(also the number of rows as it is a nXn array)
@param input 	The input data array
@return int 	The number of coumns (size of original array)
 */
int countCols(FILE* input){
	int cols = 0;
	int* tempInt;
	char tempChar;

	do{
		fscanf(input, "%d%c", tempInt, &tempChar);
		cols++;
	}while(tempChar != '\n');

	return cols;
}

/*!
This function calculates the smallest power of 2 greater than 
the size of the original array which is the size of the final array
@param givenSize 	The size of the original array
@return int 	The size of the final array
 */
int calculateSize(int givenSize){
	int i = 1;
	while(i < givenSize) i *= 2;
	return i;
}

/*!
This function inserts the original array in the 
bottom left of the new array
@param input 	The input file
@param size 	The size of the final array
@param givenSize 	The size of the original array
@return ---
 */
void insertArray(FILE* input, int size, int givenSize){
	for(int i = 0; i < size - givenSize; i++){
		for(int j = 0; j < size; j++){
			dataArray[i][j].data = 0;
		}
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - givenSize; j++){
			dataArray[i][j].data = 0;
		}
	}
	
	int i = size - givenSize;
	int j = 0;
	int tempInt;
	while(fscanf(input, "%d ", &tempInt) != EOF){
		dataArray[i + j/givenSize][i + j%givenSize].data = tempInt;	
		j++;
	}
}

/*!
This function iterates through the array and makes a quadtree
@param rowStart 	The strarting row for iteration
@param rowEnd 		The ending row for iteration
@param colStart 	The strarting col for iteration
@param colEnd 		The ending col for iteration
@param rowStart 	The strarting row for iteration
@param level 		The current level of tree
@return ---
 */
void makeTree(int rowStart, int rowEnd, int colStart, int colEnd, int level){
	int noOnes = 0;
	int noZeroes = 0;
	
	for(int i = rowStart; i < rowEnd; i++){
		for(int j = colStart; j < colEnd; j++){
			if(dataArray[i][j].data == 1) noOnes++;
			else if(dataArray[i][j].data == 0) noZeroes++;
		}
	}

	if(noZeroes == 0){
		for(int i = rowStart; i < rowEnd; i++){
			for(int j = colStart; j < colEnd; j++){
				dataArray[i][j].leafNo = leafNo;
				dataArray[i][j].level = level;	
			}
		}
		leafNo++;
	}else if(noOnes == 0){
		for(int i = rowStart; i < rowEnd; i++){
			for(int j = colStart; j < colEnd; j++){
				dataArray[i][j].leafNo = leafNo;
				dataArray[i][j].level = level;
			}
		}
		leafNo++;
	}else{
		makeTree(rowStart, (rowStart + rowEnd)/2, colStart, (colStart + colEnd)/2, level+1);
		makeTree(rowStart, (rowStart + rowEnd)/2, (colStart + colEnd)/2, colEnd, level+1);
		makeTree((rowStart + rowEnd)/2, rowEnd, colStart, (colStart + colEnd)/2, level+1);
		makeTree((rowStart + rowEnd)/2, rowEnd, (colStart + colEnd)/2, colEnd, level+1);
	}
}

/*!
This function prints the leaf number, data stored and level in 
the quadtree of the element in the 2D array at the position (x,y)
@param x 	The x coordinate of the array
@param y 	The y coordinate of the array
@return ---
 */
void printDetails(int x, int y){
	printf("LeafNo: %d\n", dataArray[x][y].leafNo);
	printf("Data: %d\n", dataArray[x][y].data);
	printf("Level: %d\n", dataArray[x][y].level);
}

/*!
This function prints the details of the leaf node specified
@param leafNo 	The number of the leaf node
@param size 	The size of the array
@return ---
 */
void leafDetails(int leafNo, int size){
	int flag = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(dataArray[i][j].leafNo == leafNo){
				printf("LeafNo: %d\n", dataArray[i][j].leafNo);
				printf("Data: %d\n", dataArray[i][j].data);
				printf("Level: %d\n", dataArray[i][j].level);
				flag = 0;
				break;
			}
		}
		if(flag == 0) break;
	}
}

int main(){
	FILE* colsCount  = fopen("inputfile.txt", "r");
	FILE* output = fopen("outputfile.txt", "w");
	FILE* input  = fopen("inputfile.txt", "r");	
	int cols = countCols(colsCount);	
	printf("%d\n", cols);
	int size = calculateSize(cols);
	printf("%d\n", size);

	printf("\n");

	dataArray = (struct dataCell**) calloc(size, sizeof(struct dataCell*));
	for(int i = 0; i < size; i++){
		dataArray[i] = (struct dataCell*) calloc(size, sizeof(struct dataCell));
	}

	insertArray(input, size, cols);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <size; j++){
			printf("%d ", dataArray[i][j].data);
		}
		printf("\n");
	}
	
	printf("\n");

	makeTree(0, size, 0, size, 0);
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j <size; j++){
			printf("%d ", dataArray[i][j].leafNo);
		}
		printf("\n");
	}
	
	printf("\n");

	printDetails(3,4);
	
	printf("\n");

	leafDetails(3, size);
	return 0;
}
