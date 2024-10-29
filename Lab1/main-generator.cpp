#include <iostream>
#include <string>
#include <fstream>


int main()
{
	// Read variables types from console
	std::string typeA, typeB;
	std::cin >> typeA >> typeB;
	std::clog << "Types of variables are: " << typeA << " and " << typeB << "\n";

	// Init a file stream	
	std::ofstream fout{ "f.cpp" };
	if (!fout.is_open())
	{
		std::cerr << "Error! Failed to open the f.cpp file!\n";
		return 1;
	}

	// Add reading from file of operators for operands

	// Write the 'f()' function code to the file
	fout << "#include <iostream>\n\n";
	fout << "int f() { \n";
	fout << "  " << typeA << " a = 2;\n";
	fout << "  " << typeB << " b{ 3 };\n";

	std::ifstream operators_file{ "operators.txt" };
	if (!operators_file.is_open()) 
	{
		std::cerr << "Error! Failed to open the operators.cpp file!\n";
		return 1;
	}
	for (char oper; operators_file >> oper; )
	{
		fout << "  std::cout << a " << oper << " b << \"\\n\"; \n";
	}

	fout << "  return 0;\n";
	fout << "}\n";

	std::clog << "Generated an f.cpp file!\n";

	return 0;
}