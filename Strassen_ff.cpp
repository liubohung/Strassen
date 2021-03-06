#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 
using namespace std;

class SArray{
	/*
		if size is 0 is mean Row and Col is not equal(not a square matrix).
		if SArray is an empty not Initialization the size
		will be -1 also then Col and Row.
	*/
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
			this->array[i] = new int[length]() ;
		}
	}
	SArray(int** arr,int length):size(length),Row(length),Col(length){
		this->array = new int*[length] ;
		for(int i =0;i<length;i++){
			this->array[i] = new int[length]();
		}
		for(int i = 0 ;i < length; i++){
			for(int j = 0;j < length;j++){
				this->array[i][j] = *(((int*)arr+(i*length+j)));
			}
		}
	}
	SArray(int** arr,int col,int row):Row(row),Col(col){
		/*. Col 為列數 Row 為行數 [col][row]
		  \ row
		col	
			X X X X   O O
			X X X X.  O O
					  O O
					  O O 
		*/
		if(col == row){
			this->size = row;
		}
		this->array = new int*[col] ;
		for(int i =0;i<col;i++){
			this->array[i] = new int[row]() ;
		}
		for(int i = 0 ;i < col; i++){
			for(int j = 0;j < row;j++){
				this->array[i][j] = *(((int*)arr+(i*row+j)));
			}
		}
	}
	~SArray(){
		if(this->array != NULL){
			this->clear_arr();
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
	void Showsize(){
		cout<<"Size :"<<this->size<<endl;
		cout<<" Col :"<<this->Col<<endl;
		cout<<" Row :"<<this->Row<<endl;
		cout<<endl;
	}
	void anti_Show(int idy,int idx){
		for(int i =0;i<idx;i++){
			for(int j=0;j<idy;j++){
				cout << this->array[i][j] << " ";
			}
			cout<<endl;
		}
	}

	int getsize(void) const{ return this->size; }
	int getRow(void) const{ return this->Row; }
	int getCol(void) const{ return this->Col; }
	
	void clear_arr(void){
		if(this->array != NULL && this->size >= 0){
			for(int i =0; i < this->Col ; i++){
				delete this->array[i];
			}
			delete[] this->array ;
		}
		this->array = NULL;
		this->size = -1;
		this->Row = -1;
		this->Col = -1;
	}

	SArray& getsub(int idx,int idy,int size) const {
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
		return *new SArray((int**)temparr,size);
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
    SArray& operator+(const SArray& a){
    	if(a.Row == this->Row && a.Col == this->Col){
    		int array[this->Col][this->Row];
			for(int i = 0; i < this->Col ; i++){
				for(int j = 0 ; j < this->Row ; j++){
					array[i][j] = this->array[i][j] + a.array[i][j];
				}
			}
			return *new SArray((int**)array,this->Row,this->Col);
		}else{
			return *new SArray();	
		}
    }
    SArray& operator-(const SArray& a){
		if(a.Row == this->Row && a.Col == this->Col){
    		int array[this->Col][this->Row];
			for(int i = 0; i < this->Col ; i++){
				for(int j = 0 ; j < this->Row ; j++){
					array[i][j] = this->array[i][j] - a.array[i][j];
				}
			}
			return *new SArray((int**)array,this->Row,this->Col);
		}else{
			return *new SArray();	
		}
    }
    SArray& pMul(const SArray& a){ 
    	if(this->Row == a.Col){
    		int array[this->Col][a.Row];
    		for(int i = 0 ; i < this->Col; i++){
				for(int j = 0 ;j < a.Row;j++){
					int num=0;
					for(int k=0 ;k < this->Row;k++){
						num += this->array[i][k] * a.array[k][j];
					}
					array[i][j] = num;
				}
			}
			return *new SArray((int**)array,this->Col,a.Row);
    	}else{
    		return *new SArray();
    	}	
    }
    SArray& operator*(int num){
    	int array[this->Col][this->Row];
    	if(this->array != NULL){
    		for(int i = 0;i<this->Col;i++){
				for(int j =0 ;j<this->Row;j++){
					array[i][j] = this->array[i][j] * num;
				}
			}
    	}
    	return *new SArray((int**)array,this->Col,this->Row);
    }
    SArray& operator=(SArray other){
    	if(this->Col != other.Col || this->Row != other.Row){
    		if(this->array != NULL){
    			this->clear_arr();
    		}
    		this->size = other.getsize();
    		this->array = new int*[other.Col];
			for(int i =0;i < other.Col ; i++){
				this->array[i] = new int[other.Row]() ;
			}
    	}
    	this->Col = other.Col;
		this->Row = other.Row;
		for(int i = 0; i < this->Col ; i++){
			for(int j = 0 ; j < this->Row ; j++){
				this->array[i][j] = other.array[i][j];
			}
		}
		return *this;
	}
    SArray& operator*(const SArray& a){ 
    	if(this->Row == a.Col){
	    	if(a.getsize()<=2){
	    		return this->pMul(a);
	    	}else{
	    		SArray Mnum[7];
				SArray ANS[4];
				int nsize = a.getsize()/2;

				Mnum[0] = ((this->getsub(0,0,nsize)) + (this->getsub(nsize,nsize,nsize))) * ((a.getsub(0,0,nsize)) + (a.getsub(nsize,nsize,nsize)));
				Mnum[1] = ((this->getsub(nsize,0,nsize) + this->getsub(nsize,nsize,nsize)) * a.getsub(0,0,nsize));
				Mnum[2] = (this->getsub(0,0,nsize) * ((a.getsub(0,nsize,nsize)) - (a.getsub(nsize,nsize,nsize))));
				Mnum[3] = (this->getsub(nsize,nsize,nsize) * ( a.getsub(nsize,0,nsize) - a.getsub(0,0,nsize)));
				Mnum[4] = (this->getsub(0,0,nsize) + this->getsub(0,nsize,nsize)) * a.getsub(nsize,nsize,nsize);
				Mnum[5] = (this->getsub(nsize,0,nsize)-this->getsub(0,0,nsize)) * (a.getsub(0,0,nsize) + a.getsub(0,nsize,nsize));
				Mnum[6] = (this->getsub(0,nsize,nsize) - this->getsub(nsize,nsize,nsize)) * (a.getsub(nsize,0,nsize) + a.getsub(nsize,nsize,nsize));
				
				ANS[0] = (Mnum[0] + Mnum[3] - Mnum[4] + Mnum[6]);
				ANS[1] = (Mnum[2] + Mnum[4]);
				ANS[2] = (Mnum[1] + Mnum[3]);
				ANS[3] = (Mnum[0] + Mnum[2] - Mnum[1] + Mnum[5]);
				if(0){
					cout<<"1"<<endl;
					cout<<"M1:"<<endl;
					Mnum[0].Show();
					cout<<"2"<<endl;
					cout<<"M2:"<<endl;
					Mnum[1].Show();
					cout<<"3"<<endl;
					cout<<"M3:"<<endl;
					Mnum[2].Show();
					cout<<"4"<<endl;
					cout<<"M4:"<<endl;
					Mnum[3].Show();
					cout<<"5"<<endl;
					cout<<"M5:"<<endl;
					Mnum[4].Show();
					cout<<"6"<<endl;
					cout<<"M6:"<<endl;
					Mnum[5].Show();
					cout<<"7"<<endl;
					cout<<"M7:"<<endl;
					Mnum[6].Show();
					cout<<"ANS array: "<<endl;
					ANS[0].Show();
					ANS[1].Show();
					ANS[2].Show();
					ANS[3].Show();
					// cout<<"ANS"<<endl;
					// this->Combine(ANS).Show();
					// cout<<"Return"<<endl;
				}

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
				return *new SArray((int**)array,newsize);
	    	}
    	}else{
    		return *new SArray();
    	}
    }
	void squarify(){
		if (this->Row != this->Col && this->size == 0){
			int big,small;
			if (this->Row > this->Col){
				big = this->Row;
				small = this->Col;
			}else{
				big = this->Col;
				small = this->Row;
			}

			int** temp = new int*[big];
			for(int i = 0 ; i < big ; i++){
				temp[i] = new int[big]() ;
			}
			for(int i = 0;i < this->Col ; i++){
				for(int j = 0; j < this->Row ; j++){
					temp[i][j] = this->array[i][j];
				}
			}

			this->clear_arr();
			this->array = temp;
			this->Row = big;
			this->Col = big;
			this->size = big;
		}
	}
	void squarify(int num){
		if( num >= this->Row && num >= this->Col ){
			int** temp = new int*[num];
			for(int i = 0 ; i < num ; i++){
				temp[i] = new int[num]() ;
			}
			for(int i = 0;i < this->Col ; i++){
				for(int j = 0; j < this->Row ; j++){
					temp[i][j] = this->array[i][j];
				}
			}
			this->clear_arr();
			this->array = temp;
			this->Row = num;
			this->Col = num;
			this->size = num;
		}
	}
	void anti_space(int idx,int idy){
		if(idx < this->Row && idy < this-> Col){
			int** temp = new int*[idy];
			for(int i = 0 ; i < idy ; i++){
				temp[i] = new int[idx]() ;
			}
			this->clear_arr();
			for(int i = 0;i < idx ; i++){
				for(int j = 0; j < idy ; j++){
					temp[i][j] = this->array[i][j];
				}
			}
			this->array = temp;
			this->Row = idx;
			this->Col = idy;
			this->size = 0;
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
void mytest1(int num){
	clock_t start, finish;   
    double duration;

	srand(time(NULL));

	int arr1[num][num],arr2[num][num];
	start = clock();  
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand();
			arr2[i][j] = rand();
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	(a*b).Show();
	finish = clock();  
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout<<"Time :"<<duration<<" seconds"<<endl;
}
void mytest2(void){
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
	int cc[2][4] = {{1,2,3,4},
					{1,1,1,1}};

	int dd[4][2] = {{4,1},
					{3,1},
					{2,1},
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
	SArray h = e.pMul(f);
	h.Show();
	cout<<"====g===="<<endl;
	SArray g = h*3;
	g.Show();
	cout<<"=======squarify======="<<endl;
	f.squarify();
	f.Showsize();
	f.Show();

	e.squarify();
	e.Showsize();
	e.Show();
	// f.anti_Show(2,4);

	SArray hh2 = f*e;
	hh2.Show();
	SArray hh1 = f.pMul(e);
	hh1.Show();
	hh2.squarify(5);
	hh1.squarify(5);
	cout<<"====5*5===="<<endl;
	(hh1*hh2).Show();
	(hh1.pMul(hh2)).Show();

	int qq[5][5] ={
		{1,2,3,4,5},
		{1,211,3,4,5},
		{121,1232,112,112,11},
		{1,1,1,1,1},
		{1,1,1,1,1}
	};
	int gg[5][5] ={
		{1,2,3,4,5},
		{1,3,1,1,1},
		{1,1,4,1,1},
		{1,1,1,7,1},
		{1,1,2,1,1}
	};
	SArray hh3 = SArray((int**)qq,5,5);
	SArray hh4 = SArray((int**)gg,5,5);
	(hh3*hh4).Show();
	(hh3.pMul(hh4)).Show();
	delete &f;
	delete &e;
	
	// d.Show();
	// (b*a).Show();
	delete &a;
	delete &b;
}
void Run_test(){
	int arg[4]={30,30,30,70};
	int arr1[arg[0]][arg[1]],arr2[arg[2]][arg[3]];
	int max=10,min= 0;
	for(int i =0;i<arg[0];i++){
		for(int j=0;j<arg[1];j++){
			arr1[i][j]=rand()% (max - min + 1) + min;
		}
	}
	for(int i =0;i<arg[2];i++){
		for(int j=0;j<arg[3];j++){
			arr2[i][j]=rand()% (max - min + 1) + min;
		}
	}

	SArray F_matrix = SArray((int**) arr1,arg[0],arg[1]);
	SArray S_matrix = SArray((int**) arr2,arg[2],arg[3]);
	F_matrix.Show();
	S_matrix.Show();
	int large=0;
	for(int i =0;i<4;i++){
		if(arg[i] > large) large = arg[i];
	}

	if( arg[0] != arg[1] && arg[2] != arg[3]){
		if((large &1) == 1){
			large++;
		}
		F_matrix.squarify(large);
		S_matrix.squarify(large);
	}
	F_matrix.Show();
	S_matrix.Show();
	// (F_matrix*S_matrix).Show();
	(F_matrix*S_matrix).anti_Show(arg[3],arg[0]);
}
void Main(void){
	int arg[4];
	scanf("%d %d %d %d\n",&arg[0],&arg[1],&arg[2],&arg[3]);
	int arr1[arg[0]][arg[1]],arr2[arg[2]][arg[3]];
	for(int i =0;i<arg[0];i++){
		for(int j=0;j<arg[1];j++){
			cin>>arr1[i][j];
		}
	}
	for(int i =0;i<arg[2];i++){
		for(int j=0;j<arg[3];j++){
			cin>>arr2[i][j];
		}
	}

	SArray F_matrix = SArray((int**) arr1,arg[0],arg[1]);
	SArray S_matrix = SArray((int**) arr2,arg[2],arg[3]);
	int large=0;
	for(int i =0;i<4;i++){
		if(arg[i] > large) large = arg[i];
	}
	if((large &1) == 1){
		large++;
	}
	F_matrix.squarify(large);
	S_matrix.squarify(large);
	
	(F_matrix*S_matrix).anti_Show(arg[3],arg[0]);
}
int main(void){
	//mytest1(500);
	Main();
}	
