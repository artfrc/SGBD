#include <iostream>
#include <fstream>

using namespace std;

int main (){

	fstream pFile;
	pFile.open("example.txt" , ios::out|ios::in);
	pFile << "This is an apple." << endl;

	pFile.seekg(6, ios::beg);

	char a[10];
	pFile.read(a, 10);

	a[10] = 0;

	cout << a << endl;

	pFile.close();

}