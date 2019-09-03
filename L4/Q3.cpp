#include<iostream>
#include<iterator>
#include<map>
using namespace std;

map<int, int> hashMap;
int sum = 0;
int length = 0;
int* arr;
int N;
int n;
int startIndex = -1;
int endIndex = -1;

/*!
This function adds the values to the map and sets the values of 
starting index, ending index and the length of longest subarray
@return ---
*/
void setValues() {  
    for (int i = 0; i < N; i++) {  
        sum += arr[i];  
        if (sum == n){
			length = i + 1;
			startIndex = 0;
			endIndex = i;
		}
        if (hashMap.find(sum) == hashMap.end()){
			hashMap[sum] = i;
		}  
        if (hashMap.find(sum - n) != hashMap.end()){  
            if (length < (i - hashMap[sum - n])){ 
                length = i - hashMap[sum - n];
				startIndex = hashMap[sum -n] + 1;
				endIndex = i;
			}
        } 
    } 
} 
  
int main(){ 
    
	cin >> N;
	arr = new int[N];
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	cin >> n;

	setValues();

	cout << "Length of longest subarrray is " << length << "\n";
	cout << "Index from " << startIndex << " to " << endIndex << "\n";
    
	return 0; 
} 
