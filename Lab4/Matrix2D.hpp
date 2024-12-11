#ifndef MATRIX_2D_H
#define MATRIX_2D_H

#include <unordered_map>
#include <utility>
#include <vector>

// Design a Matrix2D class:
//	std::unordered_map<std::pair<int, int>, double> hashTable
//		if value of matrix is not 0, then store the [x_index, y_index]-value pair in hashTable
//	addition of matrices
//	multiplication of matrices
//	matrix transpose
//	finding the inverse matrix
//	raise matrix to the power (of int or real type)
//	addition, multiplication, and raising to a power each element by value

class Matrix2D
{
public:
	Matrix2D(const std::vector<std::vector<double>>& matrix2d)
	{
		for (int i = 0; i < matrix2d.size(); ++i)
		{
			for (int j = 0; j < matrix2d[i].size(); ++j)
			{
				if (matrix2d[i][j] != 0)
				{
					hashTable.emplace(i, j, matrix2d[i][j]);
				}
			}
		}
		colSize = matrix2d.size();
		rowSize = matrix2d[0].size();
	}

	// Addition and multiplication of matrices
	friend Matrix2D operator+(const Matrix2D& m1, const Matrix2D& m2);
	friend Matrix2D operator*(const Matrix2D& m1, const Matrix2D& m2);

	// Matrix transpose
	Matrix2D transpose();

	// Finding the inverse matrix
	Matrix2D getInverse();

	// Raise matrix to the power (of int and real type)
	Matrix2D raiseToPower(int value);
	Matrix2D raiseToPower(double value);

	// Addition, multiplication, and raising to a power each element of matrix by value
	friend Matrix2D operator+(const Matrix2D& m, double value);
	friend Matrix2D operator*(const Matrix2D& m, double value);
	friend Matrix2D operator^(const Matrix2D& v, double value);

private:
	// Stores [x_index, y_index]-value pair
	std::unordered_map<std::pair<int, int>, double> hashTable;
	// Column and row size
	int colSize, rowSize;
};

#endif	// MATRIX_2D_H