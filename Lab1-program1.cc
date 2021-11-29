
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
	cout << "Please enter some text \n";
	string input;
	int countAlpha =0;
	int notAlpha =0;
	
	getline(cin,input);

	int i=0;
	
	while(input[i]){	
		if(isalpha(input[i]))
			countAlpha++;

		else if(input[i] != ' ')
			notAlpha++;
		i++;
	}
	
	cout << input << " has " << countAlpha << " alphanumeric chars and " << notAlpha << " non-alphanumeric chars \n";
	
return 0;
}
