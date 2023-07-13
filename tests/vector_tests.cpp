//
// Created by Cristie Dell on 2/26/23.
//
//#include <gtest/gtest.h>
#include <cassert>
#include "../src/vector.hpp"
#include <iterator>
#include <memory>
#include <vector>

//===----------------------------------- << Constructor/Destructor >> -----------------------------------===//
void empty_constructor_test() {
	ft::vector<int> ft_int_empty_vec;
	assert(ft_int_empty_vec.empty() && "vector not empty");
	assert(ft_int_empty_vec.capacity() == 0 && "vector not empty");
	
	ft::vector<std::string> ft_str_empty_vec;
	assert(ft_str_empty_vec.empty() && "vector not empty");
	assert(ft_str_empty_vec.capacity() == 0 && "vector not empty");
}

void get_allocator_test() {
	std::allocator<int> std_alloc;
	ft::vector<int> ft_vec(std_alloc);
	assert(ft_vec.get_allocator() == std_alloc && "Allocators are not the same");
}

void val_param_constructor_test() {
	std::vector<int> std_int_vec(5, 111);
	ft::vector<int> ft_int_vec(5, 111);
	assert(ft_int_vec.size() == std_int_vec.size());
	assert(ft_int_vec.capacity() == std_int_vec.capacity());
	for (size_t i = 0; i < ft_int_vec.size(); ++i) {
		assert(ft_int_vec[i] == std_int_vec[i]);
	}
	
	std::vector<std::string> std_str_vec(5, "str");
	ft::vector<std::string> ft_str_vec(5, "str");
	assert(ft_str_vec.size() == std_str_vec.size());
	assert(ft_str_vec.capacity() == std_str_vec.capacity());
	for (size_t i = 0; i < ft_str_vec.size(); ++i) {
		assert(ft_str_vec[i] == std_str_vec[i]);
	}
}

void copy_constructor_test() {
	std::vector<std::string> std_vec_str(5, "str");
	ft::vector<std::string> ft_vec_str(5, "str");

	std::vector<std::string> std_copy_str = std_vec_str;
	ft::vector<std::string> ft_copy_str = ft_vec_str;

	for (size_t i = 0; i < ft_copy_str.size(); ++i) {
		assert(ft_copy_str[i] == std_copy_str[i]);
	}
	
	std::vector<int> std_vec_int(5, 111);
	ft::vector<int> ft_vec_int(5, 111);
	
	std::vector<int> std_copy_int = std_vec_int;
	ft::vector<int> ft_copy_int = ft_vec_int;
	
	for (size_t i = 0; i < ft_copy_int.size(); ++i) {
		assert(ft_copy_int[i] == std_copy_int[i]);
	}
}

void iter_constructor() {
	ft::vector<std::string> ft_vect_str(5, "str");
	ft::vector<std::string>::iterator first = ft_vect_str.begin();
	ft::vector<std::string>::iterator last = ft_vect_str.end();
	ft::vector<std::string> ft_vec_iter_construct(first, last);

	std::vector<std::string> std_vect_str(5, "str");
	std::vector<std::string>::iterator first_std = std_vect_str.begin();
	std::vector<std::string>::iterator last_std = std_vect_str.end();
	std::vector<std::string> std_vec_iter_construct(first_std, last_std);

	for (size_t i = 0; i < ft_vec_iter_construct.size(); ++i) {
		assert(ft_vec_iter_construct[i] == std_vec_iter_construct[i]);
	}
}

void copy_assignment_test_empty() {
	std::vector<std::string> std_vec_str(5, "str");
	ft::vector<std::string> ft_vec_str(5, "str");
	
	std::vector<std::string> std_copy_empty;
	ft::vector<std::string> ft_copy_empty;
	
	std_copy_empty = std_vec_str;
	ft_copy_empty = ft_vec_str;
	
	for (size_t i = 0; i < ft_copy_empty.size(); ++i) {
		assert(ft_copy_empty[i] == std_copy_empty[i]);
	}
}

void copy_assignment_test_assignable_empty() {
	std::vector<std::string> std_vec_empty_str;
	ft::vector<std::string> ft_vec_empty_str;
	
	std::vector<std::string> std_copy_str(5, "str");
	ft::vector<std::string> ft_copy_str(5, "str");
	
	std_copy_str = std_vec_empty_str;
	ft_copy_str = ft_vec_empty_str;
	
	assert(ft_copy_str.size() == std_copy_str.size());
	assert(ft_copy_str.capacity() == std_copy_str.capacity());
	
	std::vector<int> std_vec_empty_int;
	ft::vector<int> ft_vec_empty_int;
	
	std::vector<int> std_copy_int(5, 111);
	ft::vector<int> ft_copy_int(5, 111);
	
	std_copy_int = std_vec_empty_int;
	ft_copy_int = ft_vec_empty_int;
	
	assert(ft_copy_int.size() == std_copy_int.size());
	assert(ft_copy_int.capacity() == std_copy_int.capacity());
}

