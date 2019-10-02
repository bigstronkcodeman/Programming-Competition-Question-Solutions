// Reverse and Add
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

unsigned long long getDigit(unsigned long long a, unsigned long long n)
{
	if (a < pow(10, n - 1))
	{
		return 0;
	}
	return (a % (unsigned long long)pow(10, n)) / (unsigned long long)pow(10, n - 1);
}

unsigned long long reverse(unsigned long long a)
{
	unsigned int numDigits = floor(log10(a) + 1);
	unsigned long long reverseNum = 0;
	unsigned int j = 0;
	for (int i = numDigits; i >= 0; --i)
	{
		unsigned long long digit = getDigit(a, i);
		reverseNum += (digit * pow(10, j++));
	}
	return reverseNum;
}

bool isPalindrome(unsigned long long a)
{
	return a == reverse(a);
}

void palindromes(unsigned long long a)
{
	unsigned long long n = a;
	unsigned long long iters = 0;
	do
	{
		n += reverse(n);
		iters++;
	} while (!isPalindrome(n));
	cout << iters << " " << n << endl;
}

int main()
{
	unsigned int t;
	cin >> t;
	for (unsigned long long i = 0; i < t; i++)
	{
		unsigned long long p;
		cin >> p;
		palindromes(p);
	}

	return 0;
}
