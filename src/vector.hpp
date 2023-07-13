//
// Created by Cristie Dell on 2/25/23.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <iterator>
#include <unistd.h>
#include <iterator>
#include "utils/random_access_iterator.hpp"
#include "utils/is_integral.hpp"
#include "utils/enable_if.hpp"
#include <stdexcept>

//===----------------------------------------------------------------------------------------------===//
//===------------------------------------- << DECLARATION >> --------------------------------------===//
//===----------------------------------------------------------------------------------------------===//

namespace ft {
	
template<class T, class Allocator = std::allocator<T> >
class vector {

public:
	typedef T											value_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef value_type*									pointer;
	typedef const value_type							const_pointer;
	
	typedef std::size_t									size_type;
	typedef Allocator									allocator_type;
	typedef std::ptrdiff_t								difference_type;
	
	typedef ft::random_access_iterator<value_type>			iterator;
	typedef ft::random_access_iterator<const value_type>	const_iterator;
//	typedef std::reverse_iterator<iterator>				reverse_iterator;
//	typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

private:
	pointer _data; // a simple array of template type (generic) data
	size_type _size;
	size_type _capacity;
	allocator_type _alloc;
	
public:
	//===----------------------------------- << Constructor/Destructor >> -----------------------------------===//
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
	vector(const vector<T, Allocator>& other);
	~vector();
	vector<T, Allocator>& operator=(const vector<T, Allocator>& other);
	template<class InputIterator>
		void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const T& val);
	
	allocator_type get_allocator() const {
		return _alloc;
	}
	
//===----------------------------------------------------------------------------------------------===//
//===----------------------------------- << MEMBER Functions >> -----------------------------------===//
//===----------------------------------------------------------------------------------------------===//
		
	//===----------------------------------- << Iterators >> -----------------------------------===//
	iterator begin() {
		return iterator(_data);
	}
	
	const_iterator begin() const {
		return const_iterator(_data);
	}
	
	iterator end() {
		return iterator(_data + _size);
	}
	
	const_iterator end() const {
		return const_iterator(_data + _size);
	}
	
	// Reverse iterator
//	reverse_iterator rbegin();
//	const_reverse_iterator rbegin() const;
//	reverse_iterator rend();
//	const_reverse_iterator rend() const;
		
	//===----------------------------------- << Capacity >> -----------------------------------===//
	bool empty() const {
		return _size == 0;
	}
	
	size_type size() const {
		return _size;
	}
	
	size_type capacity() const {
		return _capacity;
	}
	
	size_type max_size() const {
		return _alloc.max_size();
	}
	
	void reserve(size_type n);
	void resize(size_type size, T val = T());
	
	//===----------------------------------- << Element access >> -----------------------------------===//
	reference operator[](size_type n) {
		return *(_data + n);
	}
	
	const_reference operator[](size_type n) const {
		return *(_data + n);
	}
	
	const_reference at(size_type n) const {
		_range_check(n);
		return *(_data + n);
	}
	
	reference at(size_type n) {
		_range_check(n);
		return *(_data + n);
	}
	
	reference front() {
		return *begin();
	}
	
	const_reference front() const {
		return *begin();
	}
	
	reference back() {
		return *(end() - 1);
	}
	
	const_reference back() const {
		return *(end() - 1);
	}
	
	//===----------------------------------- << Modifiers >> -----------------------------------===//
	void push_back(const value_type& val);
	void pop_back();
	void swap(vector<T, Allocator>& other);
	void clear();
	
	// Iterator functions
	iterator insert(iterator position, const T& val);
	void insert(iterator position, size_type n, const T& val);
	template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

private:
	void _range_check(size_type index) {
		if (index >= _size) {
			throw std::range_error("ft::vector: Index out of range exception");
		}
	}
};

//===----------------------------------------------------------------------------------------------===//
//===----------------------------------- << NON-MEMBER Functions >> -------------------------------===//
//===----------------------------------------------------------------------------------------------===//
template<class T, class Allocator>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
template<class T, class Allocator>
	void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs);

//===----------------------------------------------------------------------------------------------===//
//===------------------------------------ << IMPLEMENTATION >> ------------------------------------===//
//===----------------------------------------------------------------------------------------------===//

//===----------------------------------- << Constructor/Destructor >> -----------------------------------===//

template<class T, class Allocator>
vector<T, Allocator>::vector(const allocator_type& alloc)
	: _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& alloc)
	: _data(nullptr), _size(n), _capacity(n), _alloc(alloc) {
	this->_data = this->_alloc.allocate(n);
	size_type i = 0;
	
	try {
		for (; i < n; ++i) {
			this->_alloc.construct(this->_data + i, val);
		}
		_size = _capacity = n;
	} catch (...) {
		for (int j = 0; j < i; ++j) {
			this->_alloc.destroy(this->_data + j);
		}
		this->_alloc.deallocate(this->_data, n);
		this->_size = 0;
		this->_capacity = 0;
		throw;
	}
}

