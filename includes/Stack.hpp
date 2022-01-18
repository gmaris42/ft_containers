/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:59:09 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/18 14:42:42 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "Vector.hpp"

namespace ft{
template< class T, class Container = ft::vector<T> >
class stack
{
	public:
		/***************\
		** member type **
		\****************/
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	protected:
		container_type c;
	public:
		/********************\
		** member functions **
		\********************/

		//Constructor
		explicit stack(const Container &cont = Container()): c(cont){}
		~stack(){};
		//size
		size_type			size() const
		{
			return this->c.size();
		}

		//empty
		bool				empty() const 
		{
			return this->c.empty();
		}

		//top
		value_type&			top()
		{
			return this->c.back();
		}
		const value_type&	top() const
		{
			return this->c.back();
		}

		//push
		void				push(const value_type& val)
		{
			this->c.push_back(val);
		}

		//pop
		void				pop()
		{
			this->c.pop_back();
		}
		/************************\
		** non-member functions **
		\************************/
		
		//relational operators
		template <class value_type, class container_type>
		friend bool operator== (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c == rhs.c);
		}
		
		template <class value_type, class container_type>
		friend bool operator!= (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c != rhs.c);
		}

		template <class value_type, class container_type>
		friend bool operator<  (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c <  rhs.c);
		}

		template <class value_type, class container_type>
		friend bool operator<= (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c <= rhs.c);
		}

		template <class value_type, class container_type>
		friend bool operator> (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c >  rhs.c);
		}

		template <class value_type, class container_type>
		friend bool operator>= (const stack<value_type, container_type>& lhs, const stack<value_type, container_type>& rhs)
		{
			return (lhs.c >= rhs.c);
		}
};

}
#endif
