#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
using namespace std;
class Matrix
{
public:
	Matrix(vector<int> X, vector<int> Y, vector<int> Summ_count, float D);
	string GetMatrixString();
	void print_matrix_to_file(ofstream& fout);
	float get_K();
	float get_D();
	friend bool operator> (const Matrix& m1, const Matrix& m2);
	friend bool operator< (const Matrix& m1, const Matrix& m2);
	friend bool operator>= (const Matrix& m1, const Matrix& m2);
	friend bool operator<= (const Matrix& m1, const Matrix& m2);
private:
	vector<int> X;
	vector<int> Y;
	vector<int> Summ_count;
	float K;
	float D;
};