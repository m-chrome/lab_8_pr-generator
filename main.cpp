#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

#define SAMPLE_SET 10

using namespace std;

// Линейный конгруэнтный метод, формула
long lcm(long prev)
{
    int m = 100;
    int a = 21;
    int c = 97;
    return (a*prev + c) % m;
}

// Генератор
vector<int> pr_generator(long seed,long size)
{
    vector<int> sample;
    srand(seed);
    sample.push_back(0 + rand() % 100);
    for(int i=1; i< size; ++i)
        sample.push_back(lcm(sample[i-1]));
    return sample;
}

// Хи-квадрат для 9 степеней свободы
bool ChiSquared(vector<int> sample)
{
    sort(sample.begin(), sample.end());

    const int       NGROUPS         = 10;
    const double    PROBABILITY     = 0.1;
    int             sampleCounter   = 0;
    int             nSize           = sample.size();
    double          gapWidth        = 10;
    double          uborder         = gapWidth;
    double          chi_expr        = 0;
    double          chi_qntl        = 16.919;

    for(int i=0; i < NGROUPS; ++i)
    {
        int freaquency=0;
        while(sample[sampleCounter] < uborder  && sampleCounter < nSize)
        {
            ++sampleCounter;
            ++freaquency;
        }
        chi_expr += std::pow(freaquency-nSize*PROBABILITY, 2)/(nSize*PROBABILITY);
        uborder += gapWidth;
    }
    return chi_expr <= chi_qntl;
}

// Выборочное среднее
double sampleMean(vector<int> sample)
{
    double sMean = 0;
    for(size_t i=0; i<sample.size(); ++i)
        sMean += sample[i];
    return (double)(sMean/sample.size());
}

// Среднеквадратичное отклонение
double stdDeviation(vector<int> sample)
{
    double sDev = 0;
    double sMean = sampleMean(sample);
    for(size_t i=0; i<sample.size(); ++i)
        sDev += pow(sample[i] - sMean, 2);
    return sqrt(sDev/sample.size());
}

// Коэффициент вариации
double variationCoef(vector<int> sample)
{
    return stdDeviation(sample)/sampleMean(sample);
}

int main()
{
    cout << "Генерация псевдослучайных чисел в отрезке [0,100]" << endl << endl;
    vector<vector<int>> sset;
    for(int i=0; i < SAMPLE_SET; ++i)
    {
        sset.push_back(pr_generator((i+1)*100, 30));
    }
    for(int i=0; i < SAMPLE_SET; ++i)
    {
        cout << "Выборка " << i+1 << ":\n";
        for(auto s: sset[i])
            cout << s << " ";
        cout << endl;
        cout << "Выборочное среднее: " << (double)sampleMean(sset[i]) << endl;
        cout << "Отклонение: " << (double)stdDeviation(sset[i]) << endl;
        cout << "Коэффициент вариации: " << (double)variationCoef(sset[i]) << endl;
        if (ChiSquared(sset[i]))
            cout << "Хи-квадрат: прошёл" << endl << endl;
        else
            cout << "Хи-квадрат: не прошёл" << endl << endl;
    }
    return 0;
}

