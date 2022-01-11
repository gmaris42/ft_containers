/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_Iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:02:07 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/10 13:24:00 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <limits>
#include <iostream>
#include <memory>

namespace ft{
template<typename T, class Allocator = std::allocator<T> >
class vector_iterator
{
	public:
		typedef	typename Allocator::value_type		value_type;
		typedef			 T*			pointer;
		typedef			 T&			reference;
		typedef	typename std::ptrdiff_t	difference_type;
		typedef			 size_t						size_type;

		typedef	std::random_access_iterator_tag		iterator_categoy;

	private:
		pointer _val;

	public:
		vector_iterator(pointer val = 0) : _val(val) {}
		vector_iterator(const vector_iterator &cpy) { _val = cpy.getPtr();}
		~vector_iterator() {}

		vector_iterator& operator=(const vector_iterator &rhs)
		{
			_val = rhs._val;
			return *this;
		}
		pointer getPtr() const {return _val;}

		reference	operator*()  const {return *_val;}
		pointer		operator->() const {return _val;}

		vector_iterator&	operator++() {++_val; return *this;}
		vector_iterator&	operator--() {--_val; return *this;}
		vector_iterator		operator++(int)
		{
			vector_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		vector_iterator		operator--(int)
		{
			vector_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		friend bool	operator==(const vector_iterator& lhs, const vector_iterator& rhs) {return lhs._val == rhs._val;}
		friend bool	operator!=(const vector_iterator& lhs, const vector_iterator& rhs) {return lhs._val != rhs._val;}
		friend bool	operator>=(const vector_iterator& lhs, const vector_iterator& rhs) {return lhs._val >= rhs._val;}
		friend bool	operator<=(const vector_iterator& lhs, const vector_iterator& rhs) {return lhs._val <= rhs._val;}
		friend bool	operator<(const vector_iterator& lhs, const vector_iterator& rhs)  {return lhs._val <  rhs._val;}
		friend bool	operator>(const vector_iterator& lhs, const vector_iterator& rhs)  {return lhs._val >  rhs._val;}

		vector_iterator& operator+=(difference_type nb)
		{
			_val += nb;
			return *this;
		}
		vector_iterator& operator-=(difference_type nb)
		{
			_val -= nb;
			return *this;
		}
		vector_iterator operator+(difference_type nb) const
		{
			vector_iterator tmp(*this);

			tmp._val += nb;
			return tmp;
		}
		vector_iterator operator-(difference_type nb) const
		{
			vector_iterator tmp(*this);

			tmp._val -= nb;
			return tmp;
		}

		reference	operator[](difference_type nb) const
		{
			return (*(*this + nb));
		}

		friend vector_iterator operator+(size_type nb, const vector_iterator& it)
		{
			vector_iterator tmp(it);
			return tmp += nb;
		}
		friend difference_type	operator-(vector_iterator &lhs, vector_iterator &rhs)
		{
			return lhs._val - rhs._val;
		}
};
}
#endif