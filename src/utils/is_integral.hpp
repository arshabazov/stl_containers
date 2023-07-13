//
// Created by Cristie Dell on 3/25/23.
//

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {
	template <class T, T val>
	struct integral_constant {
		static const T value = val;
		typedef T value_type;
		typedef integral_constant<T, val> type;
		operator T() const { return value; }
	};
	
	typedef integral_constant<bool, false> false_type;
	typedef integral_constant<bool, true> true_type;
	
	template <typename T> struct is_integral: false_type {};
	template <typename T> struct is_integral<const T>: is_integral<T> {};
	
	template <> struct is_integral<bool>: true_type {};
	template <> struct is_integral<char>: true_type {};
	template <> struct is_integral<wchar_t>: true_type {};
	template <> struct is_integral<signed char>: true_type {};
	template <> struct is_integral<short>: true_type {};
	template <> struct is_integral<int>: true_type {};
	template <> struct is_integral<long>: true_type {};
	template <> struct is_integral<long long>: true_type {};
	
	
	template <> struct is_integral<unsigned char>: true_type {};
	template <> struct is_integral<unsigned short>: true_type {};
	template <> struct is_integral<unsigned int>: true_type {};
	template <> struct is_integral<unsigned long>: true_type {};
	template <> struct is_integral<unsigned long long>: true_type {};
}

#endif //IS_INTEGRAL_HPP