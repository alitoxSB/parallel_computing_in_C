/**
 * LEAD University
 * Data Science Program
 * BCD-9218: Parallel and Distributed Computing
 * Instructor Diego Jimenez, Eng. (diego.jimenez@ulead.ac.cr)
 *  OpenMP parallel shear sort.
 */

#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"

#define MAX_VALUE 10000

// Shear sort function
//code here

int N, M;
int **A;

void rowsort(int i){
   	#pragma omp parallel for reduction(+:sum) private(x) 
	for(int j=0;j<N-1;j++){
       		for(int k=0;k<N-j-1;k++){
          		if(A[i][k]>A[i][k+1]){
                	int temp=A[i][k];
                	A[i][k]=A[i][k+1];
                	A[i][k+1]=temp;
            	}
       	}
    }
}
void rowrevsort(int i){
    #pragma omp parallel for reduction(+:sum) private(x)
    for(int j=0;j<N-1;j++){
        for(int k=0;k<N-j-1;k++){
            if(A[i][k]<A[i][k+1]){
                int temp=A[i][k];
                A[i][k]=A[i][k+1];
                A[i][k+1]=temp;
            }
        }
    }
}
void colsort(int i){
    for(int j=0;j<N-1;j++){
        for(int k=0;k<N-j-1;k++){
            if(A[k][i]>A[k+1][i]){
                int temp=A[k][i];
                A[k][i]=A[k+1][i];
                A[k+1][i]=temp;
            }
        }
    }
}
void shear_sort(int **A, int M, int N){
    //cin>>n;
    for(int j=0;j<N;j++){
        for(int k=0;k<N;k++){   
		A[j][k]=A[j][k];
        }
    }

    M=(int)ceil(log2(N));
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(j%2==0){
		cout << "debug1" << endl;
                rowsort(j);
            }else{
		cout << "debug" << endl;
                rowrevsort(j);
            }
        }
        for(int j=0;j<N;j++) colsort(j);
            cout<<endl;
        }
    for(int j=0;j<N;j++){
        if(j%2==0){
        rowsort(j);
        }else{
            rowrevsort(j);
        }
    }
}
 
// Main method
int main(int argc, char* argv[]) {
	//int N, M;
	//int **A;
	double elapsedTime;

	// checking parameters
	if (argc != 2 && argc != 3) {
		cout << "Parameters: <N> [<file>]" << endl;
		return 1;
	}
	N = atoi(argv[1]);
	M = (int) sqrt(N);
	if(N != M*M){
		cout << "N has to be a perfect square!" << endl;
		exit(1);
	}

	// allocating matrix A
	A = new int*[M];
	for (int i=0; i<M; i++){
		A[i] = new int[M];
	}

	// reading files (optional)
	if(argc == 3){
		readMatrixFile(A,M,argv[2]);
	} else {
		srand48(time(NULL));
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				A[i][j] = lrand48() % MAX_VALUE;
			}
		}
	}

	// starting timer
	timerStart();
	// calling shear sort function
	shear_sort(A,M,N);

	// testing the results is correct
	if(argc == 3){
		printMatrix(A,M);
	}

	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds" << std::endl;

	// releasing memory
	for (int i=0; i<M; i++) {
		delete [] A[i];
	}
	delete [] A;

	return 0;
}
