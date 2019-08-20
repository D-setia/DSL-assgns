#include <stdio.h>
#include <stdlib.h>

int length = 1;
int left = -1;
int right = 1;
int rightOffset = 0;//! length - right
int* deque; //!double ended queue with int as data
int* temp = 0;

/*!
This function adds a new value to the left end of the deque
@param data 	the int value to be inserted
@return ---
 */
void insertLeft(int data){
	if(right-left == 1){
		
		temp = (int*) calloc(length, sizeof(int));
		for(int i = 0; i < length; i++){
			*(temp + i) = *(deque + i);
		}
		free(deque);

		rightOffset = length - right;
		length *= 2;
		right = length - rightOffset;
		deque = (int*) calloc(length, sizeof(int));

		for(int i = 0; i <= left; i++){
			*(deque + i) = *(temp + i);
		}
		for(int i = 0; i < rightOffset; i++){
			*(deque + length -1 -i) = *(temp + length/2 -1 -i);
		}
			
		left += 1;
		*(deque + left) = data;

		free(temp);

	}else{
		left += 1;
		*(deque + left) = data;
	}
	
}

/*!
This function adds a new value to the right end of the deque
@param data 	the int value to be inserted
@return ---
 */
void insertRight(int data){
	if(right-left == 1){
			 
		temp = (int*) calloc(length, sizeof(int));
		for(int i = 0; i < length; i++){
			*(temp + i) = *(deque + i);
		}
		free(deque);
			
		rightOffset = length - right;
		length *= 2;
		right = length - rightOffset;
		deque = (int*) calloc(length, sizeof(int));
			
		for(int i = 0; i <= left; i++){
			*(deque + i) = * (temp + i);
		}
		for(int i = 0; i < rightOffset; i++){
			*(deque + length -1 -i) = *(temp + length/2 -1 -i);
		}
			
		right -= 1;
		rightOffset = length - right;

		*(deque + right) = data;
		free(temp);
	}else{
		right -= 1;
		*(deque + right) = data;
	}
}

/*!
This function deletes a value from the left end of the deque
@return ---
 */
void deleteLeft(){
	if(left == -1){
		printf("ERROR: Operation can't be performed");
	}else if((left + rightOffset == length/2)&&(length != 1)){
		
		temp = (int*) calloc(length, sizeof(int));
		for(int i = 0; i < length; i++){
			*(temp + i) = *(deque + i);
		}
			
		left -=1;
		length /= 2;
		right = length - rightOffset;

		free(deque);

		deque = (int*) calloc(length, sizeof(int));
		for(int i = 0; i <= left; i++){
			*(deque + i) = *(temp + i);
		}
		for(int i = 0; i < rightOffset; i++){
			*(deque + length -1 -i) = *(temp + 2*length -1 -i);
		}

		free(temp);
	}else{
		*(deque + left) = 0;
		left -= 1;
	}
}

/*!
This function deletes a value from the right end of the deque
@return ---
 */
void deleteRight(){
	if(right == length){
		printf("ERROR: Operation can't be performed");
	}else if((left + rightOffset == length/2)&&(length != 1)){
		
		temp = (int*) calloc(length, sizeof(int));
		for(int i = 0; i < length; i++){
			*(temp + i) = *(deque + i);
		}

		right += 1;
		rightOffset = length - right;
		length /= 2;
		right = length - rightOffset;

		free(deque);

		deque = (int*) calloc(length, sizeof(int));
		for(int i = 0; i <= left; i++){
			*(deque + i) = *(temp + i); 
		}
		for(int i = 0; i < rightOffset; i++){
			*(deque + length -1 -i) = *(temp + 2*length -1 -i);
		}

		free(temp);
	}else{
		*(deque + right) = 0;
		right += 1;
		rightOffset = length -right;
	}	
}

/*!
This method prints the contents of the dequeue and its size in bytes
@return ---
 */
void print(){
//	for(int i = 0; i <= left; i++){
//		printf("%d\n", deque[i]);
//	}
//	for(int i = left+1; i < right; i++){
//		printf("%d\n", 0);
//	}
//	for(int i = right; i < length; i++){
///		printf("%d\n", deque[i]);
//	}
	printf("Size is: %ld\n", length*sizeof(int));
}

int main(){
	deque = (int*) calloc(length, sizeof(int));
	insertLeft(1);
	print();
	insertLeft(2);
	print();
	insertRight(3);
	print();
	insertLeft(4);
	print();
	insertRight(5);
	print();
	deleteRight();
	print();
	deleteLeft();
	print();
	deleteLeft();
	print();
	deleteLeft();
deleteLeft();
	print();
	return 0;
}
