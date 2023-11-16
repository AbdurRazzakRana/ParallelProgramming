#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <fstream>
#include <chrono>
#include <mutex>
#include <stdexcept>
#include <chrono>
using namespace std;

struct padded_int {
int value;
char padding[60];
} private_count[10];

vector<int> array_3;
int t=10, length, count=0;
const int MAX_RANGE = 4;
// if user does not decide the array size, by default it will 10^7
int max_array_size=10000000;
mutex m;

// Each thread will run this method and will count 3 of its local index portion
void count3s_thread(int thread_number) {
    // Necessary calculation to identify exact working indexes for one thread
    int length_per_thread = length / t;
    int start = thread_number * length_per_thread;

    for (int i = start; i < start + length_per_thread; i++)
    {
        if (array_3[i] == 3)
        {
            // localling calculating the count with padding to avoie cache granularity
            private_count[thread_number].value++;
        }
    }
    // critical block hence synchronized with mutex
    m.lock();
    count+=private_count[thread_number].value;
    m.unlock();
}

int main(int argc, char *argv[])
{
    vector<thread> threads;
    // will take an array of 0-4 based on user given input size
    if (argc >=2 ){
        max_array_size = std::stoi(argv[1]);
    }
    random_device rd;
    // Use the random_device to seed the Mersenne Twister engine
    mt19937 gen(rd());
    // Create a uniform distribution for the specified range
    uniform_int_distribution<> distribution(0, MAX_RANGE);

    int randomNumber;
    // taking input to the array by generating random number from 0-4 inclusive
    for(int i=0;i<max_array_size;i++){
        randomNumber = distribution(gen);
        array_3.push_back(randomNumber);
    }


    auto start = chrono::high_resolution_clock::now();

    length = array_3.size();
    // creating threads and passing the count3s_thread function to work on separately
    for (int thread_number = 0; thread_number < t; thread_number++)
    {
        threads.emplace_back(thread(count3s_thread, thread_number));
    }
    // parent thread has to wait until all child thread finished
    for (thread &thread : threads)
    {
        thread.join();
    }

    //Edge Case Management:
    // for example array size is 108 and max thread is 10
    // So each thread will take care of 10 elements starting from 0-9, 10-19, and so on.
    // However, indexes from 100 to 107 will not be taken care of any threads
    // that edge case we need to handle manually in the below if case.
    int soFarChecked = (length / t) * t;
    int locCount = 0;
    if (soFarChecked < length){
        for(int i=soFarChecked;i<length;i++){
            if (array_3[i]== 3){
                locCount++;
            }
        }
    }
    count+=locCount;


    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Array Size: "<<max_array_size<<endl;
    cout << "Total Count of 3: " << count << endl;
    cout << "Parallel counting time without OMP: " << duration.count() /1000<< " ms" << endl;
    
    return 0;
}