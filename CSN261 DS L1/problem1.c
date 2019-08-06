#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*!
This struct contains all the student details and pointer 
to the next and previous students in the linked list
 */
struct student{
		int rollNo;
		char name[25];
		char dob[20];
		char address[100];
		int phoneNo;
		struct student *next;
		struct student *prev;
	};
	
struct student *first = NULL;
int newRollNo = 100;

/*!
This struct contains the roll number deleted from the linked list and 
inserted in the deque along with pointer to next deleted roll number
 */
struct deletedRollNo{
	int rollNo;
	struct deletedRollNo *next;
};
struct deletedRollNo *deletedQueue = NULL;

/*!
This function adds the deleted roll number to a queue
@param rollNo  the roll number to be added
@return ---
 */
 void addToDeleted(int rollNo){
	struct deletedRollNo *ptr;
	ptr = deletedQueue;
	if(ptr != NULL){
		while(ptr->next != NULL){
			ptr = ptr->next;	
		}
		struct deletedRollNo* new = (struct deletedRollNo*) malloc(sizeof(struct deletedRollNo));
		new->rollNo = rollNo;
		new->next = NULL;
		ptr->next = new;
	}else{
		struct deletedRollNo* new = (struct deletedRollNo*) malloc(sizeof(struct deletedRollNo));
		new->rollNo = rollNo;
		new->next = NULL;
		deletedQueue = new;
	}
}

/*!
This function gives us the next roll number to
be added to the circular doubly linked list
@param insert 	bool to check if we are inserting a roll number
				or just require the next number for comparison
@return int		the roll number
 */
int getNextRollNo(bool insert){
	if(deletedQueue != NULL){
		int requiredRollNo = deletedQueue->rollNo;
		if(insert)deletedQueue = deletedQueue->next;
		return requiredRollNo;
	}else{
		if(insert){
			newRollNo++;
			return newRollNo;
		}else{
			return newRollNo + 1;
		}
	}
}

/*!
This function inserts a new student to
the circular doubly linked list
@param name		name of the student
@param dob		date of birth of student
@param address		address of the student
@param phoneNo		phone number of student
@return  ---
 */
void insert(char name[25], char dob[20], char address[100], int phoneNo){
	struct student *ptr;
	if(first == NULL){	
		struct student* newStudent = (struct student*) malloc(sizeof(struct student));
		newStudent->rollNo = getNextRollNo(true);	
		strcpy(newStudent->name, name);
		strcpy(newStudent->dob, dob);
		strcpy(newStudent->address, address);
		newStudent->phoneNo = phoneNo;
		newStudent->next = newStudent;
		newStudent->prev = newStudent;
		first = newStudent;
	}else{
		ptr = first;
		while((ptr->next != first)&&(getNextRollNo(false) > ptr->rollNo)){
			ptr = ptr->next;
		}
		if((getNextRollNo(false) < ptr->rollNo)){
			struct student* newStudent = (struct student*) malloc(sizeof(struct student));
			newStudent->rollNo = getNextRollNo(true);
			strcpy(newStudent->name, name);
			strcpy(newStudent->dob, dob);
			strcpy(newStudent->address, address);
			newStudent->phoneNo = phoneNo;
			newStudent->next = ptr;
			newStudent->prev = ptr->prev;
			ptr->prev->next = newStudent;
			ptr->prev = newStudent;
			if(ptr==first) first = newStudent;
		}else if((ptr->next == first)){
			struct student* newStudent = (struct student*) malloc(sizeof(struct student));
			newStudent->rollNo = getNextRollNo(true);
			strcpy(newStudent->name, name);
			strcpy(newStudent->dob, dob);
			strcpy(newStudent->address, address);
			newStudent->phoneNo = phoneNo;
			newStudent->next = first;
			newStudent->prev = ptr;
			ptr->next = newStudent;
			first->prev = newStudent;
		}
	}
}

/*
This function prints all the students in the linked list in order
@return ---
 */
void print(){
	struct student *ptr;
	ptr = first;
	if(first != NULL){
		while(ptr->next != first){
			printf("Roll No: %d\n", ptr->rollNo);
			printf("Name: %s\n", ptr->name);
			printf("Date of Birth: %s\n", ptr->dob);
				ptr = ptr->next;
		}
		printf("Roll No: %d\n", ptr->rollNo);
		printf("Name: %s\n", ptr->name);
		printf("Date of Birth: %s\n", ptr->dob);
	}else{
		printf("List is empty.\n");
	}
}

/*!
This function searches for a specified roll number
@param rollNo 	the roll number required
@return struct student* 	pointer to the required struct
 */
