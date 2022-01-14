/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:38:04 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/14 21:20:47 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include "Enable_if.hpp"
namespace ft
{

struct	input_iterator_tag {};
struct	output_iterator_tag {};
struct	forward_iterator_tag : public input_iterator_tag {};
struct	bidirectional_iterator_tag : public forward_iterator_tag {};
struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
struct	iterator
{
	typedef	Category 	iterator_category;
	typedef	T			value_type;
	typedef	Distance	difference_type;
	typedef	Pointer		pointer;
	typedef	Reference	reference;
};

template <class Iterator>
struct	iterator_traits
{
	typedef typename	Iterator::iterator_category	iterator_category;
	typedef typename	Iterator::value_type		value_type;
	typedef typename	Iterator::difference_type	difference_type;
	typedef typename	Iterator::pointer			pointer;
	typedef typename	Iterator::reference			reference;
};
template <class T>
struct	iterator_traits<T*>
{
	typedef	random_access_iterator_tag	iterator_category;
	typedef	T							value_type;
	typedef	ptrdiff_t					difference_type;
	typedef	T*							pointer;
	typedef	T&							reference;
};
template <class T>
struct iterator_traits<T* const>
{
	typedef 		random_access_iterator_tag 	iterator_category;
	typedef 		T							value_type;
	typedef 		ptrdiff_t					difference_type;
	typedef const	T*							pointer;
	typedef const	T&							reference;
};

template <class T>
class random_access_iterator : private ft::iterator<random_access_iterator_tag, T>
{
	public :
		typedef T		value_type;
		typedef	T*		pointer;
		typedef	T&		reference;

		typedef typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

	protected:
		pointer _p;
	
	public:
		random_access_iterator() : _p(NULL) {}
		random_access_iterator(pointer ptr) : _p (ptr) {}
		random_access_iterator(random_access_iterator const &cpy) : _p(cpy._p) {}
		~random_access_iterator() {}

		random_access_iterator	&operator=(random_access_iterator const &rhs)
		{
			if (this == &rhs)
				return *this;
			_p = rhs._p;
			return *this;
		}
		pointer		base() const 						{return _p;}
		reference	operator*() const					{return *_p;}
		pointer		operator->() const					{return &operator*();}
		reference	operator[](difference_type n) const	{return *(_p + n);}

		operator random_access_iterator<const T>(void)
		{
			return (random_access_iterator<const T>(_p));
		}

		random_access_iterator operator+(difference_type n) const {return random_access_iterator(_p + n);}
		random_access_iterator operator-(difference_type n) const {return random_access_iterator(_p - n);}

		random_access_iterator	&operator++()
		{
			++_p;
			return *this;
		}
		random_access_iterator	operator++(int)
		{
			random_access_iterator tmp = *this;
			++_p;
			return tmp;
		}
		random_access_iterator	operator+=(difference_type n)
		{
			_p += n;
			return *this;
		}

