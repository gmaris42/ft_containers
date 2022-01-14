/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:58:13 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/14 19:47:06 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_vector_HPP
#define FT_vector_HPP

#define _RED     "\x1b[31m"
#define _GREEN   "\x1b[32m"
#define _YELLOW  "\x1b[33m"
#define _BLUE    "\x1b[34m"
#define _MAGENTA "\x1b[35m"
#define _CYAN    "\x1b[36m"
#define _RESET   "\x1b[0m"

#include <memory>
#include <exception>
#include <stdexcept>
#include "iterator.hpp"
#include "Enable_if.hpp"

namespace ft {
template<typename T, typename Allocator = std::allocator<T> >
class vector
{
	public:
		typedef	T												value_type;
		typedef	Allocator										allocator_type;
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

	private:
		pointer			_p;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
	
		/*
		** CANON
		*/

		explicit vector(const allocator_type &alloc = allocator_type()) :
			_p(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
		}
		explicit vector(size_t n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
			_p(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			this->assign(n, val);
		}
		template<class Iterator>
		vector(Iterator first, Iterator last, const allocator_type &alloc = allocator_type()) :
			_p(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			this->assign(first, last);
		}
		vector(const vector &src) :
			_p(NULL), _size(0), _capacity(0), _alloc(src._alloc)
		{
			this->assign(src.begin(), src.end());
		}

		~vector()
		{
			this->clear();
			_alloc.deallocate(_p, this->_capacity);
		}

		vector &operator=(vector const &rhs)
		{
			if (*this == rhs)
				return (*this);
			this->clear();
			this->assign(rhs.begin(), rhs.end());
			this->_alloc = rhs._alloc;
			return (*this);
		}

		/*
		** ITERATORS DONE
		*/
			  iterator begin()
		{
			return iterator(_p);
		}
		const_iterator begin() const
		{
			return const_iterator(_p);
		}
		
			  iterator end()
		{
			return iterator(_p + _size);
		}
		const_iterator end() const
		{
			return const_iterator(_p + _size);
		}

			  reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

			  reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		/*
		** CAPACITY
		*/
	
		size_type size(void) const
		{
			return (_size);
		}

		size_type max_size(void) const
		{
			return (_alloc.max_size());
		}

		void	resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				iterator it = begin();
				size_type i = 0;
				while (i < n)
				{
					++it;
					++i;
				}
				erase(it, end());
			}
			else
				insert(end(), n - _size, val);
		}

