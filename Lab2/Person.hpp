#ifndef PERSON_H
#define PERSON_H

class Person {
public:
	Person() = default;
	Person(int age, const char* name);
	Person(const Person& person);
	Person(Person&& person) noexcept;
	Person& operator=(const Person& person);
	Person& operator=(Person&& person) noexcept;
	~Person() noexcept;

	void SetAge(int age);

private:
	int* age_ = nullptr;
	char* name_ = nullptr;
};

#endif // PERSON_H