template<class T, class Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	: _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {
	if (last < first)
		throw std::length_error("vector");
	this->_size = this->_capacity = last - first;
	this->_data = this->_alloc.allocate(this->_capacity);
	 
	size_type i = 0;
	try {
		for (; i < this->_size; ++i) {
			this->_alloc.construct(this->_data + i, *(first + i));
		}
	} catch (...) {
		for (size_type j = 0; j < i; ++j) {
			this->_alloc.destroy(this->_data + j);
		}
		this->_alloc.deallocate(this->_data, this->_capacity);
		this->_size = 0;
		this->_capacity = 0;
		throw;
	}
}

template<class T, class Allocator>
vector<T, Allocator>::vector(const vector<T, Allocator>& other)
	:  _data(nullptr), _size(0), _capacity(0), _alloc(other._alloc) {
	*this = other;
}

template<class T, class Allocator>
vector<T, Allocator>::~vector() {
	this->clear();
	if (this->_capacity != 0) {
		this->_alloc.deallocate(this->_data, this->_capacity);
		this->_data = nullptr;
		this->_capacity = 0;
	}
}

template<class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<T, Allocator>& other) {
	if (this == &other) {
		return *this;
	} else if (other.size() == 0) {
		this->clear();
	} else if (other.size() < this->_size) {
		std::copy(other.begin(), other.end(), this->_data);
		for (size_type i = other.size(); i < this->_size; ++i) {
			this->_alloc.destroy(this->_data + i);
		}
		this->_size = other.size();
	} else if (other.size() < this->capacity()) {
		std::copy(other.begin(), other.end(), this->_data);
		this->_size = other.size();
	} else {
		pointer new_data = this->_alloc.allocate(other.size());
		size_type i = 0;
		try {
			for (; i < other.size(); ++i) {
				this->_alloc.construct(new_data + i, other[i]);
			}
		} catch (...) {
			for (int j = 0; j < i; ++j) {
				this->_alloc.destroy(new_data + j);
			}
			this->_alloc.deallocate(new_data, other.size());
			throw;
		}
		if (this->_size > 0) {
			for (size_type j = 0; j < this->_size; ++j) {
				this->_alloc.destroy(this->_data + j);
			}
			this->_alloc.deallocate(this->_data, this->_capacity);
		}
		this->_data = new_data;
		this->_size = this->_capacity = other.size();
		if (this->_alloc != other._alloc) {
			this->_alloc = other.get_allocator();
		}
	}
	return *this;
}

//template<class InputIterator>
//void assign(InputIterator first, InputIterator last)
//void assign(size_type n, const T& val);

//===----------------------------------------------------------------------------------------------===//
//===----------------------------------- << MEMBER Functions >> -----------------------------------===//
//===----------------------------------------------------------------------------------------------===//

//===----------------------------------- << Capacity >> -----------------------------------===//
template<class T, class Allocator>
void vector<T, Allocator>::reserve(size_type n) {
	if (n < this->_capacity) {
		return;
	}
	if (n > this->max_size()) {
		throw std::length_error("System Error: Length exceeds available memory");
	}
	pointer new_data = this->_alloc.allocate(n);
	size_type i = 0;
	try {
		for (; i < this->_size; ++i) {
			this->_alloc.construct(new_data + i, this->_data[i]);
		}
	} catch (...) {
		for (int j = 0; j < i; ++j) {
			this->_alloc.destroy(new_data + j);
		}
		this->_alloc.deallocate(new_data, n);
		throw;
	}
	if (this->_size > 0) {
		for (size_type j = 0; j < this->_size; ++j) {
			this->_alloc.destroy(this->_data + j);
		}
		this->_alloc.deallocate(this->_data, this->_capacity);
	}
	this->_data = new_data;
	this->_capacity = n;
}

//template<class T, class Allocator>
//void vector<T, Allocator>::resize(size_type size, T val) {}

//===----------------------------------- << Modifiers >> -----------------------------------===//
template<class T, class Allocator>
void vector<T, Allocator>::push_back(const value_type& val) {
	this->insert(this->end(), val);
}

template<class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	--this->_size;
	this->_alloc.destroy(this->_data + this->_size);
}

