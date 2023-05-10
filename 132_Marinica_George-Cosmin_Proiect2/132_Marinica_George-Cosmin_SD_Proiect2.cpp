#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <windows.h>

using namespace std;

class Nod
{
    int valoare;
    int grad;
    Nod *stanga;
    Nod *dreapta;
    Nod *tata;
    Nod *fiu;
    bool marcat;

public:
    // Constructori
    Nod()
    {
        this->valoare = 999999;
        this->grad = 0;
        this->stanga = nullptr;
        this->dreapta = nullptr;
        this->tata = nullptr;
        this->fiu = nullptr;
        this->marcat = false;
    }
    Nod(int valoare)
    {
        this->valoare = valoare;
        this->grad = 0;
        this->stanga = nullptr;
        this->dreapta = nullptr;
        this->tata = nullptr;
        this->fiu = nullptr;
        this->marcat = false;
    }
    Nod(const Nod &obj)
    {
        this->valoare = obj.valoare;
        this->grad = obj.grad;
        this->stanga = obj.stanga;
        this->dreapta = obj.dreapta;
        this->tata = obj.tata;
        this->fiu = obj.fiu;
        this->marcat = obj.marcat;
    }
    // Supraincarcare operatori;
    friend ostream &operator<<(ostream &out, const Nod &obj)
    {
        out << "Valoare: " << obj.valoare << endl;
        out << "Grad: " << obj.grad << endl;
        if (obj.tata == nullptr)
            out << "Nodul radacina" << endl;
        else
        {
            out << "Tata: ";
            out << obj.tata->valoare << endl;
        }
        if (obj.fiu == nullptr)
            out << "Nodul nu are fii" << endl;
        else
        {
            out << "Fiu-link: ";
            out << obj.fiu->valoare << endl;
            if (obj.grad > 1)
            {
                out << "Fii nodului: ";
                Nod *temp = obj.fiu;
                do
                {
                    if (temp->dreapta == obj.fiu)
                        out << temp->valoare;
                    else
                        out << temp->valoare << " --> ";
                    temp = temp->dreapta;
                } while (temp != obj.fiu);
            }
        }
        return out;
    }
    Nod &operator=(const Nod &obj)
    {
        if (this != &obj)
        {
            this->valoare = obj.valoare;
            this->grad = obj.grad;
            this->stanga = obj.stanga;
            this->dreapta = obj.dreapta;
            this->tata = obj.tata;
            this->fiu = obj.fiu;
            this->marcat = obj.marcat;
        }
        return *this;
    }
    // Getters
    int get_valoare() { return this->valoare; }
    int get_grad() { return this->grad; }
    Nod *get_stanga() { return this->stanga; }
    Nod *get_dreapta() { return this->dreapta; }
    Nod *get_tata() { return this->tata; }
    Nod *get_fiu() { return this->fiu; }
    bool get_marcat() { return this->marcat; }
    // Setters
    void set_valoare(int valoare) { this->valoare = valoare; }
    void set_grad(int grad) { this->grad = grad; }
    void set_stanga(Nod *stanga) { this->stanga = stanga; }
    void set_dreapta(Nod *dreapta) { this->dreapta = dreapta; }
    void set_tata(Nod *tata) { this->tata = tata; }
    void set_fiu(Nod *fiu) { this->fiu = fiu; }
    void set_marcat(bool marcat) { this->marcat = marcat; }
};

