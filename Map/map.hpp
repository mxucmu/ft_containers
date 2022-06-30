/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:09:29 by mxu               #+#    #+#             */
/*   Updated: 2022/01/02 01:41:08 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <memory>
#include <functional>
#include <iostream>
#include <utility>

#include "../Lib/utillity.hpp"
#include "../Lib/tree.hpp"
#include "../Lib/iterator.hpp"
#include "../Lib/algorithm.hpp"

// Reference from site: https://cplusplus.com/reference/map/map/

// libc++ implementation located on Mac: 
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

// Implementaion version c++98

namespace ft
{

template <class TreeIterator>
class map_iterator
{
    TreeIterator    _i;

public:
    typedef bidirectional_iterator_tag                  iterator_category;
    typedef typename TreeIterator::value_type           value_type;
    typedef typename TreeIterator::difference_type      difference_type;
    typedef typename TreeIterator::reference            reference;
    typedef typename TreeIterator::pointer              pointer;

    map_iterator() {}
    map_iterator(TreeIterator i) : _i(i) {}
    
    reference operator*() const     { return *_i; }
    pointer  operator->() const     { return &(*_i); }

    map_iterator& operator++()      { ++_i; return *this; }
    map_iterator  operator++(int)   { map_iterator t(*this); ++(*this); return t; }
    map_iterator& operator--()      { --_i; return *this; }
    map_iterator  operator--(int)   { map_iterator t(*this); --(*this); return t; }

    friend
    bool    operator==(const map_iterator& x, const map_iterator& y)
    { return x._i == y._i; }
    friend
    bool    operator!=(const map_iterator& x, const map_iterator& y)
    { return x._i != y._i; }

    template <class, class, class, class> friend class  map;
    template <class> friend class                       map_const_iterator;
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class TreeIterator>
class map_const_iterator
{
    TreeIterator    _i;

public:
    typedef bidirectional_iterator_tag                  iterator_category;
    typedef typename TreeIterator::value_type           value_type;
    typedef typename TreeIterator::difference_type      difference_type;
    typedef const value_type&                           reference;
    typedef const value_type*                           pointer;

    map_const_iterator() {}
    map_const_iterator(TreeIterator i) : _i(i) {}
    map_const_iterator(map_iterator<typename TreeIterator::non_const_iterator> i) : _i(i._i) {}
    
    reference operator*() const             { return *_i; }
    pointer  operator->() const             { return &(*_i); }

    map_const_iterator& operator++()        { ++_i; return *this; }
    map_const_iterator  operator++(int)     { map_const_iterator t(*this); ++(*this); return t; }
    map_const_iterator& operator--()        { --_i; return *this; }
    map_const_iterator  operator--(int)     { map_const_iterator t(*this); --(*this); return t; }

    friend
    bool    operator==(const map_const_iterator& x, const map_const_iterator& y)
    { return x._i == y._i; }
    friend
    bool    operator!=(const map_const_iterator& x, const map_const_iterator& y)
    { return x._i != y._i; }

    template <class, class, class, class> friend class  map;
    template <class, class, class> friend class         tree_const_iterator;
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Key, class Tp, class Compare>
class map_value_compare
{
    Compare comp;

public:
    typedef Key                                         first_argument_type;
    typedef Compare                                     third_argument_type;

    map_value_compare() : comp()                        {}
    map_value_compare(Compare c) : comp(c)              {}
    const Compare& key_comp() const                     {return comp;}

    bool operator()(const Tp& x, const Tp& y) const     { return comp(x.first, y.first); }
    bool operator()(const Tp& x, const Key& y) const    { return comp(x.first, y); }
    bool operator()(const Key& x, const Tp& y) const    { return comp(x, y.first); }
    
    void swap(map_value_compare& y)                     { std::swap(comp, y.comp); }
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Key, 
          class T, 
          class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    // Member types
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef ft::pair<const key_type, mapped_type>       value_type;
    typedef Compare                                     key_compare;
    typedef Allocator                                   allocator_type;
    typedef typename allocator_type::reference          reference;         // value_type&
    typedef typename allocator_type::const_reference    const_reference;   // const value_type&

    class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c) : comp(c) {}
    public:

        bool operator()(const value_type& x, const value_type& y) const
            { return comp(x.first, y.first); }
    };

private:
    typedef ft::pair<key_type, mapped_type>                         _value_type;
    typedef map_value_compare<key_type, _value_type, key_compare>   _vc;
    typedef std::allocator<_value_type>                             _allocator_type;
    typedef ft::RBTree<_value_type, _vc, _allocator_type>           _base;

    _base   _tree;

public:
    typedef typename allocator_type::pointer                        pointer; // pointer to ft::pair<const Key, T>
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef typename allocator_type::size_type                      size_type;
    typedef typename allocator_type::difference_type                difference_type;
    typedef map_iterator<typename _base::iterator>                  iterator;
    typedef map_const_iterator<typename _base::const_iterator>      const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

public:
    // construct/copy/destroy:
    map(const key_compare& comp = key_compare()) 
        : _tree(_vc(comp)) {}

    template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) 
        : _tree(_vc(comp))
        { insert(first, last); }

    map(const map& m) : _tree(m._tree) 
        {}

   ~map() {}

    map& operator=(const map& m)
    {
        if (this != &m)
            _tree = m._tree;
        return *this;
    }
    
    // iterators:
          iterator          begin()                         { return iterator(_tree.begin()); }
    const_iterator          begin() const                   { return const_iterator(_tree.begin()); }
          iterator          end()                           { return iterator(_tree.end()); }
    const_iterator          end()   const                   { return const_iterator(_tree.end()); }

          reverse_iterator  rbegin()                        { return reverse_iterator(end()); }
    const_reverse_iterator  rbegin() const                  { return const_reverse_iterator(end()); }
          reverse_iterator  rend()                          { return reverse_iterator(begin()); }
    const_reverse_iterator  rend()   const                  { return const_reverse_iterator(begin()); }

    // capacity:
    bool                    empty()    const                { return _tree.size() == 0; }
    size_type               size()     const                { return _tree.size(); }
    size_type               max_size() const                { return _tree.max_size(); }

    // element access:
    mapped_type&                operator[](const key_type& k)
    {
        return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
    }

    // modifiers:
    ft::pair<iterator, bool>    insert(const value_type& v)
    { return ft::make_pair(iterator(_tree.insert(v).first), _tree.insert(v).second); }
    
    iterator                    insert(const_iterator position, const value_type& v)
    { return iterator(_tree.insert(position._i, v)); }

    template <class InputIterator>
    void                        insert(InputIterator first, InputIterator last)
    { _tree.insert(first._i, last._i); }

    void            erase(iterator position)                { _tree.erase(position._i); }

    size_type       erase(const key_type& k)                { return _tree.erase(k); }

    void            erase(iterator first, iterator last)    { _tree.erase(first._i, last._i); }

    void            swap(map& m)                            { _tree.swap(m._tree); }

    void            clear()                                 { _tree.clear(); }

    // observers:
    key_compare     key_comp()      const                   { return _tree.get_vc().key_comp(); }
    value_compare   value_comp()    const                   { return value_compare(_tree.get_vc().key_comp()); }

    // operations:
          iterator  find(const key_type& k)                 { return iterator(_tree.find(k)); }

    const_iterator  find(const key_type& k) const           { return const_iterator(_tree.find(k)); }


    size_type       count(const key_type& k) const          { return _tree.count(k); }

          iterator  lower_bound(const key_type& k)          { return iterator(_tree.lower_bound(k)); }

    const_iterator  lower_bound(const key_type& k) const    { return const_iterator(_tree.lower_bound(k)); }

          iterator  upper_bound(const key_type& k)          { return iterator(_tree.upper_bound(k)); }

    const_iterator  upper_bound(const key_type& k) const    { return const_iterator(_tree.upper_bound(k)); }

    ft::pair<iterator,iterator>             equal_range(const key_type& k)
    { return ft::make_pair(iterator(_tree.equal_range(k).first), iterator(_tree.equal_range(k).second)); }

    ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
    { return ft::make_pair(const_iterator(_tree.equal_range(k).first), const_iterator(_tree.equal_range(k).second)); }

    // allocator
    allocator_type  get_allocator() const                   { allocator_type a; return a; }
};

// Non-member function overloads
template <class Key, class T, class Compare, class Allocator>
bool
operator==(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

template <class Key, class T, class Compare, class Allocator>
bool
operator< (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class Key, class T, class Compare, class Allocator>
bool
operator!=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return !(x == y); }

template <class Key, class T, class Compare, class Allocator>
bool
operator> (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return y < x; }

template <class Key, class T, class Compare, class Allocator>
bool
operator>=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return !(x < y); }

template <class Key, class T, class Compare, class Allocator>
bool
operator<=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return !(y < x); }

template <class Key, class T, class Compare, class Allocator>
void
swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
{ x.swap(y); }

}

#endif
