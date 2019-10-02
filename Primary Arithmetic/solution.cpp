// Primary Arithmetic
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

#define DECIBASE 10

using namespace std;

int getDigit(long long a, unsigned int n)
{
	if (a < pow(10, n - 1))
	{
		return 0;
	}
	return (a % (unsigned int)pow(10, n)) / (unsigned int)pow(10, n - 1);
}

int longAdditionCarries(unsigned long long a, unsigned long long b)
{
	unsigned int carry = 0;
	unsigned int count = 0;
	for (unsigned int i = 0; i < log10(max(a, b)); ++i)
	{
		unsigned int dig1 = getDigit(a, i + 1);
		unsigned int dig2 = getDigit(b, i + 1);
		if (dig1 + dig2 + carry > 9)
		{
			carry = (dig1 + dig2 + carry) / DECIBASE;
			++count;
		}
		else
		{
			carry = 0;
		}
	}
	return count;
}

int main()
{
	unsigned int a;
	unsigned int b;
	while (cin >> a >> b && !(a == 0 && b == 0))
	{
		unsigned int carries = longAdditionCarries(a, b);
		if (carries > 1)
		{
			cout << carries << " carry operations.\n";
		}
		else if (carries == 1)
		{
			cout << "1 carry operation.\n";
		}
		else
		{
			cout << "No carry operation.\n";
		}
	}

	return 0;
}
