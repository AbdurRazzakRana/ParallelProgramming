#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <fstream>
#include <chrono>
#include <mutex>
using namespace std;

vector<int> array_3;
int t, length, count;
mutex m;

void count3s_thread(int thread_number)
{
    auto currentTime_start = chrono::system_clock::now();
    auto millis_start = chrono::duration_cast<chrono::milliseconds>(currentTime_start.time_since_epoch()).count();

    int length_per_thread = length / t;
    int start = thread_number * length_per_thread;

    for (int i = start; i < start + length_per_thread; i++)
    {
        if (array_3[i] == 3)
        {
            m.lock();
            count++;
            m.unlock();
        }
    }
    auto currentTime_end = chrono::system_clock::now();
    auto millis_end = chrono::duration_cast<chrono::milliseconds>(currentTime_end.time_since_epoch()).count();
    auto execTime = millis_end - millis_start;
    cout << "Thread: " << thread_number << ", execution time:" << execTime << endl;
}
void read_generated_random_numbers()
{
    ifstream inputFile("integers.txt");
    int number;
    while (inputFile >> number)
    {
        array_3.push_back(number);
    }
    inputFile.close();
}

int main()
{
    vector<thread> threads;
    read_generated_random_numbers();

    t = 8;
    length = array_3.size();
    count = 0;
    cout << "Length of Array: " << length << endl;
    for (int thread_number = 0; thread_number < t; thread_number++)
    {
        threads.emplace_back(thread(count3s_thread, thread_number));
    }

    for (thread &thread : threads)
    {
        thread.join();
    }
    cout << "Total Count of 3: " << count << endl;
    return 0;
}
