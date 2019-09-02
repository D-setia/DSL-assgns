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
int ans = 0;

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
	int i = queenI->y;
	if(isPossible){
		if(queenI->x > (n-1)){
					if(i == 0){
						isPossible = false;
					}else{
						queenI->x = 0;
						queenArr[i-1]->x += 1;
						setQueen(queenArr[i-1]);
						flag1 = 1;
					}
				}
	for(int j = 0; j < i; j++){
		if(canAttack(queenI, queenArr[j])){
				if(queenI->x >= (n-1)){
					if(i == 0){
						isPossible = false;
					}else{
						queenI->x = 0;
						queenArr[i-1]->x += 1;
						setQueen(queenArr[i-1]);
						flag1 = 1;
					}
				}else{ 
					queenI->x += 1;
					flag1 = 1;
				}				
		}
		
	}
	}

	if(isPossible && (flag1 == 1)) setQueen(queenI);
}

bool setQueens(){
	for(int i = 0; i < n; i++){
		if(i != 0) queenArr[i]->x = 0;
		setQueen(queenArr[i]);
	}	
}

void print(){
	for(int i = n-1; i >= 0; i--){
		for(int j = 0; j < queenArr[i]->x; j++){
			printf("0 ");
		}
		printf("1 ");
		for(int j = queenArr[i]->x +1; j < n; j++){
			printf("0 ");
		}
		printf("\n");
	}
}

int main(){	
	cout << "Enter the value of n\n";
	cin >> n;
	initQueens(n);
	printf("\n");
	
	while(isPossible && (queenArr[0]->x < n)){
	setQueens();
	if(isPossible){
		print();
		printf("\n");
		ans++;
	}

	queenArr[0]->x += 1;
	}


	printf("There are %d such ways to set up the board\n", ans);
	return 0;
}