class FibonacciHeap
{
    int nrNoduri;
    Nod *min;
    Nod *capat;
    Nod *coada;

public:
    // Constructori
    FibonacciHeap()
    {
        this->nrNoduri = 0;
        this->min = nullptr;
        this->capat = nullptr;
        this->coada = nullptr;
    }
    FibonacciHeap(const FibonacciHeap &obj)
    {
        this->nrNoduri = obj.nrNoduri;
        this->min = obj.min;
        this->capat = obj.capat;
        this->coada = obj.coada;
    }
    // Supraincarcare operatori
    friend istream &operator>>(istream &in, FibonacciHeap &obj)
    {
        cout << "\nIntroduceti nod sau tastati \"done\" pentru a termina\n";
        int nr = obj.nrNoduri;
        string input;
        while (true)
        {
            in >> input;
            if (input == "done")
                break;
            try
            {
                obj.inserare(stoi(input));
                nr++;
            }
            catch (const exception &e)
            {
                cout << "Input invalid\n";
            }
        }
        obj.nrNoduri = nr;
        return in;
    }
    friend ostream &operator<<(ostream &out, FibonacciHeap &obj)
    {
        if (obj.min == nullptr)
        {
            cout << "\nHeap gol";
            return out;
        }
        cout << "\nFibonacci Heap:";
        cout << "\nNumar de noduri: " << obj.nrNoduri;
        cout << "\nMinim: " << obj.min->get_valoare();
        cout << "\nStructura heap:\n";
        Nod *nod = obj.min;
        cout << "---------------------\n";
        do
        {
            obj.printNod(nod);
            cout << "---------------------\n";
            nod = nod->get_dreapta();
        } while (nod != obj.min);
        cout << endl;
        return out;
    }
    // Getters
    int get_nrNoduri() { return this->nrNoduri; }
    // Setters
    void set_nrNoduri(int nrNoduri) { this->nrNoduri = nrNoduri; }
    void set_min(Nod *min) { this->min = min; }
    // Metode Heap Fibonacci
    Nod *getMin();
    void inserare(int valoare);
    void reunine(FibonacciHeap &obj);
    void extractMin();
    // Metode misc
    void printNod(Nod *nod);
};
Nod *FibonacciHeap::getMin()
{
    if (this->min == nullptr)
    {
        cout << "\nHeap gol.";
        Nod *temp = new Nod(-1);
        return temp;
    }
    else
        return this->min;
}
void FibonacciHeap::inserare(int valoare)
{
    Nod *nod = new Nod(valoare);
    if (this->min == nullptr)
    {
        this->coada = nod;
        this->capat = nod;
        this->capat->set_dreapta(this->capat);
        this->capat->set_stanga(this->capat);
        this->min = capat;
    }
    else
    {
        nod->set_stanga(this->capat);
        nod->set_dreapta(this->capat->get_dreapta());
        this->capat->set_dreapta(nod);
        this->capat = nod;
        this->coada->set_stanga(nod);
    }
    if (this->min->get_valoare() > this->capat->get_valoare())
        this->min = this->capat;
    this->nrNoduri++;
}
void FibonacciHeap::reunine(FibonacciHeap &fib)
{
    int contor = 0;
    if (this->min == nullptr)
    {
        this->min = fib.min;
        contor++;
    }
    if (fib.min == nullptr)
        contor++;
    if (!contor)
    {
        Nod *min1 = this->min;
        Nod *min2 = fib.min;
        Nod *min1_dreapta = this->min->get_dreapta();
        Nod *min2_dreapta = fib.min->get_dreapta();
        min1->set_dreapta(min2_dreapta);
        min2->set_dreapta(min1_dreapta);
        min1_dreapta->set_stanga(min2);
        min2_dreapta->set_stanga(min1);
        if (this->min > fib.min)
            this->min = fib.min;
    }
    this->nrNoduri = nrNoduri + fib.nrNoduri;
}
void FibonacciHeap::extractMin()
{
    if (this->min == nullptr)
    {
        cout << "\nHeap gol";
        return;
    }
    // Caz de exceptie - in heap exista doar un nod
    if (this->min == this->min->get_dreapta())
    {
        this->min = nullptr;
        this->nrNoduri--;
        return;
    }
    Nod *actual = this->min->get_dreapta();
    // Eliminare minim
    if (this->min->get_fiu() != nullptr)
    {
        Nod *nod = this->min->get_fiu();
        nod->set_stanga(this->min->get_stanga());
        nod->get_stanga()->set_dreapta(nod);
        do
        {
            nod->set_tata(nullptr);
            if (nod->get_dreapta() != this->min->get_fiu())
                nod = nod->get_dreapta();
        } while (nod->get_dreapta() != this->min->get_fiu());
        nod->set_dreapta(this->min->get_dreapta());
        nod->get_dreapta()->set_stanga(nod);
        this->min->set_fiu(nullptr);
    }
    else
    {
        this->min->get_dreapta()->set_stanga(this->min->get_stanga());
        this->min->get_stanga()->set_dreapta(this->min->get_dreapta());
    }
    this->min = actual;
    this->nrNoduri--;
    bool marked = false;
    int maxDegree = log2(this->nrNoduri) + 1;
    vector<Nod *> gradeNoduri(maxDegree, nullptr);
    while (!marked)
    {
        // Verificare conditie
        actual->set_marcat(true);
        if (actual->get_dreapta()->get_marcat() == true)
            marked = true;
        int grad = actual->get_grad();
        while (gradeNoduri[grad] != nullptr)
        {
            Nod *nod = gradeNoduri[grad];
            gradeNoduri[grad] = nullptr;

            if (actual->get_valoare() > nod->get_valoare())
            {
                Nod *aux = nod;
                nod = actual;
                actual = aux;
            }
            nod->set_marcat(false);
            nod->get_stanga()->set_dreapta(nod->get_dreapta());
            nod->get_dreapta()->set_stanga(nod->get_stanga());
            nod->set_tata(actual);
            grad++;
            actual->set_grad(grad);
            if (actual->get_fiu() == nullptr)
            {
                actual->set_fiu(nod);
                nod->set_dreapta(nod);
                nod->set_stanga(nod);
            }
            else
            {
                nod->set_stanga(actual->get_fiu()->get_stanga());
                nod->set_dreapta(actual->get_fiu());
                actual->get_fiu()->get_stanga()->set_dreapta(nod);
                actual->get_fiu()->set_stanga(nod);
            }
        }
        gradeNoduri[grad] = actual;
        // Update minim
        if (actual->get_valoare() < this->min->get_valoare())
            this->min = actual;
        actual = actual->get_dreapta();
    }
    actual = this->min;
    // Resetare marcaj noduri
    do
    {
        actual->set_marcat(false);
        actual = actual->get_dreapta();
    } while (actual != this->min);
}

