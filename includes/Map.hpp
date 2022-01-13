/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:58:44 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/12 17:53:54 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include <functional> // for std::less
#include <utility>    // for std::pair
#include "iterator.hpp"
#include "Enable_if.hpp"

namespace ft{
template<class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
	public:
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	std::pair<const Key, T>							value_type;
		typedef	Allocator										allocator_type;
		typedef	Compare											key_compare;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;

		typedef typename allocator_type::size_type				size_type;
		typedef	typename allocator_type::difference_type		difference_type;

		typedef	typename ft::random_access_iterator<T>			iterator;
		typedef	typename ft::random_access_iterator<const T>	const_iterator;
		typedef	typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		class	value_compare : std::binary_function<value_type, value_type, bool>
		{
			public:
				result_type				bool;
				first_argument_type		value_type;
				second_argument_type	value_type;

			protected:
				Compare	comp;
				value_compare(Compare c) : comp(c) {}

			public:
				bool operator()(const value_type &lhs, const value_type &rhs) const
				{
					return com(lhs.first, rhs.first);
				}
		};
	
	private:
		allocator_type	_alloc;
		key_compare		_compare;
		//tree
	
	public:
		explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _alloc(alloc), _compare(comp) {}
		template <class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = compare(), const Allocator &alloc = Allocator()) : _alloc(alloc), _compare(comp)
		{
			this->insert(first, last);
		}
		map(const map &cpy) : _alloc(cpy._alloc), _compare(cpy._compare)
		{
			this->insert(cpy.begin, cpy.end());
		}
		~map()
		{

		}

		map	&operator=(const map &rhs)
		{
			if (this == rhs)
				return *this;
			_alloc = rhs._alloc;
			_compare = rhs._compare;
			clear();
			this->insert(rhs.begin(), rhs.end());
		}

};
}
#endif
