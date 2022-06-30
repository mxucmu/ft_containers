/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:52:58 by mxu               #+#    #+#             */
/*   Updated: 2021/11/29 16:01:54 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
//#include <iterator>   // std::iterator, std::input_iterator_tag, std::iterator_traits
#include "./iterator.hpp"
#include <typeinfo>     // typeid


class MyIterator : public ft::iterator<ft::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

int main () 
{
    // std::iterator example
    int numbers[]={10,20,30,40,50};
    MyIterator from(numbers);
    MyIterator until(numbers+5);
    for (MyIterator it=from; it!=until; it++)
        std::cout << *it << ' ';
    std::cout << '\n';

    // iterator_traits example
    typedef ft::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator";

  return 0;
}
