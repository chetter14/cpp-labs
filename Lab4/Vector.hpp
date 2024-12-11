#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix2D.hpp"
#include <unordered_map>
#include <vector>

// Design a Vector class:
//	std::unordered_map<int, double> hashTable
//		if value of vector is not 0, then store the index-value pair in hashTable
//	addition of vectors
//	multiplication of vectors
//	multiplication with matrix (and no vice versa)
//	addition, multiplication, and raising to a power each element by value

class Vector
{
public:
	Vector(const std::vector<double>& vect)
	{
		for (int i = 0; i < vect.size(); ++i)
		{
			if (vect[i] != 0)
			{
				hashTable.emplace(i, vect[i]);
			}
		}
		rowSize = vect.size();
	}

	// Addition and multiplication of vectors
	friend Vector operator+(const Vector& v1, const Vector& v2);
	friend Vector operator*(const Vector& v1, const Vector& v2);

	// Multiplication with matrix (and no vice versa)
	friend Vector operator*(const Vector& v, const Matrix2D& matr);

	// Addition, multiplication, and raising to a power each element of vector by value
	friend Vector operator+(const Vector& v, double value);
	friend Vector operator*(const Vector& v, double value);
	friend Vector operator^(const Vector& v, double value);

private:
	// Stores index-value pair
	std::unordered_map<int, double> hashTable;	
	// Row size (for calculations)
	int rowSize;
};

#endif	// VECTOR_H