void copy_assignment_test_assignable_size_less_then_size() {
	std::vector<std::string> std_vec_size_less_str(3, "str_1");
	ft::vector<std::string> ft_vec_size_less_str(3, "str_1");

	std::vector<std::string> std_copy_str(5, "str_2");
	ft::vector<std::string> ft_copy_str(5, "str_2");

	std_copy_str = std_vec_size_less_str;
	ft_copy_str = ft_vec_size_less_str;

	assert(ft_copy_str.size() == std_copy_str.size());
	assert(ft_copy_str.capacity() == std_copy_str.capacity());

	for (size_t i = 0; i < ft_copy_str.size(); ++i) {
		assert(ft_copy_str[i] == std_copy_str[i]);
	}

	std::vector<int> std_vec_size_less_int(3, 222);
	ft::vector<int> ft_vec_size_less_int(3, 222);
	
	std::vector<int> std_copy_int(5, 111);
	ft::vector<int> ft_copy_int(5, 111);
	
	std_copy_int = std_vec_size_less_int;
	ft_copy_int = ft_vec_size_less_int;
	
	assert(ft_copy_int.size() == std_copy_int.size());
	assert(ft_copy_int.capacity() == std_copy_int.capacity());
	
	for (size_t i = 0; i < ft_copy_int.size(); ++i) {
		assert(ft_copy_int[i] == std_copy_int[i]);
	}
}

void copy_assignment_test_assignable_size_less_then_capacity() {
	std::vector<std::string> std_vec_size_less_than_cap_str(7, "str_1");
	ft::vector<std::string> ft_vec_size_less_than_cap_str(7, "str_1");
	
	std::vector<std::string> std_copy_str(5, "str_2");
	ft::vector<std::string> ft_copy_str(5, "str_2");
	
	std_copy_str.reserve(10);
	ft_copy_str.reserve(10);
	
	std_copy_str = std_vec_size_less_than_cap_str;
	ft_copy_str = ft_vec_size_less_than_cap_str;
	
	assert(ft_copy_str.size() == std_copy_str.size());
	assert(ft_copy_str.capacity() == std_copy_str.capacity());
	
	for (size_t i = 0; i < ft_copy_str.size(); ++i) {
		assert(ft_copy_str[i] == std_copy_str[i]);
	}
	
	std::vector<int> std_vec_size_less_then_cap_int(7, 222);
	ft::vector<int> ft_vec_size_less_then_cap_int(7, 222);
	
	std::vector<int> std_copy_int(5, 111);
	ft::vector<int> ft_copy_int(5, 111);
	
	std_copy_int.reserve(10);
	ft_copy_int.reserve(10);
	std_copy_int = std_vec_size_less_then_cap_int;
	ft_copy_int = ft_vec_size_less_then_cap_int;
	
	assert(ft_copy_int.size() == std_copy_int.size());
	assert(ft_copy_int.capacity() == std_copy_int.capacity());
	
	for (size_t i = 0; i < ft_copy_int.size(); ++i) {
		assert(ft_copy_int[i] == std_copy_int[i]);
	}
}

void copy_assignment_test_assignable_size_more_then_capacity() {
	std::vector<std::string> std_vec_size_more_than_cap_str(8, "str_1");
	ft::vector<std::string> ft_vec_size_more_than_cap_str(8, "str_1");
	
	std::vector<std::string> std_copy_str(5, "str_2");
	ft::vector<std::string> ft_copy_str(5, "str_2");
	
	std_copy_str = std_vec_size_more_than_cap_str;
	ft_copy_str = ft_vec_size_more_than_cap_str;
	
	assert(ft_copy_str.size() == std_copy_str.size());
	assert(ft_copy_str.capacity() == std_copy_str.capacity());
	
	for (size_t i = 0; i < ft_copy_str.size(); ++i) {
		assert(ft_copy_str[i] == std_copy_str[i]);
	}
	
	std::vector<int> std_vec_size_more_than_cap_int(3, 222);
	ft::vector<int> ft_vec_size_more_than_cap_int(3, 222);

	std::vector<int> std_copy_int(5, 111);
	ft::vector<int> ft_copy_int(5, 111);

	std_copy_int = std_vec_size_more_than_cap_int;
	ft_copy_int = ft_vec_size_more_than_cap_int;

	assert(ft_copy_int.size() == std_copy_int.size());
	assert(ft_copy_int.capacity() == std_copy_int.capacity());

	for (size_t i = 0; i < ft_copy_int.size(); ++i) {
		assert(ft_copy_int[i] == std_copy_int[i]);
	}
}

