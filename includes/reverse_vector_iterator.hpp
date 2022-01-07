/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_reverse_vector_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:17:40 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/05 22:16:47 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_reverse_vector_iterator_HPP
#define REVERSE_reverse_vector_iterator_HPP

#include "reverse_vector_iterator.hpp"

namespace ft
{
template<class Iterator>
class ReverseIterator
{

	public:
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef			 size_t							size_type;

		typedef 		 Iterator						iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;

	private:
		iterator_type _it;

	public:
		ReverseIterator() : _it() {}
		ReverseIterator(iterator_type it) : _it(it) {}
		ReverseIterator(const ReverseIterator &cpy) : _it(cpy._it) {}
		~ReverseIterator() {}

		ReverseIterator &operator=(const ReverseIterator &rhs)
		{
			_it = rhs._it;
			return *this;
		}

		iterator_type base() const {return _it;}

		reference operator*() const
		{
			iterator_type tmp(_it);
			--tmp;
			return *tmp;
		}
		pointer operator->() const
		{
			iterator_type tmp(_it);
			--tmp;
			return tmp.operator->();
		}

		ReverseIterator &operator++()
		{
			--_it;
			return *this;
		}
		ReverseIterator &operator--()
		{
			++_it;
			return *this;
		}
		ReverseIterator &operator++(int)
		{
			ReverseIterator tmp(*this);
			++(*this);
			return tmp;
		}
		ReverseIterator &operator--(int)
		{
			ReverseIterator tmp(*this);
			--(this);
			return tmp;
		}
		
		friend bool	operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) {return lhs.base() == rhs.base();}
		friend bool	operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) {return lhs.base() != rhs.base();}
		friend bool	operator>=(const ReverseIterator& lhs, const ReverseIterator& rhs) {return lhs.base() <= rhs.base();}
		friend bool	operator<=(const ReverseIterator& lhs, const ReverseIterator& rhs) {return lhs.base() >= rhs.base();}
		friend bool	operator<(const ReverseIterator& lhs, const ReverseIterator& rhs)  {return lhs.base() >  rhs.base();}
		friend bool	operator>(const ReverseIterator& lhs, const ReverseIterator& rhs)  {return lhs.base() <  rhs.base();}

		ReverseIterator &operator+=(difference_type nb)
		{
			_it -= nb;
			return *this;
		}
		ReverseIterator &operator-=(difference_type nb)
		{
			_it += nb;
			return *this;
		}

		ReverseIterator operator+(difference_type nb) const
		{
			ReverseIterator it(_it - nb);
			return it;
		}
		ReverseIterator operator-(difference_type nb) const
		{
			ReverseIterator it(_it + nb);
			return it;
		}

		reference operator[](difference_type nb) const
		{
			return (*(*this + nb));
		}

		friend ReverseIterator operator-(size_type n, const ReverseIterator& rev_it)
		{
			return (rev_it + n);
		}
		friend ReverseIterator operator+(ReverseIterator &lhs, ReverseIterator &rhs)
		{
			return (rhs.base() - lhs.base());
		}
};
}
#endif