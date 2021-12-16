/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:02:07 by gmaris            #+#    #+#             */
/*   Updated: 2021/12/16 18:59:54 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft{

template<class T, class Alloc>
class iterator
{	
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
	
	public:
		iterator(const iterator&);
		~iterator();

		iterator	&operator=(const iterator &lhs)
		{
			this->p = lhs.p;
		}
		iterator	&operator++() //prefix increment
		{
			this->p += ;
			return *this;
		}
		reference	operator*();
	
	public:
		int *p;
};

template<class T, class Alloc>
class input_iterator : public virtual iterator<T, Alloc>
{
	public:
		iterator	operator++(int); //postfix increment
		value_type	operator*() const;
		pointer		operator->();

		friend bool	operator==(const iterator &rhs, const iterator &lhs);
		friend bool	operator!=(const iterator &rhs, const iterator &lhs);
};

template<class T, class Alloc>
class output_iterator : public virtual iterator<T, Alloc>
{
	public:
		reference	operator*() const;
		iterator	operator++(int); //postfix increment
};


template<class T, class Alloc>
class forward_iterator : input_iterator<T, Alloc>, output_iterator<T, Alloc>
{
};

template<class T, class Alloc>
class bidirectional_iterator : forward_iterator<T, Alloc>
{
	iterator	&operator--(); //prefix decrement
	iterator	&operator--(int); //postfix decrement
};


template<class T, class Alloc>
class random_access_iterator : bidirectional_iterator<T, Alloc>
{
	iterator		&operator+=(size_type lhs);
	iterator		&operator-=(size_type lhs);

	friend bool		operator<(const iterator &rhs, const iterator &lhs);
	friend bool		operator>(const iterator &rhs, const iterator &lhs);
	friend bool		operator<=(const iterator &rhs, const iterator &lhs);
	friend bool		operator>=(const iterator &rhs, const iterator &lhs);

	friend iterator	operator+(const iterator &rhs, size_type lhs);
	friend iterator	operator+(size_type rhs, const iterator &lhs);

	friend iterator	operator-(const iterator &rhs, size_type lhs);
	friend iterator	operator-(size_type rhs, const iterator &lhs);

	reference operator[](size_type) const;

}


}
#endif