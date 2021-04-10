#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 
using namespace std;

void add(int** a,int** b,int** c,int sa,int sb){
	for(int i=0;i<sa;i++){
		for(int j =0 ;j<sb;j++){
			c[i][j] = a[i][j] + b[i][j];
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
}
// int** baseStrassen(int (*a)[2],int (*b)[2],bool Isprint = false){
// 	int Mnum[7];
// 	int **ANS = new int*[2];
// 	ANS[0] = new int[2];
// 	ANS[1] = new int[2];
// 	Mnum[0] = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
// 	Mnum[1] = (a[0][1] + a[1][1]) * b[1][1];
// 	Mnum[2] = a[0][0] * (b[0][1] - b[1][1]);
// 	Mnum[3] = a[1][1] * (b[1][0] - b[0][0]);
// 	Mnum[4] = (a[0][0] + a[0][1]) * b[1][1];
// 	Mnum[5] = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
// 	Mnum[6] = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

// 	ANS[0][0] = Mnum[0] + Mnum[2];
// 	ANS[1][1] = ANS[0][0];

// 	ANS[0][0] +=  Mnum[4] + Mnum[6];
// 	ANS[0][1] =  Mnum[2] + Mnum[4];
// 	ANS[1][0] =  Mnum[1] + Mnum[3];
// 	ANS[1][1] += - Mnum[1] + Mnum[5];

// 	if(Isprint){
// 		cout<<ANS[0][0]<<" "<<ANS[0][1]<<endl;
// 		cout<<ANS[1][0]<<" "<<ANS[1][1]<<endl;
	
// 	}
// 	return ANS;
// }

void Show(int** array,int size){	
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<array[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
int main(void){
	int qq[5][5] = {
		{1,2,3,4,5},
		{1,211,3,4,5},
		{121,1232,112,112,11},
		{1,1,1,1,1},
		{1,1,1,1,1}
	};
	int gg[5][5] = {
		{1,2,3,4,5},
		{1,3,1,1,1},
		{1,1,4,1,1},
		{1,1,1,7,1},
		{1,1,2,1,1}
	};
	int c[5][5];
	add((int**)qq,(int**)gg,(int**)c,5,5);
	Show((int**)c,5);
	// int arg[4];
	// scanf("%d %d %d %d\n",&arg[0],&arg[1],&arg[2],&arg[3]);
	// int large=0;
	// for(int i =0;i<4;i++){
	// 	if(arg[i] > large) large = arg[i];
	// }
	// if(large == 0) return 0;
	// if((large &1) == 1){
	// 	large++;
	// }
	// int arr1[arg[0]][arg[1]],arr2[arg[2]][arg[3]];
	// for(int i =0;i<arg[0];i++){
	// 	for(int j=0;j<arg[1];j++){
	// 		cin>>arr1[i][j];
	// 	}
	// }
	// for(int i =0;i<arg[2];i++){
	// 	for(int j=0;j<arg[3];j++){
	// 		cin>>arr2[i][j];
	// 	}
	// }
}	