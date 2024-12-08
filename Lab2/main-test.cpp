#include "Person.hpp"
#include <utility>
#include <iostream>
#include <vector>
#include <list>

namespace {
	void f1(Person p) {
		Person person1{ p };
		Person person2;
		person2 = p;
	}

	void f2(const Person& p) {
		Person person1{ p };
		Person person2;
		person2 = p;
	}

	void f3(Person&& p1, Person&& p2) {
		Person person1{ std::move(p1) };
		Person person2;
		person2 = std::move(p2);
	}

	Person f4() {
		Person p{ 30, "William" };
		return p;
	}
}

int main() {
	// static:
	Person a{ 10, "Bob" };
	// dynamic:
	Person* b = new Person(12, "John");
	delete b;
	// C-array:
	Person* p_array = new Person[2]{ Person(20, "Martin"), Person(15, "Victor") };
	delete[] p_array;

	// pass by value:
	f1(a);
	// pass by &:
	Person d{ 21, "Orlando" };
	f2(d);
	// pass by &&:
	Person e{ 22, "Leo" };
	Person f{ 23, "Joel" };
	f3(std::move(e), std::move(f));
	
	// RVO:
	Person g;
	g = f4();

	// vector, list:
	std::vector<Person> p_vect{ Person(30, "Jack"), Person(31, "Tony") };
	std::list<Person> p_list{ Person(32, "Brian"), Person(33, "Rocky") };

	p_vect.push_back({ 34, "Robert" });
	p_vect.emplace_back(35, "Brad");

	p_list.push_back({ 36, "Billy" });
	p_list.emplace_back(37, "Michael");

	std::cout << "Final\n\n";

	return 0;
}