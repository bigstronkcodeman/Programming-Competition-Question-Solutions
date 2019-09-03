// The Trip
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

struct Trip
{
	int students;
	vector<double> expenses;
	double averageExpense;
};

double roundnum(double num)
{
	return (int)(num * 100.0) / 100.0;
}

double max(double a, double b)
{
	return a > b ? a : b;
}

double calcMinExchange(Trip& trip)
{
	double x1 = 0;
	double x2 = 0;
	
	for (int i = 0; i < trip.expenses.size(); i++)
	{
		if (trip.expenses[i] < trip.averageExpense)
		{
			x1 += roundnum((trip.averageExpense - trip.expenses[i]));
		}
		else
		{
			x2 += roundnum((trip.expenses[i] - trip.averageExpense));
		}
	}

	return max(x1, x2);
}

int main()
{
	vector<Trip> trips;
	int n = 1;
	while (cin >> n && n != 0)
	{
		Trip trip;
		trip.students = n;

		double expense;
		double avg = 0;
		double total = 0;
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
		cout << fixed << setprecision(2) << "$" << calcMinExchange(trips[i]) << endl;
	}

	return 0;
}