struct student* search(int rollNo){
	struct student *ptr = first;
	if(first != NULL){
		while((ptr->next != first)&&(ptr->rollNo != rollNo)){
			ptr = ptr->next;
		}
			if(ptr->rollNo != rollNo){
			ptr = NULL;
			printf("ERROR: Can't find the requested roll number\n");
		}
	}else{
		printf("List is empty\n");
	}
	return ptr;
}

/*!
This function modifes the data associated with a roll number
@param rollNo 	the roll number whose data has to be modfied
@param newData 	the new data to be associated with the roll number
@return ---
 */
void modify(int rollNo, struct student newData){
	struct student *ptr;
	ptr = search(rollNo);
	if(ptr != NULL){
		strcpy(ptr->name, newData.name);
		strcpy(ptr->dob, newData.dob);
		strcpy(ptr->address, newData.address);
		ptr->phoneNo = newData.phoneNo;
	}
}

/*!
This function deletes the data of the roll number specified
@param rollNo 	the roll number to be deleted
@return ---
 */
void delete(int rollNo){
	struct student *ptr;
	ptr = search(rollNo);

	if(ptr != NULL){
		if((ptr == first)&&(ptr->next == first)){
			addToDeleted(ptr->rollNo);
			first = NULL;
		}else{
			addToDeleted(ptr->rollNo);
			ptr->next->prev = ptr->prev;
			ptr->prev->next = ptr->next;
			if(ptr == first) first = ptr->next;
		}
	}
}

/*!
This function swaps two consecutive nodes in the linked list
@param a	pointer to first student
@param b	pointer to the next student
@return ---
 */
void swap(struct student* a, struct student* b){
	struct student* temp1 = a->prev;
	struct student* temp2 = b->next;
	temp1->next = b;
	b->prev = temp1;
	a->next = temp2;
	temp2->prev = a;
	b->next = a;
	a->prev = b;
}

/*!
This function sorts the linked list 
according to the names in alphabetical order
@return --- 
 */
void sort(){
	int count = 0;
	
	if(first == NULL){
		printf("List is empty.\n");
	}else{
		struct student* ptr;
		ptr = first;
		count++;
		while(ptr->next != first){
			ptr = ptr->next;
			count++;
		}
		int inserted = 1;
		ptr = first;
		for(int j = 0; j < count; j++){
			struct student* temp = first;
			for(int k =0; k < count -1-j; k++){
				if(strcmp(temp->name, temp->next->name)>0){
					if(first == temp){
						first = first->next;
					}
					swap(temp, temp->next);
				}else{
					temp = temp->next;
				}
			}
		}
	}
}

/*!
This function converts an appropriate string to int
@param string 	a valid string to be converted to int 
@return int		the required int value
 */
int toInt(char string[]){
	int n = 0;
	for(int j = 0; j < strlen(string); j++){
		n = n * 10 + string[j] - '0';	
	}

	return n;
}

int main(){
	
	FILE* studentDataStream = fopen("./StudentData.csv", "r");
	
	char studentDataAll[2048];
	fgets(studentDataAll, 2048, studentDataStream);
	
	char studentDataArray[50][5][100];	
	int i=0;
	char* token = strtok(studentDataAll, ";");
	while(token){
		int length = strlen(token);
		for(int j = 0; j < length - 2; ++j){
				studentDataArray[(int)i/5][i%5][j] = token[j+1];	
		}	
		token = strtok(NULL, ";");
		i++;
	}

	struct student Data[(i+1)/5];

	for(int j = 0; j < (i+1)/5; j++){
		strcpy(Data[j].name, studentDataArray[j][1]);
		strcpy(Data[j].dob, studentDataArray[j][2]);
		strcpy(Data[j].address, studentDataArray[j][3]);
		Data[j].phoneNo = toInt(studentDataArray[j][4]);
	}

	//Testing
	
	delete(108);
	printf("\n");
	insert(Data[0].name, Data[0].dob, Data[0].address, Data[0].phoneNo);
	insert(Data[1].name, Data[1].dob, Data[1].address, Data[1].phoneNo);
	insert(Data[2].name, Data[2].dob, Data[2].address, Data[2].phoneNo);
	insert(Data[3].name, Data[3].dob, Data[3].address, Data[3].phoneNo);
	delete(102);
	delete(101);
	insert(Data[4].name, Data[4].dob, Data[4].address, Data[4].phoneNo);
	insert(Data[5].name, Data[5].dob, Data[5].address, Data[5].phoneNo);
	insert(Data[6].name, Data[6].dob, Data[6].address, Data[6].phoneNo);
	print();
	printf("\n");
	sort();
	print();
	printf("\n");
	struct student* modify103 = (struct student*) malloc(sizeof(struct student));
	strcpy(modify103->name, "Taylor Swift");
	strcpy(modify103->dob, "12-Jan-45");
	strcpy(modify103->address, "Brooklyn 99");
	modify103->phoneNo = 1489302673;
	modify(103, *modify103);
	print();
	
	return 0;
}
