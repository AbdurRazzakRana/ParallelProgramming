#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
using namespace std;
vector<int> array_3;
int t, length, count;

void count3s_thread(int thread_number)
{
    int length_per_thread = length / t;
    int start = thread_number * length_per_thread;
    for (int i = start; i < start + length_per_thread; i++)
    {
        if (array_3[i] == 3)
        {
            count++;
        }
    }
}
int main()
{
    vector<thread> threads;
    array_3 = {2, 3, 0, 2, 3, 3, 1, 0, 0, 1, 3, 2, 2, 3, 1, 0};
    t = 4;
    count = 0;
    length = array_3.size();
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