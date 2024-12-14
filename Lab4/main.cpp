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

int main()
{
	testVector();
	
	return 0;
}