/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:58:44 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/19 18:55:28 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include "iterator.hpp"
#include "Enable_if.hpp"
#include "binary_tree.hpp"
#include "pair.hpp"

namespace ft{
template<class Key, class T, class Compare = ft::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	ft::pair<const Key, T>							value_type;
		typedef	Allocator										allocator_type;
		typedef	Compare											key_compare;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;

		typedef typename allocator_type::size_type				size_type;
		typedef	typename allocator_type::difference_type		difference_type;

		typedef	typename ft::tree<value_type, key_compare>::iterator				iterator;
		typedef	typename ft::tree<value_type, key_compare>::const_iterator			const_iterator;
		typedef	typename ft::tree<value_type, key_compare>::reverse_iterator		reverse_iterator;
		typedef	typename ft::tree<value_type, key_compare>::const_reverse_iterator	const_reverse_iterator;

		class	value_compare : std::binary_function<value_type, value_type, bool>
		{
			public:
				bool		result_type;
				value_type	first_argument_type;
				value_type	second_argument_type;
				
				friend class	map;

			protected:
				Compare	comp;
				value_compare(Compare c) : comp(c) {}

			public:
				bool operator()(const value_type &lhs, const value_type &rhs) const
				{
					return comp(lhs.first, rhs.first);
				}
		};
	
	private:
		allocator_type							_alloc;
		key_compare								_compare;
		ft::tree<value_type, key_compare>		_tree;
	
	public:
		explicit map(const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _alloc(alloc), _compare(comp) {}
		template <class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _alloc(alloc), _compare(comp)
		{
			this->insert(first, last);
		}
		map(const map &cpy) : _alloc(cpy._alloc), _compare(cpy._compare)
		{
			this->insert(cpy.begin(), cpy.end());
		}
		~map()
		{
			
		}
	private:
		void printBT(void)
		{
			_tree.printBT();
		}
	public:
	
		map	&operator=(const map &rhs)
		{
			if (this == &rhs)
				return *this;
			_alloc = rhs._alloc;
			_compare = rhs._compare;
			clear();
			this->insert(rhs.begin(), rhs.end());
			return *this;
		}
		
		allocator_type get_allocator() const {return _alloc;}

		/*
		** Elem acces
		*/

		mapped_type &at(const Key &key)
		{
			iterator tmp = _tree.find(key);
			if (tmp == _tree.end())
				throw std::out_of_range("ft::map::at");
			else
				return tmp->second;
		}
		mapped_type &operator[](const Key &key)
		{
			iterator tmp = _tree.find(key);
			if (tmp != _tree.end())
				return tmp->second;
			insert(NULL, ft::make_pair(key, T()));
			tmp = _tree.find(key);
			return tmp->second;
		}

		/*
		** Iterators
		*/
		
		iterator begin()
		{
			return _tree.begin();
		}
		const_iterator begin() const
		{
			return _tree.begin();
		}

		iterator end()
		{
			return _tree.end();
		}
		const_iterator end() const
		{
			return _tree.end();
		}

		reverse_iterator rbegin()
		{
			return _tree.rbegin();
		}
		const_reverse_iterator rbegin() const
		{
			return _tree.rbegin();
		}

		reverse_iterator rend()
		{
			return _tree.rend();
		}
		const_reverse_iterator rend() const
		{
			return _tree.rend();
		}

		/*
		** Capacity
		*/
	
		bool empty() const
		{
			return size() == 0;
		}
		
		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size(void) const
		{
			return (_tree.max_size());
		}

		/*
		** Modifiers
		*/

		void	clear()
		{
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			iterator tmp;
			if ((tmp = _tree.find(value.first)) == end())
			{
				_tree.insert(value);
				tmp = _tree.find(value.first);
				return (ft::make_pair(tmp, true));
			}
			return (ft::make_pair(tmp, false));
		}
		iterator	insert(iterator hint, const value_type &value)
		{
			(void)hint;
			return insert(value).first;
		}
		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void	erase(iterator pos)
		{
			_tree.remove(*pos);
		}
		void	erase(iterator first, iterator last)
		{
			iterator tmp = first;
			while (first != last)
			{
				tmp = first;
				++tmp;
				erase(first);
				first = tmp;
			}
		}
		size_type erase(const Key &key)
		{
			iterator tmp = find(key);
			if (tmp == end())
				return 0;
			erase(tmp);
			return 1;
		}

		void	swap(map &x)
		{
			if (this == &x)
				return ;
			allocator_type	tmp_alloc	= x._alloc;
			key_compare		tmp_compare	= x._compare;

			x._alloc = _alloc;
			x._compare = _compare;
			_alloc = tmp_alloc;
			_compare = tmp_compare;
			_tree.swap(x._tree);
		}

		/*
		** Lookup
		*/
		
		size_type count(const Key &key) const
		{
			return find(key) == end() ? 0 : 1;
		}

		iterator	find(const Key &key)
		{
			return	_tree.find(key);
		}
		const_iterator	find(const Key &key) const
		{
			return	_tree.find(key);
		}


		iterator lower_bound(const key_type& k)
		{
			iterator it = _tree.begin();
			iterator ite = _tree.end();
			while (it != ite && _compare(it->first, k))
				it++;
			return (it);
		}
		const_iterator lower_bound(const key_type& k) const
		{
			const_iterator it = _tree.begin();
			const_iterator ite = _tree.end();
			while (it != ite && _compare(it->first, k))
				it++;
			return (it);
		}

		iterator upper_bound(const key_type& k)
		{
			iterator it = _tree.begin();
			iterator ite = _tree.end();
			while (it != ite && _compare(k, it->first) == false)
				it++;
			return (it);
		}
		const_iterator upper_bound(const key_type& k) const
		{
			const_iterator it = _tree.begin();
			const_iterator ite = _tree.end();
			while (it != ite && _compare(k, it->first) == false)
				it++;
			return (it);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		/*
		** Observers
		*/
		key_compare key_comp(void) const
		{
			return (_compare);
		}

		value_compare value_comp(void) const
		{
			return value_compare(key_compare());
		}
};
template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
};

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs == rhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(rhs < lhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
};

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs < rhs));
};

template< class Key, class T, class Compare, class Alloc >
void swap(map<Key,T,Compare,Alloc> &lhs,map<Key,T,Compare,Alloc> &rhs)
{
	lhs.swap(rhs);
}

}
#endif
