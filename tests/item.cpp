#include <utility>

struct TooManyObjects {};

struct S {
	inline static size_t objects = 0;
	
	S() {
		++objects;
		if (objects > 5) {
			throw TooManyObjects();
		}
	}
	
	S(const S& other) {
		++objects;
		if (objects > 5) {
			throw TooManyObjects();
		}
	}
};