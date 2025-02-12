#include<iostream>
#include<vector>

using namespace std;

class maze{
private:
	int N;
	vector<vector<int>> board;

	void init(int nob){
		for(int i=0;i<nob;i++){
			int x,y;
			do{
				x=rand()%N;
				y=rand()%N;
			}while(board[x][y] || (!x&&!y) || (x==N-1 && y==N-1));
			board[x][y]=1;
		}
	}

public:
	maze(int N,float pob){
        this->N=N;
        board=vector<vector<int>>(N,vector<int>(N,0));
        init((int)N*N*pob);
    }
	~maze(){};


	void print(){
		for(auto row:board){
        	for(auto col:row)
            	printf("%2d ",col);
        	cout<<endl;
   		}
   		cout<<endl;
	}
};

int main(){
	srand(time(NULL));
	maze mz(10,.3);
	mz.print();
}