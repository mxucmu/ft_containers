/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:38:48 by mxu               #+#    #+#             */
/*   Updated: 2022/01/01 22:04:25 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "../Vector/vector.hpp"

#include <iostream>

// This is a collection of examples for each function of vector container defined at:
// https://cplusplus.com/reference/stack/stack/

int main ()
{
  // constructing stacks
  std::cout << "constructing stacks" << std::endl;

  ft::vector<int> myvector (2,200);        
  ft::stack<int> first;                    
  ft::stack<int> second (myvector);        


  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';

  // stack::empty
  std::cout << std::endl << "stack::empty" << std::endl;

  ft::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

  // stack::size
  std::cout << std::endl << "stack::size" << std::endl;

  ft::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';

  // stack::top
  std::cout << std::endl << "stack::top" << std::endl;

  ft::stack<int> mystack1;

  mystack1.push(10);
  mystack1.push(20);

  mystack1.top() -= 5;

  std::cout << "mystack.top() is now " << mystack1.top() << '\n';

  // stack::push/pop
  std::cout << std::endl << "stack::push/pop" << std::endl;

  ft::stack<int> mystack2;

  for (int i=0; i<5; ++i) mystack2.push(i);

  std::cout << "Popping out elements...";
  while (!mystack2.empty())
  {
     std::cout << ' ' << mystack2.top();
     mystack2.pop();
  }
  std::cout << '\n';
  
}
