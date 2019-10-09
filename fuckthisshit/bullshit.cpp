// How Many Fibs?
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define BASE 1000000000

using namespace std;

typedef long long int_64;
typedef unsigned long long uchar;

using namespace std;

class BigInt
{
private:
	vector<uchar> base256_coefficients;
	bool negative;

	void init_base256_coefficients(int_64 num);

public:
	BigInt();
	BigInt(int_64 num);
	BigInt(vector<uchar> digits, bool negative);
	BigInt(string num, unsigned int base);
	BigInt(const BigInt& other);

	string toDecimalString();
	static BigInt pow(const BigInt& a, unsigned int b);
	static BigInt fac(const BigInt& a);

	void operator=(const BigInt& other);
	BigInt operator+(const BigInt& other);
	BigInt operator-(const BigInt& other);
	BigInt operator*(const BigInt& other);
	BigInt operator/(const BigInt& other);
	BigInt operator%(const BigInt& other);
	bool operator==(const BigInt& other);
	bool operator!=(const BigInt& other);
	bool operator<(const BigInt& other);
	bool operator>(const BigInt& other);
};

BigInt::BigInt()
{
	base256_coefficients.push_back((uchar)0);
	negative = false;
}

BigInt::BigInt(int_64 num)
{
	init_base256_coefficients(num);
	negative = num < 0 ? true : false;
}

BigInt::BigInt(vector<uchar> digits, bool negative)
{
	for (int i = 0; i < digits.size(); ++i)
	{
		base256_coefficients.push_back(digits[i]);
	}
	negative = negative;
}

BigInt::BigInt(string strnum, unsigned int base)
{
	BigInt meToBe;
	BigInt b(base);
	for (int i = 0; i < strnum.size(); ++i)
	{
		char c[] = { strnum[i] };
		meToBe = meToBe + (BigInt(atoi(c)) * BigInt::pow(b, strnum.size() - 1 - i));
	}
	*this = meToBe;
	negative = false;
}

BigInt::BigInt(const BigInt& other)
{
	for (int i = 0; i < other.base256_coefficients.size(); ++i)
	{
		base256_coefficients.push_back(other.base256_coefficients[i]);
	}
	negative = other.negative;
}





void BigInt::init_base256_coefficients(int_64 num)
{
	int_64 d = num;
	if (num == 0)
	{
		base256_coefficients.push_back(0);
		return;
	}
	int r;
	while (d > 0)
	{
		r = d % BASE;
		base256_coefficients.insert(base256_coefficients.begin(), (uchar)r);
		d /= BASE;
	}
}

string BigInt::toDecimalString()
{
	string result = "";
	if (BASE % 10 == 0)
	{
		int maxLen = log10(BASE);
		for (int i = 0; i < base256_coefficients.size(); ++i)
		{
			int currNumDigits = log10(base256_coefficients[i]) + 1;
			string str = to_string(base256_coefficients[i]);
			while (i != 0 && currNumDigits < maxLen)
			{
				str.insert(0, "0");
				++currNumDigits;
			}
			result += str;
		}
	}
	return result;
}

BigInt BigInt::pow(const BigInt& a, unsigned int b)
{
	BigInt result(1);
	if (b == 0)
	{
		return result;
	}
	if (b == 1)
	{
		return a;
	}

	result = BigInt::pow(a, b / 2);
	if (b % 2 == 0)
	{
		return result * result;
	}
	else
	{
		BigInt copy(a);
		return copy * result * result;
	}
}

BigInt BigInt::fac(const BigInt& a)
{
	BigInt result(1);

	return result;
}





void BigInt::operator=(const BigInt& other)
{
	base256_coefficients.clear();
	base256_coefficients.reserve(other.base256_coefficients.size());
	for (int i = 0; i < other.base256_coefficients.size(); i++)
	{
		base256_coefficients.push_back(other.base256_coefficients[i]);
	}
	negative = other.negative;
}

