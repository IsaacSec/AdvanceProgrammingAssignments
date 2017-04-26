#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct _thread_data{
  int id;
  int cols;
  int rows;
  int **matrixA;
  int **matrixB;
  int **matrixC;
  int diagonal;
}thread_data;

void peer_work (void *arg){
  thread_data *data = (thread_data *) arg;
  int **matrixA = (data->matrixA);
  int **matrixB = (data->matrixB);
  int **matrixC = (data->matrixC);
  int id = data->id;
  int size = data->rows;

  for (int j=0; j<size; j++){
      int result = 0;
      for (int i=0; i<size; i++){
          result += matrixA[id][i] * matrixB[i][j];
      }
      matrixC [id][j] = result;
  }
}

void print_matrix( int **matrix, int size ) {
	int row;
	int col;
	/*
 	* We loop through the matrix given to us and we print it out in the correct format
 	**/
	for(row = 0; row < size; ++row) {
		printf("[ ");
		for(col = 0; col < size; ++col) {
			printf(" %d ", matrix[row][col]);
		}
		printf(" ]\n");
	}
	printf("\n");
}

int main(){

  int size = 3;

  int **matrixA;
  int **matrixB;
  int **matrixC;

  matrixA = malloc(size * sizeof(int *));
  matrixB = malloc(size * sizeof(int *));
  matrixC = malloc(size * sizeof(int *));

  for(int i=0 ; i<size ; i++){
    matrixA[i] = malloc(size * sizeof(int *));
    matrixB[i] = malloc(size * sizeof(int *));
    matrixC[i] = malloc(size * sizeof(int *));
  }
  for(int row=0 ; row<size ; row++){
    for (int col = 0; col<size; col++){
      matrixA[row][col] = row*size+col+1;
    }
  }
  for(int row = 0; row<size ; row++){
    for (int col = 0; col<size; col++){
      matrixB[row][col] = 2;
    }
  }
  for(int row = 0; row<size ; row++){
    for (int col = 0; col<size; col++){
      matrixC[row][col] = 0;
    }
  }

  pthread_t threads[size];
  thread_data * data = (thread_data *) malloc(sizeof(thread_data));

  data-> cols = size;
  data-> rows = size;
  data-> diagonal = 0;
  data-> matrixA = matrixA;
  data-> matrixB = matrixB;
  data-> matrixC = matrixC;

  for (int i = 0; i < size ; i++) {
    data-> id = i;
    int code = pthread_create(&threads[i],NULL,(void *)peer_work,(void *)data);
    if(code){
      printf("[ERROR] at pthread_create() with CODE->(%d)\n", code);
    }
    printf("[Thread]  #%d\n", i);
  }

  for(int i = 0; i < size ;i++){
    int code = pthread_join(threads[i],NULL);
    if(code){
      printf("[ERROR] pthread_join() with CODE->(%d)\n", code);
    }
    printf("[JOIN] thread #%d \n",i);
  }

  print_matrix(matrixC,size);

  return EXIT_SUCCESS;
}
