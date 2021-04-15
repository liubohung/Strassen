#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <ctime> 
using namespace std;

class SArray{
	/*
		*For long standing Object
			Is mean the Object have itself's array not point to an other Objects array 
			If size is 0 is mean Row and Col is not equal(not a square matrix).
			If SArray is an empty not Initialization the size and all member will be 
			set -1 (Istemp will be false).
			
			long standing Object attribute
			<<=======================>>
				SArray.array  to array storage the real data
				SArray.size   to check matrix is square or not ,store the size of square matrix.
				SArray.Row and SArray.Col to record  space.
				SArray.Istemp to check SArray is temporary or not.
			<<=======================>>

		*For temporary Object 
			temporary Object must be the square matrix
			The size is to Storage the size of sub matrix 
			Row and Col is a first index 
			If the Object is temp.So Istemp will be true and the empty Object 
			will default be true

			temporary Object attribute
			<<=======================>>
				SArray.array  to point to real data from original Object .
				SArray.size   to record the size of subarray.
				SArray.Row and SArray.Col to record the begin of space.
				SArray.Istemp to check SArray is temporary or not.
			<<=======================>>

		The long standing Object can derive long standing Object(Copy or getsub_new)
		and temporary Object(getsub)
		The temporary Object only allow derive the temporary Object
		
	            	
		explain:
			[	L L L L   ]  The element L is long standing Object's value
			[	L T T L   ]	 The temporary Object is the part of long standing Object
			[	L T T L   ]	 and the element T is mean it is a part of long standing 
			[	L L L L   ]	 Object and temporary Object in same time.

		Example the Rule:
			1. Size is 0 So the Row and Col is not Equal.It is an any shape matrix 
			2. Size is not 0 as well as the Row and Col is Equal.It is a squeue matrix
			3. The Istemp is true. SO this is a temporary Object and it should be a 
			   squeue matrix. And the pointer array will point to original Object.
	
		Data Storage method :
			Col 為列數 Row 為行數 [col][row]
			  \ row
			col	        
				X X X X   	O O 		Z Z Z Z 		 col\row ----->
				X X X X.  	O O 		Z Z Z Z  		  ||
					[2][4]	O O 		Z Z Z Z 		  ||
							O O [4][2]  Z Z Z Z  [4][4]   \/
	*/
public:
	int **array;
	int size;
	int Row,Col;
	bool Istemp;

