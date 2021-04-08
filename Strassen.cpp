#include<iostream>

using namespace std;

class SArray{
public:
	int **array;
private:
	int size;
	bool IsZero;
public:
	SArray(){
		this->IsZero = true ;
		this->array = NULL;
		this->size = 0;
	}
	SArray(int length):size(length){
		this->IsZero = length == 0 ? true:false ;
		this->array = new int*[length] ;
		for(int i =0;i<size;i++){
			this->array[i] = new int[length] ;
		}
	}
	SArray(int** arr,int length):size(length){
		this->IsZero = length == 0 ? true:false ;
		this->array = new int*[length] ;
		for(int i =0;i<length;i++){
			this->array[i] = new int[length] ;
		}
		for(int i = 0 ;i < length; i++){
			for(int j = 0;j < length;j++){
				this->array[i][j] = *(((int*)arr+(i*length+j)));
			}
		}
	}
	SArray(SArray a):size(a.getsize()){
		this->IsZero = length == 0 ? true:false ;
		this->array = new int*[length] ;
		for(int i =0;i<length;i++){
			this->array[i] = new int[length] ;
		}
		for(int i = 0 ;i < length; i++){
			for(int j = 0;j < length;j++){
				this->array[i][j] = *(((int*)arr+(i*length+j)));
			}
		}
	}
	~SArray(){
		for(int i =0;i<this->size;i++){
			delete this->array[i];
		}
		delete[] this->array ;
	}


	bool reset(int** arr,int size){
		//clear array
		if(this->array == NULL){
			for(int i =0;i<this->size;i++){
				delete this->array[i];
			}
			delete this->array;
		}
		
		// make new array
		this->array = new int*[size] ;
		this->size = size;
		for(int i =0;i < size;i++){
			this->array[i] = new int[size] ;
		}

		// init new array
		for(int i = 0 ;i < size; i++){
			for(int j = 0;j < size;j++){
				this->array[i][j] = *((int*)arr+(i*size+j));
			}
		}
	}

