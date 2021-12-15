/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:25:01 by gmaris            #+#    #+#             */
/*   Updated: 2021/12/15 18:20:22 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"
#include "stack_test.hpp"
#include "color.hpp"

#include <iostream>
#include <stack>
#include <deque>
#include <vector>



void	check_Stack(void)
{
	std::cout << YELLOW << "\t=== Check_Stack ===" << NC << std::endl << std::endl;
	test_Stack<std::stack<int>, std::vector<int> >(0, true);
	std::cout << std::endl;
	test_Stack<ft::stack<int> , std::vector<int> >(0, false);
	
}

void	check_Map(void)
{

}

void	check_Vector(void)
{

}


int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "Usage:./tester option\n\toption can be \"all\" \"Stack\"";
		std::cerr << " \"Map\" ou \"Vector\"" << std::endl;
		return 1;
	}
	int all = 0;
	std::string test = argv[1];
	if (test == "all")
		all = 1;
	if (all == 1 || test == "Stack")
		check_Stack();
	if (all == 1 || test == "Map")
		check_Map();
	if (all == 1 || test == "Vector")
		check_Vector();
}