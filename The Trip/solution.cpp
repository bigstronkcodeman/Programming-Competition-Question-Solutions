// The Trip
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

struct Trip
{
	int students;
	vector<float> expenses;
	float averageExpense;
};

void swap(vector<float>& expenses, int i, int j)
{
	if (i < expenses.size() && j < expenses.size())
	{
		float temp = expenses[i];
		expenses[i] = expenses[j];
		expenses[j] = temp;
	}
}

float roundnum(float num)
{
	return roundf(num * 100) / 100;
}

void sortExpenses(vector<float>& expenses)
{
	for (int i = 1; i < expenses.size(); i++)
	{
		float toInsert = expenses[i];

		int j = i - 1;
		while (j >= 0 && expenses[j] > toInsert)
		{
			expenses[j + 1] = expenses[j];
			j--;
		}

		expenses[j + 1] = toInsert;
	}
}

float getMinExchange(Trip& trip)
{
	sortExpenses(trip.expenses);

	int index = -1;
	for (int i = 0; index == -1 && i < trip.expenses.size(); i++)
	{
		if (trip.expenses[i] > trip.averageExpense)
		{
			index = i;
		}
	}

	if (index == -1)
	{
		return 0.0;
	}

	float exchanged = 0;
	for (int i = 0; i < index; i++)
	{
		float toDistribute = trip.averageExpense - trip.expenses[i];
		int numRecipients = trip.expenses.size() - index;
		float amt = toDistribute / numRecipients;

		for (int j = index; j < trip.expenses.size(); j++)
		{
			if (trip.expenses[j] + amt >= trip.averageExpense)
			{
				exchanged += (trip.expenses[j] - trip.averageExpense);
				toDistribute -= (trip.expenses[j] - trip.averageExpense);
				toDistribute += ((trip.expenses[j] - amt) - trip.averageExpense);
				numRecipients = (trip.expenses.size() - (j + 1));
				amt = toDistribute / numRecipients;
				trip.expenses[j] = trip.averageExpense;
			}
			else
			{
				trip.expenses[j] -= amt;
				exchanged += amt;
			}
		}
	}

	return exchanged;
}

int main()
{
	vector<Trip> trips;
	int n = 1;
	while (cin >> n && n != 0)
	{
		Trip trip;
		trip.students = n;

		float expense;
		float avg = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> expense;
			trip.expenses.push_back(expense);
			avg += expense;
		}
		avg /= n;
		trip.averageExpense = avg;

		trips.push_back(trip);
	}

	for (int i = 0; i < trips.size(); i++)
	{
		//cout << "$" << getMinExchange(trips[i]);
		printf("$%.2f", getMinExchange(trips[i]));
		if (i != trips.size() - 1) cout << endl;
	}

	return 0;
}
