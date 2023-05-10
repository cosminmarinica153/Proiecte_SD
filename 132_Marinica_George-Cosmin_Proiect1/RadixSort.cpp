#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

ifstream in("input.txt");
int numCount;
int Array[1000000];

void numGenerator() // aceasta functie genereaza numCount numere ce vor fi sortate in Array cu RadixSort
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

int getMax(int Array[], int n)
{
    int mx = Array[0];
    for (int i = 1; i < n; i++)
        if (Array[i] > mx)
            mx = Array[i];
    return mx;
}

void countSort(int Array[], int n, int exp)
{
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(Array[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) // Construim output
    {
        output[count[(Array[i] / exp) % 10] - 1] = Array[i];
        count[(Array[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) // readaugam numerele in Array
        Array[i] = output[i];
}

void RadixSort(int Array[], int n)
{
    int m = getMax(Array, n);                 // cautam numarul cu cele mai multe cifre
    for (int exp = 1; m / exp > 0; exp *= 10) // vom folosi counting sort pentru fiecare cifra
        countSort(Array, n, exp);
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
    RadixSort(Array, numCount);
    auto stop = high_resolution_clock::now();
    cout << "Timpul de executie este:" << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1000 << " milliseconds" << endl;
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