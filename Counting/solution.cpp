// How Many Pieces of Land?
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <array>

#define BASE 1000000000

using namespace std;

typedef long long int_64;
typedef unsigned long long uchar;

using namespace std;

class BigInt
{
private:
	vector<uchar> base_coefficients;
	bool negative;

	void init_base_coefficients(int_64 num);

public:
	BigInt();
	BigInt(int_64 num);
	BigInt(vector<uchar> digits, bool negative);
	BigInt(string num, unsigned int base);
	BigInt(const BigInt& other);

	string toDecimalString();
	static BigInt pow(const BigInt& a, unsigned int b);
	static BigInt fac(const BigInt& a);
	static BigInt choose(const BigInt& n, const BigInt& k);
	static BigInt max(const BigInt& a, const BigInt& b);

	void operator=(const BigInt& other);
	BigInt operator+(const BigInt& other);
	BigInt operator-(const BigInt& other);
	BigInt operator*(const BigInt& other);
	BigInt operator/(const BigInt& other);
	BigInt operator%(const BigInt& other);
	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
};

BigInt::BigInt()
{
	base_coefficients.push_back((uchar)0);
	negative = false;
}

BigInt::BigInt(int_64 num)
{
	init_base_coefficients(num);
	negative = num < 0 ? true : false;
}

BigInt::BigInt(vector<uchar> digits, bool negative)
{
	for (int i = 0; i < digits.size(); ++i)
	{
		base_coefficients.push_back(digits[i]);
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
	for (int i = 0; i < other.base_coefficients.size(); ++i)
	{
		base_coefficients.push_back(other.base_coefficients[i]);
	}
	negative = other.negative;
}





void BigInt::init_base_coefficients(int_64 num)
{
	int_64 d = num;
	if (num == 0)
	{
		base_coefficients.push_back(0);
		return;
	}
	int r;
	while (d > 0)
	{
		r = d % BASE;
		base_coefficients.insert(base_coefficients.begin(), (uchar)r);
		d /= BASE;
	}
}

string BigInt::toDecimalString()
{
	string result = "";
	if (BASE % 10 == 0)
	{
		int maxLen = log10(BASE);
		for (int i = 0; i < base_coefficients.size(); ++i)
		{
			unsigned long long currNumDigits = log10(base_coefficients[i]) + 1;
			string str = to_string(base_coefficients[i]);
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
	BigInt i(2);
	while (i < a)
	{
		result = result * i;
		i = i + 1;
	}
	result = result * a;

	return result;
}

BigInt BigInt::max(const BigInt& a, const BigInt& b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}





void BigInt::operator=(const BigInt& other)
{
	base_coefficients.clear();
	base_coefficients.reserve(other.base_coefficients.size());
	for (int i = 0; i < other.base_coefficients.size(); i++)
	{
		base_coefficients.push_back(other.base_coefficients[i]);
	}
	negative = other.negative;
}

BigInt BigInt::operator+(const BigInt& other)
{
	BigInt result(vector<uchar>(), false);
	int i = base_coefficients.size() - 1;
	int j = other.base_coefficients.size() - 1;
	uchar carry = 0;
	while (i >= 0 && j >= 0)
	{
		uchar dig1 = base_coefficients[i];
		uchar dig2 = other.base_coefficients[j];
		uchar insertDig = (dig1 + dig2 + carry) % BASE;
		result.base_coefficients.insert(result.base_coefficients.begin(), insertDig);
		carry = (dig1 + dig2 + carry) / BASE;
		--i;
		--j;
	}

	while (i >= 0)
	{
		uchar dig = base_coefficients[i];
		uchar insertDig = (dig + carry) % BASE;
		result.base_coefficients.insert(result.base_coefficients.begin(), insertDig);
		carry = (dig + carry) / BASE;
		--i;
	}

	while (j >= 0)
	{
		uchar dig = other.base_coefficients[j];
		uchar insertDig = (dig + carry) % BASE;
		result.base_coefficients.insert(result.base_coefficients.begin(), insertDig);
		carry = (dig + carry) / BASE;
		--j;
	}

	if (carry > 0)
	{
		result.base_coefficients.insert(result.base_coefficients.begin(), carry);
	}

	return result;
}

BigInt BigInt::operator*(const BigInt& other)
{
	BigInt result(vector<uchar>(), false);
	if (base_coefficients.size() >= other.base_coefficients.size())
	{
		vector<BigInt> addChain;
		addChain.reserve(std::max(base_coefficients.size(), other.base_coefficients.size()));
		int i = base_coefficients.size() - 1;
		int j = other.base_coefficients.size() - 1;
		while (j >= 0)
		{
			int carry = 0;
			int k = i;
			uchar dig2 = other.base_coefficients[j];
			BigInt toAdd(vector<uchar>(), false);

			for (int l = 0; l < (other.base_coefficients.size() - 1) - j; l++)
			{
				toAdd.base_coefficients.insert(toAdd.base_coefficients.begin(), 0);
			}

			while (k >= 0)
			{
				uchar dig1 = base_coefficients[k];
				uchar insertDig = ((dig1 * dig2) + carry) % BASE;
				toAdd.base_coefficients.insert(toAdd.base_coefficients.begin(), insertDig);
				carry = ((dig1 * dig2) + carry) / BASE;
				--k;
			}

			if (carry > 0)
			{
				toAdd.base_coefficients.insert(toAdd.base_coefficients.begin(), carry);
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

bool BigInt::operator==(const BigInt& other) const
{
	if (base_coefficients.size() != other.base_coefficients.size())
	{
		return false;
	}

	for (int i = 0; i < base_coefficients.size(); ++i)
	{
		if (base_coefficients[i] != other.base_coefficients[i])
		{
			return false;
		}
	}

	return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const
{
	if (*this == other)
	{
		return false;
	}

	if (base_coefficients.size() > other.base_coefficients.size())
	{
		return false;
	}
	if (base_coefficients.size() < other.base_coefficients.size())
	{
		return true;
	}

	for (int i = 0; i < base_coefficients.size(); ++i)
	{
		if (base_coefficients[i] > other.base_coefficients[i])
		{
			return false;
		}
		else if (base_coefficients[i] < other.base_coefficients[i])
		{
			return true;
		}
	}
}

bool BigInt::operator>(const BigInt& other) const
{
	return *this != other && !(*this < other);
}


int main()
{
	array<BigInt, 1001> dp;
	dp.fill(0);

	dp[0] = 1;
	dp[1] = 2;
	dp[2] = 5;
	dp[3] = 13;
	
	for (int i = 4; i <= 1000; ++i)
	{
		dp[i] = dp[i] + dp[i - 1];
		dp[i] = dp[i] + dp[i - 2];
		dp[i] = dp[i] + dp[i - 3];
		dp[i] = dp[i] + dp[i - 1];
	}

	int n;
	while (cin >> n)
	{
		cout << dp[n].toDecimalString() << endl;
	}
}
