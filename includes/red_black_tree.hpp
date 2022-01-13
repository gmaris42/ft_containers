/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:54:17 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/13 15:44:48 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

#define BLACK   "\033[30m" /* Black   */
#define RED     "\033[31m" /* Red     */
#define GREEN   "\033[32m" /* Green   */
#define YELLOW  "\033[33m" /* Yellow  */
#define BLUE    "\033[34m" /* Blue    */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN    "\033[36m" /* Cyan    */
#define WHITE   "\033[37m" /* White   */
#define NC      "\033[0m"  /* Reset   */
#include <memory>
#include <functional> // for std::less
#include <utility>    // for std::pair
#include "iterator.hpp"
#include "Enable_if.hpp"
#define TREE_LEFT  0
#define TREE_RIGHT 1
namespace ft{

enum color_t {BLACK, RED};

template <class T>
class	node //node of red-black tree
{
	public:
		node 			*_parent;		// == NULL if root of tree
		node 			*_child[2];	// == NULL if chils is empty
						// Index is :
						// 		LEFT	:= 0, if (key < parent->key)
						// 		RIGHT	:= 1, if (key > parent->key)
		enum color_t	_color;
		T				_value;

	node(T &val)
	{
		_parent = NULL;
		_child[TREE_LEFT] = NULL;
		_child[TREE_RIGHT] = NULL;
		_color = RED;
		_value = val;
	}
	~node() {}
};

template <class T>
byte	clidDir(T N)
{
	return (N == (N->parent)->right ? RIGHT : LEFT);
}

template <class T, class Compare = std::less<T> >
class tree
{
	public:
		typedef				node<T>								Node;
		typedef				T									value_type;
		typedef typename	T::first_type						key_type;
		typedef				std::allocator<Node>				allocator_type;
		typedef				Compare								key_compare;
		typedef	typename	allocator_type::reference			reference;
		typedef	typename	allocator_type::const_reference		const_reference;
		typedef	typename	allocator_type::pointer				pointer;
		typedef	typename	allocator_type::const_pointer		const_pointer;

		typedef typename	allocator_type::size_type			size_type;
		typedef	typename	allocator_type::difference_type		difference_type;

		typedef	typename ft::random_access_iterator<Node>		iterator;
		typedef	typename ft::random_access_iterator<const Node>	const_iterator;
		typedef	typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		allocator_type	_alloc;
		key_compare		_compare;
		pointer			_root;
		pointer			_end;
		size_type		_size;

	public:
		tree(const allocator_type &alloc = allocator_type(), const key_compare &compare = key_compare()) :
			_alloc(alloc), _compare(compare), _size(0)
		{
			_end = alloc.allocate(1);
			_alloc.construct(_end, Node(T()));
			_root = _end;
		}
		~tree()
		{
			
		}

		iterator begin()
		{
			pointer tmp = _root;
			while (tmp->_child[TREE_LEFT])
				tmp = tmp->_child[TREE_LEFT];
			return iterator(tmp);
		}
		const_iterator begin()
		{
			pointer tmp = _root;
			while (tmp->_child[TREE_LEFT])
				tmp = tmp->_child[TREE_LEFT];
			return const_iterator(tmp);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_end);
		}
		const_reverse_iterator rbegin()
		{
			return const_reverse_iterator(_end);
		}

		iterator end()
		{
			return iterator(_end);
		}
		const_iterator end()
		{
			return const_iterator(_end);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend()
		{
			return const_reverse_iterator(begin());
		}

		bool	empty() const
		{
			return _size == 0;
		}

		size_type	size() const
		{
			return _size;
		}

		size_type	max_size() const
		{
			return (_alloc.max_size());
		}

		iterator	find(const key_type &key) const
		{
			pointer root = _root;
			while (root != NULL)
			{
				if (_compare(root->_value.first, key) == false && _comp(key, root->_value.first) == false)
					return iterator(root);
				if (_compare(key, root->_value.first))
					root = root->_child[TREE_LEFT];
				else
					root = root->_child[TREE_RIGHT];
			}
			return (iterator(_end));
		}

		iterator		insertNode(pointer pos, const value_type &val
		{
			
		}

		iterator	insert(iterator pos, const value_type &val)
		{
			if (_root == _end)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node(val));
				_root->right = _end;
				++_size;
				return iterator(_root);
			}
			if (_compare(val.first, pos->_value->first)) // val.first < pos->_value->first
			{
				pointer start = begin();
				while (pos != start && !_comp(val.first, pos->_value->first))
					--pos;
				if (!_comp(val.first, pos->_value->first) && !_comp(pos->_value->first, val.first))
					return pos;
				
			}
		}
};

}
#endif