		size_type capacity(void) const
		{
			return _capacity;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void reserve(size_type n)
		{
			size_type new_capa = n;
			size_type actual_capa = _size;
			size_type i = 0;
			if (n < 0 || n > max_size())
				throw std::length_error("ft::vector::reserve");
			if (n < _capacity)
				return ;
			if (actual_capa * 2 > n)
				new_capa = actual_capa * 2;
			pointer tmp = _alloc.allocate(new_capa);
			while (i < _size)
			{
				_alloc.construct(tmp + i, _p[i]);
				_alloc.destroy(&_p[i]);
				i++;
			}
			this->clear();
			_alloc.deallocate(_p, _capacity);
			_p = tmp;
			_capacity = new_capa;
			_size = i;
		}

	
		/*
		** ELEM ACCES
		*/
	
			  reference operator[](size_type n)
		{
			return *(_p + n);
		}
		const_reference operator[](size_type n) const
		{
			return *(_p + n);
		}

			  reference at(size_type n)
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			return _p[n];
		}
		const_reference at(size_type n) const
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			return _p[n];
		}

			  reference front(void)
		{
			return *begin();
		}
		const_reference front(void) const
		{
			return *begin();
		}

			  reference back(void)
		{
			return *--end();
		}
		const_reference back(void) const
		{
			return *--end();
		}
	
		/*
		** MODIFIERS
		*/
	
		void	assign(size_type count, const value_type &value)
		{
			clear();
			insert(begin(), count, value);
		}
		template <class InputIterator>
		void	assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			clear();
			insert(begin(), first, last);
		}

		void	push_back(const value_type &val)
		{
			reserve(_size + 1);
			insert(end(), val);
		}

		void	pop_back()
		{
			erase(--end());
		}

		iterator	insert(iterator pos, const value_type &val)
		{
			size_type dist = 0;
			iterator bg = begin();
			while (bg != pos)
			{
				++dist; ++bg;
			}
			insert(pos, 1, val);
			return begin() + dist;
		}
		void	insert(iterator pos, size_type n, const value_type &val)
		{
			if (n < 0)
				throw std::length_error("ft::vector::insert");
			if (n == 0)
				return ;
			size_type dist = 0;
			iterator bg = begin();
			while (bg != pos)
			{
				++dist; ++bg;
			}
			size_type nb_move = 0;
			iterator end = this->end();
			while (bg != end)
			{
				++nb_move; ++ bg;
			}
			if (_size + n > _capacity)
				reserve(_size + n);
			pointer tmp = _p + dist + (nb_move - 1);
			while (nb_move > 0)
			{
				_alloc.construct(tmp + n, *(tmp));
				_alloc.destroy(tmp);
				--tmp;
				--nb_move;
			}
			size_type j = 0;
			tmp = _p + dist;
			while (j < n)
			{
				_alloc.construct(tmp + j, val);
				++j;
			}
			_size += n;
		}
		template<class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
		insert(iterator pos, InputIterator first, InputIterator last)
		{
			size_type dist = 0;
			iterator bg = begin();
			while (bg != pos)
			{
				++dist; ++ bg;
			}
			size_type nb_move = 0;
			iterator end = this->end();
			while (bg != end)
			{
				++nb_move; ++ bg;
			}
			size_type n = 0;
			InputIterator tmp_it = first;
			while (tmp_it != last)
			{
				++n; ++ tmp_it;
			}
			if (_size + n > _capacity)
				reserve(_size + n);
			pointer tmp = _p + dist + (nb_move - 1);
			while (nb_move > 0)
			{
				_alloc.construct(tmp + n, *(tmp));
				_alloc.destroy(tmp);
				--tmp;
				--nb_move;
			}
			size_type j = 0;
			tmp = _p + dist;
			while (j < n)
			{
				_alloc.construct(tmp + j, *first);
				++first;
				++j;
			}
			_size += n;
		}

		iterator erase(iterator pos)
		{
			return erase(pos, ++pos);
		}
		iterator erase(iterator first, iterator last)
		{
			size_type start = first - begin();
			size_type nb = 0;
			iterator tmp(first);
			while (first != last)
			{
				++first;
				++nb;
			}
			if (_size > 0 && nb > 0)
			{
				size_type i = 0;
				while (i < nb)
				{
					_alloc.destroy(_p + start + i);
					++i;
				}
				size_type j = start;
				while (j + nb < _size)
				{
					_alloc.construct(_p + j, *(_p + j + nb));
					_alloc.destroy(_p + j + nb);
					++j;
				}
				_size -= nb;
			}
			return iterator(_p + start);
		}

		void	swap(vector &x)
		{
			if (this == &x)
				return ;
			value_type	*tmp(_p);
			size_type	tmp_size(_size);
			size_type	tmp_capa(_capacity);

			_p = x._p;
			_size = x._size;
			_capacity = x._capacity;

			x._p = tmp;
			x._size = tmp_size;
			x._capacity = tmp_capa;
		}

		void	clear()
		{
			this->erase(this->begin(), this->end());
		}
	
		/*
		** ALLOCATOR
		*/

		allocator_type	get_allocator() const
		{
			return _alloc;
		}
};

template<class T, class Alloc>
bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	
	typename vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
	typename vector<T, Alloc>::const_iterator it_rhs = rhs.begin();

	while (it_lhs != lhs.end() && it_rhs != rhs.end())
	{
		if (*it_lhs != *it_rhs)
			return false;
		++it_lhs;
		++it_rhs;
	}
	if (it_lhs != lhs.end() || it_rhs != rhs.end())
		return false;
	return true;
}

template<class T, class Alloc>
bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template<class T, class Alloc>
bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	typename vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
	typename vector<T, Alloc>::const_iterator it_rhs = rhs.begin();
	while (it_lhs != lhs.end() && it_rhs != rhs.end())
	{
		if (*it_lhs < *it_rhs)
			return true;
		if (*it_lhs > *it_rhs)
			return false;
		++it_rhs;
		++it_lhs;
	}
	if (it_lhs == lhs.end() && it_rhs != rhs.end())
		return true;
	return false;
}

template<class T, class Alloc>
bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (lhs < rhs || lhs == rhs);
}

template<class T, class Alloc>
bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (!(lhs < rhs) && lhs != rhs);
}

template<class T, class Alloc>
bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (lhs > rhs || lhs == rhs);
}

template<class T, class Alloc>
void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
	x.swap(y);
}

}
#endif
