/**
 * Instructor Diego Jimenez (diego.jimenez@ulead.ac.cr)
 * Cilk Plus parallel Conway's Game of Life.
 */

#include <cstdio>
#include <cstdlib>
#include <cilk/cilk.h>
#ifdef CILK_SERIALIZE
#include <cilk/cilk_stub.h>
#endif
#include "timer.h"
#include "io.h"

// Main method      
int main(int argc, char* argv[]) {

    int N,M;
    int **World;
    int **a;

    double elapsedTime;
    int checkDocument = 0;

    // checking parameters
    //  World!";
    if (argc != 3 && argc != 4) {
        cout << "Parameters: <N> <M> [<file>]" << endl;
        return 1;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);

    // allocating matrices

    World = new int*[N];
    a = new int*[N];
    for (int i=0; i<N; i++){
        World[i] = new int[N];
        a[i] = new int[N];
    }



    // reading files (optional)
    if(argc == 4){
        readMatrixFile(World,N,argv[3]);
    }else{
        for (int i = 0; i < N; ++i)
        {cilk_for( int j = 0;  j < N; ++j)
            {World[i][j] = 0 + rand() % (2);}
        }
    }


    // starting timer
    timerStart();

    // YOUR CODE GOES HERE

    int alive = 1;

    for(int p=0;p<M;p++){

        cilk_for(int fila=0;fila<N;fila++){

            for(int columna=0;columna<N;columna++){
                //Evaluation of cell

                int alive_count = 0;

                //Primer vecino
                if(fila>0 && columna>0){
                    if(World[fila-1][columna-1]==alive){
                        alive_count++;
                    }
                }
                //Segundo vecino
                if(columna>0){
                    if(World[fila][columna-1]==alive){
                        alive_count++;
                    }
                }
                //Tercer vecino
                if(fila<N-1 && columna > 0){
                    if(World[fila+1][columna-1]==alive){
                        alive_count++;
                    }
                }
                //Cuarto vecino
                if(fila>0){
                    if(World[fila-1][columna]==alive){
                        alive_count++;
                    }
                }
                //Quinto vecino
                if(fila<N-1){
                    if(World[fila+1][columna]==alive){
                        alive_count++;
                    }
                }
                //Sexto vecino
                if(fila>0 && columna<N-1){
                    if(World[fila-1][columna+1]==alive){
                        alive_count++;
                    }
                }
                //Septimo vecino
                if(columna<N-1){
                    if(World[fila][columna+1]==alive){
                        alive_count++;
                    }
                }
                //Octavo vecino
                if(fila<N-1 && columna<N-1){
                    if(World[fila+1][columna+1]==alive){
                        alive_count++;
                    }
                }

                //Rules of the game
                if((World[fila][columna]==1) && (alive_count<2 || alive_count>3)){
                    a[fila][columna] = 0;
                }
                else if(World[fila][columna]==1 && (alive_count==3)){
                    a[fila][columna] = 1;
                }
                else if(World[fila][columna]==0 && alive_count==3){
                    a[fila][columna]=1;

                }else{a[fila][columna] = World[fila][columna];}			       		
            }

        }
        World = a;
        a = new int *[N];
        for (int i = 0; i < N; i++) {
            a[i] = new int[N];
        }
    }
    // testing the results is correct
    if(argc == 4){
        printMatrix(World,N);
    }

    else{
        printMatrix(World,N);
    }

    // stopping timer
    elapsedTime = timerStop();

    cout << "Duration: " << elapsedTime << " seconds" << std::endl;

    // releasing memory
    for (int i=0; i<N; i++) {
        delete [] World[i];
    }
    delete [] World;


    return 0;
}
