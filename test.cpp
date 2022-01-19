/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaris <gmaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:39:01 by gmaris            #+#    #+#             */
/*   Updated: 2022/01/19 18:55:57 by gmaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "includes/Stack.hpp"
# include "includes/Map.hpp"
# include "includes/Vector.hpp"
# include <sys/time.h>
# include <map>
# include <stack>
# include <vector>

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define NC		"\033[0m"

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_header(std::string container)
{
	std::cout << YELLOW << "\n|***********************************************************|\n";
	std::cout << "\t\t\t" << container << std::endl;
	std::cout << "|***********************************************************|\n" << NC;
}

void	print_ex(std::string name)
{
	size_t i = 0;
	std::cout << '\n';
	std::cout << CYAN << name << ":" << std::endl;
	while (i < name.size() + 1)
	{
		std::cout << "-";
		i++;
	}
	std::cout << NC << std::endl;
}

int		main(void)
{
	print_header("stack test");
	std::cout << "A stack of any type\n";
	ft::stack <int> test;
	std::stack <int> real;
	print_ex("empty() function");
	//---------------------------//
	std::cout << "The empty function returns true (1) if the stack is empty, false (0) if not.\n";
	std::cout << "* my stack.empty():\t" << MAGENTA << test.empty() << NC << std::endl;
	std::cout << "* real stack.empty():\t" << GREEN << real.empty() << NC << std::endl;
	//-----------------------------//
	print_ex("push() function");
	std::cout << "The push is used to add an element at the top of the stack.\n";
	std::cout << "we'll add 4 numbers to the stack [42 33 10 2].\n";
	std::cout << "Here is our stack content:\n";
	test.push(42);
	test.push(33);
	test.push(10);
	test.push(2);
	real.push(42);
	real.push(33);
	real.push(10);
	real.push(2);
	while (!test.empty())
	{
		std::cout << "content:\t" << MAGENTA << test.top() << NC << std::endl;;
		test.pop();
	}
	std::cout << '\n';
	//-------------------------------//

	print_ex("size() function");
	std::cout << "Size function returns the size of the stack.\n";
	test.push(42);
	test.push(33);
	test.push(10);
	test.push(2);
	std::cout << "size of my stack:\t" << MAGENTA << test.size() << NC << std::endl;
	std::cout << "size of real stack:\t" << GREEN << test.size() << NC << std::endl;
	//-------------------------------//

	print_ex("top() function");
	std::cout << "The top function returns a &reference to the top element of the stack\n";
	std::cout << "first elem of my stack:\t\t" << MAGENTA << test.top() << NC << std::endl;
	std::cout << "first elem of real stack:\t" << GREEN << real.top() << NC << std::endl;
	//-------------------------------//

	print_ex("pop() function");
	std::cout << "The pop function removes the element at the top of the stack.\n";
	test.pop();
	real.pop();
	std::cout << "size of my stack:\t" << MAGENTA << test.size() << NC << std::endl;
	std::cout << "size of real stack:\t" << GREEN << real.size() << NC << std::endl;
	std::cout << "first elem of my stack:\t\t" << MAGENTA << test.top() << NC << std::endl;
	std::cout << "first elem of real stack:\t" << GREEN << test.top() << NC << std::endl;
	std::cout << "Iterators cannot be used to parse a stack so it s not easy to access an element in the middle of the stack.\n";
/******************************************************************************/

	print_header("vector test");
	ft::vector<long>my_vec;
	std::vector<long>re_vec;
	std::cout << "A vector container can be seen like a type tab[].\nIt can be from any type, and it allocation system works differently\n";
	//----------------------------------//

	print_ex("assign(n, value) function");
	std::cout << "The assign function puts n elements of value in the vector\n";
	std::cout << "we 'll assign 10 times the value 42:\n";
	my_vec.assign(10, 42);
	re_vec.assign(10, 42);
	ft::vector<long>::iterator it = my_vec.begin();
	std::vector<long>::iterator i = re_vec.begin();
	while (it != my_vec.end())
	{
		std::cout << "my vector content:\t" << MAGENTA << *it << NC << std::endl;
		it++;
	}
	while (i != re_vec.end())
	{
		std::cout << "real vector content:\t" << GREEN << *i << NC << std::endl;
		i++;
	}
	//-------------------------------------//

	print_ex("push_back()");
	std::cout << "The push_back function add an element to the end of the vector\n";
	std::cout << "we ll push 21.\n";
	my_vec.push_back(21);
	re_vec.push_back(21);
	std::cout << "let's display the last element using vector.back()\n";
	std::cout << "my vector:\t" << MAGENTA << my_vec.back() << NC << std::endl;
	std::cout << "real vector:\t" << GREEN << re_vec.back() << NC << std::endl;
	//------------------------------------------//

	print_ex("pop_back()");
	std::cout << "The pop_back function erase the last element of the vector\n";
	std::cout << "let's delete the 21 added previously, and ";
	my_vec.pop_back();
	re_vec.pop_back();
	std::cout << "let's display the last element using vector.back()\n";
	std::cout << "my vector:\t" << MAGENTA << my_vec.back() << NC << std::endl;
	std::cout << "real vector:\t" << GREEN << re_vec.back() << NC << std::endl;
	//-----------------------------------------//

	print_ex("insert(position, value)");
	std::cout << "insert put the value to the requested position, increasing the size of the vector by 1.\n";
	std::cout << "let's put 8 to the 10 position.\n";
	it = my_vec.end() - 1;
	i = re_vec.end()  - 1;
	my_vec.insert(it, 8);
	re_vec.insert(i, 8);
	it = my_vec.begin();
	i = re_vec.begin();
	while (it != my_vec.end())
	{
		std::cout << "my vector content:\t" << MAGENTA << *it << NC << std::endl;
		it++;
	}
	while (i != re_vec.end())
	{
		std::cout << "real vector content:\t" << GREEN << *i << NC << std::endl;
		i++;
	}
	//-------------------------------------------//

	print_ex("erase(position)");
	std::cout << "quite explicit, we'll delete the element at the 10 position\n";
	my_vec.erase(my_vec.end() - 2);
	re_vec.erase(re_vec.end() - 2);
	it = my_vec.begin();
	i = re_vec.begin();
	while (it != my_vec.end())
	{
		std::cout << "my vector content:\t" << MAGENTA << *it << NC << std::endl;
		it++;
	}
	while (i != re_vec.end())
	{
		std::cout << "real vector content:\t" << GREEN << *i << NC << std::endl;
		i++;
	}
	//---------------------------------------------//

	print_ex("swap(vector)");
	std::cout << "swap elements between 2 vectors\nWe'll create a new vector called michel\n";
	std::cout << "michel will be a vector of size 5 filled with 21.\n";
	std::cout << "We will also create an iterator (tmp)pointing on my_vec.begin() before the swap.\n";
	std::cout << "Now let's swap\n";
	ft::vector<long>michl;
	ft::vector<long>::iterator tmp = my_vec.begin();
	michl.assign(5, 21);
	my_vec.swap(michl);
	it = my_vec.begin();
	while (it != my_vec.end())
	{
		std::cout << "my vector content:\t" << MAGENTA << *it << NC << std::endl;
		it++;
	}
	it = michl.begin();
	while (it != michl.end())
	{
		std::cout << "michel vector content:\t" << GREEN << *it << NC << std::endl;
		it++;
	}
	std::cout << "tmp is pointing on :\t" << MAGENTA << *tmp << NC << std::endl;
	michl.clear();
	//------------------------------------------------//

	print_ex("clear()");
	std::cout << "The clear function removes & destroy all the element in the vector.(so practical !:D)\n";
	my_vec.clear();
	re_vec.clear();
	std::cout << "After clear my vector size is\t\t" << MAGENTA << my_vec.size() << NC << std::endl;
	std::cout << "After clear real vector size is:\t" << GREEN << re_vec.size() << NC << std::endl;
	//------------------------------------------------//

	print_ex("Iterators & const Iterators");
	std::cout << "Vector can use Iterators & const Iterators, and they must be comparable.\n";
	std::cout << "That what we're going to check right now\n";
	my_vec.assign(5, 42);
	ft::vector<long>::const_iterator ci = my_vec.begin();
	it = my_vec.begin();
	std::cout << "We pushed 5 value 42 in our vector, and assigned a const_iterator (ci) and an iterator (it)\n";
	std::cout << "both pointing on the same area my_vec.begin(). now we 'll make a comparison.\n";
	std::cout << "if (*it == *ci) we'll print 'NICE' else we'll print 'NOPE'\n";
	if (*it == *ci)
		std::cout << MAGENTA << "NICE\n" << NC;
	my_vec.clear();
