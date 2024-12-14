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
	Matrix2D transpose() const;

	// Finding the inverse matrix 
	// https://stackoverflow.com/questions/60300482/c-calculating-the-inverse-of-a-matrix
	std::optional<Matrix2D> getInverse() const;

	// Raise matrix to the power (of int and real type)
	// https://studwork.ru/spravochnik/matematika/matricy/vozvedenie-matricy-v-stepen
	std::optional<Matrix2D> raiseToPower(int power) const;

	// Addition, multiplication, and raising to a power each element of matrix by value
	friend Matrix2D operator+(const Matrix2D& m, double value);
	friend Matrix2D operator*(const Matrix2D& m, double value);
	friend Matrix2D operator^(const Matrix2D& m, double value);

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

Matrix2D Matrix2D::transpose() const
{
	Matrix2D result(colNumber_, rowNumber_);

	for (auto iter = hashTable_.cbegin(); iter != hashTable_.cend(); iter++)
	{
		auto [row, col] = iter->first;
		result.hashTable_.emplace(std::pair(col, row), iter->second);
	}
	return result;
}

std::optional<Matrix2D> Matrix2D::getInverse() const
{
	if (rowNumber_ != colNumber_)
	{
		std::cout << "The matrix is not of square form! Can't do inversion!\n";
		return {};
	}

	// Make a copy of current matrix to not modify it
	Matrix2D curMatr(*this);

	int size = rowNumber_;
	Matrix2D result(size, size);
	
	// Make an identity matrix
	for (int i = 0; i < size; ++i)
		result.hashTable_[{i, i}] = 1.0;

	// Do calculations to get an inverse matrix
	for (int i = 0; i < size; ++i) 
	{
		if (!isNotEqualToZero(curMatr.hashTable_.at({i, i})))
		{
			std::cout << "Matrix is singular and cannot be inverted!\n";
			return {};
		}

		double pivot = curMatr.hashTable_.at({i, i});
		for (int j = 0; j < size; ++j) 
		{
			if (curMatr.hashTable_.find({ i, j }) != curMatr.hashTable_.end())
			{
				curMatr.hashTable_[{i, j}] /= pivot;
			}
			if (result.hashTable_.find({ i, j }) != result.hashTable_.end())
			{
				result.hashTable_[{i, j}] /= pivot;
			}
		}

		for (int k = 0; k < size; ++k) 
		{
			if (k != i) 
			{
				double factor = curMatr.hashTable_[{k, i}];
				for (int j = 0; j < size; ++j) 
				{
					if (curMatr.hashTable_.find({ i, j }) != curMatr.hashTable_.end())
					{
						curMatr.hashTable_[{k, j}] -= factor * curMatr.hashTable_[{i, j}];
					}
					if (result.hashTable_.find({ i, j }) != result.hashTable_.end())
					{
						result.hashTable_[{k, j}] -= factor * result.hashTable_[{i, j}];
					}	
				}
			}
		}
	}
	return result;
}

std::optional<Matrix2D> Matrix2D::raiseToPower(int power) const
{
	if (power < 2)
	{
		std::cout << "Power value must be greater or equal to 2!\n";
		return {};
	}

	// Make a copy of current matrix
	Matrix2D result(*this);

	for (int i = 2; i <= power; ++i)
	{
		result = (result * (*this)).value();
	}
	return result;
}

Matrix2D operator+(const Matrix2D& m, double value)
{
	Matrix2D result(m.rowNumber_, m.colNumber_);

	// No way to avoid brute-force iteration
	for (int i = 0; i < m.rowNumber_; ++i)
	{
		for (int j = 0; j < m.colNumber_; ++j)
		{
			double curValue = m.hashTable_.count({ i, j }) != 0 ? m.hashTable_.at({ i, j }) : 0.0;
			curValue += value;
			if (isNotEqualToZero(curValue))
			{
				result.hashTable_.emplace(std::pair(i, j), curValue);
			}
		}
	}
	return result;
}

Matrix2D operator*(const Matrix2D& m, double value)
{
	Matrix2D result(m.rowNumber_, m.colNumber_);

	for (auto iter = m.IterCbegin(); iter != m.IterCend(); iter++)
	{
		auto [rowNumber, colNumber] = iter->first;
		result.hashTable_.emplace(std::pair(rowNumber, colNumber), iter->second * value);
	}
	return result;
}

Matrix2D operator^(const Matrix2D& m, double value)
{
	Matrix2D result(m.rowNumber_, m.colNumber_);

	for (auto iter = m.IterCbegin(); iter != m.IterCend(); iter++)
	{
		auto [rowNumber, colNumber] = iter->first;
		result.hashTable_.emplace(std::pair(rowNumber, colNumber), std::pow(iter->second, value));
	}
	return result;
}

#endif	// MATRIX_2D_H