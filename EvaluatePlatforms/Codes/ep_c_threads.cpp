#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <fstream>
#include <chrono>
#include <mutex>
using namespace std;

struct padded_int {
int value;
char padding[60];
};


int t, length, count;

mutex m;

void count3s_C_thread(int thread_number, vector<int>& array_3)
{
    // thread local counter with padding
    padded_int countLocal;
    countLocal.value = 0;
    
    int length_per_thread = ::length / ::t;
    int start = thread_number * length_per_thread;
    // loop through the local indexes and cound the 3's
    for (int i = start; i < start + length_per_thread; i++)
    {
        if (array_3[i] == 3)
        {
            countLocal.value ++;
            
        }
    }
    // updating the global values with local counts with lock to avaid racing
    m.lock();
    ::count+=countLocal.value;
    m.unlock();
}

// This method will initiate all the threads
void count3s_C_By_Thread_Func(vector<int>& array_3, int array_len, int threadNumber){
    // initializing the global vales
    vector<thread> threads;
    ::count = 0;
    ::t = threadNumber;
    ::length = array_len;
    // creating the threads
    for (int thread_number = 0; thread_number < t; thread_number++){
        threads.emplace_back(thread(count3s_C_thread, thread_number, ref(array_3)));
    }
    // waiting for child threads to finish and join back
    for (thread &thread : threads){
        thread.join();
    }
    // showing the output
    cout << "Total Count of 3 from C-Threads: " << ::count << endl;
    
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <number of threads>" << endl;
        return 1;
    }

    //fetching the command line arguments
    int thread_num = stoi(argv[1]);
    int array_len = stoi(argv[2]);
    
    // starting the timer
    auto currentTime_start = chrono::system_clock::now();
    auto millis_start = chrono::duration_cast<chrono::milliseconds>(currentTime_start.time_since_epoch()).count();

    // taking the file pointer access to read
    FILE *fp;
    if ((fp = fopen("input.txt", "r")) == NULL) {
      fprintf(stderr, "Error: Unable to open the file.\n");
      return 1;
    }
    int x, actualCount=0;
    vector<int> array_3;
    // reading the file and getting the integer values of the array
    for(int i=0; i<array_len; i++) {
        fscanf(fp,"%d", &x);
        array_3.push_back(x);
        if(x==3) actualCount++;
    }
    // actual count 3 by serial calculation
    cout << "Actual Count of 3 by serial: "<< actualCount<<endl;
    count3s_C_By_Thread_Func(array_3, array_len, thread_num);

    // end the timer and calculate runtime
    auto currentTime_end = chrono::system_clock::now();
    auto millis_end = chrono::duration_cast<chrono::milliseconds>(currentTime_end.time_since_epoch()).count();
    auto execTime = millis_end - millis_start;
    cout << "Total Execution time: "<<execTime <<" ms"<< endl;
    return 0;
}
