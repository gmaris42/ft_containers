/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:20:59 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/12 15:38:15 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP
namespace ft {

template <bool Cond, typename Result=void>
struct enable_if { };

template <typename Result>
struct enable_if<true, Result>
{
 	typedef Result type;;
};

template <typename T, bool b_type>
struct integral_constant
{
	typedef T type;
	const static bool value = b_type;
};

template <class T> struct is_integral : public integral_constant<T, false> {};
template <> struct is_integral<bool> : public integral_constant<bool, true> {};
template <> struct is_integral<char> : public integral_constant<char, true> {};
template <> struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
template <> struct is_integral<signed char> : public integral_constant<signed char, true> {};
template <> struct is_integral<short int> : public integral_constant<short int, true> {};
template <> struct is_integral<int> : public integral_constant<int, true> {};
template <> struct is_integral<long int> : public integral_constant<long int, true> {};
template <> struct is_integral<long long int> : public integral_constant<long long int, true> {};
template <> struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};
template <> struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};
template <> struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
template <> struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};
template <> struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};

}
#endif