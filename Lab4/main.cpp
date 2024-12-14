#include "Vector.hpp"
#include "Matrix2D.hpp"
#include <iostream>
#include <vector>
#include <chrono>

std::vector<double> stlVectorAddition(const std::vector<double>& v1, const std::vector<double>& v2)
{
	std::vector<double> result(v1.size());
	for (int i = 0; i < v1.size(); ++i)
	{
		result[i] = v1[i] + v2[i];
	}
	return result;
}

double stlVectorMultiplication(const std::vector<double>& v1, const std::vector<double>& v2)
{
	double result = 0.0;
	for (int i = 0; i < v1.size(); ++i)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

std::vector<double> stlVectorMultiplyByValue(const std::vector<double>& v, double value)
{
	std::vector<double> result(v.size());
	for (int i = 0; i < v.size(); ++i)
	{
		result[i] = v[i] * value;
	}
	return result;
}

void testVector()
{
	constexpr int VECTOR_SIZE = 10'000;
	std::vector<double> v1(VECTOR_SIZE, 0.0);
	std::vector<double> v2(VECTOR_SIZE, 0.0);

	for (int i = 0; i < VECTOR_SIZE; i += 100)
	{
		v1[i] = 1.0;
		v2[i] = 1.0;
	}

	Vector vect1(v1);
	Vector vect2(v2);

	/*
	*	Custom Vector:
	*/
	auto customVectorStart = std::chrono::high_resolution_clock::now();

	//std::optional<Vector> customResult = vect1 + vect2;			// vectors add
	//double customResult = vect1 * vect2;							// vectors multiply
	Vector customResult = vect1 * 2;								// vector value multiply

	auto customVectorEnd = std::chrono::high_resolution_clock::now();

	std::cout << "Custom: " << customResult << "\n";

	/*
	*	STL vector:
	*/
	auto stlVectorStart = std::chrono::high_resolution_clock::now();

	//std::vector<double> stlResult = stlVectorAddition(v1, v2);		// vectors add
	//double stlResult = stlVectorMultiplication(v1, v2);				// vectors multiply
	std::vector<double> stlResult = stlVectorMultiplyByValue(v1, 2);	// vector value multiply

	auto stlVectorEnd = std::chrono::high_resolution_clock::now();

	std::cout << "Stl: ";
	//std::cout << stlResult;
	for (auto val : stlResult)
	{
		std::cout << val << " ";
	}
	std::cout << "\n";

	std::cout << "Custom time - " << customVectorEnd - customVectorStart << "\nStl time - " << stlVectorEnd - stlVectorStart << "\n";
}

std::vector<std::vector<double>> stlMatrixAddition(const std::vector<std::vector<double>>& m1, const std::vector<std::vector<double>>& m2)
{
	std::vector<std::vector<double>> result(m1.size(), std::vector<double>(m1[0].size()));
	for (int i = 0; i < m1.size(); ++i)
	{
		for (int j = 0; j < m1[0].size(); ++j)
		{
			result[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return result;
}

void testMatrix()
{
	constexpr int MATRIX_SIZE = 100, DELTA_STEP = 25;
	std::vector<std::vector<double>> m1(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE));
	std::vector<std::vector<double>> m2(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE));

	for (int i = 0; i < MATRIX_SIZE; i += DELTA_STEP)
	{
		for (int j = 0; j < MATRIX_SIZE; j += DELTA_STEP)
		{
			m1[i][j] = 1.0;
			m2[i][j] = 1.0;
		}
	}

	Matrix2D matr1(m1);
	Matrix2D matr2(m2);

	/*
	*	Custom Matrix2D:
	*/
	auto customMatrixStart = std::chrono::high_resolution_clock::now();

	std::optional<Matrix2D> customResult = matr1 + matr2;			// matrices add

	auto customMatrixEnd = std::chrono::high_resolution_clock::now();

	//std::cout << "Custom: " << *customResult << "\n";

	/*
	*	STL matrix 2D:
	*/
	auto stlMatrixStart = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<double>> stlResult = stlMatrixAddition(m1, m2);		// matrices add

	auto stlMatrixEnd = std::chrono::high_resolution_clock::now();

	//std::cout << "Stl: ";
	////std::cout << stlResult;
	//for (int i = 0; i < stlResult.size(); ++i)
	//{
	//	for (auto val : stlResult[i])
	//	{
	//		std::cout << val << " ";
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "\n";

	std::cout << "Custom time - " << customMatrixEnd - customMatrixStart << "\nStl time - " << stlMatrixEnd - stlMatrixStart << "\n";
}

int main()
{
	//testVector();
	testMatrix();
	
	return 0;
}