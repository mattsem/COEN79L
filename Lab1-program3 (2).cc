//program3

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(){
	string line;
	ifstream file("text.txt");
	if(file.is_open()){
		while(file.get() != EOF){
			file >> line;
			int i=0;
			while(i < line.length()){
				if(isalpha(line[i]))
					i++;
				else
					line.erase(i,1);
				
			}
		
			if(line.length() >= 10){
				for(int j=0;j<line.length();j++){
					cout << (char) toupper(line[j]);
				}	
			cout << "\n";
			
			}	
		}
		file.close();

	}
	else cout << "can't open \n";

}
