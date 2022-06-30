/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:53:12 by mxu               #+#    #+#             */
/*   Updated: 2022/01/10 14:57:29 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <memory>

#include "../Lib/iterator.hpp"

namespace ft
{

// lexicographical_compare

template <class Compare, class InputIterator1, class InputIterator2>
bool    lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    for (; first2 != last2; ++first1, (void) ++first2)
    {
        if (first1 == last1 || comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
    return false;
}

template <class InputIterator1, class InputIterator2>
bool    lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
    for (; first2 != last2; ++first1, (void) ++first2)
    {
        if (first1 == last1 || *first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return false;
}

// equal

template <class InputIterator1, class InputIterator2>
bool    equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    for (; first1 != last1; ++first1, (void) ++first2)
        if (*first1 != *first2)
            return false;
    return true;
}

}

#endif
