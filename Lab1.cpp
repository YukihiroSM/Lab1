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

	cout << "Enter the number of equations (it should be >= 1) -> ";
	cin >> rows;
	cout << "\nNow enter the number of unknowns (it should be >= 1) -> ";
	cin >> columns;

	if (rows != columns)
	{
		cout << "Sorry, but this system can't be solved by this method." << endl;
		cout << "Would you like to try again? (1 - yes | 2 - no): ";
		char test;
		cin >> test;
		if (test == '1') goto try_again;
		else exit(0);
	}
	vector<vector<double>> mainMatrix(rows, vector<double>(columns));
	vector<vector<double>> matrix(rows, vector<double>(columns));
	vector<double> rightPart(rows);
	vector<double> solution(columns);
	cout << "Now enter coefficients near to unknowns: " << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << i + 1 << " equanation:" << endl;
		for (int j = 0; j < columns; j++)
		{
			cout << "X" << j+1 << " = ";
			cin >> temp;
			matrix[i][j] = temp;
		}
		cout << "\n";
	}

	cout << "Enter what's is in the right part:";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "(" << matrix[i][j] << ")" << "x" << j + 1;
			if (j != columns - 1) cout << " + ";
			else cout << " = ";
		}
		cin >> temp;
		rightPart.push_back(temp);
	}

	mainMatrix = matrix;
	int n = columns - 1; // Fot better cycles
	double mainDet = Gauss(matrix, n);

	for (int i = 0; i <= n; i++) {
		matrix = mainMatrix;
		for (int j = 0; j <= n; j++) {
			matrix[i][j] = rightPart[j];
		}
		solution[i] = Gauss(matrix, n) / mainDet;
	}
	for (int i = 0; i <= n; i++)
		cout << "X" << i + 1 << " = " << solution[i] << endl;

    return 0;
}
vector<vector<double>> Sort(vector<vector<double>> matrix, int n) {
	int indMax = 0, i = 0;
	double temp = 0, max = 0;
	while (true) {
		temp = 0;
		max = fabs(matrix[i][i]);
		indMax = i;
		for (int j = i; j <= n; j++) {
			if (fabs(matrix[j][i]) > fabs(max)) {
				max = fabs(matrix[j][i]);
				indMax = j;
			}
		}
		if (indMax == i) ++i;
		else
		{
			for (int j = 0; j <= n; j++) {
				temp = matrix[i][j];
				matrix[i][j] = matrix[indMax][j];
				matrix[indMax][j] = temp;
			}
			++i;
		}
		if (i <= n) break;
	}
	return matrix;
}
double Gauss(vector<vector<double>> matrix, int n) {
	matrix = Sort(matrix, n);
	int i, j = 0;

	for (int k = 0; k <= n - 1; k++)
	{
		i = k + 1;
		while (i <= n) {
			double G = matrix[i][k] / matrix[k][k];
			j = k;
			while (j <= n) {
				matrix[i][j] = matrix[i][j] - G * matrix[k][j];
				j++;
			}
			i++;
		}
	}

	double det = 1;
	for (int i = 0; i <= n; i++) {
		det = det * matrix[i][i];
	}

	return det;
}

