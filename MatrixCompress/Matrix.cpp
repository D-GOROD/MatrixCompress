#include "Matrix.h"
#include <chrono>
#define END_FOO "\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\"
#define START_FOO "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/"

Matrix::Matrix(vector<int> X, vector<int> Y, vector<int> Summ_count, float D)
{
	this->X = X;
	this->Y = Y;
	this->Summ_count = Summ_count;
	this->D = D;
	this->K = static_cast<float>(X.size() * Y.size()) / static_cast<float>(Summ_count.capacity());
}

float Matrix::get_K()
{
	return K;
}
float Matrix::get_D()
{
	return D;
}
string Matrix::GetMatrixString()
{
	string str;
	char buff[10];
	for (int y : Y)
	{
		for (int x : X) {
			sprintf_s(buff, "%3d", x + y);
			str.append(buff);
		}
		str.append("\r\n");
	}
	/*str.append("\r\n");
	for (int i = 0; i < Summ_count.size(); i++)
	{
		sprintf_s(buff, "%2d |", i);
		str.append(buff);
	}
	str.append("\r\n");
	for (int z : Summ_count)
	{
		sprintf_s(buff, "%2d |", z);
		str.append(buff);
	}*/
	str.append("\r\n");
	str.append("  K = ");
	str.append(std::to_string(K));
	str.append("\r\n");
	str.append("  D = ");
	str.append(std::to_string(D));
	str.append("\r\n");
	return str;
	
}
void Matrix::print_matrix_to_file(ofstream& fout)
{
	fout << START_FOO << endl;
	for (int y : Y)
	{
		for (int x : X) {
			fout << x + y << "\t";
		}
		fout << endl;
	}
	fout << endl;
	for (int i = 0; i < Summ_count.size(); i++)
	{
		fout << i << "\t" << "|";
	}
	fout << endl;
	for (int z : Summ_count)
	{
		fout << z << "\t" << "|";
	}
	fout << endl << endl;
	fout << "K = " << K << endl << "D = " << D << endl;
	fout << END_FOO << endl;
}

bool operator>(const Matrix& m1, const Matrix& m2)
{
	return m1.K > m2.K;
}
bool operator<(const Matrix& m1, const Matrix& m2)
{
	return m1.K < m2.K;
}
bool operator>=(const Matrix& m1, const Matrix& m2)
{
	return m1.K >= m2.K;
}
bool operator<=(const Matrix& m1, const Matrix& m2)
{
	return m1.K <= m2.K;
}