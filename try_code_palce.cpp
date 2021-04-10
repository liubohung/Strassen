#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 
using namespace std;


int main(void){
	int **temp= new int*[1] ;
	temp[0] = new int[1];
	temp[0][0] = 1;
	cout<<temp[0][0] <<endl;
}	