	SArray(){ //Empty Constructor
		this->array = NULL;
		this->size = -1;
		this->Row = -1;
		this->Col = -1;
		this->Istemp = true;
	}
	SArray(int** arr,bool Istemp,int col,int row,int size){
		/* 
			This constructor is only for the temporary Object 
			use in the method getsub() .
			
			This constructor is use to helped the getsub be fast 
			when multiply the big Object 

			The size is store the the original matrix's size.It's to 
			help to count the this sub matrix position. 
			Must to use carefully using.
		*/
		if(arr != NULL){
			this->array = arr ;
			this->size = size ;
			this->Row = row ;
			this->Col = col ;
			this->Istemp = true;
		}else{
			this->array = NULL;
			this->size = -1 ;
			this->Row = -1 ;
			this->Col = -1 ;
			this->Istemp = true;
		}
	}
	SArray(int length):size(length),Row(length),Col(length){
		this->array = new int*[length] ;
		for(int i = 0;i<size;i++){
			this->array[i] = new int[length]();
		}
		this->Istemp = false;
	}
	SArray(int** arr,int length):size(length),Row(length),Col(length){
		/*
			make a square matrix and initialize array by paramatter arr.
			arrtribute arr must be square matrix.
		*/
		this->array = new int*[length] ;
		this->Istemp = false;

		for(int i =0;i<length;i++)
			this->array[i] = new int[length]();
		
		if(length == 1){ // if size is 1
			this->array[0][0] = arr[0][0];
		}else{
			for(int i = 0 ;i < length; i++){
				for(int j = 0;j < length;j++){
					this->array[i][j] = *(((int*)arr+(i*length+j)));
				}
			}
		}
	}
	SArray(int** arr,int col,int row):Row(row),Col(col){
		//Make a matrix and initialize array by paramatter arr.
		//This matrix probably not a square matrix but it still can being.
		this->Istemp = false;
		if(col == row) this->size = row;

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
		if( this->size == -1 || this->array == NULL){
			cout<<"Is empty"<<endl;
		}else if(this->Istemp){//not complete i think it have some error 
			cout<<"Print temporary Object " << endl;
			if (this->size == 1) {
				cout<<this->array[this->Col][this->Row]<<endl;
			} else {
				for (int i = this->Col ; i < this->size + this->Col ; i++) {
					for(int j = this->Row ; j < this->size + this->Row ; j++){
						cout<< this->array[i][j] <<" ";
					}
					cout<<endl;
				}
			}
		}else{
			cout<<"Show Print long standing Object " << endl;
			if(this->Col == 1 && this->Row == 1){
				cout<<this->array[0][0]<<endl;
			}else{
				for(int i=0;i<this->Col;i++){
					for(int j=0;j<this->Row;j++){
						cout<< this->array[i][j] <<" ";
					}
					cout<<endl;
				}
			}
		}
		cout<<endl;
	}
	void Showsize(){
		if(this->size == 0){
			cout<<"It's not a square matrix. " << endl;
		}else if(this->size > 0){
			cout<<"It's a square matrix. " << endl;
		}else if(this->size < 0){
			cout<<"It's  empty. " << endl;
		}
		cout<<"Size :"<< this->size <<endl;
		if(this->Istemp){
			cout<<"idy  :"<< this->Col <<endl;
			cout<<"idx  :"<< this->Row <<endl;
			cout<<"The Array address : "<<this->array<<endl;
			cout<<"!! It's a temporary Object "<<endl;
		}else{
			cout<<"Col  :"<< this->Col <<endl;
			cout<<"Row  :"<< this->Row <<endl;
			cout<<"The Array address : "<<this->array<<endl;
		}
		cout<<endl;
	}
	void anti_Show(int idy,int idx){
		if (this->Istemp) {
			if (idy < this->size && idx < this->size ) { 
				for (int i = this->Col ; i < idx ; i++) {
					for (int j = this->Row ;j < idy ; j++) {
						cout << this->array[i][j] << " ";
					}
					cout<<"\n";
				}
			}
		}else{
			if (idy < this->Row && idx < this->Col ) {
				for (int i =0;i<idx;i++) {
					for (int j=0;j<idy;j++) { 
						cout << this->array[i][j] << " ";
					}
					cout<<"\n";
				}
			}
		}	
	}