	void Show(void){
		for(int i=0;i<this->size;i++){
			for(int j=0;j<this->size;j++){
				cout<<this->array[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	int getsize(void){
		return this->size;
	}

	SArray getsub(int idx,int idy,int size){

		static int a = 0;
		cout<<a<<endl;a++;
		if((idx+size)*(idy+size) > (this->size * this->size)){
			return SArray(0);
		}else{
			int temparr[size][size];
			// cout<<"Idx: "<<idx<<" Idy"<<idy<<endl;
			for(int i = idx;i<(idx+size);i++){
				for(int j = idy;j<(idy+size);j++){
					temparr[i-idx][j-idy] = this->array[i][j];
					// cout<<temparr[i-idx][j-idy]<<" ";
				}
				// cout<<endl;
			}
			return SArray((int**)temparr,size);
		}
	}
	SArray& operator+=(SArray& a){ 
		if(a.getsize() == this->size){
			for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					this->array[i][j] += a.array[i][j];
				}
			}
		}
		return *this;
    }
    SArray& operator-=(SArray& a){ 
		if(a.getsize() == this->size){
			for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					this->array[i][j] -= a.array[i][j];
				}
			}
		}
		return *this;
    }
    SArray operator+(SArray a){
    	int array[a.getsize()][a.getsize()] ;
		if(a.getsize() == this->size){
			for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					array[i][j] = this->array[i][j] + a.array[i][j];
				}
			}
		}
		return SArray((int**)array,this->size);
    }
	SArray operator-(SArray a){
    	int array[a.getsize()][a.getsize()] ;
		if(a.getsize() == this->size){
			for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					array[i][j] = this->array[i][j] - a.array[i][j];
				}
			}
		}
		return SArray((int**)array,this->size);
    }
    SArray pMul(SArray a){ 
    	int ss = a.getsize();
    	int array[ss][ss];
    	if(this->array != NULL && ss == this->size){
    		for(int i = 0 ; i<size; i++){
				for(int j = 0 ;j<size;j++){
					int num=0;
					for(int k=0;k<size;k++){
						num += this->array[i][k] * a.array[k][j];
					}
					array[i][j] = num;
					// cout<<"i: "<<i<<" "<<"j: "<<j<<" "<< "ans: "<< temp.array[i][j]<<endl;
				}
			}
    	}
    	return SArray((int**)array,a.getsize());
    }
    SArray operator*(int num){ 
    	int array[this->getsize()][this->getsize()];
    	if(this->array != NULL){
    		for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					array[i][j] *= num;
				}
			}
    	}
    	return *this;
    }
    SArray Combine(SArray a[4]){ 
    	cout<<"Combine"<<endl;
    	cout<<"Size:"<<a[0].size * 2<<endl;
    	//set size
    	int original = a[0].size;
    	int newsize = original * 2;
    	int array[newsize][newsize];
    	/*
    	combine 
    		a0 a1
    		a2 a3
		*/
    	for(int i = 0 ;i < original ; i++){
    		for(int j = 0; j< original ; j++){
				array[i][j] = a[0].array[i][j];
    		}
    		for(int k = original; k < newsize ; k++){
    			array[i][k] = a[1].array[i][k-original];
    		}
    	}
    	for(int i = original; i < newsize ; i++){
    		for(int j = 0; j < original ; j++){
				array[i][j] = a[2].array[i-original][j];
    		}
    		for(int k = original; k < newsize ; k++){
    			array[i][k] = a[3].array[i-original][k-original];
    		}
    	}
		return SArray((int**)array,newsize);
    }
    SArray operator*(SArray a){ 
    	if(a.getsize()<=2){
    		return this->pMul(a);
    	}else{
    		SArray Mnum[7];
			SArray ANS[4];
			int nsize = a.getsize()/2;
			cout<<"1:"<<endl;
			Mnum[0] = (this->getsub(0,0,nsize) + this->getsub(nsize,nsize,nsize)) * (a.getsub(0,0,nsize) + a.getsub(nsize,nsize,nsize));
			cout<<"M1:"<<endl;
			Mnum[0].Show();
			cout<<"2"<<endl;
			Mnum[1] = (this->getsub(nsize,0,nsize) + this->getsub(nsize,nsize,nsize)) * a.getsub(0,0,nsize);
			cout<<"M2:"<<endl;
			Mnum[1].Show();
			cout<<"3"<<endl;
			Mnum[2] = this->getsub(0,0,nsize) * (a.getsub(0,nsize,nsize) - a.getsub(nsize,nsize,nsize));
			cout<<"M3:"<<endl;
			Mnum[2].Show();
			cout<<"4"<<endl;
			Mnum[3] = this->getsub(nsize,nsize,nsize) * ( a.getsub(nsize,0,nsize) - a.getsub(0,0,nsize));
			cout<<"M4:"<<endl;
			Mnum[3].Show();
			cout<<"5"<<endl;
			Mnum[4] = (this->getsub(0,0,nsize) + this->getsub(0,nsize,nsize)) * a.getsub(nsize,nsize,nsize);
			cout<<"M5:"<<endl;
			Mnum[4].Show();
			cout<<"6"<<endl;
			Mnum[5] = (this->getsub(nsize,0,nsize) - this->getsub(0,0,nsize)) * (a.getsub(0,0,nsize) + a.getsub(0,nsize,nsize));
			cout<<"M6:"<<endl;
			Mnum[5].Show();
			cout<<"7"<<endl;
			Mnum[6] = (this->getsub(0,nsize,nsize) - this->getsub(nsize,nsize,nsize)) * (a.getsub(nsize,0,nsize) + a.getsub(nsize,nsize,nsize));
			cout<<"M7:"<<endl;
			Mnum[6].Show();

			ANS[0] = ( Mnum[0] + Mnum[3] - Mnum[4] + Mnum[6]);
			ANS[1] = (Mnum[2] + Mnum[4]);
			ANS[2] = (Mnum[1] + Mnum[3]);
			ANS[3] = (Mnum[0] + Mnum[2] - Mnum[1] + Mnum[5]);
			
			cout<<"ANS array: "<<endl;
			ANS[0].Show();
			ANS[1].Show();
			ANS[2].Show();
			ANS[3].Show();
			cout<<"ANS"<<endl;
			this->Combine(ANS).Show();
			cout<<"Return"<<endl;
			return this->Combine(ANS);
    	}
		
    }
	// SArray operator=(SArray other){
	//     if (this == &other)
	//         return *this;
	//     else{
	//     	if(other.getsize() != this->size){
	//     		if( this->array != NULL){
	//     			for(int i = 0;i<this->size;i++){
	// 		    		delete this->array[i];
	// 		    	}
	// 		    	delete[] this->array;
	//     		}
	    		
	// 	    	this->size = other.getsize();
	// 	    	this->array = new int*[other.getsize()];
	// 			for(int i =0;i < this->size ; i++){
	// 				this->array[i] = new int[other.getsize()] ;
	// 			}
	//     	}
	//     	for(int i = 0;i<this->size;i++){
	// 			for(int j =0 ;j<this->size;j++){
	// 				this->array[i][j] = other.array[i][j];
	// 			}
	// 		}
	// 		return *this;
	// 	}
	// }
	SArray& Strassen(SArray& other){

	}
};

