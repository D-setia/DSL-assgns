#include<iostream>
#include<iterator>
#include<map>
using namespace std;

// int noOfElements;
// int sum;
// int* preSumArray;
// map<int, int> hashMap;
// int indexStart = -1;
// int indexEnd = -1;
// int length = 0;

// void getValues(int i){
// 	for(int j = 0; j < i; j++){
// 		if(preSumArray[j] == (preSumArray[i]-sum)){
// 			hashMap.insert(pair<int, int>(i, j));
// 			if((i - j) > length){
// 				indexStart = j+1;
// 				indexEnd = i;
// 				length = i-j;
// 			}
// 			break;
// 		}
// 	}
// }

// void print(){
// 	if(length != 0){
// 		printf("Length of longest array is %d\n", length);
// 		printf("Index from %d to %d\n", indexStart, indexEnd);
// 	}else{
// 		printf("Not Found\n");
// 	}
// }

// int main(){
// 	cin >> noOfElements;
// 	preSumArray = new int[noOfElements];
	
// 	for(int i = 0; i < noOfElements; i++){
// 		if(i == 0){
// 			cin >> preSumArray[i];
// 		}else{
// 			cin >> preSumArray[i];
// 			preSumArray[i] += preSumArray[i-1];
// 		}
// 	}

// 	cin >> sum;
	
// 	for(int i = 0; i < noOfElements; i++){
// 		getValues(i);
// 	}
// 	print();

// 	return 0;
// }

int lenOfLongSubarr(int arr[],  int n, int k) { 
  
    unordered_map<int, int> um; 
    int sum = 0, maxLen = 0; 
   
    for (int i = 0; i < n; i++) {  
        sum += arr[i];  
        if (sum == k) 
            maxLen = i + 1;  
        if (um.find(sum) == um.end()) 
            um[sum] = i; 
  
        // check if 'sum-k' is present in 'um' 
        // or not 
        if (um.find(sum - k) != um.end()) { 
  
            // update maxLength 
            if (maxLen < (i - um[sum - k])) 
                maxLen = i - um[sum - k]; 
        } 
    } 
  
    // required maximum length 
    return maxLen; 
} 
  
// Driver Code 
int main() 
{ 
    int arr[] = {10, 5, 2, 7, 1, 9}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    int k = 15; 
    cout << "Length = "
         << lenOfLongSubarr(arr, n, k); 
    return 0; 
} 
