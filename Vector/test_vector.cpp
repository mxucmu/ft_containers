/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:25:44 by mxu               #+#    #+#             */
/*   Updated: 2022/01/02 23:20:14 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"

// This is a collection of examples for each function of vector container defined at:
// https://www.cplusplus.com/reference/vector/vector/

int main ()
{
  // constructors used in the same order as described above:
  std::cout << "constructors used in the same order as described above" << std::endl;
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);                       // a copy of third

  int myints[] = {16,2,77,29};
  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  
  // vector assignment
  std::cout << std::endl << "vector assignment" << std::endl;
  ft::vector<int> foo (3,0);
  ft::vector<int> bar (5,0);

  bar = foo;
  foo = ft::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';

  // vector::begin/end
  std::cout << std::endl << "vector::begin/end" << std::endl;
  ft::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  // vector::rbegin/rend
  std::cout << std::endl << "vector::rbegin/rend" << std::endl;
  ft::vector<int> myvec1 (5);  // 5 default-constructed ints

  int j=0;

  ft::vector<int>::reverse_iterator rit = myvec1.rbegin();
  for (; rit!= myvec1.rend(); ++rit)
    *rit = ++j;

  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = myvec1.begin(); it != myvec1.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  // vector::size
  std::cout << std::endl << "vector::size" << std::endl;
  ft::vector<int> myints1;
  std::cout << "0. size: " << myints1.size() << '\n';

  for (int i=0; i<10; i++) myints1.push_back(i);
  std::cout << "1. size: " << myints1.size() << '\n';

  myints1.insert (myints1.end(),10,100);
  std::cout << "2. size: " << myints1.size() << '\n';

  myints1.pop_back();
  std::cout << "3. size: " << myints1.size() << '\n';

  // comparing size, capacity and max_size
  std::cout << std::endl << "comparing size, capacity and max_size" << std::endl;
  ft::vector<int> myvector1;

  for (int i=0; i<100; i++) myvector1.push_back(i);

  std::cout << "size: " << myvector1.size() << "\n";
  std::cout << "capacity: " << myvector1.capacity() << "\n";
  std::cout << "max_size: " << myvector1.max_size() << "\n";

  // resizing vector
  std::cout << std::endl << "resizing vector" << std::endl;
  ft::vector<int> myvector2;

  for (int i=1;i<10;i++) myvector2.push_back(i);

  myvector2.resize(5);
  myvector2.resize(12);

  std::cout << "myvector contains:";
  for (int i=0; i<(int)myvector2.size();i++)
    std::cout << ' ' << myvector2[i];
  std::cout << '\n';

  // vector::empty
  std::cout << std::endl << "vector::empty" << std::endl;
  ft::vector<int> myvector3;
  int sum (0);

  for (int i=1;i<=10;i++) myvector3.push_back(i);

  while (!myvector3.empty())
  {
     sum += myvector3.back();
     myvector3.pop_back();
  }

  std::cout << "total: " << sum << '\n';

  // vector::reserve
  std::cout << std::endl << "vector::reserve" << std::endl;
  ft::vector<int>::size_type sz;

  ft::vector<int> foo1;
  sz = foo1.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo1.push_back(i);
    if (sz!=foo1.capacity()) {
      sz = foo1.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  ft::vector<int> bar1;
  sz = bar1.capacity();
  bar1.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar1.push_back(i);
    if (sz!=bar1.capacity()) {
      sz = bar1.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  // vector::operator[]
  std::cout << std::endl << "vector::operator[]" << std::endl;
  ft::vector<int> myvector4 (10);   // 10 zero-initialized elements

  ft::vector<int>::size_type sz1 = myvector4.size();

  for (unsigned i=0; i<sz1; i++) myvector4[i]=i;

  for (unsigned i=0; i<sz1/2; i++)
  {
    int temp;
    temp = myvector4[sz1-1-i];
    myvector4[sz1-1-i]=myvector4[i];
    myvector4[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz1; i++)
    std::cout << ' ' << myvector4[i];
  std::cout << '\n';

  // vector::at
  std::cout << std::endl << "vector::at" << std::endl;
  ft::vector<int> myvector5 (10);   // 10 zero-initialized ints

  for (unsigned i=0; i<myvector5.size(); i++)
    myvector5.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector5.size(); i++)
    std::cout << ' ' << myvector5.at(i);
  std::cout << '\n';

  // vector::front
  std::cout << std::endl << "vector::front" << std::endl;
  ft::vector<int> myvector6;

  myvector6.push_back(78);
  myvector6.push_back(16);

  myvector6.front() -= myvector6.back();

  std::cout << "myvector.front() is now " << myvector6.front() << '\n';

  // vector::back
  std::cout << std::endl << "vector::back" << std::endl;
  ft::vector<int> myvector7;

  myvector7.push_back(10);

  while (myvector7.back() != 0)
  {
    myvector7.push_back ( myvector7.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector7.size() ; i++)
    std::cout << ' ' << myvector7[i];
  std::cout << '\n';

  // vector assign
  std::cout << std::endl << "vector assign" << std::endl;
  ft::vector<int> first2;
  ft::vector<int> second2;
  ft::vector<int> third2;

  first2.assign (7,100);             // 7 ints with a value of 100

  ft::vector<int>::iterator it;
  it=first2.begin()+1;

  second2.assign (it,first2.end()-1); // the 5 central values of first

  int myints2[] = {1776,7,4};
  third2.assign (myints2,myints2+3);   // assigning from array.

  std::cout << "Size of first: " << int (first2.size()) << '\n';
  std::cout << "Size of second: " << int (second2.size()) << '\n';
  std::cout << "Size of third: " << int (third2.size()) << '\n';

  // vector::push_back
  std::cout << std::endl << "vector::push_back" << std::endl;
  ft::vector<int> myvector8;
  int myint3;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint3;
    myvector8.push_back (myint3);
  } while (myint3);

  std::cout << "myvector stores " << int(myvector8.size()) << " numbers.\n";

  // vector::pop_back
  std::cout << std::endl << "vector::pop_back" << std::endl;
  ft::vector<int> myvector9;
  int sum1 (0);
  myvector9.push_back (100);
  myvector9.push_back (200);
  myvector9.push_back (300);

  while (!myvector9.empty())
  {
    sum1+=myvector9.back();
    myvector9.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum1 << '\n';

  // inserting into a vector
  std::cout << std::endl << "inserting into a vector" << std::endl;
  ft::vector<int> myvector10 (3,100);
  ft::vector<int>::iterator it3;

  it3 = myvector10.begin();
  it3 = myvector10.insert ( it3 , 200 );

  myvector10.insert (it3,2,300);

  it3 = myvector10.begin();

  ft::vector<int> anothervector (2,400);
  myvector10.insert (it3+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector10.insert (myvector10.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it3=myvector10.begin(); it3<myvector10.end(); it3++)
    std::cout << ' ' << *it3;
  std::cout << '\n';

  // erasing from vector
  std::cout << std::endl << "erasing from vector" << std::endl;
  ft::vector<int> myvector11;

  for (int i=1; i<=10; i++) myvector11.push_back(i);

  myvector11.erase (myvector11.begin()+5);

  myvector11.erase (myvector11.begin(),myvector11.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector11.size(); ++i)
    std::cout << ' ' << myvector11[i];
  std::cout << '\n';

  // swap vectors
  std::cout << std::endl << "swap vectors" << std::endl;
  ft::vector<int> foo2 (3,100);   // three ints with a value of 100
  ft::vector<int> bar2 (5,200);   // five ints with a value of 200

  foo2.swap(bar2);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo2.size(); i++)
    std::cout << ' ' << foo2[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar2.size(); i++)
    std::cout << ' ' << bar2[i];
  std::cout << '\n';

  // clearing vectors
  std::cout << std::endl << "clearing vectors" << std::endl;
  ft::vector<int> myvector12;
  myvector12.push_back (100);
  myvector12.push_back (200);
  myvector12.push_back (300);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector12.size(); i++)
    std::cout << ' ' << myvector12[i];
  std::cout << '\n';

  myvector12.clear();
  myvector12.push_back (1101);
  myvector12.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector12.size(); i++)
    std::cout << ' ' << myvector12[i];
  std::cout << '\n';

  // vector::get_allocator
  std::cout << std::endl << "vector::get_allocator" << std::endl;
  ft::vector<int> myvector13;
  int * p;
  unsigned int i;

      // allocate an array with space for 5 elements using vector's allocator:
  p = myvector13.get_allocator().allocate(5);

      // construct values in-place on the array:
  for (i=0; i<5; i++) myvector13.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

      // destroy and deallocate:
  for (i=0; i<5; i++) myvector13.get_allocator().destroy(&p[i]);
  myvector13.get_allocator().deallocate(p,5);

  // vector comparisons
  std::cout << std::endl << "vector comparisons" << std::endl;
  ft::vector<int> foo3 (3,100);   // three ints with a value of 100
  ft::vector<int> bar3 (2,200);   // two ints with a value of 200

  if (foo3==bar3) std::cout << "foo and bar are equal\n";
  if (foo3!=bar3) std::cout << "foo and bar are not equal\n";
  if (foo3< bar3) std::cout << "foo is less than bar\n";
  if (foo3> bar3) std::cout << "foo is greater than bar\n";
  if (foo3<=bar3) std::cout << "foo is less than or equal to bar\n";
  if (foo3>=bar3) std::cout << "foo is greater than or equal to bar\n";

  // swap (vector overload)
  std::cout << std::endl << "swap (vector overload)" << std::endl;
  
  ft::vector<int> foo4 (3,100);   // three ints with a value of 100
  ft::vector<int> bar4 (5,200);   // five ints with a value of 200

  foo4.swap(bar4);

  std::cout << "foo contains:";
  for (ft::vector<int>::iterator it = foo4.begin(); it!=foo4.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (ft::vector<int>::iterator it = bar4.begin(); it!=bar4.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
