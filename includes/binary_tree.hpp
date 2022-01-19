/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:54:17 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/19 17:14:46 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

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
				remove(_root->data);
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
			// std::cout << _GREEN << "  alloc addr" << tmp << "key = "<< tmp->data.first << _NC << std::endl;
			return tmp;
		}
		void		rmNode(pointer pos)
		{
			// std::cout << _RED << "dealloc addr" << pos << "key = "<< pos->data.first << _NC << std::endl;
			--_size;
			_alloc.destroy(pos);
			_alloc.deallocate(pos, 1);
		}
		pointer	minValueNode(pointer n)
		{
			pointer current = n;
			while (current->right != NULL && current->right != _end)
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
			if (z == NULL)
				return NULL;
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
			if (z == NULL)
				return NULL;
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
				pos->left = leftRotate(pos->left);
				return rightRotate(pos);
			}
			if (balance < -1)
			{
				if (_compare(pos->right->data.first, val.first))
					return leftRotate(pos);
				pos->right = rightRotate(pos->right);
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
				_end->parent = _root;
				_root->height = 1;
				return begin();
			}
			else
				return iterator(insertNode(_root, val));
		}
	
	private:
		pointer		deleteNode(pointer root, const value_type &val)
		{
			if (root == _end)
				return root;
			if (root == NULL)
				return root;
			if (_compare(val.first, root->data.first))
				root->left = deleteNode(root->left, val);
			else if (_compare(root->data.first, val.first))
				root->right = deleteNode(root->right, val);
			else
			{
				//one or no child
				if (root->left == NULL || root->right == NULL)
				{
					pointer tmp_child = root->left ? root->left : root->right;
					pointer tmp_replace;
					//no child
					if (tmp_child == NULL)
					{
						if (root->parent == NULL)
						{
							return NULL;
						}
						else
						{
							if (root->parent->left == root)
							{
								root->parent->left = NULL;
							}
							else
							{
								root->parent->right = NULL;
							}
						}
						tmp_replace = NULL;
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
						tmp_replace = tmp_child;
					}
					root->left = NULL;
					root->right = NULL;
					root->parent = NULL;
					rmNode(root);
					root = tmp_replace;
				}
				// two child
				else
				{
					pointer tmp = minValueNode(root->left); // may be null
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
					if (tmp->parent == NULL)
						_root = tmp;
					root->left = NULL;
					root->right = NULL;
					root->parent = NULL;
					rmNode(root);
					root = tmp;
				}
			}
			if (root == _end)
				return _end;
			if (root == NULL)
				return NULL;
			root->height = 1 + max(height(root->left), height(root->right));
			int balance = getBalance(root);
			if (balance > 1)
			{
				if (getBalance(root->left) >= 0)
					return rightRotate(root);
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1)
			{
				if (getBalance(root->right) <= 0)
					return leftRotate(root);
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
			return root;
		}
	public:
		void		remove(iterator it)
		{
			if (_root == _end)
				return ;
			else
				deleteNode(it.base(), *it);
		}
		void		remove(const value_type &val)
		{
			if (_root == _end)
				return ;
			else
				deleteNode(_root, val);
		}

		void	clear(void)
		{
			while (_root != _end)
				remove(_root->data);
			_root = _end;
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
				std::cout << "end ";
				if (node->parent)
					std::cout << "[" << node->parent->data.first << "]" << std::endl;
				else
					std::cout << "[null]" << std::endl;
				// printBT( prefix + (isLeft ? "│   " : "    "), node->left, true, i + 1);
				// printBT( prefix + (isLeft ? "│   " : "    "), node->right, false, i + 1);
			}
			else if( node != NULL )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node
				std::cout << node->data.first << "(" << node->data.second << ")";
				if (node->parent)
					std::cout << "[" << node->parent->data.first << "]";
				else
					std::cout << "[null]";
				std::cout << "{" << node->height << "}" << std::endl;
				// enter the next tree level - left and right branch
				printBT( prefix + (isLeft ? "│   " : "    "), node->left, true, i + 1);
				printBT( prefix + (isLeft ? "│   " : "    "), node->right, false, i + 1);
			}
		}
public:
		void printBT(void)
		{
			std::cout << "\tkey(value)[parent]{height}\n\n";
			printBT("", _root, false, 0);
		}
		void printBT(std::string prefix)
		{
			std::cout << "\tkey(value)[parent]{height}\n\n";
			printBT(prefix, _root, false, 0);
		}
		void printBT(const pointer node)
		{
			std::cout << "\tkey(value)[parent]{height}\n\n";
			printBT("", node, false, 0);
		}
};
}
#endif