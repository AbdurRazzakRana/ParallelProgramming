#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int globalCount;

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("Argument Error\n");
    return 1;
  }
  // Fetching the length from arguments
  int length = atoi(argv[1]);
  
  clock_t start, end;
  double runtime;
  // starting the time
  start = clock();
    
  int world_size;
  int myId, value, numProcs, tag = 101;
  
  // setting up the environemnt to run MPI
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myId);

  // preparing the subarray for each threads
  int length_per_process=length/numProcs;
  int *myArray=(int *) malloc(length_per_process*sizeof(int));

  FILE *fp;
  int p, i,j,k,l;

  if (myId == 0){
    // the parent thread will read the file for the rest of the child thread
    if ((fp = fopen("input.txt", "r")) == NULL) {
      fprintf(stderr, "Error: Unable to open the file.\n");
      return 1;
    }
    for(p=0; p<numProcs-1; p++) {
      for(i=0; i<length_per_process; i++) {
        fscanf(fp,"%d", myArray+i);
      }
      // sending the sub array to each child thread.
      MPI_Send(myArray, length_per_process, MPI_INT, p+1, tag, MPI_COMM_WORLD);
    }
    // processing some part for the parent thread itself.
    for(i=0; i<length_per_process; i++) {
        fscanf(fp,"%d", myArray+i);
    }
  }
  else {
    // will receive the responses from the child threads.
    MPI_Recv(myArray, length_per_process, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
  }

  //thread local part
  int myCount = 0;
  for(i=0; i<length_per_process; i++) {
    if(myArray[i]==3) {
      myCount++; 
    }
  }
  // doing the reduce operation to calculate all the sum of 3 into global count.
  MPI_Reduce(&myCount, &globalCount, 1, MPI_INT, MPI_SUM, 0 , MPI_COMM_WORLD);

  if(myId==0) {
    // ending the execution time.
    end = clock();
    printf("Count of 3 from MPI: %d\n", globalCount);
    runtime = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Total Execution time: %f ms\n", runtime);
  }
  MPI_Finalize();
}