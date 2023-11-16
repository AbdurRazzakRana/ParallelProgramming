The Aim of this task is to run the counting 3 algorithm from a very large dynamic input size of array running with three different parallelisms: Multi-threaded C++, Multi-threaded Java, and OpenMP. The performance comparison metric is the execution time.

Besides the code also take care of Edge Management. For example, an array has 108 elements and 10 threads are working on it count the 3s. The allocation process is each thread will have 108/10 = 10 elements. That means 10*10 indexes are being checked by the threads and the last 8 elements is not being covered by any threads.


# 1. C++ code without OpenMP:
From the previous assignment, we did thread level parallelization with local count and adding to the global count at the end with mutex. We also have taken care of cache granularity by using padding. In number one, we are using that code to compare with others.

Running the code from terminal: 
g++ -std=c++11 -pthread count3s_withoutOMP.cpp -o count3cpp 
./count3cpp 10008

Output: Total execution time is 1 millisecond for 10008 array size. And average of 5 runs is 1ms as well.


# 2. Count 3s code in C++ with OpenMP:
This time we added OpenMP code just like Figure 6.28. Time Calculation and adding the input size for array is also implemented here. However, openMP does not require edge case management like the abovementioned scenario because system automatically allocate required threads and all the cases are covered here. No worries of some indexes being leftover. Here is a screenshot if all the indexes are 3 and an uneven array size 107 is also counted in full of no loss.

Running the code:
g++ Count3s_OpenMP.cpp -o count3_openMP -fopenmp
./count3_openMP 10008

Output: Total execution time taken is 38 ms and after 5 runs, the average time for parallelism is 39.6 ms.


# 3. Multi-threading with Java:
Parallelization in java is implemented here with concurrency following the figure 6.27 in the
book. 10 different threads are created to calculate the portion of array.

Running the Code:
javac CountThrees.java
java CountThrees 10008

Output: Execution time takes 17ms, however, average of 5 times run for the same size of array 10008 is 22.6 ms

# Comparative Analysis:
For every case, 1008 array size is processed to keep the standard size of processing for every technique.
Threaded C++ code with Padding to avoid Cash Granularity: Average time 1 milliseconds.
OpenMP C++ code: Average time 39.6 milliseconds
Multithreaded Java Code: Average time 22.6 milliseconds
As we can see, threaded C++ with padding is fastest than any other else.

# Conclusion:
From the best of my understanding and analysis, OpenMP is taking more time because it allocates the number of processes at runtime and hence sometimes, there is high chance of assigning more threads than required. As a result, more thread communication overhead is added with it. However, the positive side is, it’s easy to write parallel code in OpenMP with just few lines.
In java implementation, I think it is the usual time if each thread accesses the global memory count once when its own portion is locally calculated. However, number of threads are assigned based on necessity makes less thread communication and hence a little bit faster than OpenMP.
On the other hand, most optimized implementation among these three is C++ multithreading with padding. The padding helps to reduce communication between 2 processes under 1 L1 cache. L1 cache is hit 80% of the time in overall program memory.
Hence, optimizing L1 cache coherency by adding padding is boosting the application overall time. Therefore, this the most precise implementation for count 3 algorithm.