void copy_assignment_test() {
	copy_assignment_test_empty();
	copy_assignment_test_assignable_empty();
	copy_assignment_test_assignable_size_less_then_size();
	copy_assignment_test_assignable_size_less_then_capacity();
	copy_assignment_test_assignable_size_more_then_capacity();
	iter_constructor();
}

void destructor_test() {
	ft::vector<int> ft_int_vec(5, 111);
	ft_int_vec.~vector();
}

void test_constructor() {
	empty_constructor_test();
	get_allocator_test();
	val_param_constructor_test();
	copy_constructor_test();
	copy_assignment_test();
	destructor_test();
}

void reserve_test() {
	std::vector<int> std_vec;
	ft::vector<int> ft_vec;
	
	std_vec.reserve(10);
	ft_vec.reserve(10);
	
	assert(ft_vec.capacity() == std_vec.capacity());
}

void begin_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::vector<std::string>::iterator std_str_it = std_str_vec.begin();
	ft::vector<std::string>::iterator ft_str_it = ft_str_vec.begin();
	
	assert(*ft_str_it == *std_str_it);
	
	std::vector<int> std_int_vec(3, 111);
	ft::vector<int> ft_int_vec(3, 111);
	
	std::vector<int>::iterator std_int_it = std_int_vec.begin();
	ft::vector<int>::iterator ft_int_it = ft_int_vec.begin();
	
	assert(*ft_int_it == *std_int_it);
}

void const_begin_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::vector<std::string>::iterator std_str_it = std_str_vec.begin();
	const ft::vector<std::string>::iterator ft_str_it = ft_str_vec.begin();
	
	assert(*ft_str_it == *std_str_it);
	
	std::vector<int> std_int_vec(3, 111);
	ft::vector<int> ft_int_vec(3, 111);
	
	const std::vector<int>::iterator std_int_it = std_int_vec.begin();
	const ft::vector<int>::iterator ft_int_it = ft_int_vec.begin();
	
	assert(*ft_int_it == *std_int_it);
}

void end_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::vector<std::string>::iterator std_str_it = std_str_vec.begin();
	ft::vector<std::string>::iterator ft_str_it = ft_str_vec.begin();
	
	for (; ft_str_it < ft_str_vec.end() && std_str_it < std_str_vec.end(); ++ft_str_it) {
		assert(*ft_str_it == *std_str_it);
		++std_str_it;
	}
}

void iterator_test() {
	begin_test();
	const_begin_test();
	end_test();
}

void operator_brackets_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::string& std_str = std_str_vec[1];
	std::string& ft_str = ft_str_vec[1];
	
	assert(ft_str == std_str);
	
	std::vector<int> std_int_vec(3, 111);
	ft::vector<int> ft_int_vec(3, 111);
	
	int std_int = std_int_vec[1];
	int ft_int = ft_int_vec[1];
	
	assert(ft_int == std_int);
}

void const_operator_brackets_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::string& std_str = std_str_vec[1];
	const std::string& ft_str = ft_str_vec[1];
	
	assert(ft_str == std_str);
}

void const_at_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::string& std_str = std_str_vec.at(0);
	const std::string& ft_str = ft_str_vec.at(0);
	
	assert(ft_str == std_str);
	
	bool exceptionThrown = false;
	try {
		const std::string& ft_str_except = ft_str_vec.at(4);
		(void) ft_str_except;
	} catch (...) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void at_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::string& std_str = std_str_vec.at(1);
	const std::string& ft_str = ft_str_vec.at(1);
	
	assert(ft_str == std_str);
	
	bool exceptionThrown = false;
	try {
		const std::string& ft_str_except = ft_str_vec.at(4);
		(void) ft_str_except;
	} catch (...) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void const_front_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::string& std_str = std_str_vec.front();
	const std::string& ft_str = ft_str_vec.front();
	
	assert(ft_str == std_str);
}

void front_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::string& std_str = std_str_vec.at(1);
	std::string& ft_str = ft_str_vec.at(1);
	
	assert(ft_str == std_str);
}

