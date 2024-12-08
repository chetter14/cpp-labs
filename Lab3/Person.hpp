#ifndef PERSON_HPP
#define	PERSON_HPP

#include <string>

class Person {
public:
	Person() = default;
	Person(int age, const std::string& name)
	{
		age_ = age;
		name_ = name;
	}

	int getAge() const { return age_; }
	const std::string& getName() const { return name_; }

private:
	int age_ = 0;
	std::string name_;
};

#endif	// PERSON_HPP