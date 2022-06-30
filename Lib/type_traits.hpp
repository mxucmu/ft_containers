/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:30:56 by mxu               #+#    #+#             */
/*   Updated: 2021/11/26 17:40:57 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include <string>

namespace ft
{

// helper traits

// enable_if
// The type T is enabled as member type enable_if::type if condition is true.
// Otherwise, enable_if is not defined.
template <bool, class T = void>
struct enable_if {};

template <class T> 
struct enable_if<true, T>
{
    typedef T type;
};

// helper class

// integral_constant
// This template is designed to provide compile-time constants as types.
// It is used by several parts of the standard library as the base class for 
// trait types, especially in their bool variant: see true_type and false_type.

template <class T, T v>
struct integral_constant
{
    static const T              value = v;
    typedef T                   value_type;
    typedef integral_constant   type;
    operator value_type() const {return value;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// Primary classification traits

// remove_const
template <class T>  struct remove_const                     {typedef T type;};
template <class T>  struct remove_const<const T>            {typedef T type;};

// is_integral
template <class T>  struct _is_integral                     : public false_type {};
template <>         struct _is_integral<bool>               : public true_type {};
template <>         struct _is_integral<char>               : public true_type {};
template <>         struct _is_integral<signed char>        : public true_type {};
template <>         struct _is_integral<unsigned char>      : public true_type {};
template <>         struct _is_integral<wchar_t>            : public true_type {};
template <>         struct _is_integral<char16_t>           : public true_type {};
template <>         struct _is_integral<char32_t>           : public true_type {};
template <>         struct _is_integral<short>              : public true_type {};
template <>         struct _is_integral<unsigned short>     : public true_type {};
template <>         struct _is_integral<int>                : public true_type {};
template <>         struct _is_integral<unsigned int>       : public true_type {};
template <>         struct _is_integral<long>               : public true_type {};
template <>         struct _is_integral<unsigned long>      : public true_type {};
template <>         struct _is_integral<long long>          : public true_type {};
template <>         struct _is_integral<unsigned long long> : public true_type {};

template <class T>
struct is_integral : public _is_integral<typename remove_const<T>::type> {};

}

#endif
