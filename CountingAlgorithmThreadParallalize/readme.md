Problem Statement:

Apply thread level parallalism in counting 3's from an array. Simple array will not generate enough race condition and also impact of parallalism will not be fully understood and hence array has to be big enough. The goal is to reduce execution time to a maximum level and achieve speed up over sequential execution.

Step-1: Implementing count 3 algorithm on simple array [Count3_simpleArray_4_thread.cpp]
As there are only 16 inputs on the array, each thread will get 4 subparts of the array to count 3. For example, thread 1 will get the first 4, thread 2 will get the next 4, and so on. However, the task load for each processor is too small.

Step-2: Big array without mutex [Count3_big_array_4_thread_withoutMutex.cpp
Different threads will access the global memory count at various times with different values and hence, different runs of this program will produce different count numbers which is an inconsistent result.

Step-3: Adding mutex [Count3_8_thread_with_mutex.cpp]
After implementing the mutex, the total count of 3 is now consistent in different runs of the program which is 2796832. As each thread is accessing the shared variable count each time of having a 3 and updating the count value is being synchronized, there is a lot of thread overhead time. As thread numbers increase, the mutex synchronized overhead is also increased.

Step-4: Implementing thread local count and add to the global count at the end [Count3_8_thread_local_count]
As each thread is accessing the shared variable “count” just once at the end, the thread execution time is reduced now to nearly 90 on average. However, the threads are still taking more time than the serial execution. It is because of cache line granularity as each time 2 on-chip processors continuously communicate with each other and discard values in L1 on-chip cache.

Step-5: Add padding to avoid cache line granularity and reduce on-chip communication for L1 discarding [Count3_8_thread_Add_padding_to_avoid_Cache_Line_Granularity.cpp]
As on-chip communication is reduced for L1 cache updating, a massive improvement can be found when the thread is increased.


At the end of gradual improvement until step-5, 7.1 speed up can be achieved by the parallelism.