		random_access_iterator	&operator--()
		{
			--_p;
			return *this;
		}
		random_access_iterator	operator--(int)
		{
			random_access_iterator tmp = *this;
			--_p;
			return tmp;
		}
		random_access_iterator	operator-=(difference_type n)
		{
			_p -= n;
			return *this;
		}
};

template <class It1, class It2>
bool	operator==(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() == rhs.base());
}
template <class It1, class It2>
bool	operator!=(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() != rhs.base());
}
template <class It1, class It2>
bool	operator<(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() < rhs.base());
}
template <class It1, class It2>
bool	operator<=(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() <= rhs.base());
}
template <class It1, class It2>
bool	operator>(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() > rhs.base());
}
template <class It1, class It2>
bool	operator>=(const It1 &lhs, const It2 &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <typename f_T, typename f_U>
typename ft::random_access_iterator<f_T>::difference_type operator-(const random_access_iterator<f_T> &l, const random_access_iterator<f_U> &r)
{
	return (l.operator->() - r.operator->());
}

template <typename f_T>
random_access_iterator<f_T> operator+(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r)
{
	return (random_access_iterator<f_T>(r.operator->() + n));
}

template <typename f_T>
random_access_iterator<f_T> operator-(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r)
{
	return (random_access_iterator<f_T>(r.operator->() - n));
}

template <typename T, bool isConst, class Compare = std::less<T> >
class bidirectional_iterator : private ft::iterator<bidirectional_iterator_tag, T>
{
	public:
		typedef typename ft::enable_if_const<isConst, T>::value_type								value_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

	private:
		T*	_p;

	public:
		bidirectional_iterator() : _p(0) {}
		bidirectional_iterator(T* p) : _p(p) {}
		template <typename A, bool B, class C>
		bidirectional_iterator(const bidirectional_iterator<A, B, C>  &cpy, typename ft::enable_if<!B>::type* = 0) : _p(cpy.base()) {}
		~bidirectional_iterator() {}

	
		bidirectional_iterator& operator=(const bidirectional_iterator &cpy)
		{
			if (this == &cpy)
				return *this;
			_p = cpy._p;
		}

		pointer		base() const		{return _p;}
		reference	operator*() const	{return _p->data;}
		pointer		operator->() const	{return &operator*();}


		bool operator==(const bidirectional_iterator &rhs)
		{
			return (_p->data.first == rhs._p->data.first);
		}
		bool operator!=(const bidirectional_iterator &rhs)
		{
			return (_p->data.first != rhs._p->data.first);
		}

		bidirectional_iterator &operator++(void)
		{
			if (_p->right)
			{
				_p = _p->right;
				while (_p->_left)
					_p = _p->left;
			}
			else
			{
				while (_p->parent && _p->parent->right == _p)
					_p = _p->parent;
				if (_p->parent)
					_p = _p->parent;
			}
			return (*this);
		}
		bidirectional_iterator &operator++(int)
		{
			bidirectional_iterator tmp(*this);
			operator++();
			return tmp;
		}

		bidirectional_iterator &operator--()
		{
			if (_p->left)
			{
				_p = _p->left;
				while (_p->right)
					_p = _p->right;
			}
			else
			{
				while (_p->parent && _p->_parent->left == _p)
					_p = _p->parent;
				if (_p->parent)
					_p = _p->parent;
			}
			return *this;
		}
		bidirectional_iterator &operator--(int)
		{
			bidirectional_iterator tmp(*this);
			operator--();
			return tmp;
		}

		operator bidirectional_iterator<const T, true, Compare>(void)
		{
			return (bidirectional_iterator<const T, true, Compare>(_p));
		}


};


template <class Iterator>
class reverse_iterator
{
	public:
		typedef				Iterator										iterator_type;
		typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	iterator_traits<Iterator>::value_type			value_type;
		typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	iterator_traits<Iterator>::pointer				pointer;
		typedef typename	iterator_traits<Iterator>::reference			reference;

	protected:
		iterator_type _p;

	public:
		reverse_iterator() : _p(){}
		explicit reverse_iterator(iterator_type it) : _p(it){}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it): _p(rev_it.base()){}
		virtual	~reverse_iterator(){}

		iterator_type	base() const { return _p; }
		reference	operator*() const
		{
			iterator_type tmp_iter = _p;
			return *(--tmp_iter);
		}
		pointer		operator->() const {return &(operator*()); }
		reference	operator[](difference_type n) const {return (_p[-n - 1]);}

		reverse_iterator	operator+(difference_type n) const {return reverse_iterator(_p - n);}
		reverse_iterator	operator-(difference_type n) const {return reverse_iterator(_p + n);}
	
		reverse_iterator	&operator++()
		{
			--_p;
			return *this;
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator tmp = *this;
			--_p;
			return tmp;
		}
		reverse_iterator	&operator+=(difference_type n)
		{
			_p -= n;
			return *this;
		}
		reverse_iterator	&operator--()
		{
			++_p;
			return *this;
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator tmp = *this;
			++_p;
			return tmp;
		}
		reverse_iterator	&operator-=(difference_type n)
		{
			_p += n;
			return *this;
		}
		difference_type operator-(reverse_iterator const &r)
		{
			return (r.base() - this->base());
		}

};

template <class It1, class It2>
bool	operator==(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
{
	return (lhs.base() == rhs.base());
}
template <class It1, class It2>
bool	operator!=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
{
	return (lhs.base() != rhs.base());
}
template <class It1, class It2>
bool	operator<(const reverse_iterator<It1> &lhs,const reverse_iterator<It2> &rhs)
{
	return (lhs.base() > rhs.base());
}
template <class It1, class It2>
bool	operator<=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
{
	return (lhs.base() >= rhs.base());
}
template <class It1, class It2>
bool	operator>(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
{
	return (lhs.base() < rhs.base());
}
template <class It1, class It2>
bool	operator>=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator> &rev_it)
{
	return rev_it + n;
}

}
#endif
