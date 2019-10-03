// The Stern-Brocot Number System
#include <iostream>
#include <string>

using namespace std;

string sternBrocotPath(int numerator, int denominator)
{
	string result = "";
	int m = 0;
	int n = 1;
	int m_prime = 1;
	int n_prime = 0;
	int p = m + m_prime;
	int q = n + n_prime;
	while ((double)p / q != (double)numerator / denominator)
	{
		if ((double)numerator / denominator > (double)p / q)
		{
			result += "R";
			m = p;
			n = q;

		}
		else
		{
			result += "L";
			m_prime = p;
			n_prime = q;
		}
		p = m + m_prime;
		q = n + n_prime;
	}
	return result;
}

int main()
{
	int m;
	int n;
	while (cin >> m >> n && !(m == 1 && n == 1))
	{
		cout << sternBrocotPath(m, n) << endl;
	}

	return 0;
}
