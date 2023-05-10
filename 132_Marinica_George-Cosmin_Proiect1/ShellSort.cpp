#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

ifstream in("input.txt");
int numCount;
int Array[1000000];

void numGenerator() // aceasta functie genereaza numCount numere ce vor fi sortate in Array cu ShellSort
{
    srand(time(NULL));
    for (int i = 0; i < numCount; i++)
        Array[i] = 1 + (rand() % 10000);
}

void input()
{
    int x;
    int i = 0;
    while (in >> x)
        Array[i++] = x;
    numCount = i;
}

bool isSorted(int Array[], int n)
{
    if (n == 1 || n == 0)
        return true;
    return Array[n - 1] >= Array[n - 2] &&
           isSorted(Array, n - 1);
}

void ShellSort(int Array[], int gap)
{
    for (int i = gap / 2; i > 0; gap /= 2)
    {
        for (int i = gap; i < numCount; i += 1)
        {
            int aux = Array[i];
            int j;
            for (j = i; j >= gap && Array[j - gap] > aux; j -= gap)
                Array[j] = Array[j - gap];
            Array[j] = aux;
        }
    }
}

int main()
{
    string cond;
    cout << "Vreti sa sortati numerele din fisier input.txt?" << endl;
    cin >> cond;
    if (cond == "Da" || cond == "da" || cond == "DA")
        input();
    else
    {
        cout << "Cate numere vreti sa sortati?" << endl;
        cin >> numCount;
        cout << endl;
        numGenerator();
    }
    /*
    cout << "Numerele care vor fi sortate sunt:" << endl;
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
    cout << endl;
    */
    auto start = high_resolution_clock::now();
    ShellSort(Array, numCount);
    auto stop = high_resolution_clock::now();
    cout << "Timpul de executie este:" << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1 << " microseconds" << endl;
    int n = numCount;
    if (isSorted(Array, n))
        cout << "Vectorul este sortat";
    else
        cout << "Vectorul nu a fost sortat";
    cout << endl;
    /*
    cout << "Numerele sortate sunt:" << endl;
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
    cout << endl;
    */
    return 0;
    in.close();
}