void MyFree(int** dd,int size){
	if(dd != NULL && size != 0 ){
		for(int i = 0;i<size;i++){
			delete dd[i];
		}
		delete dd;
	}
}

int** baseStrassen(int (*a)[2],int (*b)[2],bool Isprint = false){
	int Mnum[7];
	int **ANS = new int*[2];
	ANS[0] = new int[2];
	ANS[1] = new int[2];
	Mnum[0] = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
	Mnum[1] = (a[0][1] + a[1][1]) * b[1][1];
	Mnum[2] = a[0][0] * (b[0][1] - b[1][1]);
	Mnum[3] = a[1][1] * (b[1][0] - b[0][0]);
	Mnum[4] = (a[0][0] + a[0][1]) * b[1][1];
	Mnum[5] = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
	Mnum[6] = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

	ANS[0][0] = Mnum[0] + Mnum[2];
	ANS[1][1] = ANS[0][0];

	ANS[0][0] +=  Mnum[4] + Mnum[6];
	ANS[0][1] =  Mnum[2] + Mnum[4];
	ANS[1][0] =  Mnum[1] + Mnum[3];
	ANS[1][1] += - Mnum[1] + Mnum[5];

	if(Isprint){
		cout<<ANS[0][0]<<" "<<ANS[0][1]<<endl;
		cout<<ANS[1][0]<<" "<<ANS[1][1]<<endl;
	
	}
	return ANS;
}


int main(void){
	int aa[4][4] = {{2,1,1,0},
					{1,1,1,0},
					{1,1,2,0},
					{0,0,0,0}};

	int bb[4][4] = {{1,2,3,0},
					{1,2,3,0},
					{1,2,3,0},
					{0,0,0,0}};
	SArray a = SArray((int**)aa,4);
	SArray b = SArray((int**)bb,4);
	
	cout<<"a: "<<endl;
	a.Show();
	cout<<"b: "<<endl;
	b.Show();

	// int cc[2][2] = {{1,2},{1,1}};
	// int dd[2][2] = {{3,2},{2,2}};
	// SArray& f = *new SArray((int**)cc,2);
	// SArray& g = *new SArray((int**)dd,2);
	cout << "C:" << endl;
	SArray c = (a*b);
	cout<<"D:"<<endl;
	SArray d = (a.pMul(b));
	c.Show();
	d.Show();
	
}	
