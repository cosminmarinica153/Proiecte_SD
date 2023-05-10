#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

ifstream in("input.txt");
int numCount;
int Array[1000000];

void numGenerator(int numCount, int Array[]) // aceasta functie genereaza numCount numere ce vor fi sortate in Array cu MergeSort
{
    srand(time(NULL));
    for (int i = 0; i < numCount; i++)
        Array[i] = 1 + (rand() % 1000);
}

void input(int Array[]) // aceasta funtie citeste numele din fisier si le adauga in Array
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

void Merge(int Array[], int left, int mid, int right)
{
    int n = mid - left + 1;
    int m = right - mid;
    int *leftArray = new int[n]; // leftArray si rightArray sunt matrici temporare ce vor fi interclasate
    int *rightArray = new int[m];
    for (int i = 0; i < n; i++)
        leftArray[i] = Array[left + i];
    for (int j = 0; j < m; j++)
        rightArray[j] = Array[mid + 1 + j];
    int i = 0;             // index-ul initial al leftArray
    int j = 0;             // index-ul initial al rightArray
    int k = left;          // index-ul initial al matricei unde se adauga elementele interclasate
    while (i < n && j < m) // interclasam leftArray si rightArray
    {
        if (leftArray[i] <= rightArray[j])
        {
            Array[k++] = leftArray[i];
            i++;
        }
        else
        {
            Array[k++] = rightArray[j];
            j++;
        }
    }
    while (i < n) // daca raman numere in leftArray le adaugam, in ordine, la final
    {
        Array[k++] = leftArray[i];
        i++;
    }
    while (j < m) // daca raman numere in rightArray le adaugam, in ordine, la final
    {
        Array[k++] = rightArray[j];
        j++;
    }
}

void MergeSort(int Array[], int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    MergeSort(Array, left, mid);
    MergeSort(Array, mid + 1, right);
    Merge(Array, left, mid, right);
}

void PrintArray(int Array[])
{
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
}

int main()
{
    string cond;
    cout << "Vreti sa sortati numerele din fisier input.txt?" << endl;
    cin >> cond;
    if (cond == "Da" || cond == "da" || cond == "DA")
        input(Array);
    else
    {
        cout << "Cate numere vreti sa sortati?" << endl;
        cin >> numCount;
        cout << endl;
        numGenerator(numCount, Array);
    }
    /*
    cout << "Numerele care vor fi sortate sunt:" << endl;
    for (int i = 0; i < numCount; i++)
        cout << Array[i] << ' ';
    cout << endl;
    */
    auto start = high_resolution_clock::now();
    MergeSort(Array, 0, numCount);
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