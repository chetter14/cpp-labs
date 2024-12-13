#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix2D.hpp"
#include <unordered_map>
#include <vector>
#include <optional>
#include <cmath>
#include <iostream>

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

	auto IterBegin() { return hashTable_.begin(); }
	auto IterEnd() { return hashTable_.begin(); }
	auto IterCbegin() const { return hashTable_.cbegin(); }
	auto IterCend() const { return hashTable_.cend(); }

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
	// Column number
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

	for (auto iterV1 = v1.IterCbegin(); iterV1 != v1.IterCend(); iterV1++ )
	{
		auto [index, value] = (*iterV1);
		result.hashTable_.emplace(index, value);
	}

	for (auto iterV2 = v2.IterCbegin(); iterV2 != v2.IterCend(); iterV2++)
	{
		auto [index, value] = (*iterV2);
		if (result.hashTable_.count(index) != 0)			// already added from the iterator 1
		{
			double sum = result.hashTable_.at(index) + value;
			if (isNotEqualToZero(sum))						// after an addition from iterator 2
			{													// not zero - update the result
				result.hashTable_.emplace(index, sum);
			}
			else												// zero - erase an element
			{
				result.hashTable_.erase(index);
			}
		}
		else
		{
			result.hashTable_.emplace(index, value);
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

	std::vector<double> tempVect(v1.colNumber_);
	for (auto iterV1 = v1.IterCbegin(); iterV1 != v1.IterCend(); iterV1++)
	{
		tempVect[iterV1->first] = iterV1->second;
	}

	double result = 0.0;
	for (auto iterV2 = v2.IterCbegin(); iterV2 != v2.IterCend(); iterV2++)
	{
		auto [index, value] = (*iterV2);
		if (isNotEqualToZero(tempVect[index]))
		{
			result += tempVect[index] * value;
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

	std::vector<double> tempVector(v.colNumber_);

	// Iterate over vector and inside the iteration iterate over matrix
	// (if col number in vector is equal to row number in matrix - do calculations)
	// After that iterate over result Vector and erase elements that are equal to 0

	for (auto iterVect = v.IterCbegin(); iterVect != v.IterCend(); iterVect++)
	{
		for (auto iterMatr = matr.IterCbegin(); iterMatr != matr.IterCend(); iterMatr++)
		{
			int vectColNumber = iterVect->first;
			auto [matrRowNumber, matrColNumber] = iterMatr->first;
			if (vectColNumber == matrRowNumber)
			{
				result.hashTable_[matrColNumber] += iterVect->second * iterMatr->second;
			}
		}
	}

	for (int i = 0; i < result.hashTable_.size(); ++i)
	{
		if (!isNotEqualToZero(result.hashTable_.at(i)))	// if the value is zero
		{
			result.hashTable_.erase(i);
		}
	}	
	return result;
}

Vector operator+(const Vector& v, double value)
{
	Vector result(v.colNumber_);

	// No way to avoid brute-force iteration
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

	for (auto iter = result.IterBegin(); iter != result.IterEnd(); iter++)
	{
		iter->second *= value;
	}
	return result;
}

Vector operator^(const Vector& v, double value)
{
	Vector result(v.colNumber_);

	for (auto iter = result.IterBegin(); iter != result.IterEnd(); iter++)
	{
		iter->second = std::pow(iter->second, value);
	}
	return result;
}

#endif	// VECTOR_H