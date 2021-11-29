#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


int main(){
	int num,count=0;
	cout << "think of a number between 1 and 20. \n";
	cin >> num;
	srand(time(NULL));
	
	char response;
	while(true){
		count++;
		int guess = rand() %20 +1; 
		cout << "is the number  "  << guess <<"? \n";
		cin >> response;
		if(response == 'y')
			break;
		else if(response != 'n')
			cout << "please enter a valid input \n";

	}
	cout << "i found the answer in " << count << "guesses \n";

}