BigInt BigInt::operator+(const BigInt& other)
{
	BigInt result(vector<uchar>(), false);
	int i = base256_coefficients.size() - 1;
	int j = other.base256_coefficients.size() - 1;
	uchar carry = 0;
	while (i >= 0 && j >= 0)
	{
		uchar dig1 = base256_coefficients[i];
		uchar dig2 = other.base256_coefficients[j];
		uchar insertDig = (dig1 + dig2 + carry) % BASE;
		result.base256_coefficients.insert(result.base256_coefficients.begin(), insertDig);
		carry = (dig1 + dig2 + carry) / BASE;
		--i;
		--j;
	}

	while (i >= 0)
	{
		uchar dig = base256_coefficients[i];
		uchar insertDig = (dig + carry) % BASE;
		result.base256_coefficients.insert(result.base256_coefficients.begin(), insertDig);
		carry = (dig + carry) / BASE;
		--i;
	}

	while (j >= 0)
	{
		uchar dig = other.base256_coefficients[j];
		uchar insertDig = (dig + carry) % BASE;
		result.base256_coefficients.insert(result.base256_coefficients.begin(), insertDig);
		carry = (dig + carry) / BASE;
		--j;
	}

	if (carry > 0)
	{
		result.base256_coefficients.insert(result.base256_coefficients.begin(), carry);
	}

	return result;
}

BigInt BigInt::operator*(const BigInt& other)
{
	BigInt result(vector<uchar>(), false);
	if (base256_coefficients.size() >= other.base256_coefficients.size())
	{
		vector<BigInt> addChain;
		addChain.reserve(max(base256_coefficients.size(), other.base256_coefficients.size()));
		int i = base256_coefficients.size() - 1;
		int j = other.base256_coefficients.size() - 1;
		while (j >= 0)
		{
			int carry = 0;
			int k = i;
			uchar dig2 = other.base256_coefficients[j];
			BigInt toAdd(vector<uchar>(), false);

			for (int l = 0; l < (other.base256_coefficients.size() - 1) - j; l++)
			{
				toAdd.base256_coefficients.insert(toAdd.base256_coefficients.begin(), 0);
			}

			while (k >= 0)
			{
				uchar dig1 = base256_coefficients[k];
				uchar insertDig = ((dig1 * dig2) + carry) % BASE;
				toAdd.base256_coefficients.insert(toAdd.base256_coefficients.begin(), insertDig);
				carry = ((dig1 * dig2) + carry) / BASE;
				--k;
			}

			if (carry > 0)
			{
				toAdd.base256_coefficients.insert(toAdd.base256_coefficients.begin(), carry);
			}

			addChain.push_back(toAdd);
			--j;
		}

		for (int k = 0; k < addChain.size(); k++)
		{
			result = result + addChain[k];
		}
	}
	else
	{
		return BigInt(other) * (*this);
	}
	return result;
}

bool BigInt::operator==(const BigInt& other)
{
	if (base256_coefficients.size() != other.base256_coefficients.size())
	{
		return false;
	}

	for (int i = 0; i < base256_coefficients.size(); ++i)
	{
		if (base256_coefficients[i] != other.base256_coefficients[i])
		{
			return false;
		}
	}

	return true;
}

bool BigInt::operator!=(const BigInt& other)
{
	return !(*this == other);
}

bool BigInt::operator<(const BigInt& other)
{
	if (*this == other)
	{
		return false;
	}

	if (base256_coefficients.size() > other.base256_coefficients.size())
	{
		return false;
	}
	if (base256_coefficients.size() < other.base256_coefficients.size())
	{
		return true;
	}

	for (int i = 0; i < base256_coefficients.size(); ++i)
	{
		if (base256_coefficients[i] > other.base256_coefficients[i])
		{
			return false;
		}
		else if (base256_coefficients[i] < other.base256_coefficients[i])
		{
			return true;
		}
	}
}

bool BigInt::operator>(const BigInt& other)
{
	return *this != other && !(*this < other);
}

int fib(BigInt l, BigInt h)
{
	BigInt f1(1);
	BigInt f2(2);
	BigInt curr = f1 + f2;
	int count = 0;
	if ((f1 > l || f1 == l) && (f1 < h || f1 == h)) ++count;
	if ((f2 > l || f2 == l) && (f2 < h || f2 == h)) ++count;
	while ((curr < h) || (curr == h))
	{
		if ((curr > l || curr == l) && (curr < h || curr == h)) ++count;
		f1 = f2;
		f2 = curr;
		curr = f1 + f2;
	}
	return count;
}

int main()
{
	vector<vector<BigInt>> instances;
	string num1, num2;
	while (cin >> num1 >> num2 && (num1 != "0" || num2 != "0"))
	{
		BigInt low(num1, 10);
		BigInt high(num2, 10);
		instances.push_back({ low, high });
		//cout << fib(low, high) << endl;
	}

	for (int i = 0; i < instances.size(); i++)
	{
		cout << fib(instances[i][0], instances[i][1]) << endl;
	}

	return 0;
}
