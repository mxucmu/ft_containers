/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_buffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 00:30:02 by mxu               #+#    #+#             */
/*   Updated: 2021/12/31 19:09:05 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_BUFFER_
#define SPLIT_BUFFER_

#include <memory>
#include <algorithm>

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
struct split_buffer
{
private: 
    split_buffer(const split_buffer&);
    split_buffer& operator=(const split_buffer&);

public:
    typedef T                                           value_type;
    typedef Allocator                                   allocator_type;

    typedef value_type&                                 reference;          // typename allocator_type::reference
    typedef const value_type&                           const_reference;    // typename allocator_type::const_reference
    typedef T*                                          pointer;            // std::allocator_traits<allocator_type>::pointer
    typedef const T*                                    const_pointer;      // std::allocator_traits<allocator_type>::const_pointer
    typedef size_t                                      size_type;          // std::allocator_traits<allocator_type>::size_type
    typedef ptrdiff_t                                   difference_type;    // std::allocator_traits<allocator_type>::difference_type
    typedef ft::wrap_iter<pointer>                      iterator;
    
public:
    pointer                                             _first;
    pointer                                             _begin;
    pointer                                             _end;
    ft::pair<pointer, allocator_type>                   _end_cap;  // first: a pointer at _begin + allocated size; second: allocator_type

    split_buffer() : _first(nullptr), _begin(nullptr), _end(nullptr) { end_cap() = nullptr; }

    split_buffer(const allocator_type& _a) : _first(nullptr), _begin(nullptr), _end(nullptr),
                     _end_cap(nullptr, _a) {}

    split_buffer(size_type _cap, size_type _start, allocator_type& _a) : _end_cap(nullptr, _a)
    {
        _first = _cap != 0 ? std::allocator_traits<allocator_type>::allocate(this->alloc(), _cap) : nullptr;
        _begin = _end = _first + _start;
        end_cap() = _first + _cap;
    }
    
    ~split_buffer()
    {
        destruct_at_end(_begin);
        if (_first)
            std::allocator_traits<allocator_type>::deallocate(this->alloc(), _first, end_cap() - _first);
    }

    allocator_type&         alloc() 
    {
        return _end_cap.second;
    }

    const allocator_type&   alloc() const
    {
        return _end_cap.second;
    }

    pointer&                end_cap()
    {
        return _end_cap.first;
    }

    const pointer&          end_cap() const
    {
        return _end_cap.first;
    }

    void    construct_at_end(size_type _n)
    {
        do
        {
            std::allocator_traits<allocator_type>::construct(this->alloc(), this->_end);
            ++this->_end;
            --_n;
        } while (_n > 0);
    }


    void    construct_at_end(size_type _n, const_reference _x)
    {
        do
        {
            std::allocator_traits<allocator_type>::construct(this->alloc(), this->_end, _x);
            ++this->_end;
            --_n;
        } while (_n > 0);
    }

    void     construct_at_end(iterator _first, iterator _last)
    {
        for (; _first != _last; ++_first)
        {
            std::allocator_traits<allocator_type>::construct(this->alloc(), this->_end, *_first);
            ++this->_end;
        }
    }

    void    destruct_at_end(pointer _p)
    {
        while (_p != _end)
            std::allocator_traits<allocator_type>::destroy(this->alloc(), --this->_end);
    }

    void    push_back(const_reference _x)
    {
        if (_end == end_cap())
        {
            if (_begin > _first)
            {
                difference_type _d = _begin - _first;
                _d = (_d + 1) / 2;
                _end = std::move(_begin, _end, _begin - _d);
                _begin -= _d;
            }
            else
            {
                size_type _c = std::max<size_type>(2 * static_cast<size_type>(end_cap() - _first), 1);
                split_buffer<value_type, allocator_type> _t(_c, _c / 4, this->alloc());
                _t.construct_at_end(iterator(this->_begin), iterator(this->_end));
                std::swap(_first, _t._first);
                std::swap(_begin, _t._begin);
                std::swap(_end, _t._end);
                std::swap(end_cap(), _t.end_cap());
            }
        }
        std::allocator_traits<allocator_type>::construct(this->alloc(), _end, _x);
        ++_end;
    }
};

}

#endif
