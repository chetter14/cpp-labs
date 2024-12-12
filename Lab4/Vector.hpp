#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix2D.hpp"
#include <unordered_map>
#include <vector>
#include <optional>
#include <cmath>
#include <iostream>

bool isNotEqualToZero(double val)
{
	return std::abs(val - 0.0) < 1e-6;
}

class Vector
{
public:
	Vector(const std::vector<double>& vect)
	{
		for (int i = 0; i < vect.size(); ++i)
		{
			if (vect[i] != 0)
			{
				hashTable_.emplace(i, vect[i]);
			}
		}
		colNumber_ = vect.size();
	}

	Vector(int colNumber)
	{
		colNumber_ = colNumber;
	}

	int getVectorSize() const { return hashTable_.size(); }

	friend std::ostream& operator<<(std::ostream& out, const Vector& vect);

	// Addition of vectors
	friend std::optional<Vector> operator+(const Vector& v1, const Vector& v2);
	// Scalar multiplication of vectors
	friend double operator*(const Vector& v1, const Vector& v2);

	// Multiplication with matrix (and no vice versa)
	friend std::optional<Vector> operator*(const Vector& v, const Matrix2D& matr);

	// Addition, multiplication, and raising to a power each element of vector by value
	friend Vector operator+(const Vector& v, double value);
	friend Vector operator*(const Vector& v, double value);
	friend Vector operator^(const Vector& v, double value);

private:
	// Stores index-value pair
	std::unordered_map<int, double> hashTable_;	
	// Row size (for calculations)
	int colNumber_;
};

std::ostream& operator<<(std::ostream& out, const Vector& vect)
{
	for (int i = 0; i < vect.colNumber_; ++i)
	{
		if (vect.hashTable_.count(i) != 0)
		{
			out << vect.hashTable_.at(i) << " ";
		}
		else
		{
			out << "0.0 ";
		}
	}
	return out;
}

std::optional<Vector> operator+(const Vector& v1, const Vector& v2)
{
	if (v1.colNumber_ != v2.colNumber_)
	{
		std::cout << "Can't do addition of vectors! Different sizes!\n";
		return {};	// return an empty vector
	}

	int size = v1.colNumber_;
	Vector result(size);

	double valuesSum;
	for (int i = 0; i < size; ++i)
	{
		valuesSum = 0.0;
		if (v1.hashTable_.count(i) != 0)		// if value at such index is not 0
		{
			valuesSum += v1.hashTable_.at(i);
		}
		if (v2.hashTable_.count(i) != 0)
		{
			valuesSum += v2.hashTable_.at(i);
		}

		if (isNotEqualToZero(valuesSum))		// if sum is different from 0.0
		{
			result.hashTable_.emplace(i, valuesSum);
		}
	}
	return result;
}

double operator*(const Vector& v1, const Vector& v2)
{
	if (v1.colNumber_ != v2.colNumber_)
	{
		std::cout << "Can't do scalar multiplication of vectors! Different sizes!\n";
		return 0;	// return 0
	}

	double result = 0.0;
	for (int i = 0; i < v1.colNumber_; ++i)
	{
		if (v1.hashTable_.count(i) != 0 
			&& v2.hashTable_.count(i) != 0)		// if values at such indices are not 0s
		{
			result += v1.hashTable_.at(i) * v2.hashTable_.at(i);
		}
	}
	return result;
}

std::optional<Vector> operator*(const Vector& v, const Matrix2D& matr)
{
	if (v.colNumber_ != matr.getRowNumber())
	{
		std::cout << "Can't do multiplication of vector and matrix! Vector column number is not equal to matrix row number!\n";
		return {};	// return an empty vector
	}

	Vector result(matr.getColNumber());
	
	for (int i = 0; i < matr.getColNumber(); ++i)		// iterate over columns
	{
		double valuesResult = 0.0;

		for (int j = 0; j < matr.getRowNumber(); ++j)	// iterate over rows
		{
			if (v.hashTable_.count(j) != 0
				&& matr.isNotZero(j, i))		// if values at such indices are not 0s
			{
				valuesResult += v.hashTable_.at(j) * matr.getValueAt(j, i);
			}
		}
		if (isNotEqualToZero(valuesResult))
		{
			result.hashTable_.emplace(i, valuesResult);
		}
	}
	
	return result;
}

Vector operator+(const Vector& v, double value)
{
	Vector result(v.colNumber_);

	for (int i = 0; i < v.colNumber_; ++i)
	{
		double curValue = v.hashTable_.count(i) != 0 ? v.hashTable_.at(i) : 0.0;
		curValue += value;
		if (isNotEqualToZero(curValue))
		{
			result.hashTable_.emplace(i, curValue);
		}
	}
	return result;
}

Vector operator*(const Vector& v, double value)
{
	Vector result(v.colNumber_);

	for (int i = 0; i < v.colNumber_; ++i)
	{
		double curValue = v.hashTable_.count(i) != 0 ? v.hashTable_.at(i) : 0.0;
		curValue *= value;
		if (isNotEqualToZero(curValue))
		{
			result.hashTable_.emplace(i, curValue);
		}
	}
	return result;
}

Vector operator^(const Vector& v, double value)
{
	Vector result(v.colNumber_);

	for (int i = 0; i < v.colNumber_; ++i)
	{
		double curValue = v.hashTable_.count(i) != 0 ? v.hashTable_.at(i) : 0.0;
		curValue = std::pow(curValue, value);
		if (isNotEqualToZero(curValue))
		{
			result.hashTable_.emplace(i, curValue);
		}
	}
	return result;
}

#endif	// VECTOR_H