template<class T, class Allocator>
void vector<T, Allocator>::swap(vector<T, Allocator>& other) {
	std::swap(this->_data, other._data);
	std::swap(this->_size, other._size);
	std::swap(this->_capacity, other._capacity);
	if (this->_alloc != other._alloc) {
		std::swap(this->_alloc, other._alloc);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::clear() {
	for (size_type i = 0; i < this->_size; ++i) {
		this->_alloc.destroy(this->_data + i);
	}
	this->_size = 0;
}

// Iterator functions
template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator position, const T& val) {
	size_type offset = position - this->begin();
	this->insert(position, 1, val);

	return this->begin() + offset;
}

template<class T, class Allocator>
void vector<T, Allocator>::insert(iterator position, size_type n, const T& val) {
	if (n == 0) {
		return ;
	}
	if (this->_size + n < this->_capacity) {
		if (position == this->end()) {
			while (n > 0) {
				this->_alloc.construct(this->_data + this->_size++, val);
				--n;
			}
		} else {
			size_type index = this->_size - 1;
			for (size_type i = 0; i < n; ++i) {
				this->_alloc.construct(this->_data + (index + n - i), this->_data[index - i]);
			}
			for (size_type i = 0; i < n; ++i) {
				this->_alloc.construct(&(*position) + i, val);
			}
			this->_size += n;
		}
	} else {
		size_type offset = position - this->begin();
		size_type new_capacity = this->capacity() > 0 ? this->capacity() * 2 : n;
		pointer new_data = this->_alloc.allocate(new_capacity);
		size_type i = 0;
		try {
			for (; i < offset; ++i) {
				this->_alloc.construct(new_data + i, this->_data[i]);
			}
			for (; i < offset + n; ++i) {
				this->_alloc.construct(new_data + i, val);
			}
			for (size_type j = offset; j < this->_size; ++j, ++i) {
				this->_alloc.construct(new_data + i, this->_data[j]);
			}
		} catch (...) {
			for (size_type j = 0; j < i; ++j) {
				this->_alloc.destroy(new_data + j);
			}
			this->_alloc.deallocate(new_data, new_capacity);
			throw;
		}
		if (this->_size > 0) {
			for (size_type j = 0; j < this->_size; ++j) {
				this->_alloc.destroy(this->_data + j);
			}
			this->_alloc.deallocate(this->_data, this->_capacity);
		}
		this->_data = new_data;
		this->_capacity = new_capacity;
		this->_size = i;
	}
}

template<class T, class Allocator>
template <class InputIterator>
void vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*) {
	if (first >= last) {
		return ;
	}
	size_type offset = position - this->begin();
	size_type count = last - first;
	
	if (this->_size + count < this->_capacity) {
		if (position == this->end()) {
			for (; first != last; ++first) {
				this->_alloc.construct(this->_data + this->_size++, *first);
			}
		} else {
			size_type index = this->_size - 1;
			for (size_type i = 0; i < count; ++i) {
				this->_alloc.construct(this->_data + (index + count - i), this->_data[index - i]);
			}
			size_type i = offset;
			for (; first != last; ++first, ++i) {
				this->_alloc.construct(this->_data + i, *first);
			}
			this->_size += count;
		}
	} else {
		size_type new_capacity = this->capacity() > 0 ? this->capacity() * 2 : count;
		pointer new_data = this->_alloc.allocate(new_capacity);
		size_type i = 0;
		try {
			for (; i < offset; ++i) {
				this->_alloc.construct(new_data + i, this->_data[i]);
			}
			for (; first != last; ++first, ++i) {
				this->_alloc.construct(new_data + i, *first);
			}
			for (size_type j = offset; j < this->_size; ++j, ++i) {
				this->_alloc.construct(new_data + i, this->_data[j]);
			}
		} catch (...) {
			for (size_type j = 0; j < i; ++j) {
				this->_alloc.destroy(new_data + j);
			}
			this->_alloc.deallocate(new_data, new_capacity);
			throw;
		}
		if (this->_size > 0) {
			for (size_type j = 0; j < this->_size; ++j) {
				this->_alloc.destroy(this->_data + j);
			}
			this->_alloc.deallocate(this->_data, this->_capacity);
		}
		this->_data = new_data;
		this->_capacity = new_capacity;
		this->_size = i;
	}
}
template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator position) {
	return erase(position, position + 1);
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last) {
	pointer first_trp = &(*first);
	pointer last_ptr = &(*last);
	size_type count = last - first;
	
	for (; first_trp != last_ptr; first_trp++) {
		this->_alloc.destroy(first_trp);
	}
	if (last != this->end()) {
		first_trp = &(*first);
		for(; last != this->end(); ++last) {
			this->_alloc.construct(first_trp++, *last_ptr++);
		}
	}
	this->_size -= count;
	return first;
}

//===----------------------------------------------------------------------------------------------===//
//===----------------------------------- << NON-MEMBER Functions >> -------------------------------===//
//===----------------------------------------------------------------------------------------------===//

//template<class T, class Allocator>
//bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
//
//template<class T, class Allocator>
//void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs);

} // namespace ft
#endif //VECTOR_HPP