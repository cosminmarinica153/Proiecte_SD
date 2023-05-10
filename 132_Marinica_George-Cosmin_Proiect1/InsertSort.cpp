#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

ifstream in("input.txt");
int numCount;
int Array[1000000];

void numGenerator() // aceasta functie genereaza numCount numere ce vor fi sortate in Array cu InsertSort
{
    srand(time(NULL));
    for (int i = 0; i < numCount; i++)
        Array[i] = 1 + (rand() % 1000);
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

void InsertSort(int Array[], int n)
{
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        k = Array[i]; // k va lua valoarea Array[i] pentru a tine evidenta termenului pe care il mutam prin insertie
        j = i - 1;
        while (j >= 0 && Array[j] > k)
        {
            Array[j + 1] = Array[j];
            j--;
        }
        Array[j + 1] = k;
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

    // cout << "Numerele care vor fi sortate sunt:" << endl;
    // for (int i = 0; i < numCount; i++)
    //     cout << Array[i] << ' ';
    // cout << endl;

    int n = numCount;
    auto start = high_resolution_clock::now();
    InsertSort(Array, n);
    auto stop = high_resolution_clock::now();
    cout << "Timpul de executie este:" << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1000 << " milliseconds" << endl;
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