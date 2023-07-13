#include <iostream>
#include <vector>
#include "src/vector.hpp"
#include <exception>
#include <iterator>

struct TooManyObjects : public std::exception {};

//struct S {
//	inline static size_t objects = 0;
//
//	S() {
//		++objects;
//		if (objects > 5) {
//			throw TooManyObjects();
//		}
//	}
//
//	S(const S& other) {
//		++objects;
//		if (objects > 5) {
//			throw TooManyObjects();
//		}
//	}
//};

int main() {
	ft::vector<int> vec;
	vec.reserve(10);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.erase(vec.begin() + 2, vec.end() - 1);
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << ' ';
	}
	std::cout << std::endl;
	
	return 0;
}