void const_back_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	const std::string& std_str = std_str_vec.back();
	const std::string& ft_str = ft_str_vec.back();
	
	assert(ft_str == std_str);
}

void back_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::string& std_str = std_str_vec.back();
	std::string& ft_str = ft_str_vec.back();
	
	assert(ft_str == std_str);
}

void element_access_test() {
	operator_brackets_test();
	const_operator_brackets_test();
	const_at_test();
	at_test();
	const_front_test();
	front_test();
	const_back_test();
	back_test();
}

void swap_test() {
	std::vector<std::string> std_str_vec(3, "str");
	ft::vector<std::string> ft_str_vec(3, "str");
	
	std::vector<std::string> std_str_swappable(5, "hello");
	ft::vector<std::string> ft_str_swappable(5, "hello");
	
	std_str_vec.swap(std_str_swappable);
	ft_str_vec.swap(ft_str_swappable);
	
	for (size_t i = 0; i < ft_str_vec.size(); ++i) {
		assert(ft_str_vec[i] == std_str_vec[i]);
	}
}

void clear_test() {
	std::vector<std::string> std_str_vec(1000, "str");
	ft::vector<std::string> ft_str_vec(1000, "str");
	
	std_str_vec.clear();
	ft_str_vec.clear();
	
	assert(ft_str_vec.size() == std_str_vec.size());
	assert(ft_str_vec.capacity() == std_str_vec.capacity());
}

void insert_one_elem_test() {
	ft::vector<std::string> ft_vec(5, "aaa");
	std::vector<std::string> std_vec(5, "aaa");
	
	ft_vec.insert(ft_vec.begin() + 2, "bbb");
	std_vec.insert(std_vec.begin() + 2, "bbb");
	
	for (size_t i = 0; i < ft_vec.size(); ++i) {
		assert(ft_vec[i] == std_vec[i]);
	}
	assert(ft_vec.size() == std_vec.size());
	assert(ft_vec.capacity() == std_vec.capacity());
}

