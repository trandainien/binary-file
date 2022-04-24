#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Polynomial
{
    int degree;
    int coefficient;
};

void write()
{
    ofstream fout("POLY.BIN", ios::binary | ios::out);
    int numberOfTerms = 5;
    Polynomial *a = new Polynomial[numberOfTerms];
    a[0].degree = 1;
    a[0].coefficient = 2;
    a[1].degree = 2;
    a[1].coefficient = 3;
    a[2].degree = 3;
    a[2].coefficient = 4;
    a[3].degree = 3;
    a[3].coefficient = 2;
    a[4].degree = 2;
    a[4].coefficient = 1;
    fout.write((char *)&numberOfTerms, sizeof(numberOfTerms));

    fout.write((char *)a, sizeof(a) * numberOfTerms);

    fout.close();
}

void read(Polynomial *&a, int &numberOfTerms)
{
    ifstream fin("POLY.BIN", ios::binary | ios::in);

    fin.read((char *)&numberOfTerms, sizeof(numberOfTerms));

    a = new Polynomial[numberOfTerms];

    fin.read((char *)a, sizeof(a) * numberOfTerms);

    fin.close();
}

void FindLargestPoly()
{
    Polynomial *a = nullptr;
    int n;
    read(a, n);

    cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i].coefficient << "x^" << a[i].degree << endl;
    }

    int max_degree = -1;

    for (int i = 0; i < n; i++)
    {
        if (max_degree < a[i].degree)
        {
            max_degree = a[i].degree;
        }
    }

    Polynomial *result = new Polynomial[n];
    int num = 0;

    for (int i = 0; i < n; i++)
    {
        if (max_degree == a[i].degree)
        {
            result[num] = a[i];
            num++;
        }
    }

    ofstream fout("POLY_LARGEST.BIN", ios::binary | ios::out);

    fout.write((char *)&num, sizeof(num));
    fout.write((char *)result, sizeof(result) * num);
    fout.close();

    ifstream fin("POLY_LARGEST.BIN", ios::binary | ios::in);
    fin.read((char *)&num, sizeof(num));
    fin.read((char *)result, sizeof(result) * num);

    fin.close();

    cout << endl;
    for (int i = 0; i < num; i++)
    {
        cout << result[i].coefficient << "x^" << result[i].degree << endl;
    }
}

int main()
{
    write();
    // read();
    FindLargestPoly();
}
