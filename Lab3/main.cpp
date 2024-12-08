#include "Person.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <algorithm>
#include <list>
#include <memory>
#include <iterator>
#include <cmath>


int GetV1Size(std::mt19937& gen)
{
	std::uniform_int_distribution<std::mt19937::result_type> sizeGenerator(500, 1000);
	return sizeGenerator(gen);
}

int GetListSize(std::mt19937& gen)
{
	std::uniform_int_distribution<std::mt19937::result_type> sizeGenerator(20, 50);
	return sizeGenerator(gen);
}

int main()
{
	// Define a generator and related structures
	constexpr int maxNumber = 7;
	std::array<int, maxNumber> ageArray{ 18, 19, 20, 21, 22, 23, 24 };
	std::array<std::string, maxNumber> nameArray{ "John", "Bob", "Maria", "William", "Kate", "Julia", "Robert" };

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<std::mt19937::result_type> indexGenerator(0, maxNumber - 1);

	// 1) Fill in v1 vector 
	auto filler = [&]() -> Person {
		return { ageArray[indexGenerator(gen)], nameArray[indexGenerator(gen)] };
	};
	std::vector<Person> v1(GetV1Size(gen));
	std::generate(v1.begin(), v1.end(), filler);

	// 2) Create v2 vector and copy the last 200 elements from v1
	std::vector<Person> v2(200);
	std::copy(v1.end() - 200, v1.end(), v2.begin());

	// From the largest to the smallest comparator:
	auto comparator = [&](const Person& lhs, const Person& rhs)
	{	// by age in descending order (from 100 to 0) and by name in ascending order (from "A" to "Z")
		if (lhs.getAge() == rhs.getAge())
			return lhs.getName().compare(rhs.getName()) < 0;
		return lhs.getAge() > rhs.getAge();
	};

	// 3) Create list1 with the first 20-50 largest elements from v1
	int list1Size = GetListSize(gen);
	std::list<Person> list1(list1Size);
	std::sort(v1.begin(), v1.end(), comparator);
	std::copy(v1.begin(), v1.begin() + list1Size, list1.begin());

	// 4) Create list2 with the last 20-50 smallest elements from v2
	int list2Size = list1Size;
	std::list<Person> list2(list2Size);
	std::sort(v2.begin(), v2.end(), comparator);
	std::copy(v2.end() - list2Size, v2.end(), list2.begin());

	// 5) Remove from v1 and v2 elements that were copied
	v1.erase(v1.begin(), v1.begin() + list1Size);
	v2.erase(v2.end() - list2Size, v2.end());

	// 6) For list1, find element with the "average" value (don't use strings because there is no 
	//	"average" string) and rearrange list1 (simple sorting would work)
	list1.sort([](const Person& lhs, const Person& rhs) {
		return lhs.getAge() > rhs.getAge();
	});

	// 7) Remove odd elements from list2
	int curElem = 0;
	list2.remove_if([&](const Person& person) {
		return (curElem++) % 2 == 1;
	});

	// 8) Create v3 vector from v1 and v2
	std::vector<Person> v3(v1.size() + v2.size());
	std::copy(v1.begin(), v1.end(), v3.begin());
	std::copy(v2.begin(), v2.end(), v3.begin() + v1.size());

	// 9) Create list3 from list1 and list2
	int sizeDelta = list1.size() - list2.size();
	std::list<Person>& listToModify = (sizeDelta > 0) ? list1 : list2;

	// Remove unnecessary elements from beginning of the larger list
	auto eraseRangeEnd = listToModify.begin();
	std::advance(eraseRangeEnd, std::abs(sizeDelta));
	listToModify.erase(listToModify.begin(), eraseRangeEnd);

	// Now list1 size and list2 size are equal
	std::list<std::pair<Person, Person>> list3;
	auto list2Iter = list2.begin();
	std::for_each(list1.begin(), list1.end(), [&](const Person& person) {
		list3.emplace_back(person, *list2Iter);
		std::advance(list2Iter, 1);
	});

	// 10) Create a vector of pairs of v1 and v2 elements
	sizeDelta = v1.size() - v2.size();
	std::vector<Person>& smallerVect = (sizeDelta > 0) ? v2 : v1;
	std::vector<Person>& largerVect = (sizeDelta > 0) ? v1 : v2;

	std::vector<std::pair<Person, Person>> vectPairs;
	auto largerVectIter = largerVect.begin();
	std::for_each(smallerVect.begin(), smallerVect.end(), [&](const Person& person) {
		vectPairs.emplace_back(person, *largerVectIter);
		largerVectIter++;
	});

	return 0;
}