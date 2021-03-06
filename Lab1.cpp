// Lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

double Gauss(vector<vector<double>>, int);
vector<vector<double>> Sort(vector<vector<double>>, int);

int main()
{
	int rows, columns = 0;
	double temp = 0;
	
try_again: //If rows != columns and user want to try again.

	cout << "Enter the number of rows (it should be >= 1) -> ";
	cin >> rows;
	cout << "\nNow enter the number of columns (it should be >= 1) -> ";
	cin >> columns;

	if (rows != columns)
	{
		cout << "Sorry, but this matrix can't be solved by this method." << endl;
		cout << "Would you like to try again? (1 - yes | 2 - no): ";
		char test;
		cin >> test;
		if (test == '1') goto try_again;
		else exit(0);
	}
	vector<vector<double>> matrix(rows, vector<double>(columns));

	cout << "Now enter this matrix: " << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "[" << i << "][" << j << "] = ";
			cin >> matrix[i][j];
		}
		cout << "\n";
	}
	int n = columns - 1;
	double det = Gauss(matrix, n);

	cout << "\nDeterminant of this matrix: " << det << ".\n";

    return 0;
}

double Gauss(vector<vector<double>> matrix, int n) 
{
	int i, j = 0;
	matrix = Sort(matrix, n);
	//Алгоритм Гауса
	for (int k = 0; k <= n - 1; k++)
	{
		i = k + 1;
		while (i <= n) 
		{
			double G = matrix[i][k] / matrix[k][k];
			j = k;
			while (j <= n) 
			{
				matrix[i][j] = matrix[i][j] - G * matrix[k][j];
				j++;
			}
			i++;
		}
	}
	
	//Обрахування визначника.
	double det = 1;
	for (int i = 0; i <= n; i++) 
	{
		det = det * matrix[i][i];
	}

	return det;
}

vector<vector<double>> Sort(vector<vector<double>> matrix, int n)
{
	int indMax = 0;
	double max;
	double temp = 0;
	for (int i = 0; i < n; i++) {
		max = matrix[i][i];
		indMax = i;
		for (int j = i; j < n; j++) {
			if (matrix[j][i] > max) {
				max = matrix[j][i];
				indMax = j;
			}
		}
		for (int j = 0; j < n; j++) {
			temp = matrix[i][j];
			matrix[i][j] = matrix[indMax][j];
			matrix[indMax][j] = temp;
		}
	}
	return matrix;
}
