#include <iostream>
#include <random>
#include <fstream>
using namespace std;
void generate_random_numbers(int sz, int lowest, int highest)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(lowest, highest);
    ofstream outputFile("input.txt");
    int val;
    int count=0;
    for (int i = 0; i < sz; i++)
    {
        val = distribution(gen);
        if(val==3) count++;
        outputFile << val << std::endl;
    }
    outputFile.close();
    cout<<"All the number are between "<<lowest<<" to "<<highest<<endl;
    cout<<"Total Numbers: "<<sz<<endl;
    cout<<"Total 3's : "<<count<<endl;
}
int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Arguments not proper" << endl;
        return 1;
    }

    int array_len = stoi(argv[1]);
    int minNum = stoi(argv[2]);
    int maxNum = stoi(argv[3]);
    generate_random_numbers(array_len, minNum, maxNum);
    return 0;
}