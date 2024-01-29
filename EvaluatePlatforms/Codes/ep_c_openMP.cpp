/*
Author: Abdur Razzak
Date: Dec 10, 2023
Course: Parallel Programming
Input-output: This OpenMP program will take input the number
    of parallel threads and input size from file. Then the threads
    will calculate how many 3 they have among the portion of array
    they received. At the end it prints the count of 3 and the
    execution time.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <omp.h>
using namespace std;

int count;

// This method will run OpenMP parallilism on array_3 to find the count of 3
void count3s_usingOpenMP(vector<int>& array_3, int thread_numbers, int array_len){
    int i, count_p;
    // setting up the thread number
    omp_set_num_threads(thread_numbers);
    #pragma omp parallel shared(array_3, count, array_len) private(count_p, i) 
    {
        // thread local area to find the 3 of local part
        count_p = 0;
        #pragma omp for
        for(i=0; i<array_len; i++){
            if(array_3[i]==3){
                count_p++;
            }
        }
        #pragma omp critical
        {
            // adding back to the global sum
            count+=count_p;
        }
    }
    cout << "Count of 3 from OpenMP: " << count << endl;

}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <number of threads>" << endl;
        return 1;
    }

    //Accessing command line arguments
    int thread_num = stoi(argv[1]);
    int array_len = stoi(argv[2]);
    
    // staring the timer 
    auto currentTime_start = chrono::system_clock::now();
    auto millis_start = chrono::duration_cast<chrono::milliseconds>(currentTime_start.time_since_epoch()).count();

    // accessing the file pointer to read the values
    FILE *fp;
    if ((fp = fopen("input.txt", "r")) == NULL) {
      fprintf(stderr, "Error: Unable to open the file.\n");
      return 1;
    }
    int x, actualCount=0;
    // reading the values from the file
    vector<int> array_3;
    for(int i=0; i<array_len; i++) {
        fscanf(fp,"%d", &x);
        array_3.push_back(x);
        if(x==3) actualCount++;
    }
    
    cout << "Actual Count of 3 by serial: "<< actualCount<<endl;
    count = 0;
    count3s_usingOpenMP(array_3, thread_num, array_len);

    // taking the end time and calculating the execution time
    auto currentTime_end = chrono::system_clock::now();
    auto millis_end = chrono::duration_cast<chrono::milliseconds>(currentTime_end.time_since_epoch()).count();
    auto execTime = millis_end - millis_start;
    cout << "Total Execution time: "<<execTime <<" ms"<< endl;

    return 0;
}