void insert_n_elems_enough_capacity_test() {
	ft::vector<int> ft_vec_1(5, 5);
	ft::vector<int> ft_vec_2;
	ft_vec_2.reserve(10);
	ft_vec_2 = ft_vec_1;
	
	ft::vector<int>::iterator ft_it = ft_vec_2.begin() + 2;
	ft_vec_2.insert(ft_it, 2, 10);
	
	std::vector<int> std_vec_1(5, 5);
	std::vector<int> std_vec_2;
	std_vec_2.reserve(10);
	std_vec_2 = std_vec_1;

	std::vector<int>::iterator std_it = std_vec_2.begin() + 2;
	std_vec_2.insert(std_it, 2, 10);

	for (size_t i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}
	
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void insert_n_elems_NOT_enough_capacity_test() {
	ft::vector<int> ft_vec_1(5, 5);
	ft::vector<int> ft_vec_2;
	ft_vec_2.reserve(10);
	ft_vec_2 = ft_vec_1;
	
	ft::vector<int>::iterator ft_it = ft_vec_2.begin() + 2;
	ft_vec_2.insert(ft_it, 7, 10);
	
	std::vector<int> std_vec_1(5, 5);
	std::vector<int> std_vec_2;
	std_vec_2.reserve(10);
	std_vec_2 = std_vec_1;
	
	std::vector<int>::iterator std_it = std_vec_2.begin() + 2;
	std_vec_2.insert(std_it, 7, 10);
	
	for (size_t i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}
	
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void insert_n_elems_empty_vec_test() {
	ft::vector<std::string> ft_vec;
	std::vector<std::string> std_vec;
	
	ft_vec.insert(ft_vec.begin(), 5, "aaa");
	std_vec.insert(std_vec.begin(), 5, "aaa");
	for (size_t i = 0; i < ft_vec.size(); ++i) {
		assert(ft_vec[i] == std_vec[i]);
	}
	assert(ft_vec.size() == std_vec.size());
	assert(ft_vec.capacity() == std_vec.capacity());
}

void insert_iter_enough_capacity_test() {
	ft::vector<std::string> ft_vec_1(3, "aaa");
	ft::vector<std::string> ft_vec_2;
	ft_vec_2.reserve(10);
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft::vector<std::string>::iterator ft_first = ft_vec_1.begin();
	ft::vector<std::string>::iterator ft_last = ft_vec_1.end();
	ft_vec_2.insert(ft_vec_2.begin() + 2, ft_first, ft_last);
	
	std::vector<std::string> std_vec_1(3, "aaa");
	std::vector<std::string> std_vec_2;
	std_vec_2.reserve(10);
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std::vector<std::string>::iterator std_first = std_vec_1.begin();
	std::vector<std::string>::iterator std_last = std_vec_1.end();
	std_vec_2.insert(std_vec_2.begin() + 2, std_first, std_last);
	
	for (int i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void insert_iter_NOT_enough_capacity_test() {
	ft::vector<std::string> ft_vec_1(8, "aaa");
	ft::vector<std::string> ft_vec_2;
	ft_vec_2.reserve(10);
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft_vec_2.push_back("bbb");
	ft::vector<std::string>::iterator ft_first = ft_vec_1.begin();
	ft::vector<std::string>::iterator ft_last = ft_vec_1.end();
	ft_vec_2.insert(ft_vec_2.begin() + 2, ft_first, ft_last);
	
	std::vector<std::string> std_vec_1(8, "aaa");
	std::vector<std::string> std_vec_2;
	std_vec_2.reserve(10);
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std_vec_2.push_back("bbb");
	std::vector<std::string>::iterator std_first = std_vec_1.begin();
	std::vector<std::string>::iterator std_last = std_vec_1.end();
	std_vec_2.insert(std_vec_2.begin() + 2, std_first, std_last);
	
	for (int i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void insert_iter_elems_empty_vec_test() {
	ft::vector<std::string> ft_vec_1(5, "aaa");
	std::vector<std::string> std_vec_1(5, "aaa");
	
	ft::vector<std::string> ft_vec_2;
	std::vector<std::string> std_vec_2;
	
	ft_vec_2.insert(ft_vec_2.begin(), ft_vec_1.begin() + 1, ft_vec_1.end());
	std_vec_2.insert(std_vec_2.begin(), std_vec_1.begin() + 1, std_vec_1.end());
	for (size_t i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void insert_test() {
	insert_one_elem_test();
	insert_n_elems_enough_capacity_test();
	insert_n_elems_NOT_enough_capacity_test();
	insert_n_elems_empty_vec_test();
	insert_iter_enough_capacity_test();
	insert_iter_NOT_enough_capacity_test();
	insert_iter_elems_empty_vec_test();
}

void erase_position_test() {
	ft::vector<std::string> ft_vec_1(10, "aaa");
	std::vector<std::string> std_vec_1(10, "aaa");
	ft_vec_1.erase(ft_vec_1.end() - 2);
	std_vec_1.erase(std_vec_1.end() - 2);
	assert(ft_vec_1.size() == std_vec_1.size());
	assert(ft_vec_1.capacity() == std_vec_1.capacity());

	ft::vector<std::string> ft_vec_2(10, "aaa");
	std::vector<std::string> std_vec_2(10, "aaa");
	ft_vec_2.erase(ft_vec_2.begin() + 2);
	std_vec_2.erase(std_vec_2.begin() + 2);
	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void erase_first_last_test() {
	ft::vector<std::string> ft_vec_1(10, "aaa");
	ft_vec_1.erase(ft_vec_1.begin() + 2, ft_vec_1.end() - 2);

	std::vector<std::string> std_vec_1(10, "aaa");
	std_vec_1.erase(std_vec_1.begin() + 2, std_vec_1.end() - 2);

	for (size_t i = 0; i < ft_vec_1.size(); ++i) {
		assert(ft_vec_1[i] == std_vec_1[i]);
	}

	assert(ft_vec_1.size() == std_vec_1.size());
	assert(ft_vec_1.capacity() == std_vec_1.capacity());

	ft::vector<std::string> ft_vec_2(10, "aaa");
	ft_vec_2.erase(ft_vec_2.begin(), ft_vec_2.end());

	std::vector<std::string> std_vec_2(10, "aaa");
	std_vec_2.erase(std_vec_2.begin(), std_vec_2.end());

	for (size_t i = 0; i < ft_vec_2.size(); ++i) {
		assert(ft_vec_2[i] == std_vec_2[i]);
	}

	assert(ft_vec_2.size() == std_vec_2.size());
	assert(ft_vec_2.capacity() == std_vec_2.capacity());
}

void erase_test() {
	erase_position_test();
	erase_first_last_test();
}

void modifiers_test() {
	swap_test();
	clear_test();
	insert_test();
	erase_test();
}

int main() {
	test_constructor();
	reserve_test();
	iterator_test();
	element_access_test();
	modifiers_test();
	
	return 0;
}
