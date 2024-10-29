#include "Person.hpp"
#include <cstring>
#include <iostream>

Person::Person(int age, const char* name) {
	age_ = new int(age);
	name_ = new char[strlen(name) + 1];		// include null-terminator '\0' 
	strcpy(name_, name);

	std::cout << "Default constructor: " << name_ << "\n";
}

Person::Person(const Person& person) {
	age_ = new int(*person.age_);
	name_ = new char[strlen(person.name_) + 1];
	strcpy(name_, person.name_);

	std::cout << "Copy constructor from " << name_ << "\n";
}

Person::Person(Person&& person) noexcept {
	age_ = person.age_;
	name_ = person.name_;
	person.age_ = nullptr;
	person.name_ = nullptr;

	std::cout << "Move constructor from " << name_ << "\n";
}

Person& Person::operator=(const Person& person) {
	if (age_ != nullptr) {
		delete age_;
	}
	if (name_ != nullptr) {
		delete[] name_;
	}

	age_ = new int(*person.age_);
	name_ = new char[strlen(person.name_) + 1];
	strcpy(name_, person.name_);

	std::cout << "Copy assignment from " << name_ << "\n";

	return *this;
}

Person& Person::operator=(Person&& person) noexcept {
	if (age_ != nullptr) {
		delete age_;
	}
	if (name_ != nullptr) {
		delete[] name_;
	}

	age_ = person.age_;
	name_ = person.name_;
	person.age_ = nullptr;
	person.name_ = nullptr;

	std::cout << "Move assignment from " << name_ << "\n";

	return *this;
}

Person::~Person() noexcept {
	if (name_ != nullptr) {
		std::cout << "Destructor of " << name_ << "\n\n";
	} else {
		std::cout << "Destructor\n\n";
	}
	
	if (age_ != nullptr) {
		delete age_;
	}
	if (name_ != nullptr) {
		delete[] name_;
	}
}

void Person::SetAge(int age) {
	if (age_ != nullptr) {
		*age_ = age;
	}
}