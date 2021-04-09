#include<iostream>

using namespace std;

class SArray{
public:
	int **array;
	int size;
	int Row,Col;
	SArray(){
		this->array = NULL;
		this->size = -1;
		this->Row = -1;
		this->Col = -1;
	}
	SArray(int length):size(length),Row(length),Col(length){
		this->array = new int*[length] ;
		for(int i =0;i<size;i++){
			this->array[i] = new int[length] ;
		}
	}
	SArray(int** arr,int length):size(length),Row(length),Col(length){
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
	SArray(int** arr,int col,int row):Row(row),Col(col),size(0){
		//Col 為列數 row 為行數 [col][row]
		/*
		  \ row
		col	
			X X X X   O O
			X X X X.  O O
					  O O
					  O O 
		*/
		this->array = new int*[col] ;
		for(int i =0;i<col;i++){
			this->array[i] = new int[row] ;
		}
		for(int i = 0 ;i < col; i++){
			for(int j = 0;j < row;j++){
				this->array[i][j] = *(((int*)arr+(i*row+j)));
			}
		}
	}
	~SArray(){
		if(this->array != NULL){
			for(int i =0;i<this->Col;i++){
				delete this->array[i];
			}
			delete[] this->array ;
		}	
	}

	void Show(void){
		if(this->size== -1){
			cout<<"Is empty"<<endl;
		}else{
			for(int i=0;i<this->Col;i++){
				for(int j=0;j<this->Row;j++){
					cout<<this->array[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
	}

	int getsize(void) const{ return this->size; }
	int getRow(void) const{ return this->Row; }
	int getCol(void) const{ return this->Col; }

	SArray getsub(int idx,int idy,int size) const {
		//must to be a square matrix 
		int temparr[size][size];
		for(int i = idx;i<(idx+size);i++){
			for(int j = idy;j<(idy+size);j++){
				if(i > this->size || j > this->size ){
					temparr[i-idx][j-idy] = 0;
				}else{
					temparr[i-idx][j-idy] = this->array[i][j];
				}	
			}
		}
		return SArray((int**)temparr,size);
	}
	SArray& operator+=(SArray& a){ 
		if(a.Row == this->Row && a.Col == this->Col){
			for(int i = 0; i < this->Col ; i++){
				for(int j = 0 ; j < this->Row ; j++){
					this->array[i][j] += a.array[i][j];
				}
			}
		}
		return *this;
    }
    SArray& operator-=(SArray& a){ 
		if(a.Row == this->Row && a.Col == this->Col){
			for(int i = 0; i < this->Col ; i++){
				for(int j =0 ; j < this->Row ; j++){
					this->array[i][j] -= a.array[i][j];
				}
			}
		}
		return *this;
    }
    SArray operator+(const SArray& a){
    	if(a.Row == this->Row && a.Col == this->Col){
    		int array[this->Col][this->Row];
			for(int i = 0; i < this->Col ; i++){
				for(int j = 0 ; j < this->Row ; j++){
					array[i][j] = this->array[i][j] + a.array[i][j];
				}
			}
			return SArray((int**)array,this->size);
		}else{
			return SArray();	
		}
    }
    SArray operator-(const SArray& a){
		if(a.Row == this->Row && a.Col == this->Col){
    		int array[this->Col][this->Row];
			for(int i = 0; i < this->Col ; i++){
				for(int j = 0 ; j < this->Row ; j++){
					array[i][j] = this->array[i][j] + a.array[i][j];
				}
			}
			return SArray((int**)array,this->size);
		}else{
			return SArray();	
		}
    }
    SArray pMul(const SArray& a){ 
    	if(this->Row == a.Col){
    		int array[this->Col][a.Row];
    		for(int i = 0 ; i < this->Col; i++){
				for(int j = 0 ;j < this->Row;j++){
					int num=0;
					for(int k=0 ;k < this->Row;k++){
						num += this->array[i][k] * a.array[k][j];
					}
					array[i][j] = num;
					// cout<<"i: "<<i<<" "<<"j: "<<j<<" "<< "ans: "<< temp.array[i][j]<<endl;
				}
			}
			return SArray((int**)array,this->Col,a.Row);
    	}else{
    		return SArray();
    	}
    	
    }
    SArray operator*(int num){
    	int array[this->size][this->size];
    	if(this->array != NULL){
    		for(int i = 0;i<size;i++){
				for(int j =0 ;j<size;j++){
					array[i][j] = this->array[i][j] * num;
				}
			}
    	}
    	return SArray((int**)array,this->size);
    }
    static SArray Combine(SArray a[4]) {
    	// cout<<"Combine"<<endl;
    	// cout<<"Size:"<<a[0]->size * 2<<endl;

    	int original = a[0].size;
    	int newsize = original * 2;
    	int array[newsize][newsize];
    	//top
    	for(int i = 0 ;i < original ; i++){
    		for(int j = 0; j< original ; j++){
				array[i][j] = a[0].array[i][j];
    		}
    		for(int k = original; k < newsize ; k++){
    			array[i][k] = a[1].array[i][k-original];
    		}
    	}
    	//down
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
    SArray& operator=(SArray other){
    	if(other.getsize() != this->size){
    		if(this->array != NULL){
    			for(int i =0;i<this->size;i++){
		    		delete this->array[i];
		    	}
	    		delete[] this->array;
    		}
    		this->size = other.getsize();
    	}
    	this->array = new int*[other.getsize()];
		for(int i =0;i < this->size ; i++){
			this->array[i] = new int[other.getsize()] ;
		}
		for(int i = 0; i < this->Col ; i++){
			for(int j = 0 ; j < this->Row ; j++){
				this->array[i][j] = other.array[i][j];
			}
		}
		return *this;
	}
    SArray operator*(const SArray& a){ 
    	if(a.getsize()<=2){
    		return this->pMul(a);
    	}else{
    		SArray Mnum[7];
			SArray ANS[4];
			int nsize = a.getsize()/2;

			Mnum[0] = ((this->getsub(0,0,nsize)) + (this->getsub(nsize,nsize,nsize))) * ((a.getsub(0,0,nsize)) + (a.getsub(nsize,nsize,nsize)));
			Mnum[1] = (this->getsub(nsize,0,nsize) + this->getsub(nsize,nsize,nsize)) * a.getsub(0,0,nsize);
			Mnum[2] = this->getsub(0,0,nsize) * (a.getsub(0,nsize,nsize) - a.getsub(nsize,nsize,nsize));
			Mnum[3] = this->getsub(nsize,nsize,nsize) * ( a.getsub(nsize,0,nsize) - a.getsub(0,0,nsize));
			Mnum[4] = (this->getsub(0,0,nsize) + this->getsub(0,nsize,nsize)) * a.getsub(nsize,nsize,nsize);
			Mnum[5] = (this->getsub(nsize,0,nsize) - this->getsub(0,0,nsize)) * (a.getsub(0,0,nsize) + a.getsub(0,nsize,nsize));
			Mnum[6] = (this->getsub(0,nsize,nsize) - this->getsub(nsize,nsize,nsize)) * (a.getsub(nsize,0,nsize) + a.getsub(nsize,nsize,nsize));
			
			ANS[0] = (Mnum[0] + Mnum[3] - Mnum[4] + Mnum[6]);
			ANS[1] = (Mnum[2] + Mnum[4]);
			ANS[2] = (Mnum[1] + Mnum[3]);
			ANS[3] = (Mnum[0] + Mnum[2] - Mnum[1] + Mnum[5]);

			// if(false){
			// 	cout<<"1"<<endl;
			// 	cout<<"M1:"<<endl;
			// 	Mnum[0].Show();
			// 	cout<<"2"<<endl;
			// 	cout<<"M2:"<<endl;
			// 	Mnum[1].Show();
			// 	cout<<"3"<<endl;
			// 	cout<<"M3:"<<endl;
			// 	Mnum[2].Show();
			// 	cout<<"4"<<endl;
			// 	cout<<"M4:"<<endl;
			// 	Mnum[3].Show();
			// 	cout<<"5"<<endl;
			// 	cout<<"M5:"<<endl;
			// 	Mnum[4].Show();
			// 	cout<<"6"<<endl;
			// 	cout<<"M6:"<<endl;
			// 	Mnum[5].Show();
			// 	cout<<"7"<<endl;
			// 	cout<<"M7:"<<endl;
			// 	Mnum[6].Show();
			// 	cout<<"ANS array: "<<endl;
			// 	ANS[0]->Show();
			// 	ANS[1]->Show();
			// 	ANS[2]->Show();
			// 	ANS[3]->Show();
			// 	cout<<"ANS"<<endl;
			// 	this->Combine(ANS).Show();
			// 	cout<<"Return"<<endl;
			// }
			int original = nsize;
	    	int newsize = original * 2;
	    	int array[newsize][newsize];

			for(int i = 0 ;i < original ; i++){
	    		for(int j = 0; j < original ; j++){
					array[i][j] = ANS[0].array[i][j];
	    		}
	    		for(int k = original; k < newsize ; k++){
	    			array[i][k] = ANS[1].array[i][k-original];
	    		}
	    	}
	    	//down
	    	for(int i = original; i < newsize ; i++){
	    		for(int j = 0; j < original ; j++){
					array[i][j] = ANS[2].array[i-original][j];
	    		}
	    		for(int k = original; k < newsize ; k++){
	    			array[i][k] = ANS[3].array[i-original][k-original];
	    		}
	    	}
			return SArray((int**)array,newsize);
    	}
    }
	
	
};

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
	int aa[4][4] = {{1,1,1,0},
					{1,1,1,0},
					{2,2,2,0},
					{0,0,0,0}
				};

	int bb[4][4] = {{1,2,3,4},
					{1,2,3,4},
					{1,2,3,4},
					{1,2,3,4}
				};
	int cc[2][4] = {{1,1,1,1},
					{1,1,1,1}};
	int dd[4][2] = {{1,1},
					{1,1},
					{1,1},
					{1,1}};

	int ee[4][8] = {{1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1}
					};

	SArray& a = *new SArray((int**)aa,4);
	SArray& b = *new SArray((int**)bb,4);
	a.getsub(0,0,2).Show();
	a.getsub(2,2,2).Show();

	SArray c = (a.getsub(0,0,2) + a.getsub(2,2,2));
	c.Show();
	cout<<"====C===="<<endl;
	// SArray d = a*b;
	SArray& e = *new SArray((int**)cc,2,4);
	e.Show();
	SArray& f = *new SArray((int**)dd,4,2);		
	f.Show();			
	e.Show();
	// e.Show();
	SArray h = e+f;
	h.Show();
	delete &f;
	delete &e;
	
	// d.Show();
	// (b*a).Show();
	delete &a;
	delete &b;
	
}	