void FibonacciHeap::printNod(Nod *nod)
{
    cout << "Nod: " << nod->get_valoare() << endl;
    if (nod->get_fiu() != nullptr)
    {
        cout << "Nodul are fii:"
             << endl;
        Nod *fiu = nod->get_fiu();
        do
        {
            printNod(fiu);
            fiu = fiu->get_dreapta();
        } while (fiu != nod->get_fiu());
    }
    else
        cout << "Nodul nu are fii." << endl;
}

void header()
{
    system("CLS");
    cout << "\n----------------------------------------"
         << "\nStudent: Marinica George-Cosmin"
         << "\nGroupa: 132"
         << "\nProiect: Fibonacci Heap Implementation"
         << "\n----------------------------------------"
         << endl;
}

int main()
{
    FibonacciHeap fib1;
    FibonacciHeap fib2;
    bool going = true;
    while (going)
    {
        header();
        int input;
        cout << "\n1. Citire Fibonacci Heap"
             << "\n2. Afisare Fibonacci Heap"
             << "\n3. Get minim"
             << "\n4. Reuniune"
             << "\n5. Extract minim"
             << "\n6. Quit"
             << "\n(introduceti numarul corespunzator)"
             << endl;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            header();
            cin >> fib1;
            cout << "\n\nHeap citit cu succes!";
            Sleep(1500);
            break;
        }
        case 2:
        {
            header();
            cout << fib1;
            string goBack;
            cout << "\nScrie \"inapoi\" pentru a te intoarce la meniul principal\n";
            cin >> goBack;
            if (goBack == "inapoi")
                break;
            else
            {
                cout << "\nInput Invalid.";
                Sleep(1000);
            }
        }
        case 3:
        {
            header();
            Nod *temp = fib1.getMin();
            if (temp->get_valoare() == -1)
                cout << "\nNu exista minim!";
            else
            {
                cout << "\nMinim din heap este: " << temp->get_valoare() << endl;
                cout << *temp;
            }
            Sleep(1500);
            break;
        }
        case 4:
        {
            if (fib1.get_nrNoduri() == 0)
            {
                cout << "\nIntroduceti primul Heap inainte.";
                Sleep(1000);
                break;
            }
            header();
            cout << "\nIntroduceti valorile din al doilea Heap: \n";
            cin >> fib2;
            cout << "\n\nHeap citit cu succes!";
            Sleep(1000);
            header();
            fib1.reunine(fib2);
            cout << fib1;
            break;
        }
        case 5:
        {
            fib1.extractMin();
            cout << "\nMinim extras cu succes!"
                 << "\nAfisati heap pentru a observa schimbarile.";
            Sleep(1000);
            break;
        }
        case 6:
        {
            going = false;
            break;
        }
        default:
        {
            cout << "Input invalid.";
            Sleep(1000);
            break;
        }
        }
    }
}