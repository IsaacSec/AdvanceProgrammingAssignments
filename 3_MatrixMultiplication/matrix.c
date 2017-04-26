#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _matrix{
  int id;
  int cols;
  int rows;
  int **matrix;
}Matrix;

int main(){

  int A[][3] =  {{1,2,3},{4,5,6},{7,8,9}};
  int B[][3] =  {{2,0,0},{0,2,0},{0,0,2}};
  Matrix *m  = (Matrix *) malloc (sizeof (Matrix) );

  m->id   = 0;
  m->cols = 3;
  m->rows = 3;
  m->matrix = &A[0][0];
    /*int aj=3, ai=3;
    int bj=3, bi=3;

    int matrixC[bj][ai];

    int matrixA[][3] =  {{1,2,3},{4,5,6},{7,8,9}};
    int matrixB[][3] =  {{2,0,0},{0,2,0},{0,0,2}};

    // Normal process
    for (int k=0; k<aj; k++){
        for (int j=0; j<bi; j++){
            int result = 0;
            for (int i=0; i<ai; i++){
                result += matrixA[k][i] * matrixB[i][j];
            }
            printf("%d ",result);
        }
        printf("\n");
    }
    */
    return EXIT_SUCCESS;
}

/*

For this assignment you are required to implement a parallel version of the matrix
multiplication algorithm. Your program should create N child threads that compute the
multiplication of row i X column j of two square matrices and then send their results to
the parent thread using thread synchronization.

The parent thread assembles the data and prints out the resulting matrix. Make sure that
the parent thread waits for its child  threads.

Do not make any assumptions on the matrix size (i.e. this should be a constant defiined
at compile time or an input at runtime). Although, you could write the application without
a critical section make sure you use locks (either conditional or not) to access any shared
data structures.

Also one of the child threads must compute the sum of the elements of the main diagonal
(or the diagonal for square matrices). This last requirement will need for you to synchronize
with the other threads.

*/
