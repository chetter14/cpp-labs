#include <iostream>

int f() { 
  int a = 2;
  double b{ 3 };
  std::cout << a + b << "\n"; 
  std::cout << a - b << "\n"; 
  std::cout << a * b << "\n"; 
  std::cout << a / b << "\n"; 
  return 0;
}
