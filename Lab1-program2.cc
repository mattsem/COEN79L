#include <iostream>
#include <stdio.h>
#include <string>

using namespace std; 


int main(){
	cout << "enter 10 digits with no spaces \n";
    string nums;
	cin >> nums;
    if(nums.length()<10){
        cout << "please enter 10 digits";
    }
	for(int i=0; i<6;i++){
		for(int j=0;j<i+1;j++){
			cout << " ";
		}
		for(int k=0;k<10;k++){
			cout << nums[k];
		}
		for(int j=0;j<i+1;j++){
			cout << "  ";
		}
		for(int k=9;k>=0;k--){
			cout << nums[k];
		}
		cout << "\n";
	}


}
