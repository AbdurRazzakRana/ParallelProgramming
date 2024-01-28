#include <stdio.h>
#include <stdlib.h>
#include <device_launch_parameters.h>
#include <cuda_runtime.h>

// CUDA kernel to count occurrences of the value 3 in the chunk of array
__global__ void count3s_kernel(const int* array, size_t size, int* result) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int localCount = 0;

    for (int i = tid; i < size; i += blockDim.x * gridDim.x) {
        if (array[i] == 3) {
            localCount++;
        }
    }

    atomicAdd(result, localCount);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Argument is not proper");
        return 1;
    }
    // Fetching the array length from argument
    int arraySize = atoi(argv[1]);

    clock_t start, end;
    double runtime;
    // timer starts
    start = clock();

    // accessting the file pointer to read
    FILE *fp;
    if ((fp = fopen("input.txt", "r")) == NULL) {
      fprintf(stderr, "Error: Unable to open the file.\n");
      return 1;
    }
    int x, actualCount=0, i;
    // reading the values from file and keeping them in host array.
    int* hostArray = new int[arraySize];
    for(i=0; i<arraySize; i++) {
        fscanf(fp,"%d", &x);
        hostArray[i] = x;
        if(x==3) actualCount++;
    }
    // allocating memory for the gpu threads and their local result 
    int* deviceArray;
    int* deviceResult;
    cudaMalloc((void**)&deviceArray, arraySize * sizeof(int));
    cudaMalloc((void**)&deviceResult, sizeof(int));

    // Copy array from host to device
    cudaMemcpy(deviceArray, hostArray, arraySize * sizeof(int), cudaMemcpyHostToDevice);

    // Initialize result on the device
    cudaMemset(deviceResult, 0, sizeof(int));

    // finding the maximum block size in order to ensure maximum parallilism.
    int maxBlockSize, GridSize;
    cudaOccupancyMaxPotentialBlockSize(&GridSize, &maxBlockSize, count3s_kernel, 0, 0);
    printf("Block used: %d\n", maxBlockSize);
    printf("Grid used: %d\n", GridSize);

    // Launch CUDA kernel to count occurrences of '3' in deviceArray
    count3s_kernel<<<GridSize, maxBlockSize>>>(deviceArray, arraySize, deviceResult);

    // Copy result back to host
    int hostResult;
    cudaMemcpy(&hostResult, deviceResult, sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Count from CUDA: %d\n", hostResult);
    
    // timer end
    end = clock();
    runtime = ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Total Execution time: %f ms\n", runtime);

    // Cleanup
    delete[] hostArray;
    cudaFree(deviceArray);
    cudaFree(deviceResult);
    return 0;
}