/******************************************************************************/

	print_header("Map test");
	std::cout << "A map container is a binary tree composed of elements(a pair).\n";
	std::cout << "Each element is a pair of two types. Composed by a key and a value.\n";
	std::cout << "Elements in the map are sorted by ascending order (reverse if less).\n";
	std::cout << "The key is used store and parse the map, so it has to be unique.\n";
	std::cout << "The same value can be encontered twice as they will not have the same key.\n";
	std::cout << "Map containers are really usefull to create dictionnary\n";
	//-------------------------------------------------//

	print_ex("insert(pair)");
	ft::map<std::string, std::string>my_map;
	std::map<std::string, std::string>re_map;
	ft::pair<std::string, std::string>first("first", "oh great");
	my_map.insert(first);
	std::cout << "we'll create a pair named 'first' and containing 'oh great'\ninsert it and display it\n";
	std::cout << "my_map[first] =\t" << MAGENTA << my_map["first"] << NC << std::endl;
	//-------------------------------------------------//


	print_ex("erase(key)");
	std::cout << "The erase function erase the element, it can be used with the key or an iterator(position)\n";
	std::cout << "We'll erase the only element we havei and ";
	my_map.erase("first");
	std::cout << "display the nb of element using map.size() and, if the map is empty using map.empty()\n";
	std::cout << "map size:\t" << MAGENTA << my_map.size() << NC << std::endl;
	std::cout << "is map empty:\t" << MAGENTA << my_map.empty() << std::endl;
	//--------------------------------------------------//

	print_ex("swap(other map)");
	std::cout << "Works the same as the other containers, map containers has to be the same type\n";
	std::cout << "Michel is back but as a map container. it will contain:\n[michel][michel]\n[michelle][michelle]\n";
	std::cout << "my first map will contain: [fred][jamy] and [phili][poutou]\n";
	ft::map<std::string, std::string>michel;
	michel["michel"] = "michel";
	michel["michelle"] = "michelle";
	my_map["fred"] = "jamy";
	my_map["phili"] = "poutou";
	std::cout << "Now let's swap !\n";
	my_map.swap(michel);
	ft::map<std::string, std::string>::iterator j = my_map.begin();
	while (j != my_map.end())
	{
		std::cout << "content in my map[" << MAGENTA << j->first << NC << "] = " << MAGENTA  << j->second << NC << std::endl;
		j++;
	}
	j = michel.begin();
	while (j != michel.end())
	{
		std::cout << "content in michel map[" << GREEN << j->first << NC << "] = " << GREEN  << j->second << NC << std::endl;
		j++;
	}
	//---------------------------------------------------//


	print_ex("clear()");
	std::cout << "I'm quite sure you know what it does, so let's get rid of our useless michel\n";
	michel.clear();
	std::cout << "Michel size using michel.size() = " << MAGENTA << michel.size() << NC << std::endl;
	std::cout << "now to be sure using michel.empty() = " << MAGENTA << michel.empty() << NC << std::endl;
	//----------------------------------------------------//
	
	print_ex("find(key)");
	j = my_map.find("michel");
	std::cout << "find the pair using the key, if it's not found, an iterator on map.end() is returned\n";
	std::cout << "my_map.find['michel'] = " << MAGENTA << j->second << NC << std::endl;
	j = my_map.find("nothing");
	std::cout << "my_map.find['nothing'] =" << j->second << std::endl;\
	//--------------------------------------------------//
		
	print_ex("count(key)");
	std::cout << "The count function find occurence of key in the map\nIt returns 1 is there is any, 0 if not.";
	std::cout << "We added [jackson][Percy] and [jackson][Janette] to my_map\n";
	my_map["jackson"] = "Percy";
	my_map["jackson"] = "Janette";
	std::cout << "my_map.count('jackson') = " << MAGENTA << my_map.count("jackson") << NC << std::endl;
	std::cout << "now we do erase('jackson') and do my_map.count('jackson') again.\n";
	my_map.erase("jackson");
	std::cout << "my_map.count('jackson') = " << MAGENTA << my_map.count("jackson") << NC << std::endl;
	//---------------------------------------------------//
	
	print_ex("lower_bound(key k)");
	std::cout << "This function returns an iterator pointing to the first element in the container\nwhose key is not considered to go before k\n";
	j = my_map.lower_bound("michel");
	std::cout << "j = my_map.lower_bound('michel') j->first = " << MAGENTA << j->first << NC << "\tj->second = " << MAGENTA << j->second << NC << std::endl;
	print_ex("upper_bound(key k)");
	j = my_map.upper_bound("michel");
	std::cout << "j = my_map.upper_bound('michel') j->first = " << MAGENTA << j->first << NC << "\tj->second = " << MAGENTA << j->second << NC << std::endl;
	//---------------------------------------------------//
	
	print_ex("equal_range(key k)");
	std::cout << "Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.\n";
	std::cout << "Because the elements in a map container have unique keys, the range returned will contain a single element at most.\n";
	std::cout << "We 'll add more element to our map so it is more explicit\n";
	std::cout << "let's add [michel][drucker]\n";
	my_map["michel"] = "drucker";
	ft::pair<ft::map<std::string, std::string>::iterator,ft::map<std::string, std::string>::iterator> ret;
	ret = my_map.equal_range("michel");
	std::cout << "lower bound points to: ";
	std::cout << MAGENTA << ret.first->first << NC << " => " << MAGENTA << ret.first->second << NC << '\n';
	std::cout << "upper bound points to: ";
	std::cout << MAGENTA << ret.second->first << NC << " => " << MAGENTA << ret.second->second << NC << '\n';


	print_header("Time testing");
	size_t timestamp = ft_get_time();
	print_ex("map");
	std::map<int, int> real_map;
	for (int i = 0; i < 1000000; i++)
		real_map[i] = i;
	std::cout << "Real time in mls:\t" << GREEN << ft_get_time() - timestamp << NC << std::endl;
	timestamp = ft_get_time();
	ft::map<int, int> la_map;
	for (int j = 0; j < 1000000; j++)
		la_map[j] = j;
	std::cout << "My time mls:\t" << MAGENTA << ft_get_time() - timestamp << NC << std::endl;
	la_map.clear();
	real_map.clear();




	print_ex("vector");
	timestamp = ft_get_time();
	for (int i = 0; i < 10000000; i++)
		re_vec.push_back(i);
	std::cout << "Real time mls:\t" << GREEN << ft_get_time() - timestamp << NC << std::endl;
	timestamp = ft_get_time();

	for (int j = 0; j < 10000000; j++)
		my_vec.push_back(j);
	std::cout << "My time mls:\t" << MAGENTA << ft_get_time() - timestamp << NC << std::endl;
	re_vec.clear();
	my_vec.clear();
	return (0);
}
