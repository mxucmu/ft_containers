/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:48:25 by mxu               #+#    #+#             */
/*   Updated: 2022/01/10 14:51:02 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <limits>
#include <utility>
#include <exception>
#include <cassert>
#include "../Lib/utillity.hpp"
#include "../Lib/iterator.hpp"
#include "../Lib/type_traits.hpp"
#include "../Lib/algorithm.hpp"
#include "../Lib/split_buffer.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))

// Reference from site: https://cplusplus.com/reference/vector/vector/

// libc++ implementation located on Mac: 
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

// Implementaion version c++98

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
    // Member types
    typedef T                                           value_type;
    typedef Allocator                                   allocator_type;

    typedef typename allocator_type::reference          reference;          // value_type&
    typedef typename allocator_type::const_reference    const_reference;    // const value_type&
    typedef typename allocator_type::pointer            pointer;            // std::allocator_traits<allocator_type>::pointer
    typedef typename allocator_type::const_pointer      const_pointer;      // std::allocator_traits<allocator_type>::const_pointer
    typedef typename allocator_type::size_type          size_type;          // std::allocator_traits<allocator_type>::size_type
    typedef typename allocator_type::difference_type    difference_type;    // std::allocator_traits<allocator_type>::difference_type
    typedef ft::wrap_iter<pointer>                      iterator;
    typedef ft::wrap_iter<const_pointer>                const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

    // Member functions
    vector();
    explicit vector(size_type n);
    vector(size_type n, const value_type& x);
    vector(iterator first, iterator last);
    template <class InputIterator>
        vector(InputIterator first, 
        typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                               !std::__is_forward_iterator<InputIterator>::value, InputIterator>::type last);
    template <class ForwardIterator>
        vector(ForwardIterator first, 
        typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last);
    vector(const vector& x);
    ~vector();
    vector& operator=(const vector& x);

    // Iterators
    iterator                begin();
    const_iterator          begin() const;
    iterator                end();
    const_iterator          end() const;
    
    reverse_iterator        rbegin();
    const_reverse_iterator  rbegin() const;
    reverse_iterator        rend();
    const_reverse_iterator  rend() const;

    // Capacity
    size_type               size() const;
    size_type               max_size() const;
    void                    resize(size_type sz);
    size_type               capacity() const;
    bool                    empty() const;
    void                    reserve(size_type n);

    // Element access
    reference               operator[](size_type n);
    const_reference         operator[](size_type n) const;
    reference               at(size_type n);
    const_reference         at(size_type n) const;
    reference               front();
    const_reference         front() const;
    reference               back();
    const_reference         back() const;

    // Modifiers
    void                    assign(iterator first, iterator last);
    template <class InputIterator>
    typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                       !std::__is_forward_iterator<InputIterator>::value, void>::type
                            assign(InputIterator first, InputIterator last);
    template <class ForwardIterator>
    typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, void>::type  
                            assign(ForwardIterator first, ForwardIterator last);
    void                    assign(size_type n, const value_type& u);
    void                    push_back(const value_type& x);
    void                    pop_back();
    iterator                insert(const_iterator position, const_reference x);
    iterator                insert(const_iterator position, size_type n, const_reference x);
    iterator                insert(const_iterator position, iterator first, iterator last);
    template <class InputIterator>
    typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                       !std::__is_forward_iterator<InputIterator>::value, iterator>::type
                            insert(const_iterator position, InputIterator first, InputIterator last);
    template <class ForwardIterator>
    typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, iterator>::type
                            insert(const_iterator position, ForwardIterator first, ForwardIterator last);
    iterator                erase(const_iterator position);
    iterator                erase(const_iterator first, const_iterator last);
    void                    swap(vector& x);
    void                    clear();

    // Allocator
    allocator_type          get_allocator() const;

private:
    pointer                             _begin;
    pointer                             _end;
    ft::pair<pointer, allocator_type>   _end_cap_;  // first: a pointer at _begin + allocated size; second: allocator_type

    allocator_type&         _alloc();
    const allocator_type&   _alloc() const;
    pointer&                _end_cap();
    const pointer&          _end_cap() const;
    void                    _vallocate(size_type _n);
    void                    _vdeallocate();
    void                    _copy_assign_alloc(const vector& _x);
    size_type               _recommend(size_type _n) const;
    void                    _construct_at_end(size_type _n);
    void                    _construct_at_end(size_type _n, const_reference _x);
    void                    _construct_at_end(iterator _first, iterator _last, size_type _n);
    template <class ForwardIterator>
    typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, void>::type
                            _construct_at_end(ForwardIterator _first, ForwardIterator _last, size_type _n);
    void                    _append(size_type _n);
    void                    _append(size_type _n, const_reference _x);
    void                    _destruct_at_end(pointer _p);
    void                    _construct_backward(allocator_type& _a, pointer _begin1, pointer _end1, pointer& _end2);
    void                    _construct_forward(allocator_type& _a, pointer _begin1, pointer _end1, pointer& _begin2);
    void                    _swap_out_circular_buffer(split_buffer<value_type, allocator_type>& _v);
    pointer                 _swap_out_circular_buffer(split_buffer<value_type, allocator_type>& _v, pointer _p);
    iterator                _make_iter(pointer _p) const;
    const_iterator          _make_iter(const_pointer _p) const;
    template <class Up>
    void                    _push_back_slow_path(Up& _x);
    void                    _move_range(pointer _from_s, pointer _from_e, pointer _to);

};

// Non-member function overloads
template <class T, class Allocator>
bool    operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    const typename ft::vector<T, Allocator>::size_type  sz = x.size();
    return sz == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class T, class Allocator>
bool    operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T, class Allocator>
bool    operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    return !(x == y);
}

template <class T, class Allocator>
bool    operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    return y < x;
}

template <class T, class Allocator>
bool    operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    return !(x < y);
}

template <class T, class Allocator>
bool    operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    return !(y < x);
}

template <class T, class Allocator>
void    swap(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
    x.swap(y);
}

// Implementation: Private functions
template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type&         vector<T, Allocator>::_alloc() 
{
    return _end_cap_.second;
}

template <class T, class Allocator>
const typename vector<T, Allocator>::allocator_type&   vector<T, Allocator>::_alloc() const
{
    return _end_cap_.second;
}

template <class T, class Allocator>
typename vector<T, Allocator>::pointer&                vector<T, Allocator>::_end_cap()
{
    return _end_cap_.first;
}

template <class T, class Allocator>
const typename vector<T, Allocator>::pointer&          vector<T, Allocator>::_end_cap() const
{
    return _end_cap_.first;
}

template <class T, class Allocator>
void    vector<T, Allocator>::_vallocate(size_type _n)
{
    if (_n > max_size())
        throw std::length_error("Vector");
    this->_begin = this->_end = std::allocator_traits<allocator_type>::allocate(this->_alloc(), _n);
    this->_end_cap() = this->_begin + _n;
}

template <class T, class Allocator>
void    vector<T, Allocator>::_vdeallocate()
{
    if (this->_begin != nullptr)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(this->_alloc(), this->_begin, capacity());
        this->_begin = this->_end = this->_end_cap() = nullptr;
    }
}

template <class T, class Allocator>
void    vector<T, Allocator>::_copy_assign_alloc(const vector& _x)
{
    if (this->_alloc() != _x._alloc())
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(this->_alloc(), this->_begin, capacity());
        this->_begin = this->_end = this->_end_cap() = nullptr;
    }
    this->_alloc() = _x._alloc();
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type    vector<T, Allocator>::_recommend(size_type _n) const
{
    const size_type     _ms = max_size();
    if (_n > _ms)
        throw std::length_error("Vector");
    const size_type     _cap = capacity();
    if (_cap >= _ms / 2)
        return _ms;
    return std::max<size_type>(2 * _cap, _n);
}

template <class T, class Allocator>
void    vector<T, Allocator>::_construct_at_end(size_type _n)
{
    allocator_type& _a = this->_alloc();
    do
    {
        std::allocator_traits<allocator_type>::construct(_a, this->_end);
        ++this->_end;
        --_n;
    } while (_n > 0);
}

template <class T, class Allocator>
void    vector<T, Allocator>::_construct_at_end(size_type _n, const_reference _x)
{
    allocator_type& _a = this->_alloc();
    do
    {
        std::allocator_traits<allocator_type>::construct(_a, this->_end, _x);
        ++this->_end;
        --_n;
    } while (_n > 0);
}

template <class T, class Allocator>
void     vector<T, Allocator>::_construct_at_end(iterator _first, iterator _last, size_type _n)
{
    allocator_type& _a = this->_alloc();
    for (; _first != _last; ++_first)
    {
        std::allocator_traits<allocator_type>::construct(_a, this->_end, *_first);
        ++this->_end;
        _n = 0;
    }
}

template <class T, class Allocator>
template <class ForwardIterator>
typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, void>::type
    vector<T, Allocator>::_construct_at_end(ForwardIterator _first, ForwardIterator _last, size_type _n)
    {
        allocator_type& _a = this->_alloc();
        std::allocator_traits<allocator_type>::__construct_range_forward(_a, _first, _last, this->_end); 
        _n = 0;
    }

template <class T, class Allocator>
void    vector<T, Allocator>::_append(size_type _n)
{
    if (static_cast<size_type>(this->_end_cap() - this->_end) >= _n)
        this->_construct_at_end(_n);
    else
    {
        allocator_type& _a = this->_alloc();
        split_buffer<value_type, allocator_type> _v(_recommend(size() + _n), size(), _a);
        _v.construct_at_end(_n);
        _swap_out_circular_buffer(_v);
    }
}

template <class T, class Allocator>
void    vector<T, Allocator>::_append(size_type _n, const_reference _x)
{
    if (static_cast<size_type>(this->_end_cap() - this->_end) >= _n)
        this->_construct_at_end(_n, _x);
    else
    {
        allocator_type& _a = this->_alloc();
        split_buffer<value_type, allocator_type> _v(_recommend(size() + _n), size(), _a);
        _v.construct_at_end(_n, _x);
        _swap_out_circular_buffer(_v);
    }
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator    vector<T, Allocator>::_make_iter(pointer _p) const
{
    return iterator(_p);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator    vector<T, Allocator>::_make_iter(const_pointer _p) const
{
    return const_iterator(_p);
}

template <class T, class Allocator>
void    vector<T, Allocator>::_destruct_at_end(pointer _p)
{
    pointer     tmp = _end;
    while (_p != tmp)
    {
        std::allocator_traits<allocator_type>::destroy(this->_alloc(), --tmp);
    }
    this->_end = tmp;
}

template <class T, class Allocator>
void    vector<T, Allocator>::_construct_backward(allocator_type& _a, pointer _begin1, pointer _end1, pointer& _end2)
{
    while (_end1 != _begin1)
    {
        std::allocator_traits<allocator_type>::construct(_a, _end2 - 1, *--_end1);
        --_end2;
    }
}

template <class T, class Allocator>
void    vector<T, Allocator>::_construct_forward(allocator_type& _a, pointer _begin1, pointer _end1, pointer& _begin2)
{
    for (; _begin1 != _end1; ++_begin1, (void) ++_begin2)
        std::allocator_traits<allocator_type>::construct(_a, _begin2, *_begin1);
}

template <class T, class Allocator>
void                                        vector<T, Allocator>::_swap_out_circular_buffer(
                                                ft::split_buffer<value_type, allocator_type>& _v)
{
    _construct_backward(this->_alloc(), this->_begin, this->_end, _v._begin);
    std::swap(this->_begin, _v._begin);
    std::swap(this->_end, _v._end);
    std::swap(this->_end_cap(), _v.end_cap());
    _v._first = _v._begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::pointer      vector<T, Allocator>::_swap_out_circular_buffer(
                                                ft::split_buffer<value_type, allocator_type>& _v, pointer _p)
{
    pointer r = _v._begin;
    _construct_backward(this->_alloc(), this->_begin, _p, _v._begin);
    _construct_forward(this->_alloc(), _p, this->_end, _v._end);
    std::swap(this->_begin, _v._begin);
    std::swap(this->_end, _v._end);
    std::swap(this->_end_cap(), _v.end_cap());
    _v._first = _v._begin;
    return r;
}

template <class T, class Allocator>
void                    vector<T, Allocator>::_move_range(pointer _from_s, pointer _from_e, pointer _to)
{
    pointer         old_last = this->_end;
    difference_type n = old_last - _to;
    for (pointer i = _from_s + n; i < _from_e; ++i, ++this->_end)
        std::allocator_traits<allocator_type>::construct(this->_alloc(), this->_end, std::move(*i));
    std::move_backward(_from_s, _from_s + n, old_last);
}

// Implementation: Member functions
template <class T, class Allocator>
vector<T, Allocator>::vector() : _begin(nullptr), _end(nullptr), _end_cap_() {}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type n)
{
    if (n > 0)
    {
        _vallocate(n);
        _construct_at_end(n);
    }
}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const value_type& x)
{
    if (n > 0)
    {
        _vallocate(n);
        _construct_at_end(n, x);
    }
}

template <class T, class Allocator>
vector<T, Allocator>::vector(iterator first, iterator last)
{
    size_type   n = static_cast<size_type>(last - first);
    if (n > 0)
    {
        _vallocate(n);
        _construct_at_end(first, last, n);
    }
}

template <class T, class Allocator>
template <class InputIterator>
    vector<T, Allocator>::vector(InputIterator first, 
        typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                               !std::__is_forward_iterator<InputIterator>::value, InputIterator>::type last)
    {
        for (; first != last; ++first)
            push_back(*first);
    }

template <class T, class Allocator>
template <class ForwardIterator>
    vector<T, Allocator>::vector(ForwardIterator first, 
        typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last)
    {
        size_type   n = static_cast<size_type>(std::distance(first, last));
        if (n > 0)
        {
            _vallocate(n);
            _construct_at_end(first, last, n);
        }
    }

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& x)
{
    size_type n = x.size();
    if (n > 0)
    {
        _vallocate(n);
        _construct_at_end(x._begin, x._end, n);
    }
}

template <class T, class Allocator>
vector<T, Allocator>::~vector()
{
    if (_begin != nullptr)
    {
        clear();
        std::allocator_traits<allocator_type>::deallocate(_alloc(), _begin, capacity());
    }
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x)
{
    if (this != &x)
    {
        _copy_assign_alloc(x);
        assign(x._begin, x._end);
    }
    return *this;
}

// Implementation: Iterators
template <class T, class Allocator>
typename vector<T, Allocator>::iterator    vector<T, Allocator>::begin()
{
    return _make_iter(this->_begin);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator    vector<T, Allocator>::begin() const
{
    return _make_iter(this->_begin);
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator                 vector<T, Allocator>::end()
{
    return _make_iter(this->_end);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator           vector<T, Allocator>::end() const
{
    return _make_iter(this->_end);
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator         vector<T, Allocator>::rbegin()
{
    return reverse_iterator(end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator   vector<T, Allocator>::rbegin() const
{
    return const_reverse_iterator(end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator         vector<T, Allocator>::rend()
{
    return reverse_iterator(begin());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator   vector<T, Allocator>::rend() const
{
    return const_reverse_iterator(begin());
}

// Implementation: Capacity
template <class T, class Allocator>
typename vector<T, Allocator>::size_type                vector<T, Allocator>::size() const
{
    return static_cast<size_type>(this->_end - this->_begin);
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type                vector<T, Allocator>::max_size() const
{
    return std::min<size_type>(std::allocator_traits<allocator_type>::max_size(this->_alloc()), 
                               std::numeric_limits<difference_type>::max());
}

template <class T, class Allocator>
void                    vector<T, Allocator>::resize(size_type sz)
{
    size_type cs = size();
    if (cs < sz)
        this->_append(sz - cs);
    else if (cs > sz)
        this->_destruct_at_end(this->_begin + sz);
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type               vector<T, Allocator>::capacity() const
{
    return static_cast<size_type>(this->_end_cap() - this->_begin);
}

template <class T, class Allocator>
bool                    vector<T, Allocator>::empty() const
{
    return this->_begin == this->_end;
}

template <class T, class Allocator>
void                    vector<T, Allocator>::reserve(size_type n)
{
    if (n > capacity())
    {
        allocator_type& a = this->_alloc();
        split_buffer<value_type, allocator_type> v(n, size(), a);
        _swap_out_circular_buffer(v);
    }
}
    
// Implementation: Element access 
template <class T, class Allocator>    
typename vector<T, Allocator>::reference                vector<T, Allocator>::operator[](size_type n)
{
    assertm(n < size(), "vector[] index out of bounds");
    return this->_begin[n];
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::const_reference          vector<T, Allocator>::operator[](size_type n) const
{
    assertm(n < size(), "vector[] index out of bounds");
    return this->_begin[n];
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::reference                vector<T, Allocator>::at(size_type n)
{
    if (n > size())
        throw std::out_of_range("Vector");
    return this->_begin[n];
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::const_reference          vector<T, Allocator>::at(size_type n) const
{
    if (n > size())
        throw std::out_of_range("Vector");
    return this->_begin[n];
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::reference                vector<T, Allocator>::front()
{
    assertm(!empty(), "front() called for empty vector");
    return *this->_begin;
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::const_reference          vector<T, Allocator>::front() const
{
    assertm(!empty(), "front() called for empty vector");
    return *this->_begin;
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::reference                vector<T, Allocator>::back()
{
    assertm(!empty(), "back() called for empty vector");
    return *(this->_end - 1);    
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::const_reference          vector<T, Allocator>::back() const
{
    assertm(!empty(), "back() called for empty vector");
    return *(this->_end - 1);
}

// Implementation: Modifiers
template <class T, class Allocator> 
void                    vector<T, Allocator>::assign(iterator first, iterator last)
{
    size_type   new_size = static_cast<size_type>(last - first);
    if (new_size <= capacity())
    {
        iterator    mid = last;
        bool        growing = false;
        if (new_size > size())
        {
            growing = true;
            mid = first;
            mid +=size();
        }
        pointer m = std::copy(first, mid, this->_begin);
        if (growing)
            _construct_at_end(mid, last, new_size - size());
        else
            this->_destruct_at_end(m);
    }
    else
    {
        _vdeallocate();
        _vallocate(_recommend(new_size));
        _construct_at_end(first, last, new_size);
    }
}

template <class T, class Allocator> 
template <class InputIterator>
typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                   !std::__is_forward_iterator<InputIterator>::value, void>::type
    vector<T, Allocator>::assign(InputIterator first, InputIterator last)
    {
        clear();
        for (; first != last; ++first)
            push_back(*(first));
    }


template <class T, class Allocator> 
template <class ForwardIterator>
typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, void>::type  
    vector<T, Allocator>::assign(ForwardIterator first, ForwardIterator last)
    {
        size_type   new_size = static_cast<size_type>(std::distance(first, last));
        if (new_size <= capacity())
        {
            ForwardIterator mid = last;
            bool    growing = false;
            if (new_size > size())
            {
                growing = true;
                mid = first;
                std::advance(mid, size());
            }
            pointer m = std::copy(first, mid, this->_begin);
            if (growing)
                _construct_at_end(mid, last, new_size - size());
            else
                this->_destruct_at_end(m);
        }
        else
        {
            _vdeallocate();
            _vallocate(_recommend(new_size));
            _construct_at_end(first, last, new_size);
        }
    }    
    
template <class T, class Allocator>    
void                    vector<T, Allocator>::assign(size_type n, const value_type& u)
{
    if (n <= capacity())
    {
        size_type s = size();
        std::fill_n(this->_begin, std::min(n, s), u);
        if (n > s)
            _construct_at_end(n - s, u);
        else
            this->_destruct_at_end(this->_begin + n);
    }
    else
    {
        _vdeallocate();
        _vallocate(_recommend(static_cast<size_type>(n)));
        _construct_at_end(n, u);
    }
}

template <class T, class Allocator>
template <class Up>
void                    vector<T, Allocator>::_push_back_slow_path(Up& _x)
{
    allocator_type& a = this->_alloc();
    split_buffer<value_type, allocator_type> v(_recommend(size() + 1), size(), a);
    std::allocator_traits<allocator_type>::construct(a, v._end, std::forward<Up>(_x));
    v._end++;
    _swap_out_circular_buffer(v);
}
    
template <class T, class Allocator>    
void                    vector<T, Allocator>::push_back(const value_type& x)
{
    if (this->_end != this->_end_cap())
    {
        std::allocator_traits<allocator_type>::construct(this->_alloc(), this->_end, x);
        ++this->_end;
    }
    else
        _push_back_slow_path(x);
}
    
template <class T, class Allocator>    
void                    vector<T, Allocator>::pop_back()
{
    assertm(!empty(), "vector::pop_back called for empty vector");
    this->_destruct_at_end(this->_end - 1);
}

template <class T, class Allocator>    
typename vector<T, Allocator>::iterator     vector<T, Allocator>::insert(const_iterator position, 
                                                                         const_reference x)
{
    pointer p = this->_begin + (position - begin());
    if (this->_end < this->_end_cap())
    {
        if (p == this->_end)
        {
            std::allocator_traits<allocator_type>::construct(this->_alloc(), this->_end, x);
            ++this->_end;
        }
        else
        {
            _move_range(p, this->_end, p + 1);
            const_pointer xr = std::pointer_traits<const_pointer>::pointer_to(x);
            if (p <= xr && xr < this->_end)
                ++xr;
            *p = *xr;
        }
    }
    else
    {
        allocator_type& a = this->_alloc();
        split_buffer<value_type, allocator_type> v(_recommend(size() + 1), p - this->_begin, a);
        v.push_back(x);
        p = _swap_out_circular_buffer(v, p);
    }
    return _make_iter(p);
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::iterator     vector<T, Allocator>::insert(const_iterator position, 
                                                                         size_type n, const_reference x)
{
    pointer p = this->_begin + (position - begin());
    if (n > 0)
    {
        if (n <= static_cast<size_type>(this->_end_cap() - this->_end))
        {
            size_type   old_n = n;
            pointer     old_last = this->_end;
            if (n > static_cast<size_type>(this->_end - p))
            {
                size_type   cx = n - (this->_end - p);
                _construct_at_end(cx, x);
                n -= cx;
            }
            if (n > 0)
            {
                _move_range(p, old_last, p + old_n);
                const_pointer xr = std::pointer_traits<const_pointer>::pointer_to(x);
                if (p <= xr && xr < this->_end)
                    xr += old_n;
                std::fill_n(p, n, *xr);
            }
        }
        else
        {
            allocator_type& a = this->_alloc();
            split_buffer<value_type, allocator_type> v(_recommend(size() + n), p - this->_begin, a);
            v.construct_at_end(n, x);
            p = _swap_out_circular_buffer(v, p);
        }
    }
    return _make_iter(p);
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator     vector<T, Allocator>::insert(const_iterator position, 
                                                                         iterator first, iterator last)
{
    pointer         p = this->_begin + (position - begin());
    difference_type n = last - first;
    if (n > 0)
    {
        if (n <= this->_end_cap() - this->_end)
        {
            size_type       old_n = n;
            pointer         old_last = this->_end;
            iterator        m = last;
            difference_type dx = this->_end - p;
            if (n > dx)
            {
                m = first;
                difference_type diff = this->_end - p;
                m += diff;
                _construct_at_end(m, last, n - diff);
                n = dx;
            }
            if (n > 0)
            {
                _move_range(p, old_last, p + old_n);
                std::copy(first, m, p);
            }
        }
        else
        {
            allocator_type& a = this->_alloc();
            split_buffer<value_type, allocator_type> v(_recommend(size() + n), p - this->_begin, a);
            v.construct_at_end(first, last);
            p = _swap_out_circular_buffer(v, p);
        }
    }
    return _make_iter(p);
}

template <class T, class Allocator>    
template <class InputIterator>
typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
                       !std::__is_forward_iterator<InputIterator>::value, 
                       typename vector<T, Allocator>::iterator>::type
    vector<T, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last)
    {
        difference_type off = position - begin();
        pointer         p = this->begin + off;
        allocator_type& a = this->_alloc();
        pointer         old_last = this->_end;
        for (; this->_end != this->_end_cap() && first != last; ++first)
        {
            std::allocator_traits<allocator_type>::construct(a, this->_end, *first);
            ++this->end;
        }
        split_buffer<value_type, allocator_type> v(a);
        if (first != last)
        {
            try
            {
                v.construct_at_end(first, last);
                difference_type old_size = old_last - this->_begin;
                difference_type old_p = p - this->_begin;
                reserve(_recommend(size() + v.size()));
                p = this->_begin + old_p;
                old_last = this->_begin + old_size;
            }
            catch(...)
            {
                erase(_make_iter(old_last), end());
                throw;
            }
        }
        p = std::rotate(p, old_last, this->_end);
        insert(_make_iter(p), std::make_move_iterator(v.begin()), std::make_move_iterator(v.end()));
        return begin() + off;
    }
    
template <class T, class Allocator>  
template <class ForwardIterator>
    typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, 
                           typename vector<T, Allocator>::iterator>::type
    vector<T, Allocator>::insert(const_iterator position, ForwardIterator first, ForwardIterator last)
    {
        pointer         p = this->_begin + (position - begin());
        difference_type n = std::distance(first, last);
        if (n > 0)
        {
            if (n <= this->_end_cap() - this->_end)
            {
                size_type       old_n = n;
                pointer         old_last = this->_end;
                ForwardIterator m = last;
                difference_type dx = this->_end - p;
                if (n > dx)
                {
                    m = first;
                    difference_type diff = this->_end - p;
                    std::advance(m, diff);
                    _construct_at_end(m, last, n - diff);
                    n = dx;
                }
                if (n > 0)
                {
                    _move_range(p, old_last, p + old_n);
                    std::copy(first, m, p);
                }
            }
            else
            {
                allocator_type& a = this->_alloc();
                split_buffer<value_type, allocator_type> v(_recommend(size() + n), p - this->_begin, a);
                v.construct_at_end(first, last);
                p = _swap_out_circular_buffer(v, p);
            }
        }
        return _make_iter(p);
    }

template <class T, class Allocator>    
typename vector<T, Allocator>::iterator     vector<T, Allocator>::erase(const_iterator position)
{
    assertm(position != end(), "vector::erase(iterator) called with a non-dereferenceable iterator");
    difference_type ps = position - static_cast<const_iterator>(begin());
    pointer         p = this->_begin + ps;
    this->_destruct_at_end(std::move(p + 1, this->_end, p));
    (void) (p - 1);
    iterator    r = _make_iter(p);
    return r;
}
    
template <class T, class Allocator>    
typename vector<T, Allocator>::iterator     vector<T, Allocator>::erase(const_iterator first, const_iterator last)
{
    assertm(first <= last, "vector::erase(first, last) called with invalid range");
    pointer     p = this->_begin + (first - begin());
    if (first != last)
    {
        this->_destruct_at_end(std::move(p + (last - first), this->_end, p));
        (void) (p - 1);
    }
    iterator    r = _make_iter(p);
    return r;
}
    
template <class T, class Allocator>    
void                                        vector<T, Allocator>::swap(vector& x)
{
    assertm(this->_alloc() == x._alloc(),
            "vector::swap: the allocators must compare equal");
    std::swap(this->_begin, x._begin);
    std::swap(this->_end, x._end);
    std::swap(this->_end_cap(), x._end_cap());
}
    
template <class T, class Allocator>    
void                                        vector<T, Allocator>::clear()
{
    _destruct_at_end(this->_begin);
}

// Implementation: Allocator
template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type          vector<T, Allocator>::get_allocator() const
{
    return _alloc();
}

}

#endif
