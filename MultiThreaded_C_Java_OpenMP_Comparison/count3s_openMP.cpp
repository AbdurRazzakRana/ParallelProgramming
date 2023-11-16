#include<iostream>
#include<vector>
#include <random>
#include <chrono>
#include <omp.h>
using namespace std;

int max_array_size = 1000000;
const int MAX_RANGE = 4;
int number_of_threads, length;
vector<int> arr;

// the funtion that will initiatite parallel processes
int count3s() {
    int i, count_p;
    int count=0;
    //defining parallel section
    #pragma omp parallel shared(arr, count, max_array_size) private(count_p, i)
    {
        count_p=0;
        #pragma omp for
        for(i=0; i<max_array_size; i++) {
            if(arr[i]==3) {
                count_p++;
            }
        }
        // critical section as the count is the global varaible. 
        // Updating that global value requires synchronized access.
        #pragma omp critical 
        {
            count+=count_p;
        }
        // Just to see how many threads are being used by the system.
        #pragma omp single
        {
                number_of_threads = omp_get_num_threads();
                // cout<<number_of_threads<<endl;
        }
    }
    return count;
}

int main (int argc, char *argv[]){
    // making the user input as the size of array
    if (argc >= 2){
        max_array_size = stoi(argv[1]);
    }
    random_device rd;
    // Use the random_device to seed the Mersenne Twister engine
    mt19937 gen(rd());
    // Create a uniform distribution for the specified range
    uniform_int_distribution<> distribution(0, MAX_RANGE);

    int randomNumber;
    // preparaing the the array with values 0-4 inclusive
    for(int i=0;i<max_array_size;i++){
        randomNumber = distribution(gen);
        arr.push_back(randomNumber);
    }

    auto start = chrono::high_resolution_clock::now();
    // calling the count3s method and parallilism begin from threre.
    int answerCount = count3s();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout<<"Array Size: "<<max_array_size<<endl;
    cout<<"Number of threes: "<<answerCount<<endl;
    // Print the execution time
    cout << "Parallel counting time: " << duration.count() /1000<< " ms" << endl;

    return 0;
}