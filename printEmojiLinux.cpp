#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

int main(){

	string empty = "0    ";
	string obstacle = "\U000026F0";
	string path = "\U0001F3C3"; 
	string start = "\U0001F3E0";
	string end = "\U0001F3F3";
	
	cout << "A runner " + empty +"\n";
	cout << "A runner " + obstacle +"\n";
	cout << "A runner " + path +"\n";
	cout << "A runner " + start +"\n";
	cout << "A runner " + end +"\n";


return 0;
}
