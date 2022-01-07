/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:58:13 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/06 14:27:24 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_vector_HPP
#define FT_vector_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include "vector_Iterator.hpp"
#include "reverse_vector_iterator.hpp"

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

		typedef size_t										size_type;
		typedef	typename allocator_type::difference_type	difference_type;

		typedef	ft::vector_iterator<value_type>			iterator;
		typedef	ft::vector_iterator<const value_type>	const_iterator;


		typedef	ft::ReverseIterator<iterator>			reverse_iterator;
		typedef	ft::ReverseIterator<const_iterator>		const_reverse_iterator;

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

		void	reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("ft::vector::reserve");
			if (n <= _capacity)
				return ;
			value_type *new_p = _alloc.allocate(n);
			size_type i = 0;
			while (i < _size)
			{
				_alloc.construct(&new_p[i], _p[i]);
				_alloc.destroy(&_p[i]);
				++i;
			}
			_alloc.deallocate(_p, _capacity);
			_capacity = n;
			_p = new_p;
		}

	
		/*
		** ELEM ACCES
		*/
	
			  reference operator[](size_type n)
		{
			return _p[n];
		}
		const_reference operator[](size_type n) const
		{
			return _p[n];
		}

			  reference at(size_type n)
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			return *this[n];
		}
		const_reference at(size_type n) const
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			return *this[n];;
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
	
		template<class InputIterator>
		void	assign(InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}
		void	assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void	push_back(const value_type &val)
		{
			reserve(_calc_new_capacity(_size + 1));
			insert(end(), val);
		}

		void	pop_back()
		{
			erase(--end());
		}

		iterator	insert(iterator pos, const value_type &val)
		{
			insert(pos, static_cast<size_type>(1), val);
			return pos;
		}
		void	insert(iterator pos, size_type n, const value_type &val)
		{
			if (n == 0)
				return ;
			
			size_type			index = pos - begin();
			reserve(_size + n);
			_make_room(index, n);
			size_type	i = 0;
			while (i < n)
			{
				_alloc.construct(&_p[index + i], val);
				++i;
			}
			_size += n;
		}
		template<class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last)
		{
			size_t index = position - begin();
			size_t n = last - first;
			allocator_type alloc;

			reserve(_size + n);

			vector tmp(begin() + index, this->end());

			for (size_t i = 0; i < tmp.size(); i++)
				pop_back();
			while (first != last)
			{
				push_back(static_cast<T*>(*first));
				++first;
			}
			for (iterator it = tmp.begin(); it != tmp.end(); it++)
				push_back(*it);
		}

		iterator erase(iterator pos)
		{
			return erase(pos, pos + 1);
		}
		iterator erase(iterator first, iterator last)
		{
			size_type nb = last - first;
			size_type start = first - begin();
			size_type end = start + nb;

			size_type i = start;
			while (i < end)
			{
				_alloc.destroy(_p + i);
				++i;
			}
			while (i < _size)
			{
				_alloc.construct(&_p[i - nb], _p[i]);
				//_alloc.destroy[_p + i];
				++i;
			}
			_size -= nb;
			return first;
		}

		void	swap(vector &x)
		{
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

		/*
		** help fonction
		*/
	private:
			/*
			** Capacity calc
			*/
		size_type _calc_new_capacity(size_type nb_elem)
		{
			if (_capacity == 0)
				return nb_elem;
			
			size_type new_capa = _capacity;
			while (new_capa < nb_elem)
				new_capa *=2;
			return (new_capa);
		}

			/*
			** Make room for insert
			*/
		void _make_room(size_t index, size_t nb_move)
		{
			if (_size == 0)
				return ;
			size_type i = _size;
			while (i >= index && i > 0)
			{
				_alloc.construct(&_p[i + nb_move], _p[i]);
				_alloc.destroy(&_p[i]);
				--i;
			}
		}


};

template<class T, class Alloc>
bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	
	typename vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
	typename vector<T, Alloc>::const_iterator it_rhs = rhs.begin();

	while (it_lhs != lhs.end())
	{
		if (*it_lhs != *it_rhs)
			return false;
		++it_lhs;
		++it_rhs;
	}
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
	while (it_rhs != rhs.end())
	{
		if (it_lhs == lhs.end() || *it_lhs < *it_rhs)
			return true;
		++it_rhs;
		++it_lhs;
	}
	return false;
}

template<class T, class Alloc>
bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs > rhs);
}

template<class T, class Alloc>
bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (lhs > rhs);
}

template<class T, class Alloc>
bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

template<class T, class Alloc>
void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
	x.swap(y);
}

}
#endif

