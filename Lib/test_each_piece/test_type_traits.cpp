/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_type_traits.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:45:27 by mxu               #+#    #+#             */
/*   Updated: 2021/11/26 18:30:10 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type_traits.hpp"

#include <iostream>
//#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename ft::enable_if<ft::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

int main() {

  short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  return 0;
}
