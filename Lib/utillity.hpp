/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utillity.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:25:39 by mxu               #+#    #+#             */
/*   Updated: 2021/11/19 18:56:14 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

namespace ft
{

template <class T1, class T2>
struct pair
{
    typedef T1  first_type;
    typedef T2  second_type;

    T1  first;
    T2  second;

    pair() : first(), second() {}
    pair(const T1& x, const T2& y) : first(x), second(y) {}
    template<class U, class V>
        pair(const pair<U, V>& p) : first(p.first), second(p.second) {}
    template<class U, class V>
        pair& operator=(const pair<U, V>& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }
};

template <class T1, class T2> 
    bool operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    } 

template <class T1, class T2> 
    bool operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(x == y);
    } 

template <class T1, class T2> 
    bool operator< (const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    } 

template <class T1, class T2> 
    bool operator> (const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return y < x;
    } 

template <class T1, class T2> 
    bool operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(x < y);
    } 

template <class T1, class T2> 
    bool operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(y < x);
    }
    
template <class T1, class T2>
  pair<T1,T2> make_pair (T1 x, T2 y)
  {
      return pair<T1, T2>(x, y);
  }

}

#endif
