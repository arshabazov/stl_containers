//
// Created by Cristie Dell on 3/17/23.
//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template <class RandomAccessIterator> //Iterator of type Random Access Iterator
class reverse_iterator : public iterator<
		typename ft::iterator_traits<RandomAccessIterator>::iterator_category,
		typename ft::iterator_traits<RandomAccessIterator>::value_type,
		typename ft::iterator_traits<RandomAccessIterator>::difference_type,
		typename ft::iterator_traits<RandomAccessIterator>::pointer,
		typename ft::iterator_traits<RandomAccessIterator>::reference>
{
public:
	typedef RandomAccessIterator iterator_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference reference;
	
	reverse_iterator() : _current() {}
	
	explicit reverse_iterator(iterator_type other) : _current(other) {}
	
	template <class U>
	reverse_iterator(const reverse_iterator<U>& other) : _current(other.base()) {}
	
	iterator_type base() const {
		return _current;
	}
	
	reference operator*() const {
		iterator_type tmp =_current;
		return *--tmp;
	}
	
	pointer operator->() const {
		return &**this;
	}
	
	reverse_iterator& operator++() {
		--_current;
		return *this;
	}
	
	reverse_iterator operator++(int) {
		reverse_iterator tmp = *this;
		--_current;
		return tmp;
	}
	
	reverse_iterator& operator--() {
		++_current;
		return *this;
	}
	
	reverse_iterator operator--(int) {
		reverse_iterator tmp = *this;
		++_current;
		return tmp;
	}
	
	reverse_iterator& operator+=(difference_type n) {
		_current -= n;
		return *this;
	}
	
	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(_current - n);
	}
	
	reverse_iterator& operator-=(difference_type n) {
		_current += n;
		return *this;
	}
	
	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator(_current + n);
	}
	
	reference operator[](difference_type n) const {
		return *(*this + n);
	}

protected:
	iterator_type _current;
};

template <class Iterator>
bool operator==(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return !(lhs == rhs);
}

template <class Iterator>
bool operator<(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return rhs.base() < lhs.base();
}

template <class Iterator>
bool operator<=(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return !(rhs < lhs);
}

template <class Iterator>
bool operator>(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return rhs < lhs;
}

template <class Iterator>
bool operator>=(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return !(lhs < rhs);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return rhs.base() - lhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& iter)
{
	// return reverse_iterator<Iterator>(iter.base() - n);
	return iter + n;
}

} // namespace ft
#endif //REVERSE_ITERATOR_HPP