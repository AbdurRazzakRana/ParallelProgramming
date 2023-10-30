#include <iostream>
#include <random>
#include <fstream>
using namespace std;
void generate_random_numbers(int sz, int lowest, int highest)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(lowest, highest);
    ofstream outputFile("integers.txt");
    for (int i = 0; i < sz; i++)
    {
        outputFile << distribution(gen) << std::endl;
    }
    outputFile.close();
}
int main()
{
    generate_random_numbers(16777216, 0, 5);
    return 0;
}