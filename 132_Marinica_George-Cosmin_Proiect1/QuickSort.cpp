#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

ifstream in("input.txt");
int numCount;
int Array[1000000];

void numGenerator() // aceasta functie genereaza numCount numere ce vor fi sortate in Array cu QuickSort
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

int partition(int Array[], int left, int right)
{
    int pivot = Array[left];
    int count = 0;
    for (int i = left + 1; i <= right; i++)
    {
        if (Array[i] <= pivot)
            count++;
    }
    int k = left + count; // decidem pozitia pivotului
    int aux = Array[k];
    Array[k] = Array[left];
    Array[left] = aux;
    int i = left;
    int j = right;
    while (i < k && j > k) // sortam elementele din stanga si din dreapta pivotului
    {

        while (Array[i] <= pivot)
            i++;
        while (Array[j] > pivot)
            j--;
        if (i < k && j > k)
        {
            swap(Array[i++], Array[j--]);
        }
    }

    return k;
}

void QuickSort(int Array[], int left, int right)
{

    if (left >= right)
        return;

    int p = partition(Array, left, right);
    QuickSort(Array, left, p - 1);
    QuickSort(Array, p + 1, right);
}

int main()
{
    string cond;
    cout << "Vreti sa sortati numerele din fisier input.txt?" << endl;
    cin >> cond;
    if (cond == "Da" || cond == "da" || cond == "DA")
    { // input();
        int k;
        cin >> k;
        for (int i = 0; i < k; i++)
            cin >> Array[i];
    }
    else
    {
        cout << "Cate numere vreti sa sortati?" << endl;
        cin >> numCount;
        cout << endl;
        numGenerator();
    }

    cout << "Numerele care vor fi sortate sunt:" << endl;
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
    cout << endl;

    auto start = high_resolution_clock::now();
    QuickSort(Array, 0, numCount);
    auto stop = high_resolution_clock::now();
    cout << "Timpul de executie este:" << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1000 << " millisecnods" << endl;
    int n = numCount;
    if (isSorted(Array, n))
        cout << "Vectorul este sortat";
    else
        cout << "Vectorul nu a fost sortat";
    cout << endl;

    cout << "Numerele sortate sunt:" << endl;
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
    cout << endl;

    return 0;
    in.close();
}