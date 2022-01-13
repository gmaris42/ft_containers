/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:25:01 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/13 15:25:19 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <deque>
#include <vector>
#include <map>


int main(void)
{
	std::map<int, int> lst;
	std::pair<int,int> t;
	t.first = 42;
	t.second = 4;
	lst.insert(lst.begin(), t);
	t.first = 42;
	t.second = 442;
	lst.insert(lst.begin(), t);
	std::cout <<"test" << lst[42];

	std::map<int, int>::iterator it;

	it = lst.begin();
	it.base();
}