	inline int getsize(void) const{ return this->size; }
	inline int getRow(void) const{ return this->Row; }
	inline int getCol(void) const{ return this->Col; }
private:
	//The private way only provide some danger method 
	//for clear Object or rebuild Object 
	void clear_arr(void){
		/*
			Clear the Object and set the Object to unavailable status
		
			if the Object is temporary Object,then it can't not be clear
			So let the pointer array to NULL not delete
		*/
		if( this->array != NULL && (!this->Istemp) ){
			for(int i =0; i < this->Col ; i++){
				delete this->array[i];
			}
			delete[] this->array ;
		}
		this->array = NULL;
		this->size = -1;
		this->Row = -1;
		this->Col = -1;
		this->Istemp = false;
	}
	void reuse(int size){
		/*
			Some Object Initialization call base constructor ,But we need to use 
			that Object. So we need to call reuse to reinitialize.
			This method must very carefully using. 
		*/
		if (this->array != NULL && (!this->Istemp)) {
			for(int i =0; i < this->Col ; i++){
				delete this->array[i];
			}
			delete[] this->array ;
		}
		this->array = new int*[size] ;
		for (int i = 0;i<size;i++) {
			this->array[i] = new int[size]();
		}
		this->size = size;
		this->Row = size;
		this->Col = size;
		this->Istemp = false; //must very becarefully 
	}

public:	
	SArray getsub_new(int idx,int idy,int size) const {
		/*
			0. Index start with 0.
			1. The method getsub_new can used when the size is zero's Object. 
			2. If row or col out of range,the value will be full of 0.
			3. If the temporary Object call this method. it will return the empty 
			   Object.
			4. It will get the long standing Object
		*/ 
		if(this->Istemp && this->array == NULL){//Can't build a temp Object to long standing Object
			return SArray();
		}else{
			if(this->size == 1 || size == 1){//To deal the situation when the size is 1 
				int temp[1][1];
				temp[0][0] = (idx > this->Row || idy > this->Col || this->Istemp ) ? 0:this->array[idy][idx];
				return SArray((int**)temp,1);
			}else{
				int temparr[size][size];
				for(int i = idy ; i < (idy+size) ; i++){
					for(int j = idx ; j < (idx+size) ; j++){
						if(i > this->Row || j > this->Col || this->Istemp ){
							temparr[i-idx][j-idy] = 0;
							cout<<temparr[i-idx][j-idy]<<" ";
						}else{
							temparr[i-idx][j-idy] = this->array[i][j];
							cout<<temparr[i-idx][j-idy]<<" ";
						}	
					}
				}
				return SArray((int**)temparr,size);
			}
		}
	}
	SArray getsub(int idx,int idy,int size) const {
		/*	
		0. Index start with 0.
		1. The idx,idy and size.Range have be insided this array if not then retrun the
		   empty SArray.
		2. The getsub can't using when Object size is zero.Because it probably
		   get a mistake result.
		3. It will get the square matrix from the this Object (no matter the Object
		   is temporary Object or long standing Object).

		2. Return the temporary Object and set the same size in temporary Object(the
		   size is use to count the right position ,when temporary Object need to 
		   get a value).
		3. !! The origin Object can't delete when the temporary Object are using,and must
		   be carefully.
		5. Can't changing any temporary Object's value. 
		*/
		if( idx+size > this->Row+this->size ||  size+idy > this->Col+this->size || this->getsize() <= 0 || size == 0 || size > this->size||this->array == NULL){
			return SArray(); 
		}
		if(this->Istemp == true ){
			return SArray(this->array,true,this->Col+idy,this->Row+idx,size);
		}else{
			return SArray(this->array,true,idy,idx,size);
		}
	}
	bool operator ==(const SArray& a){
		if ( a.Istemp | this->Istemp ) {// One is temporary Object
			if ( a.Istemp ^ this->Istemp) { // Other one is not temporary Object
				if ( this->size == 0 || a.size == 0 || !(this->size == a.size) ) 
					return false; // Both are the square matrix and have same size
				cout<<"good"<<endl;
				// ** this part can be better
				if (this->Istemp) {//this is a submatrix
					for (int i =this->Col , j=a.Col ; i < size;i++,j++) {
						for (int k=this->Row , q=a.Row ; k < size;k++,q++) {
							if ( this->array[i][k] != a.array[j][q]) return false;
						}
					}
				} else { //Parameter a is a submatrix
					for(int i =this->Col , j=a.Col ; i < size;i++,j++) {
						for(int k=this->Row , q=a.Row ; k < size;k++,q++) {
							if(this->array[i][k] != a.array[j][q]) return false;
						}
					}
				}
			}else{ // Both are the temporary Object
				if(this->array == a.array && this->Row == a.Row && this->Col == a.Col && this->size == a.size) 
					return true; //same palce same size
				if( this->size != a.size ) return false;
				for(int i =this->Col , j=a.Col ; i < size;i++) {
					for(int k=this->Row , q=a.Row ; k < size;k++) {
						if(this->array[i][k] != a.array[j][q]) return false;
					}
				}
			}
		}else{// both are long standing Object
			if(this->Row != a.Row || this->Col != a.Col) return false;
			if(this->size == a.size && this->size != 0){// to check square matrix
				for(int i =0;i<this->size;i++){
					for(int j =0;j<this->size;j++){
						if( this->array[i][j] != a.array[i][j] ) return false;
					}
				}
			}
		}
		return true;
	}
	SArray& operator+=(const SArray& a){ 
		if (this->size == -1) return *this; // if this Object can not using
		if (!this->Istemp) { // if this is a temporary Object (temporary Object can't change)
			if (a.Istemp) { //a is a temporary Object 
				if( this->size == a.size ){
					for (int i =0 , j=a.Col ; i < this->size ; i++,j++) {
						for (int k =0 , q=a.Row ; k < this->size;k++,q++) {
							this->array[i][k] += a.array[j][q] ;
						}
					}
				}
			} else {
				if (a.Row == this->Row && a.Col == this->Col) {
					for (int i = 0; i < this->Col ; i++) {
						for (int j = 0 ; j < this->Row ; j++) {
							this->array[i][j] += a.array[i][j];
						}
					}
				}
			}
		}	
		return *this;
    }
    SArray& operator-=(const SArray& a){ 
		if (this->size == -1) return *this;// if this Object can not using
		if (!this->Istemp) { // if this is a temporary Object (temporary Object can't change)
			if (a.Istemp) { //a is a temporary Object 
				if( this->size == a.size ){
					for (int i =0 , j=a.Col ; i < this->size ; i++,j++) {
						for (int k =0 , q=a.Row ; k < this->size;k++,q++) {
							this->array[i][k] -= a.array[j][q] ;
						}
					}
				}
			} else {
				if (a.Row == this->Row && a.Col == this->Col) {
					for (int i = 0; i < this->Col ; i++) {
						for (int j = 0 ; j < this->Row ; j++) {
							this->array[i][j] -= a.array[i][j];
						}
					}
				}
			}
		}	
		return *this;
    }
    SArray operator+(const SArray& a){
		/* 
			no matter which one is a temporary Object or not . 
			operator+ have to return the long standing Object to count result.
		*/
		if(this->array == NULL || a.array == NULL) return SArray(); //check both are can use
		if ( this->Istemp | a.Istemp ) { //one is a temporary Object 
			if ( this->size != a.size ){ //size is not equal so can't add
				return SArray();	
			} else {
				// if this Object is temporary Object then end need to add col
				// else then the size is end
				int array[this->size][this->size];
				for (int i = this->Istemp ? this->Col:0,j=a.Istemp?a.Col:0,h=0; h < this->size ;h++, i++, j++) {
					for (int k = this->Istemp?this->Row:0,q=a.Istemp?a.Row:0,z=0; z < this->size ;z++, k++, q++) {
						array[h][z] =  this->array[i][k] + a.array[j][q] ;
					}
				}
				return SArray((int**)array,this->size);	
			}
		} else { // both are long standing Object
			if(a.Row == this->Row && a.Col == this->Col ){ 
				int array[this->Col][this->Row];
				for(int i = 0; i < this->Col ; i++){
					for(int j = 0 ; j < this->Row ; j++){
						array[i][j] = this->array[i][j] + a.array[i][j];
					}
				}	
				return SArray((int**)array,this->Row,this->Col);
			}else{
				return SArray();	
			}
		}
    }
    SArray operator-(const SArray& a){
		/* 
			no matter which one is temporary Object or not . 
			operator- have to return the long standing Object to count result.
		*/
		if(this->array == NULL || a.array == NULL) return SArray();//check both are can use
		if ( this->Istemp | a.Istemp ) { //one is a temporary Object 
			if ( this->size != a.size ){ //size is not equal so can't sub
				return SArray();	
			} else {
				// if this  Object is a temporary Object then end need to add col
				// else then the size is end
				int array[this->size][this->size];
				for (int i = this->Istemp?this->Col:0,j=a.Istemp?a.Col:0,h=0; h < this->size ;h++, i++, j++) {
					for (int k = this->Istemp?this->Row:0,q=a.Istemp?a.Row:0,z=0; z < this->size ;z++, k++, q++) {
						array[h][z] =  this->array[i][k] - a.array[j][q] ;
					}
				}
				return SArray((int**)array,this->size);	
			}
		} else { // both are long standing Object
			if(a.Row == this->Row && a.Col == this->Col ){ 
				int array[this->Col][this->Row];
				for(int i = 0; i < this->Col ; i++){
					for(int j = 0 ; j < this->Row ; j++){
						array[i][j] = this->array[i][j] - a.array[i][j];
					}
				}	
				return SArray((int**)array,this->Row,this->Col);
			}else{
				return SArray();	
			}
		}
    	
    }
    SArray pMul(const SArray& a){ 
		if (this->size != a.size) { // Difference size  cna't mul
			cout<<"Size is didderence"<<endl;
			return SArray();		// if both are 0 0 need to special process
		} else if ( this->Istemp && a.Istemp ) { // Both Object are temporary Object
			cout<<"Both are temporary"<<endl;
			int array[this->size][this->size];
			for(int i =0;i<this->size;i++){
				for(int j =0;j<this->size;j++){
					 array[i][j] = 0;
				}
			}
			for (int i = this->Col ; i < this->Col + this->size; i++) {
				for (int j = a.Row ;j < a.Row + a.size;j++) {
					int num = 0;
					for (int k=this->Row,q=a.Col ;k < this->Row+this->size ;k++,q++) {
						num += this->array[i][k] * a.array[q][j];
					}
					array[i-this->Col][j-a.Row] = num;
				}
			}
			return SArray((int**)array,this->size);
		} else if( (this->Istemp ^ a.Istemp) ) { // a or this Object is a temporary Object
			if(a.Istemp){ // a is a temporary Object 
				cout<<"a is temporary"<<endl;
				int array[this->size][this->size];
				for (int i = 0 ; i < this->size; i++) {
					for (int j = a.Row ;j < a.Row+a.size;j++) {
						int num=0;
						for (int k=0 ;k < this->size ;k++) {
							num += this->array[i][k] * a.array[k+a.Col][j];
						}
						array[i][j-a.Row] = num;
					}
				}
				return SArray((int**)array,this->size);
			}else{ // this Object is a temporary Object
				cout<<"this is temporary"<<endl;
				int array[a.size][a.size];
				for (int i = this->Col ; i < this->size+this->Col; i++) {
					for (int j = 0 ;j < a.size ;j++) {
						int num=0;
						for (int k = 0 ;k < this->size ;k++) {
							num += this->array[i][k+this->Row] * a.array[k][j];
						}
						array[i-this->Col][j] = num;
					}
				}
				return SArray((int**)array,a.size);
			}
		} else if (this->Row == a.Col) {// a Object and this Object have diffference but can mul
				int array[this->Col][a.Row];
				for (int i = 0 ; i < this->Col; i++) {
					for (int j = 0 ;j < a.Row;j++) {
						int num=0;
						for (int k=0 ;k < this->Row;k++) {
							num += this->array[i][k] * a.array[k][j];
						}
						array[i][j] = num;
					}
				}
				return SArray((int**)array,this->Col,a.Row);
		}else{
			return SArray();
		}
    }
    SArray operator*(int num){
		if(this->array == NULL) SArray(); //the empty Object can't use 
		if(this->Istemp){
			int array[this->size][this->size];
			for (int i = this->Col ; i<this->size ; i++) {
				for (int j =this->Row ; j<this->size ; j++) {
					array[i][j] = this->array[i][j] * num;
				}
			}
			return SArray((int**)array,this->size);
		}else{
			int array[this->Col][this->Row];
			for (int i = 0;i<this->Col;i++) {
				for (int j =0 ;j<this->Row;j++) {
					array[i][j] = this->array[i][j] * num;
				}
			}
			return SArray((int**)array,this->Col,this->Row);
		}
    }
    SArray& operator=(SArray other){
		if (this->array == NULL && this->Istemp == true && this->size == -1 ){ //if this is not init  
			this->reuse(other.size);
		}
		if(!this->Istemp){ //It's not a temporary Object  
			if(other.Istemp){
				if(this->size == other.size){
					for (int i = other.Col,q=0;i < other.Col+other.size; i++,q++) {
						for(int j = other.Row,k=0;j < other.Row+other.size; j++,k++) {
							this->array[q][k] = other.array[i][j];
						}
					}
				}
			}else{
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
			}
		}
		return *this;
	}
    SArray operator*(const SArray& a){ 
		if (this->size != a.size) { // Difference size  cna't mul
			cout<<"Size is didderence"<<endl;
			return SArray();		// if both are 0 0 need to special process
		} else if ( this->Row == a.Col && this->size == 0 && a.size == 0) {// a Object and this Object have diffference but can mul
				int array[this->Col][a.Row];
				for (int i = 0 ; i < this->Col; i++) {
					for (int j = 0 ;j < a.Row;j++) {
						int num=0;
						for (int k=0 ;k < this->Row;k++) {
							num += this->array[i][k] * a.array[k][j];
						}
						array[i][j] = num;
					}
				}
				return SArray((int**)array,this->Col,a.Row);
		} else {
			if (this->size <= 2 ) {
				return this->pMul(a);
			} else {
				bool isodd = false;// let below constrouct know it need to Subtract
				if ( (this->size &1) == 1 ) { //if this matrix size is odd
					cout<<"It's odd"<<endl;
					isodd = true;
					if (this->Istemp && this->array != NULL) { // for temporary Object

					} else { // for long standing Object
						this->squarify(this->size+1);
					}
				}
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
				int array[isodd ? newsize-1 : newsize][isodd ? newsize-1 : newsize];
				// if it is odd. it must be Subtract.

				for(int i = 0 ;i < original ; i++){
					for(int j = 0; j < original ; j++){
						array[i][j] = ANS[0].array[i][j];
					}
					for(int k = original; k < (isodd? newsize-1:newsize) ; k++){
						array[i][k] = ANS[1].array[i][k-original];
					}
				}
				//down
				for(int i = original; i < (isodd ? newsize-1 : newsize) ; i++){
					for(int j = 0; j < original ; j++){
						array[i][j] = ANS[2].array[i-original][j];
					}
					for(int k = original; k < (isodd ? newsize-1 :newsize) ; k++){
						array[i][k] = ANS[3].array[i-original][k-original];
					}
				}
				return SArray((int**)array,newsize);
			}
		}
    }
	void squarify(){
		//some time array need to squarify to match the counting size
		//can't using in temporary Object
		if(this->Istemp) return;
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
		//some time array need to squarify to match the counting size
		//can't using in temporary Object
		if(this->Istemp) return;

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

void mytest_matrix_equal(unsigned int num){
	int arr1[num][num],arr2[num][num];
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand();
			arr2[i][j] = arr1[i][j];
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	if(a == b) {
		cout << "right: Is equal"<<endl;
	}
	if(a == (b.getsub_new(0,0,2))) {
		cout << "false: Is not equal"<<endl;
	}else{
		cout << "right: sub Is not equal origin"<<endl;
	}
}
void mytest_matrix_getSub(unsigned int num){
	int arr1[num][num],arr2[num][num];
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand();
			arr2[i][j] = arr1[i][j];
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = a.getsub(0,0,2);
	a.Showsize();
	a.Show();
	b.Showsize();
	b.Show();
	SArray c = b.getsub(0,0,1);
	c.Showsize();
	c.Show();
}
void mytest_matrix_operator_equal(unsigned int num){
	int arr1[num][num],arr2[num][num];
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand();
			arr2[i][j] = rand();
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	SArray c = b.getsub(0,0,2);
	SArray d = a.getsub(0,0,2);
	SArray e = a.getsub(0,0,num);
	SArray h = b.getsub(0,0,2);
	a.Show();
	b.Show();
	c.Showsize();
	c.Show();
	d.Show();
	e.Show();
	if (a == a) { 
		cout<< "1. right : a is equal a"<<endl;
	} else {
		cout<< "1. error : a is not equal a"<<endl;
	}
	if (a == b) { 
		cout<< "2. error : a is equal b"<<endl;
	} else {
		cout<< "2. right : a is not equal b"<<endl;
	}
	if (a == c) { 
		cout<< "3. error : a is equal c"<<endl;
	} else {
		cout<< "3. right : a is not equal c"<<endl;
	}
	if (d == c) { 
		cout<< "4. error : d is equal c"<<endl;
	} else {
		cout<< "4. right : d is not equal c"<<endl;
	}
	if (e == a) { 
		cout<< "5. right : a is equal e"<<endl;
	}else {
		cout<< "5. error : a is not equal e"<<endl;
	}
	if (c == h) { 
		cout<< "6. right : c is equal h"<<endl;
	}else {
		cout<< "6. error : c is not equal h"<<endl;
	}

}
void mytest_matrix_add_equal(unsigned int num){
	int arr1[num][num],arr2[num][num];
	int max=1000,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	a.getsub(0,0,num).Showsize();
	SArray c = a.getsub(0,0,num);
	a.Show();
	b.Show();
	a+=b;
	a.Show();
	c.Show();
	b+=c;
	b.Show();
}
void mytest_matrix_sub_equal(unsigned int num){
	int arr1[num][num],arr2[num][num];
	int max=1000,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	SArray c = a.getsub(0,0,num);
	cout<<"a:"<<endl;
	a.Show();
	cout<<"b:"<<endl;
	b.Show();
	a-=b;
	cout<<"a-=b:"<<endl;
	a.Show();
	cout<<"c:"<<endl;
	c.Show();
	cout<<"b-=c:"<<endl;
	b-=c;
	b.Show();
	cout<<"c-=b:"<<endl;
	c-=b;
	c.Show();
}
void mytest_matrix_operator_add(unsigned int num){
	int arr1[num][num],arr2[num][num];
	int max=1000,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	SArray c = a+b;
	SArray e = b+a.getsub(0,0,num);
	SArray h = b.getsub(0,0,num)+a;
	SArray g = b.getsub(0,0,num)+a.getsub(0,0,num);
	cout<<"a: "<<endl;
	a.Show();
	cout<<"b: "<<endl;
	b.Show();
	cout<<"c: a+b "<<endl;
	c.Showsize();
	c.Show();
	cout<<"e: b+a.getsub(0,0,num)"<<endl;
	e.Showsize();
	e.Show();
	cout<<"h: b.getsub(0,0,num)+a"<<endl;
	h.Showsize();
	h.Show();
	cout<<"g: b.getsub(0,0,num)+a.getsub(0,0,num)"<<endl;
	g.Showsize();
	g.Show();
}
void mytest_matrix_pMul(unsigned int num){
	int arr1[num][num],arr2[num][num];
	int max=10,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	SArray c = a.pMul(b);
	cout<<"a: "<<endl;
	a.Show();
	cout<<"b: "<<endl;
	b.Show();
	cout<<"c: a.pMul(b) "<<endl;
	c.Showsize();
	c.Show();
	cout<<"e: b.pMul(a.getsub(0,0,num))"<<endl;
	SArray e = b.getsub(0,0,num).pMul(a.getsub(0,0,num));
	e.Showsize();
	e.Show();
	cout<<"h: b.getsub(0,0,num).pMul(a)"<<endl;
	SArray h = b.getsub(0,0,num).pMul(a);
	h.Showsize();
	h.Show();
	cout<<"g: b.pMul(a.getsub(0,0,num))"<<endl;
	SArray g = b.pMul(a.getsub(0,0,num));
	g.Showsize();
	g.Show();
	cout<<"g: b.getsub(0,0,2).pMul(a.getsub(1,1,2)) "<<endl;
	SArray L = b.getsub(0,0,2).pMul(a.getsub(1,1,2));
	L.Showsize();
	L.Show();
}
void mytest_matrix_operator_asssign(unsigned int num){
	int arr1[num][num],arr2[num][num];
	int max=1000,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	a.Show();
	SArray b = SArray((int**) arr2,num,num);
	b.Show();
	SArray c =a.getsub(0,0,2);
	c.Show();
	SArray d[4];
	cout<<"1"<<endl;
	d[0] = b.getsub(0,0,2);
	d[0].Show();
	cout<<"2"<<endl;
	d[1] = a.getsub(1,1,2);
	d[1].Show();
	cout<<"3"<<endl;
	d[2] = b.getsub(0,0,2) + a.getsub(1,1,2);
	d[2].Show();
	cout<<"4.==="<<endl;
	d[3] = b.getsub(0,0,2).pMul(a.getsub(1,1,2));
	cout<<"4.show"<<endl;
	d[3].Showsize();
	d[3].Show();
}

void mytest_matrix_operator_Mul(unsigned int num){

	//But now the answer is wrong
	int arr1[num][num],arr2[num][num];
	int max=20,min=0;
	for(int i =0;i<num;i++){
		for(int j=0;j<num;j++){
			arr1[i][j] = rand() % (max - min + 1) + min;
			arr2[i][j] = rand() % (max - min + 1) + min;
		}
	}
	SArray a = SArray((int**) arr1,num,num);
	SArray b = SArray((int**) arr2,num,num);
	cout<<"a: "<<endl;
	a.Show();
	cout<<"b: "<<endl;
	b.Show();
	// cout<<"d: b*a "<<endl;
	// SArray d = b*a;
	// d.Showsize();
	// d.Show();
	cout<<"a.pMul(b)"<<endl;
	SArray e = a.pMul(b);
	// e.Showsize();
	e.Show();
	cout<<"c: a*b "<<endl; // e and c must be equal
	SArray c = a*b;
	// c.Showsize();
	c.Show();
	
	
}


void mytest1(unsigned int num){
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
	cout<<"Time :" << duration << " seconds."<<endl;
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
void Main(void){
	int arg[4];
	scanf("%d %d %d %d\n",&arg[0],&arg[1],&arg[2],&arg[3]);
	int large=0;
	for(int i =0;i<4;i++){
		if(arg[i] > large) large = arg[i];
	}
	if(large == 0) return;
	if((large &1) == 1){
		large++;
	}
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
	
	F_matrix.squarify(large);
	S_matrix.squarify(large);
	(F_matrix*S_matrix).anti_Show(arg[3],arg[0]);
}

int main(void){
	srand( time(NULL) );
	int i=0;
	cin>>i;
	while( (i&1) == 1 ){
		cin>>i;
	}
	// mytest_matrix_getSub(i);
	// mytest_matrix_equal(i);
	// mytest_matrix_operator_equal(i);
	// mytest_matrix_add_equal(i);
	// mytest_matrix_sub_equal(i);
	// mytest_matrix_pMul(i);
	// mytest_matrix_operator_asssign(i);
	mytest_matrix_operator_Mul(i);
}	
