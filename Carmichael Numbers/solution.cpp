// Carmichael Numbers
#include <iostream>
#include <vector>
#include <math.h>

#define MAXN 65000

using namespace std;

bool prime[MAXN + 1];

void calcPrimes()
{
	for (int i = 0; i <= MAXN; ++i)
	{
		prime[i] = true;
	}
	prime[0] = false;

	for (int i = 2; i <= MAXN; ++i)
	{
		if (prime[i])
		{
			for (int j = 2; i * j <= MAXN; ++j)
			{
				prime[i * j] = false;
			}
		}
	}
}

long long exp(long long a, long long b)
{
	if (b == 0)
	{
		return 1;
	}

	long long part = pow(a, b / 2);
	if (b % 2 == 0)
	{
		return part * part;
	}
	else
	{
		return a * part * part;
	}
}

vector<long long> binaryPart(long long n)
{
	vector<long long> parts;
	long long i = 0;
	long long d = n;
	long long r = d % 2;
	while (d >= 1)
	{
		if (r != 0) parts.push_back(exp(2, i));
		d /= 2;
		r = d % 2;
		++i;
	}
	return parts;
}

bool in(vector<long long>& list, long long key)
{
	for (long long i = 0; i < list.size(); ++i)
	{
		if (list[i] == key)
		{
			return true;
		}
	}
	return false;
}

long long fme(long long a, long long b, long long c)
{
	unsigned long long result = 1;
	vector<long long> parts = binaryPart(b);

	long long p = 1;
	long long temp = a % c;
	long long max2power = parts[parts.size() - 1];
	while (p <= max2power)
	{
		if (in(parts, p))
		{
			result = (result * temp) % c;
		}
		temp = (temp * temp) % c;
		p *= 2;
	}
	
	return result % c;
}

bool isCarmichael(long long n)
{
	for (long long i = 2; i < n; ++i)
	{
		long long mod = fme(i, n, n);
		if (mod != i)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	calcPrimes();
	long long n;
	cin >> n;
	while (n != 0)
	{
		if (!prime[n] && isCarmichael(n))
		{
			cout << "The number " << n << " is a Carmichael number.\n";
		}
		else
		{
			cout << n << " is normal.\n";
		}
		cin >> n;
	}

	return 0;
}
