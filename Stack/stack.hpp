/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:01:14 by mxu               #+#    #+#             */
/*   Updated: 2021/12/16 16:13:39 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP_
#define STACK_HPP_

#include "../Vector/vector.hpp"

// Reference from site: https://cplusplus.com/reference/stack/stack/

// libc++ implementation located on Mac: 
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

// Implementaion version c++98

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    stack() : c()                                       {}
    ~stack()                                            {}        

    stack(const stack& q) : c(q.c)                      {}

    stack& operator=(const stack& q)                    { c = q.c; return *this; }

    explicit stack(const container_type& _c) : c(_c)    {}

    bool empty() const                                  { return c.empty(); }
    size_type size() const                              { return c.size(); }
    value_type& top()                                   { return c.back(); }
    const value_type& top() const                       { return c.back(); }
    void push(const value_type& x)                      { c.push_back(x); }
    void pop()                                          { c.pop_back(); }
};

template <class T, class Container>
  bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
{
    return x.c == y.c;
}

template <class T, class Container>
  bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
{
    return x.c < y.c;
}

template <class T, class Container>
  bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
{
    return !(x == y);
}

template <class T, class Container>
  bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
{
    return y < x;
}

template <class T, class Container>
  bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
{
    return !(x < y);
}

template <class T, class Container>
  bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
{
    return !(y < x);
}

}

#endif
