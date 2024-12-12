#include "Vector.hpp"
#include "Matrix2D.hpp"
#include <iostream>
#include <vector>


int main()
{
	std::vector<double> v1{ 0.0, 0.0, 3.0, 0.0 };
	std::vector<double> v2{ 1.0, 0.0, 2.0, 0.0 };

	Vector vect1(v1);
	Vector vect2(v2);
	std::cout << "vect1 size - " << vect1.getVectorSize() << "\n";
	std::cout << "vect2 size - " << vect2.getVectorSize() << "\n";

	std::optional<Vector> result = vect1 + vect2;
	if (result.has_value())
	{
		std::cout << *result << "\n";
		std::cout << "result size - " << (*result).getVectorSize() << "\n";
	}	
	else
		std::cout << "No result!\n";
	
	return 0;
}