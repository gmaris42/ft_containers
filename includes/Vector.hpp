/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:58:13 by gmaris            #+#    #+#             */
/*   Updated: 2021/12/16 18:59:53 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>

namespace ft {
template< class T, class Alloc = std::allocator<T> >
class vector
{
	/******************\
	** iterator class **
	\******************/



	public:
		/***************\
		** member type **
		\****************/
		typedef T 								value_type;
		typedef Alloc							allocator_type;
		typedef allocator_type::reference		reference;
		typedef allocator_type::pointer			pointer;
		typedef allocator_type::const_pointer	const_pointer;
		typedef ptrdiff_t 						difference_type;
		typedef size_t 							size_type;
		//typedef iterator iterator;
		//typedef          const_iterator
		//typedef          reverse_iterator
		//typedef          const_reverse_iterator;

	protected:

	public:
		/********************\
		** member functions **
		\********************/

		//Constructor
		explicit vector(const allocator_type &alloc = allocator_type())
		{

		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{

		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
		{

		}
		vector(const vector &x)
		{

		}
		~vector()
		{

		}
		
};

}
#endif
