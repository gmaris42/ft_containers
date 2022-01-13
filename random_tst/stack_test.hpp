/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:09:45 by gmaris            #+#    #+#             */
/*   Updated: 2021/12/15 18:17:37 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"

#ifndef STACK_TEST_HPP
#define STACK_TEST_HPP

template<class StackType, class ContainerType>
void test_Stack(int i, bool real)
{
	std::cout << MAGENTA << "\t=== Test Stack " << i << " ===" << NC << std::endl;
	if (real == true)
		std::cout << MAGENTA <<"\t    Real Stack" << NC << std::endl;
	else
		std::cout << MAGENTA <<"\t    mine Stack" << NC << std::endl;

	StackType empty;
	std::cout << BLUE << std::endl << "Empty stack test : " << NC << std::endl;
	{
		if (empty.empty() == true)
			std::cout << GREEN << "\tstack is empty" << NC << std::endl;
		else
			std::cout << RED << "\tstack is not empty" << NC << std::endl;
		if (empty.size() == 0)
			std::cout << GREEN << "\tstack size = 0" << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
	}

	StackType s;
	std::cout << BLUE << std::endl << "Push stack test : " << NC << std::endl;
	{
		s.push(1);
		if (empty.size() != 1)
			std::cout << GREEN << "\tstack size = 1 top value = " << s.top()  << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
		s.push(2);
		if (empty.size() != 2)
			std::cout << GREEN << "\tstack size = 2 top value = " << s.top()  << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
		s.push(3);
		if (empty.size() != 3)
			std::cout << GREEN << "\tstack size = 3 top value = " << s.top()  << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
	}

	std::cout << BLUE << std::endl << "Pop stack test : " << NC << std::endl;
	{
		s.pop();
		if (empty.size() != 2)
			std::cout << GREEN << "\tstack size = 2 top value = " << s.top()  << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
		s.pop();
		if (empty.size() != 1)
			std::cout << GREEN << "\tstack size = 1 top value = " << s.top()  << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
		s.pop();
		if (empty.size() == 0)
			std::cout << GREEN << "\tstack size = 0" << NC << std::endl;
		else
			std::cout << RED << "\tstack size == " << empty.size() << NC << std::endl;
	}

	std::cout << BLUE << std::endl << "Comparison stack test : " << NC << std::endl;
	{
		StackType s1;
		StackType s1_bis;

		s1.push(42); s1_bis.push(42);
		s1.push(11); s1_bis.push(11);
		s1.push(17); s1_bis.push(17);

		StackType s2;
		s2.push(42);
		s2.push(11);
		s2.push(17);
		s2.push(10);

		StackType s3;
		s2.push(42);
		s2.push(11);

		std::cout << BLUE << "\tSame stack comparison :" << std::endl;
		std::cout <<"\t\t== :" << (s1 == s1_bis) << std::endl;
		std::cout <<"\t\t!= :" << (s1 != s1_bis) << std::endl;
		std::cout <<"\t\t>  :" << (s1 >  s1_bis) << std::endl;
		std::cout <<"\t\t>= :" << (s1 >= s1_bis) << std::endl;
		std::cout <<"\t\t<  :" << (s1 <  s1_bis) << std::endl;
		std::cout <<"\t\t<= :" << (s1 <= s1_bis) << std::endl << NC;

		std::cout << BLUE << "\tsmall vs big stack comparison :" << std::endl;
		std::cout <<"\t\t== :" << (s1 == s2) << std::endl;
		std::cout <<"\t\t!= :" << (s1 != s2) << std::endl;
		std::cout <<"\t\t>  :" << (s1 >  s2) << std::endl;
		std::cout <<"\t\t>= :" << (s1 >= s2) << std::endl;
		std::cout <<"\t\t<  :" << (s1 <  s2) << std::endl;
		std::cout <<"\t\t<= :" << (s1 <= s2) << std::endl << NC;

		std::cout << BLUE << "\tbig vs small stack comparison :" << std::endl;
		std::cout <<"\t\t== :" << (s1 == s3) << std::endl;
		std::cout <<"\t\t!= :" << (s1 != s3) << std::endl;
		std::cout <<"\t\t>  :" << (s1 >  s3) << std::endl;
		std::cout <<"\t\t>= :" << (s1 >= s3) << std::endl;
		std::cout <<"\t\t<  :" << (s1 <  s3) << std::endl;
		std::cout <<"\t\t<= :" << (s1 <= s3) << std::endl << NC;
	}
}

#endif
