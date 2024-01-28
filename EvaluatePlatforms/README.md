# Introduction
In the realm of computing, where diverse platforms offer parallelism, a thorough evaluation becomes imperative. Testing these platforms with various datasets is a crucial step in discerning their capabilities. This multifaceted assessment involves subjecting each platform to rigorous scrutiny to analyze their performance under distinct conditions. Finally, by meticulously gauging the runtime intricacies, one can make an informed decision on the optimal platform for specific purposes. This comprehensive evaluation ensures that the chosen platform aligns seamlessly with the intended tasks, maximizing efficiency and performance in parallel processing scenarios.

# Platforms Evaluated: 
Cuda, OpenMP, MPI with Cluter of Servers, Java, C++ with Multi threads.

# Preparing Input:
1. For each size of input, one input file will be generated, and the exact file will be tested to 5 different algorithms to make them feel the same completely to compare proper runtime.
2. Before running every algorithm, generating3 file will be run once.
   ./generate3 10000 2 4
   
   Here, the first argument is the size of the array, and the next values are the range of integers that the array will have. 2 is the lower bound and 4 is the upper bound. Therefore, this array will have 10,000 integers and all of them are between 2 and 4. Also, the number of serial counts is taken to compare with parallel algorithms. 
Here, 3256 number of times the three is in the array.
3. Preparing MPI with 4 nodes connected in the host file.

# Running the codes:
Please find the 5 parallel codes inside the Codes directory and execute the following instructions to execute the codes. Assuming each executible will run 16 threads and 10,000 of array size.

C++:<br>
g++ ep_c_threads.cpp -o thread<br>
./cthread 16 10000

Java:<br>
javac EvaluatePerformanceJavaThreads.java<br>
java EvaluatePerformanceJavaThreads 16 10000

MPI:<br>
mpirun -n 16 -hostfile host_file --mca routed direct ./ep_mpi 10000

OpenMP:<br>
g++ ep_c_openMP.cpp -o openmp -fopenmp <br>
./openmp 16 10000

Cuda:<br>
nvcc ep_c_cuda.cu -o cuda <br>
./cuda 10000<br>
[Note: in Cuda, maximum possible blocks and grids are used to process the input]

# Analyzing Output Graphs:
Graph 1: When the array size is 10k, the same array is run with 4 algorithms:  Cpp, Java, MPI and OpenMP. Cuda is not comparable with them and that is why, to make a fair comparison, it is excluded.

As we can see MPI and Java threads are performing badly because MPI works with an Inter-Process Communication messaging technique in which process communication always adds overhead. C-threads and OpenMP are performing a way better.
![Comparison of 10k dataset with 4 algorithms and their execution time](https://github.com/AbdurRazzakRana/ParallelProgramming/blob/main/EvaluatePlatforms/Output_Graphs/10k_Data_4_Algo_Comp.png)


Graph 2: Compares runtime of same 4 algorithms with 100k dataset. When the data set increased, MPI’s execution time became reduced and closer to the C-threads or OpenMP runtime. As we can see C-threads and OpenMP are performing better regardless of the scenarios whether the data size is big or small.
![Comparison in execution time of 100k dataset with 4 algorithms](https://github.com/AbdurRazzakRana/ParallelProgramming/blob/main/EvaluatePlatforms/Output_Graphs/100K_Data_4_Algo_Comp.png)


Graph 3: Let us compare them with CUDA performance. In this picture, when the dataset increases a lot, then a fixed number of parallelisms like c-threads cannot offer good performance though it is more optimized and performs better than other fixed-size parallel platforms. Cuda shows much improvement as it is running with a high number of threads such as 768 blocks and 96 grids. Although there is some communication overhead involved for the inclusion of such high threads when the dataset is super high, these communication costs are negligible, and involving a high number or parallelism is effective in that case.
![Comparison in execution time between Cuda and Optimized CPP over the dataset change](https://github.com/AbdurRazzakRana/ParallelProgramming/blob/main/EvaluatePlatforms/Output_Graphs/Cuda_vs_OptimizedC.png)


