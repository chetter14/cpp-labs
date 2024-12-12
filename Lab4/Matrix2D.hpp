#ifndef MATRIX_2D_H
#define MATRIX_2D_H

#include <unordered_map>
#include <utility>
#include <vector>

// Define hashing function for "pair<int, int>" key
template<>
struct std::hash<std::pair<int, int>>
{
	std::size_t operator()(const std::pair<int, int>& values) const noexcept
	{
		return (std::hash<int>()(values.first)
			^ std::hash<int>()(values.second));
	}
};

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
					hashTable_.emplace(std::pair(i, j), matrix2d[i][j]);
				}
			}
		}
		rowNumber_ = matrix2d.size();
		colNumber_ = matrix2d[0].size();
	}

	int getColNumber() const noexcept { return colNumber_; }
	int getRowNumber() const noexcept { return rowNumber_; }

	bool isNotZero(int x, int y) const noexcept 
	{	// if such a value exists, then it's not a zero
		return hashTable_.count(std::pair(x, y)) != 0; 
	}

	double getValueAt(int x, int y) const noexcept 
	{ 
		return hashTable_.at(std::pair(x, y));
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
	std::unordered_map<std::pair<int, int>, double> hashTable_;
	// Column and row size
	int rowNumber_, colNumber_;
};

#endif	// MATRIX_2D_H