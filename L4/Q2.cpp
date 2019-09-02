#include<iostream>
using namespace std;

int noOfWays = 0;
int** chessBoard;
int n; 
  
bool isSafe(int row, int col) {
  
    for (int i = 0; i < col; i++){ 
        if (chessBoard[row][i]){
			return false;
		}  
	}

    for (int i=row, j=col; i>=0 && j>=0; i--, j--){ 
        if (chessBoard[i][j]){
            return false;
		}
	}

    for (int i=row, j=col; j>=0 && i<n; i++, j--){
        if (chessBoard[i][j]){
            return false; 
		}
	}

    return true; 
}

void print() 
{ 
    noOfWays++; 
    for (int i = 0; i < n; i++) 
    { 
        for (int j = 0; j < n; j++) 
            printf("%d ", chessBoard[i][j]); 
        printf("\n"); 
    } 
    printf("\n"); 
}
  
/* A recursive utility function to solve N 
Queen problem */
bool setQueens(int col){ 
    if (col == n) 
    { 
        print(); 
        return true; 
    } 
	
    bool isPossible = false;
	
    for (int i = 0; i < n; i++){ 
        if ( isSafe(i, col) ) { 
            chessBoard[i][col] = 1; 
            isPossible = setQueens(col + 1) || isPossible; 
            chessBoard[i][col] = 0;
        } 
    } 

    return isPossible; 
} 
   
  
int main(){
	cout << "Enter the value of n\n";
	cin >> n;
	chessBoard = new int*[n];
	
	for(int i = 0; i < n; ++i) {
    chessBoard[i] = new int[n];
	}

	cout << "\n";
  
  	setQueens(0); 

	cout << "There are " << noOfWays << " ways to set the board\n";
    return 0; 
} 
