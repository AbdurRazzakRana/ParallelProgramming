Problem Statement:

Apply thread level parallalism in counting 3's from an array. Simple array will not generate enough race condition and also impact of parallalism will not be fully understood and hence array has to be big enough.

Step-1: Count3_simpleArray_4_thread.cpp

As there are only 16 inputs on the array, each thread will get 4 subparts of the array to count 3. For example, thread 1 will get the first 4, thread 2 will get the next 4, and so on. However, the task load for each processor is too small.
