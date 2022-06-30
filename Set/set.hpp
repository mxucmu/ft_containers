/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:07:42 by mxu               #+#    #+#             */
/*   Updated: 2022/01/10 14:53:44 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP_
#define SET_HPP_

#include <memory>
#include <functional>
#include <iostream>
#include <utility>

#include "../Lib/utillity.hpp"
#include "../Lib/tree.hpp"
#include "../Lib/iterator.hpp"
#include "../Lib/algorithm.hpp"

// Reference from site: https://cplusplus.com/reference/set/set/

// libc++ implementation located on Mac: 
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

// Implementaion version c++98

namespace ft
{

template <class Key, class Tp, class Compare>
class set_value_compare
{
    Compare comp;

public:
    typedef Key                                         first_argument_type;
    typedef Compare                                     third_argument_type;

    set_value_compare() : comp()                        {}
    set_value_compare(Compare c) : comp(c)              {}
    const Compare& key_comp() const                     {return comp;}

    bool operator()(const Tp& x, const Tp& y) const     { return comp(x, y); }
    
    void swap(set_value_compare& y)                     { std::swap(comp, y.comp); }
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Key, 
          class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set
{
public:
    typedef Key                                         key_type;
    typedef key_type                                    value_type;
    typedef Compare                                     key_compare;
    typedef key_compare                                 value_compare;
    typedef Allocator                                   allocator_type;
    typedef value_type&                                 reference;         
    typedef const value_type&                           const_reference;

private:
    typedef set_value_compare<key_type, value_type, key_compare>    _vc;
    typedef ft::RBTree<value_type, _vc, allocator_type>             _base;

    _base   _tree;

public:
    typedef typename _base::pointer                     pointer;
    typedef typename _base::const_pointer               const_pointer;
    typedef typename _base::size_type                   size_type;
    typedef typename _base::difference_type             difference_type;
    typedef typename _base::iterator                    iterator;
    typedef typename _base::const_iterator              const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

public:
    // construct/copy/destroy:
    explicit set(const key_compare& comp = key_compare()) 
        : _tree(_vc(comp)) {}
    
        set(iterator first, iterator last, const key_compare& comp = key_compare()) 
        : _tree(_vc(comp))
        { insert(first, last); }

    template <class InputIterator>
        set(InputIterator first, 
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
            !std::__is_forward_iterator<InputIterator>::value, InputIterator>::type last, 
            const key_compare& comp = key_compare())
        : _tree(_vc(comp))
        { insert(first, last); }

    template <class ForwardIterator>
        set(ForwardIterator first, 
			typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last,
            const key_compare& comp = key_compare())
        : _tree(_vc(comp))
        { insert(first, last); }

    set(const set& s) : _tree(s._tree) 
        {}

   ~set() {}

    set& operator=(const set& s)
    {
        if (this != &s)
            _tree = s._tree;
        return *this;
    }

    // iterators:
          iterator          begin()                         { return _tree.begin(); }
    const_iterator          begin() const                   { return _tree.begin(); }
          iterator          end()                           { return _tree.end(); }
    const_iterator          end()   const                   { return _tree.end(); }

          reverse_iterator  rbegin()                        { return reverse_iterator(end()); }
    const_reverse_iterator  rbegin() const                  { return const_reverse_iterator(end()); }
          reverse_iterator  rend()                          { return reverse_iterator(begin()); }
    const_reverse_iterator  rend()   const                  { return const_reverse_iterator(begin()); }

    // capacity:
    bool                    empty()    const                { return _tree.size() == 0; }
    size_type               size()     const                { return _tree.size(); }
    size_type               max_size() const                { return _tree.max_size(); }

    // modifiers:
    ft::pair<iterator, bool>    insert(const value_type& v)
    { return ft::make_pair(_tree.insert(v).first, _tree.insert(v).second); }
    
    iterator                    insert(const_iterator position, const value_type& v)
    { return _tree.insert(position, v); }

    void                        insert(iterator first, iterator last)
    { _tree.insert(first, last); }

    template <class InputIterator>
    void                        insert(InputIterator first, 
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
            !std::__is_forward_iterator<InputIterator>::value, InputIterator>::type last)
    { _tree.insert(first, last); }

    template <class ForwardIterator>
    void                        insert(ForwardIterator first, 
			typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last)
    { _tree.insert(first, last); }

    void            erase(iterator position)                { _tree.erase(position); }

    size_type       erase(const key_type& k)                { return _tree.erase(k); }

    void            erase(iterator first, iterator last)    { _tree.erase(first, last); }

    void            swap(set& s)                            { _tree.swap(s._tree); }

    void            clear()                                 { _tree.clear(); }

    // observers:
    key_compare     key_comp()      const                   { return _tree.get_vc().key_comp(); }
    value_compare   value_comp()    const                   { return _tree.get_vc().key_comp(); }

    // operations:
          iterator  find(const key_type& k)                 { return _tree.find(k); }

    const_iterator  find(const key_type& k) const           { return _tree.find(k); }

    size_type       count(const key_type& k) const          { return _tree.count(k); }

          iterator  lower_bound(const key_type& k)          { return _tree.lower_bound(k); }

    const_iterator  lower_bound(const key_type& k) const    { return _tree.lower_bound(k); }

          iterator  upper_bound(const key_type& k)          { return _tree.upper_bound(k); }

    const_iterator  upper_bound(const key_type& k) const    { return _tree.upper_bound(k); }

    ft::pair<iterator,iterator>             equal_range(const key_type& k)
    { return ft::make_pair(_tree.equal_range(k).first, _tree.equal_range(k).second); }

    ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
    { return ft::make_pair(_tree.equal_range(k).first, _tree.equal_range(k).second); }

    // allocator
    allocator_type  get_allocator() const                   { allocator_type a; return a; }
 };

// Non-member function overloads
template <class Key, class Compare, class Allocator>
bool
operator==(const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

template <class Key, class Compare, class Allocator>
bool
operator< (const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class Key, class Compare, class Allocator>
bool
operator!=(const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return !(x == y); }

template <class Key, class Compare, class Allocator>
bool
operator> (const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return y < x; }

template <class Key, class Compare, class Allocator>
bool
operator>=(const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return !(x < y); }

template <class Key, class Compare, class Allocator>
bool
operator<=(const set<Key, Compare, Allocator>& x,
           const set<Key, Compare, Allocator>& y)
{ return !(y < x); }

template <class Key, class Compare, class Allocator>
void
swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
{ x.swap(y); }

}

#endif
