#ifndef MATRIX_2D_H
#define MATRIX_2D_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>
#include <optional>
#include <cassert>

bool isNotEqualToZero(double val)
{
	return std::abs(val - 0.0) < 1e-6;
}

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

	Matrix2D(int rowNumber, int colNumber)
	{
		rowNumber_ = rowNumber;
		colNumber_ = colNumber;
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

	auto IterBegin() { return hashTable_.begin(); }
	auto IterEnd() { return hashTable_.begin(); }
	auto IterCbegin() const { return hashTable_.cbegin(); }
	auto IterCend() const { return hashTable_.cend(); }

	friend std::ostream& operator<<(std::ostream& out, const Matrix2D& matr);

	// Addition and multiplication of matrices
	friend std::optional<Matrix2D> operator+(const Matrix2D& m1, const Matrix2D& m2);
	friend std::optional<Matrix2D> operator*(const Matrix2D& m1, const Matrix2D& m2);

	// Used for multiplication of matrices
	friend double calculateSumForMult(const Matrix2D& m1, const Matrix2D& m2, int curI, int curJ);

	// Matrix transpose
	Matrix2D transpose();

	// Finding the inverse matrix 
	// https://stackoverflow.com/questions/60300482/c-calculating-the-inverse-of-a-matrix
	Matrix2D getInverse();

	// Raise matrix to the power (of int and real type)
	// https://studwork.ru/spravochnik/matematika/matricy/vozvedenie-matricy-v-stepen
	Matrix2D raiseToPower(int value);

	// Addition, multiplication, and raising to a power each element of matrix by value
	friend Matrix2D operator+(const Matrix2D& m, double value);
	friend Matrix2D operator*(const Matrix2D& m, double value);
	friend Matrix2D operator^(const Matrix2D& v, double value);

private:
	// Stores [x_index, y_index]-value pair
	std::unordered_map<std::pair<int, int>, double> hashTable_;
	// Row and column sizes
	int rowNumber_, colNumber_;
};

std::ostream& operator<<(std::ostream& out, const Matrix2D& matr)
{
	for (int i = 0; i < matr.rowNumber_; ++i)
	{
		for (int j = 0; j < matr.colNumber_; ++j)
		{
			if (matr.isNotZero(i, j))
			{
				out << matr.getValueAt(i, j) << " ";
			}
			else
			{
				out << "0.0 ";
			}
		}
		std::cout << "\n";
	}
	return out;
}

std::optional<Matrix2D> operator+(const Matrix2D& m1, const Matrix2D& m2)
{
	if (m1.rowNumber_ != m2.rowNumber_ && m1.colNumber_ != m2.colNumber_)
	{
		std::cout << "Can't do addition of matrices! Different sizes!\n";
		return {};	// return an empty matrix
	}

	int rowSize = m1.rowNumber_, colSize = m1.colNumber_;
	Matrix2D result(rowSize, colSize);

	for (auto iterM1 = m1.IterCbegin(); iterM1 != m1.IterCend(); iterM1++)
	{
		auto [indicesPair, value] = (*iterM1);
		result.hashTable_.emplace(indicesPair, value);
	}

	for (auto iterM2 = m2.IterCbegin(); iterM2 != m2.IterCend(); iterM2++)
	{
		auto [indicesPair, value] = (*iterM2);
		if (result.hashTable_.count(indicesPair) != 0)	// already added from the iterator 1
		{
			double sum = result.hashTable_.at(indicesPair) + value;
			if (isNotEqualToZero(sum))						// after an addition from iterator 2
			{													// not zero - update the result
				result.hashTable_.emplace(indicesPair, sum);
			}
			else												// zero - erase an element
			{
				result.hashTable_.erase(indicesPair);
			}
		}
		else					// no such a point after iterator 1
		{
			result.hashTable_.emplace(indicesPair, value);
		}
	}
	return result;
}

//double calculateSumForMult(const Matrix2D& m1, const Matrix2D& m2, int curI, int curJ)
//{
//	assert(m1.colNumber_ == m2.rowNumber_);
//	double sum = 0.0;
//	for (int j = 0, i = 0; j < m1.colNumber_; ++j, ++i)
//	{
//		if (m1.isNotZero(curI, j) && m2.isNotZero(i, curJ))
//		{
//			sum += m1.getValueAt(curI, j) * m2.getValueAt(i, curJ);
//		}
//	}
//	return sum;
//}

std::optional<Matrix2D> operator*(const Matrix2D& m1, const Matrix2D& m2)
{
	if (m1.colNumber_ != m2.rowNumber_)
	{
		std::cout << "Can't do multiplication of matrices! Different sizes!\n";
		return {};	// return an empty matrix
	}

	int rowSize = m1.rowNumber_, colSize = m2.colNumber_;
	Matrix2D result(rowSize, colSize);

	for (auto iterM1 = m1.IterCbegin(); iterM1 != m1.IterCend(); iterM1++)
	{
		for (auto iterM2 = m2.IterCbegin(); iterM2 != m2.IterCend(); iterM2++)
		{
			auto [m1RowNumber, m1ColNumber] = iterM1->first;
			auto [m2RowNumber, m2ColNumber] = iterM2->first;
			if (m1ColNumber == m2RowNumber)
			{
				result.hashTable_[std::pair(m1RowNumber, m2ColNumber)] += iterM1->second * iterM2->second;
			}
		}
	}

	// size is random (just to avoid many allocations)
	std::vector<std::pair<int, int>> indicesToErased;	
	indicesToErased.reserve(rowSize + colSize);

	for (auto it = result.IterCbegin(); it != result.IterEnd(); it++)
	{
		if (!isNotEqualToZero(it->second))	// if the value is zero
		{
			indicesToErased.push_back(it->first);
		}
	}
	for (auto& indices : indicesToErased)
	{
		result.hashTable_.erase(indices);
	}
	return result;

	//	!!!	Keep it for later	!!!
	//for (int curI = 0; curI < rowSize; ++curI)
	//{
	//	for (int curJ = 0; curJ < colSize; ++curJ)
	//	{
	//		double sum = calculateSumForMult(m1, m2, curI, curJ);
	//		if (isNotEqualToZero(sum))
	//		{
	//			result.hashTable_.emplace(std::pair(curI, curJ), sum);
	//		}
	//	}
	//}
}

Matrix2D Matrix2D::transpose()
{
	Matrix2D result(colNumber_, rowNumber_);
	for (int i = 0; i < rowNumber_; ++i)
	{
		for (int j = 0; j < colNumber_; ++j)
		{

		}
	}

}

#endif	// MATRIX_2D_H