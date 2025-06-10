#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
bool NextSet(vector<int>& a, int n, int m)
{
    int k = m;
    for (int i = k - 1; i >= 0; --i)
        if (a[i] < n - k + i + 1)
        {
            ++a[i];
            for (int j = i + 1; j < k; ++j)
                a[j] = a[j - 1] + 1;
            return true;
        }
    return false;
}
void Print(vector<int> a, int n)
{
    static int num = 1;
    cout.width(3);
    cout << num++ << ": ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

double factorial(int number)
{
    int res = 1;
    for (int j = 1; j <= number; j++)
    {
        res = res * j;
    }

    return res;
}

double Gamma_func(double value)
{
    if (value == 1)
    {
        return value;
    }
    if (value == 0.5)
    {
        const double PI = 3.141592653589793;
        return sqrt(PI);
    }

    return (value - 1) * Gamma_func(value - 1);
}

double integral_xhi_in_sqr(int r, double R0)
{
    int n = 10000;
    double res = 0;
    for (int i = 1; i <= n; i++)
    {
        double x1 = R0 * double(i - 1) / double(n);
        double gamma1 = tgamma(double(r) / 2);
        double x2 = R0 * double(i) / double(n);

        double g1 = pow(2, -double(r) * 0.5) * (1 / gamma1) * pow(x1, double(r) * 0.5 - 1) * std::exp(-x1 * 0.5);
        double g2 = pow(2, -double(r) * 0.5) * (1 / gamma1) * pow(x2, double(r) * 0.5 - 1) * std::exp(-x2 * 0.5);
        res +=  (g1 + g2);
    }
    res *= R0 / double(2 * n);

    return res;
}

int main()
{
    /*
    int n, m;
    cout << "N = ";
    cin >> n;
    cout << "M = ";
    cin >> m;
    vector<int> a;
    for (int i = 0; i < n; i++)
        a.push_back(i);

    Print(a, m);
    if (n >= m)
    {
        while (NextSet(a, n, m))
            Print(a, m);
    }
    cin.get(); cin.get();
    return 0;
    */

    /*
    int count_elemetns = 10;
    int k = 2;
    std::cout << (pow(2, count_elemetns) - pow(2, count_elemetns - k)) / (pow(2, count_elemetns) - 1) << " " << (pow(2, k + 1) - 2) / (pow(2, k+1) - 1);
    */

    std:: cout << Gamma_func(1) << " " << 1-integral_xhi_in_sqr(10, 9.53255);
}