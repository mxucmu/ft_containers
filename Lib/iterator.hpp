/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:39:45 by mxu               #+#    #+#             */
/*   Updated: 2021/12/31 00:29:12 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <cstddef>
#include <memory>
#include <type_traits>

namespace ft
{

// This serves as template parameter for Iterators.  The Category of an interator must 
// be one of the following iterator tags.
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag         : public input_iterator_tag {};
struct bidirectional_iterator_tag   : public forward_iterator_tag {};
struct random_access_iterator_tag   : public bidirectional_iterator_tag {};

// This is a base class template that can be used to derive iterator classes from.
template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Category    iterator_category;
};

// Iterator traits
// Standard algorithms determine certain properties of the iterators passed to them
// and the range they represent by using the members of the corresponding iterator_traits 
// instantiation.
template <class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
    typedef typename Iterator::iterator_category    iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef random_access_iterator_tag  iterator_category;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
    typedef random_access_iterator_tag  iterator_category;
};

// Wrap a pointer to get a functioning random-access iterator
template <class Iterator>
class wrap_iter
{
public:
    typedef Iterator                                                    iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type         value_type;
    typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
    typedef typename iterator_traits<iterator_type>::pointer            pointer;
    typedef typename iterator_traits<iterator_type>::reference          reference;
private:
    iterator_type   i;
public:
    wrap_iter() {}

    wrap_iter(iterator_type x) : i(x) {}

    template <class Up> 
        wrap_iter(const wrap_iter<Up>& u) : i(u.base()) {}

    iterator_type   base() const                    { return i; }
    
    reference       operator*() const               { return *i; }
    pointer         operator->() const              { return (pointer)std::addressof(*i); }
    wrap_iter&      operator++()                    { ++i; return *this; }
    wrap_iter       operator++(int)                 { wrap_iter tmp(*this); ++(*this); return tmp; }
    wrap_iter&      operator--()                    { --i; return *this; }
    wrap_iter       operator--(int)                 { wrap_iter tmp(*this); --(*this); return tmp; }
    wrap_iter       operator+(difference_type n)    { wrap_iter tmp(*this); tmp += n; return tmp; }
    wrap_iter&      operator+=(difference_type n)   { i += n; return *this; }
    wrap_iter       operator-(difference_type n)    { return *this + (-n); }
    wrap_iter&      operator-=(difference_type n)   { *this += -n; return *this; }
    reference       operator[](difference_type n)   { return i[n]; }
private:
    template <class Up> friend class                    wrap_iter;
    template <class T, class Allocator> friend class    vector;

    template <class Iterator1, class Iterator2> friend
    bool    operator==(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    bool    operator<(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    bool    operator!=(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    bool    operator>(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    bool    operator>=(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    bool    operator<=(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&);

    template <class Iterator1, class Iterator2> friend
    typename wrap_iter<Iterator1>::difference_type    
    operator-(const wrap_iter<Iterator1>&, const wrap_iter<Iterator2>&); 

    template <class Iterator1> friend
    wrap_iter<Iterator1>
    operator+(typename wrap_iter<Iterator1>::difference_type, wrap_iter<Iterator1>);

    template<class T>
    T*  unwrap_iter(wrap_iter<T*>);
};

// Non-member function overloads
template <class Iterator1, class Iterator2>
bool    operator==(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return x.base() == y.base();
}

template <class Iterator1, class Iterator2>
bool    operator<(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return x.base() < y.base();
}

template <class Iterator1, class Iterator2>
bool    operator!=(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return !(x == y);
}

template <class Iterator1, class Iterator2>
bool    operator>(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return y < x;
}

template <class Iterator1, class Iterator2>
bool    operator>=(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return !(x < y);
}

template <class Iterator1, class Iterator2>
bool    operator<=(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y)
{
    return !(y < x);
}

template <class Iterator>
bool    operator!=(const wrap_iter<Iterator>& x, const wrap_iter<Iterator>& y)
{
    return !(x == y);
}

template <class Iterator>
bool    operator>(const wrap_iter<Iterator>& x, const wrap_iter<Iterator>& y)
{
    return y < x;
}

template <class Iterator>
bool    operator>=(const wrap_iter<Iterator>& x, const wrap_iter<Iterator>& y)
{
    return !(x < y);
}

template <class Iterator>
bool    operator<=(const wrap_iter<Iterator>& x, const wrap_iter<Iterator>& y)
{
    return !(y < x);
}

template <class Iterator1, class Iterator2>
typename wrap_iter<Iterator1>::difference_type    
    operator-(const wrap_iter<Iterator1>& x, const wrap_iter<Iterator2>& y) 
    {
        return x.base() - y.base();
    }

template <class Iterator>
wrap_iter<Iterator>  
    operator+(typename wrap_iter<Iterator>::difference_type n, wrap_iter<Iterator> x)
    {
        x += n;
        return x;
    }

// Reverse iterator
// This class reverses the direction in which a bidirectional or random-access iterator 
// iterates through a range.
template <class Iterator>
class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                         typename iterator_traits<Iterator>::value_type,
                                         typename iterator_traits<Iterator>::difference_type,
                                         typename iterator_traits<Iterator>::pointer,
                                         typename iterator_traits<Iterator>::reference>
{
protected:
    // A copy of the base iterator
    Iterator    current;
public:
    // Member types
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;

    // Member functions
    reverse_iterator() : current() {}

    explicit reverse_iterator(Iterator x) : current(x) {}

    template <class U> 
    reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {}

    template <class U> 
    reverse_iterator& operator=(const reverse_iterator<U>& u)   { current = u.base(); return *this; }

    Iterator            base() const        { return current; }

    reference           operator*() const   { Iterator tmp = current; return *--tmp; }

    pointer             operator->() const  { return std::addressof(operator*()); }

    reverse_iterator&   operator++()        { --current; return *this; }

    reverse_iterator    operator++(int)     { reverse_iterator tmp(*this); --current; return tmp; }

    reverse_iterator&   operator--()        { ++current; return *this; }

    reverse_iterator    operator--(int)     { reverse_iterator tmp(*this); ++current; return tmp; }

    reverse_iterator    operator+ (difference_type n) const     { return reverse_iterator(current - n); }

    reverse_iterator&   operator+=(difference_type n)           { current -= n; return *this; }

    reverse_iterator    operator- (difference_type n) const     { return reverse_iterator(current + n); }

    reverse_iterator&   operator-=(difference_type n)           { current += n; return *this; }

    reference           operator[](difference_type n) const     { return *(*this + n); }
};

// Non-member function overloads
template <class Iterator1, class Iterator2>
bool    operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() == y.base();
}

template <class Iterator1, class Iterator2>
bool    operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() > y.base();
}

template <class Iterator1, class Iterator2>
bool    operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() != y.base();
}

template <class Iterator1, class Iterator2>
bool    operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() < y.base();
}

template <class Iterator1, class Iterator2>
bool    operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() <= y.base();
}

template <class Iterator1, class Iterator2>
bool    operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
    return x.base() >= y.base();
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type    
    operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) 
    {
        return y.base() - x.base();
    }

template <class Iterator>
reverse_iterator<Iterator>  
    operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
    {
        return reverse_iterator<Iterator>(x.base() - n);
    }

}

#endif
