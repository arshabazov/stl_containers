//
// Created by Cristie Dell on 3/22/23.
//

#ifndef _RANDOM_ACCESS_ITERATOR_ALT_HPP
#define _RANDOM_ACCESS_ITERATOR_ALT_HPP

#include "./iterator_traits.hpp"

namespace ft {

template <class T>
class random_access_iterator: public ft::iterator<ft::random_access_iterator_tag, T> {
public:
	typedef random_access_iterator<T> iterator;
	
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;

protected:
	pointer _current;

public:
	
	random_access_iterator() {}
	
	explicit random_access_iterator(pointer ptr) : _current(ptr) {}
	
	random_access_iterator(const iterator& other): _current(other.base()) {}
	
	pointer base() const {
		return _current;
	}
	
	reference operator*() const {
		return *_current;
	}
	
	pointer operator->() const {
		return _current;
	}
	
	iterator& operator++() {
		++_current;
		return *this;
	}
	
	iterator operator++(int) {
		iterator tmp = *this;
		++_current;
		return tmp;
		// OR rand_iter(_current++);
	}
	
	iterator& operator--() {
		--_current;
		return *this;
	}
	
	iterator operator--(int) {
		iterator tmp = *this;
		--_current;
		return tmp;
		// OR rand_iter(_current--);
	}
	
	iterator& operator+=(difference_type n) {
		_current += n;
		return *this;
	}
	
	iterator operator+(difference_type n) const {
		return iterator(_current + n);
	}
	
	iterator& operator-=(difference_type n) {
		_current -= n;
		return *this;
	}
	
	iterator operator-(difference_type n) const {
		return iterator(_current - n);
	}
	
	reference operator[](difference_type n) const {
		return *(_current + n);
	}
	
	bool operator==(const iterator& other) const {
		return _current == other._current;
	}
	
	bool operator!=(const iterator& other) const {
		return !(*this == other);
	}
	
	bool operator<(const iterator& other) {
		return _current < other._current;
	}
	
	bool operator<=(const iterator& other) {
		return !(other < *this);
	}
	
	bool operator>(const iterator& other) {
		return other < *this;
	}
	
	bool operator>=(const iterator& other) {
		return !(*this < other);
	}
};

template <typename IteratorL, typename IteratorR>
bool operator==(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return lhs.base() == rhs.base();
}
template <typename IteratorL, typename IteratorR>
bool operator!=(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return !(lhs == rhs);
}
template <typename IteratorL, typename IteratorR>
bool operator<(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return lhs.base() < rhs.base();
}
template <typename IteratorL, typename IteratorR>
bool operator<=(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return !(rhs < lhs); // !(lhs > rhs)
}
template <typename IteratorL, typename IteratorR>
bool operator>(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return rhs < lhs;
}
template <typename IteratorL, typename IterR>
bool operator>=(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IterR>& rhs)
{
	return !(lhs < rhs);
}
template <typename IteratorL, typename IteratorR>
typename random_access_iterator<IteratorL>::difference_type
operator-(
		const random_access_iterator<IteratorL>& lhs,
		const random_access_iterator<IteratorR>& rhs)
{
	return lhs.base() - rhs.base();
}
template <typename Iterator>
typename random_access_iterator<Iterator>::difference_type
operator-(
		const random_access_iterator<Iterator>& lhs,
		const random_access_iterator<Iterator>& rhs)
{
	return lhs.base() - rhs.base();
}
template <typename Iterator>
random_access_iterator<Iterator>
operator+(
		typename random_access_iterator<Iterator>::difference_type n,
		const random_access_iterator<Iterator>& iterator)
{
	return random_access_iterator<Iterator>(iterator.base() + n);
}

} // namespace ft

#endif //RANDOM_ACCESS_ITERATOR_ALT_HPP

