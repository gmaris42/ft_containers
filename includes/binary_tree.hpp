/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:54:17 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/17 22:05:22 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

#define _BLACK   "\033[30m" /* Black   */
#define _RED     "\033[31m" /* Red     */
#define _GREEN   "\033[32m" /* Green   */
#define _YELLOW  "\033[33m" /* Yellow  */
#define _BLUE    "\033[34m" /* Blue    */
#define _MAGENTA "\033[35m" /* Magenta */
#define _CYAN    "\033[36m" /* Cyan    */
#define _WHITE   "\033[37m" /* White   */
#define _NC      "\033[0m"  /* Reset   */
#include <memory>
#include "iterator.hpp"
#include "Enable_if.hpp"
#include "pair.hpp"
namespace ft{

template <class T>
class	node
{
	public:
		typedef		T	value_type;
		node	*left;
		node	*right;
		node	*parent;
		T		data;
		int		height;

	node(T val) : data(val)
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
	}
	~node() {}

	// node &operator=(const node &cpy)
	// {
	// 	left = cpy.left;
	// 	right = cpy.right;
	// 	parent = cpy.parent;
	// 	data = cpy.data;
	// 	height = cpy.height;
	// 	return *this;
	// }
};

template <class T, class Compare = ft::less<T> >
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

		typedef	typename ft::bidirectional_iterator<Node, false, Compare>	iterator;
		typedef	typename ft::bidirectional_iterator<Node, true, Compare>		const_iterator;
		typedef	typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

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
			_end = _alloc.allocate(1);
			_alloc.construct(_end, Node(T()));
			_end->height = 0;
			_root = _end;
		}
		~tree()
		{
			while (_root != _end)
			{
				remove(_root->data);
			}
			_alloc.destroy(_root);
			_alloc.deallocate(_root, 1);
		}

		iterator begin()
		{
			pointer tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}
		const_iterator begin() const
		{
			pointer tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_end);
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_end);
		}

		iterator end()
		{
			return iterator(_end);
		}
		const_iterator end() const
		{
			return const_iterator(_end);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
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
			while (root != _end && root != NULL)
			{
				if (_compare(root->data.first, key) == false && _compare(key, root->data.first) == false)
					return iterator(root);
				if (_compare(key, root->data.first))
					root = root->left;
				else
					root = root->right;
			}
			return (iterator(_end));
		}

	private:
		int max(int a, int b) {return (a > b)? a : b;}
		int	height(pointer n)
		{
			if (n == NULL)
				return 0;
			return n->height;
		}
		void	actuHeight(pointer root)
		{
			// root = root->parent;
			int i = 0;
			while (root != NULL && i <= 12)
			{
				root->height = 1 + max(height(root->left), height(root->right));
				root = root->parent;
				++i;
			}
			if (i >= 12)
				exit(0);
		}
		int	getBalance(pointer n)
		{
			if (n == NULL)
				return 0;
			return height(n->left) - height(n->right);
		}

		pointer		newNode(const value_type &val)
		{
			pointer tmp;
			tmp = _alloc.allocate(1);
			_alloc.construct(tmp, Node(val));
			++_size;
			return tmp;
		}
		void		rmNode(pointer pos)
		{
			// std::cout << _RED << "rm  node pos " << pos << _NC;
			// std::cout << _RED << "rm  node key = " << pos->data.first << _NC << std::endl;
			--_size;
			_alloc.destroy(pos);
			_alloc.deallocate(pos, 1);
		}
		pointer	minValueNode(pointer n)
		{
			pointer current = n;
			while (current->right != NULL)
				current = current->right;
			return current;
		}

		/*
		**	T1, T2, T3 and T4 are subtrees.
		**	         z                                      y 
		**	        / \                                   /   \
		**	       y   T4      Right Rotate (z)          x      z
		**	      / \          - - - - - - - - ->      /  \    /  \ 
		**	     x   T3                               T1  T2  T3  T4
		**	    / \
		**	  T1   T2
		*/
		pointer rightRotate(pointer z) 
		{ 
			pointer y = z->left;
			pointer t_tre = y->right;

			y->right = z;
			z->left = t_tre;

			y->parent = z->parent;

			z->parent = y;
			if (t_tre != NULL)
				t_tre->parent = z;
			z->height = max(height(z->left), height(z->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;
			if (y->parent == NULL)
				_root = y;
			return y; 
		} 

		/*
		**		z                                y
		**	   /  \                            /   \ 
		**	 T1   y     Left Rotate(z)        z      x
		**		 /  \    - - - - - - - ->    / \    / \
		*		T2   x                      T1  T2 T3  T4
		**			/ \
		**		   T3  T4
		*/
		pointer leftRotate(pointer z) 
		{
			pointer y = z->right;
			pointer t_two = y->left;

			y->left = z; 
			z->right = t_two; 
			y->parent = z->parent;

			z->parent = y;
			if (t_two != NULL)
				t_two->parent = z;
			z->height = max(height(z->left), height(z->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;
			if (y->parent == NULL)
				_root = y;
			return y; 
		} 


		pointer	insertNode(pointer pos, const value_type &val)
		{
			if (pos == _end)
			{
				pointer tmp = newNode(val);
				tmp->right = _end;
				_end->parent = tmp;
				return tmp;
			}
			if (pos == NULL)
				return newNode(val);
			if (_compare(val.first, pos->data.first))
			{
				pos->left = insertNode(pos->left, val);
				pos->left->parent = pos;
			}
			else if (_compare(pos->data.first, val.first))
			{
				pos->right = insertNode(pos->right, val);
				pos->right->parent = pos;
			}
			else
				return pos;
			pos->height = 1 + max(height(pos->left), height(pos->right));
			int balance = getBalance(pos);
			if (balance > 1)
			{
				if (_compare(val.first, pos->left->data.first))
					return rightRotate(pos);
				leftRotate(pos);
				return rightRotate(pos);
			}
			if (balance < -1)
			{
				if (_compare(pos->right->data.first, val.first))
					return leftRotate(pos);
				rightRotate(pos);
				return leftRotate(pos);
			}
			return pos;
		}
	public:
		iterator	insert(const value_type &val)
		{
			if (_root == _end)
			{
				_root = newNode(val);
				_root->right = _end;
				_root->height = 1;
				return begin();
			}
			else
				return iterator(insertNode(_root, val));
		}
	
	private:
		pointer		deleteNode(pointer root, const value_type &val)
		{
			if (root == NULL)
				return root;
			if (_compare(val.first, root->data.first))
				deleteNode(root->left, val);
			else if (_compare(root->data.first, val.first))
				deleteNode(root->right, val);
			else
			{
				//one or no child
				if (root->left == NULL || root->right == NULL)
				{
					pointer tmp_child = root->left ? root->left : root->right;
					//no child
					if (tmp_child == NULL)
					{

						if (root->parent == NULL)
						{
							_root = _end;
						}
						else
						{
							if (root->parent->left == root)
								root->parent->left = NULL;
							else
								root->parent->right = NULL;
						}
						actuHeight(root);
					}
					// one child
					else
					{

						if (root->parent == NULL)
						{
							_root = tmp_child;
						}
						else
						{
							if (root->parent->left == root)
								root->parent->left = tmp_child;
							else
								root->parent->right = tmp_child;
						}
						tmp_child->parent = root->parent;
						actuHeight(tmp_child);
					}
					rmNode(root);
				}
				// two child
				else
				{

					pointer tmp = minValueNode(root->left); // may be null
					pointer tmp_parent = tmp->parent;

					//tmp->right == NULL is 100%
					if (tmp->left == NULL)//tmp no child
					{
						//rm tmp from it's old parent
						if (tmp->parent)
						{
							if (tmp->parent->right == tmp)
								tmp->parent->right = NULL;
							else
								tmp->parent->left = NULL;
						}
						
						//set tmp <-> new parent relation
						tmp->parent = root->parent;
						if (tmp->parent)
						{
							if (root->parent->left == root)
								root->parent->left = tmp;
							else
								root->parent->right = tmp;
						}
						
						//set tmp <-> new left relation
						if (tmp == root->left)
							tmp->left = NULL;
						else
						{
							tmp->left = root->left;
							if (tmp->left)
								tmp->left->parent = tmp;
						}
						
						//set tmp <-> new right relation
						if (tmp == root->right)
							tmp->right = NULL;
						else
						{
							tmp->right = root->right;
							if (tmp->right)
								tmp->right->parent = tmp;
						}
					}
					else if (tmp->left != NULL)//tmp has a child
					{
						//child take place of tmp
						//set tmp->child <-> new child parent
						tmp->left->parent = tmp->parent;
						if (tmp->parent->left == tmp)
							tmp->parent->left = tmp->left;
						else
							tmp->parent->right = tmp->left;

						//set tmp <-> new parent relation
						tmp->parent = root->parent;
						if (tmp->parent)
						{
							if (root->parent->left == root)
								root->parent->left = tmp;
							else
								root->parent->right = tmp;
						}
						
						//set tmp <-> new left relation
						if (tmp == root->left)
							tmp->left = NULL;
						else
						{
							tmp->left = root->left;
							if (tmp->left)
								tmp->left->parent = tmp;
						}
						
						//set tmp <-> new right relation
						if (tmp == root->right)
							tmp->right = NULL;
						else
						{
							tmp->right = root->right;
							if (tmp->right)
								tmp->right->parent = tmp;
						}
					}
					actuHeight(tmp_parent);
					if (tmp->parent == NULL)
						_root = tmp;
					rmNode(root);
					root = tmp;
				}
			}
			if (root == NULL || root == _end)
				return NULL;
			root->height = 1 + max(height(root->left), height(root->right));

			int balance = getBalance(root);
			if (balance > 1)
			{
				if (getBalance(root->left) >= 0)
					return rightRotate(root);
				leftRotate(root);
				return rightRotate(root);
			}
			if (balance < -1)
			{
				if (getBalance(root->right) <= 0)
					return leftRotate(root);
				rightRotate(root);
				return leftRotate(root);
			}
			return root;
		}
	public:
		void		remove(const value_type &val)
		{
			if (_root == _end)
				return ;
			else
				deleteNode(_root, val);
		}

		void	swap(tree &x)
		{
			allocator_type	tmp_alloc	= x._alloc;
			key_compare		tmp_compare	= x._compare;
			pointer			tmp_root	= x._root;
			pointer			tmp_end		= x._end;
			size_type		tmp_size	= x._size;


			x._alloc =_alloc;
			x._compare = _compare;
			x._root = _root;
			x._end = _end;
			x._size = _size;

			_alloc = tmp_alloc;
			_compare = tmp_compare;
			_root = tmp_root;
			_end = tmp_end;
			_size = tmp_size;
		}
	private:
		void printBT(const std::string& prefix, const pointer node, bool isLeft, int i)
		{
			if ( i > 10)
				return;
			if(node == _end)
			{

				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node
				std::cout << "end" << std::endl;
				return ;
			}
			if( node != NULL )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node
				std::cout << node->data.first << "(" << node->height << ")" <<  std::endl;

				// enter the next tree level - left and right branch
				printBT( prefix + (isLeft ? "│   " : "    "), node->left, true, i + 1);
				printBT( prefix + (isLeft ? "│   " : "    "), node->right, false, i + 1);
			}
		}
public:
		void printBT(void)
		{
			printBT("", _root, false, 0);
		}
};
}
#endif