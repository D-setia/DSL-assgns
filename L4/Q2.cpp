#include<iostream>
using namespace std;

class Queen{
public:
	int x = -1;
	int y = -1;

	Queen(int yCoor){
		x = 0;
		y = yCoor;
	}
};

Queen** queenArr;
int n;
bool isPossible = true;

void initQueens(int n){
	queenArr = new Queen*[n];
	for(int i = 0; i < n; i++){
		queenArr[i] = new Queen(i);
	}
}

bool canAttack(Queen* queenI, Queen* queenJ){
	if(queenI->x == queenJ->x){
		return true;
	}else if(abs(queenI->y - queenJ->y) == abs(queenI->x - queenJ->x)){
		return true;	
	}else{
		return false;
	}
}

void setQueen(Queen* queenI){
	int flag1 = 0;
	int flag2 = 0;
	int i = queenI->y;
	cout << i << "\n";
	for(int j = 0; j < i; j++){
		if(canAttack(queenI, queenArr[j])){
			if(queenI->x == n-1){
				if(i == 0){
					isPossible = false;
				}else{
					setQueen(queenArr[i-1]);
					flag2 = 1;
				//	flag1 = 1;
				}
			}else{ 
				queenI->x += 1;
				cout << queenI->x << "\n";
			}
			flag1 = 1;	
		}
	}
	if(flag2 == 1) queenI->x = 0;
	if(flag1 == 1) setQueen(queenI);
}

bool setQueens(){
	for(int i = 0; i < n; i++){
		setQueen(queenArr[i]);
	}	
}

void print(){
	for(int i = 0; i < n; i++){
		printf("Queen No. %d, x = %d, y = %d \n", i, queenArr[i]->x, queenArr[i]->y);
	}
}

int main(){	
//	cout << "Enter the value of n\n";
//	cin >> n;
//	initQueens(n);
	//setQueens();
	Queen* queen1 = new Queen(0);
	Queen* queen2 = new Queen(2);
	queen2->x = 1;
	cout << canAttack(queen1, queen2) << "\n";
	cout << "\n";
//	if(isPossible){
//		print();
//	}else{
//		printf("It is not possible to set up the board");
//	}
	return 0;
}
