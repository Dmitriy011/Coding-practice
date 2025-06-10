// Test2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


bool NextSet(std::vector<int>& a, int n, int m)
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

void Print(std::vector<int> a, int n)
{
	static int num = 1;
	cout.width(3);
	cout << num++ << ": ";
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

double combination_2(int n, int k)
{
	double res = 1;
	for (int i = 1; i <= k; i++)
	{
		res *= double(n) / double(i);
		n--;
	}

	return res;
}

int main()
{
    /*
    int n = 5;
    int k = 3;
    std::cout << (pow(2, n) - pow(2, n - k))/ (pow(2, n) - 1) << "     "  << (pow(2, k+1) - 2) / (pow(2, k+1) - 1) ;
    */

	
	int n, m;
	std::vector<int> a;
	cout << "N = ";
	cin >> n;
	cout << "M = ";
	cin >> m;
	for (int i = 0; i < n; i++)
		a.push_back(i+1);
	Print(a, m);
	if (n >= m)
	{
		while (NextSet(a, n, m))
		{
			Print(a, m);
		}
	}
	
	/*
	int n = 5;
	int k = 3;
	std::cout << combination_2(n, k);
	*/

	/*
	while (true)
	{
		cout << pow(-1, int(rand() % 2)) << " ";
		//cout << rand() % 2;
	}
	*/
	
}

