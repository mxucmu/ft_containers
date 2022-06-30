/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 23:33:29 by mxu               #+#    #+#             */
/*   Updated: 2022/01/05 23:22:52 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"

#include <iostream>

// This is a collection of examples for each function of vector container defined at:
// https://cplusplus.com/reference/set/set/

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  // constructing sets
  std::cout << std::endl << "*constructing sets*" << std::endl;

  ft::set<int> first;                           // empty set of ints

  int myints5[]= {10,20,30,40,50};
  ft::set<int> second (myints5,myints5+5);        // range

  ft::set<int> third (second);                  // a copy of second

  ft::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  ft::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  ft::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

  // set::begin/end
  std::cout << std::endl << std::endl<< "*set::begin/end*" << std::endl;

  int myints[] = {75,23,65,42,13};
  ft::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  // set::rbegin/rend
  std::cout << std::endl << std::endl<< "*set::rbegin/rend*" << std::endl;

  int myints1[] = {21,64,17,78,49};
  ft::set<int> myset1 (myints1,myints1+5);

  ft::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit=myset1.rbegin(); rit != myset1.rend(); ++rit)
    std::cout << ' ' << *rit;

  // set::empty
  std::cout << std::endl << std::endl<< "*set::empty*" << std::endl;

  ft::set<int> myset2;

  myset2.insert(20);
  myset2.insert(30);
  myset2.insert(10);

  std::cout << "myset contains:";
  while (!myset2.empty())
  {
     std::cout << ' ' << *myset2.begin();
     myset2.erase(myset2.begin());
  }

  // set::size
  std::cout << std::endl << std::endl<< "*set::size*" << std::endl;

  ft::set<int> myints2;
  std::cout << "0. size: " << myints2.size() << '\n';

  for (int i=0; i<10; ++i) myints2.insert(i);
  std::cout << "1. size: " << myints2.size() << '\n';

  myints2.insert (100);
  std::cout << "2. size: " << myints2.size() << '\n';

  myints2.erase(5);
  std::cout << "3. size: " << myints2.size() << '\n';

  // set::max_size
  std::cout << std::endl << "*set::max_size*" << std::endl;

  int i;
  ft::set<int> myset3;

  if (myset3.max_size()>1000)
  {
    for (i=0; i<1000; i++) myset3.insert(i);
    std::cout << "The set contains 1000 elements.\n";
  }
  else std::cout << "The set could not hold 1000 elements.\n";

  // set::insert (C++98)
  std::cout << std::endl << "*set::insert (C++98)*" << std::endl;

  ft::set<int> myset4;
  ft::set<int>::iterator it;
  ft::pair<ft::set<int>::iterator,bool> ret;

  for (int i=1; i<=5; ++i) myset4.insert(i*10);    // set: 10 20 30 40 50

  ret = myset4.insert(20);               // no new element inserted

  if (ret.second==false) it=ret.first;  // "it" now points to element 20

  myset4.insert (it,25);                 // max efficiency inserting
  myset4.insert (it,24);                 // max efficiency inserting
  myset4.insert (it,26);                 // no max efficiency inserting

  int myints3[]= {5,10,15};              // 10 already in set, not inserted
  myset4.insert (myints3,myints3+3);

  std::cout << "myset contains:";
  for (it=myset4.begin(); it!=myset4.end(); ++it)
    std::cout << ' ' << *it;

  // erasing from set
  std::cout << std::endl << std::endl << "*erasing from set*" << std::endl;

  ft::set<int> myset5;
  ft::set<int>::iterator it1;

  for (int i=1; i<10; i++) myset5.insert(i*10);  // 10 20 30 40 50 60 70 80 90
  
  it1 = myset5.begin();
  ++it1;                                         // "it" points now to 20

  myset5.erase (it1);

  myset5.erase (40);
  
  it1 = myset5.find (60);
  myset5.erase (it1, myset5.end());

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset5.begin(); it!=myset5.end(); ++it)
    std::cout << ' ' << *it;

  // swap sets
  std::cout << std::endl << std::endl << "*swap sets*" << std::endl;

  int myints4[]={12,75,10,32,20,25};
  ft::set<int> first1 (myints4,myints4+3);     // 10,12,75
  ft::set<int> second1 (myints4+3,myints4+6);  // 20,25,32

  first1.swap(second1);

  std::cout << "first contains:";
  for (ft::set<int>::iterator it=first1.begin(); it!=first1.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "second contains:";
  for (ft::set<int>::iterator it=second1.begin(); it!=second1.end(); ++it)
    std::cout << ' ' << *it;

  // set::clear
  std::cout << std::endl << std::endl << "*set::clear*" << std::endl;

  ft::set<int> myset6;

  myset6.insert (100);
  myset6.insert (200);
  myset6.insert (300);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset6.begin(); it!=myset6.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  myset6.clear();
  myset6.insert (1101);
  myset6.insert (2202);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset6.begin(); it!=myset6.end(); ++it)
    std::cout << ' ' << *it;

  // set::key_comp
  std::cout << std::endl << std::endl << "*set::key_comp*" << std::endl;

  ft::set<int> myset7;
  int highest;

  ft::set<int>::key_compare mycomp = myset7.key_comp();

  for (int i=0; i<=5; i++) myset7.insert(i);

  std::cout << "myset contains:";

  highest=*myset7.rbegin();
  ft::set<int>::iterator it2=myset7.begin();
  do {
    std::cout << ' ' << *it2;
  } while ( mycomp(*(++it2),highest) );

  // set::value_comp
  std::cout << std::endl << std::endl << "*set::value_comp*" << std::endl;

  ft::set<int> myset8;

  ft::set<int>::value_compare mycomp1 = myset8.value_comp();

  for (int i=0; i<=5; i++) myset8.insert(i);

  std::cout << "myset contains:";

  int highest1=*myset8.rbegin();
  ft::set<int>::iterator it3=myset8.begin();
  do {
    std::cout << ' ' << *it3;
  } while ( mycomp1(*(++it3),highest1) );

  // set::find
  std::cout << std::endl << std::endl << "*set::find*" << std::endl;

  ft::set<int> myset9;
  ft::set<int>::iterator it4;

  for (int i=1; i<=5; i++) myset9.insert(i*10);    

  it4=myset9.find(20);
  myset9.erase (it4);
  myset9.erase (myset9.find(40));

  std::cout << "myset contains:";
  for (it4=myset9.begin(); it4!=myset9.end(); ++it4)
    std::cout << ' ' << *it4;

  // set::count
  std::cout << std::endl << std::endl << "*set::count*" << std::endl;

  ft::set<int> myset10;

  for (int i=1; i<5; ++i) myset10.insert(i*3);    

  for (int i=0; i<10; ++i)
  {
    std::cout << i;
    if (myset10.count(i)!=0)
      std::cout << " is an element of myset.\n";
    else
      std::cout << " is not an element of myset.\n";
  }

  // set::lower_bound/upper_bound
  std::cout << std::endl << "*set::lower_bound/upper_bound*" << std::endl;

  ft::set<int> myset11;
  ft::set<int>::iterator itlow,itup, temp;

  for (int i=1; i<10; i++) myset11.insert(i*10); 

  itlow=myset11.lower_bound (30);                
  itup=myset11.upper_bound (60);
  
  myset11.erase(itlow,itup);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset11.begin(); it!=myset11.end(); ++it)
    std::cout << ' ' << *it;

  // set::equal_elements
  std::cout << std::endl << std::endl << "*set::equal_elements*" << std::endl;

  ft::set<int> myset12;

  for (int i=1; i<=5; i++) myset12.insert(i*10);   

  ft::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret1;
  ret1 = myset12.equal_range(30);

  std::cout << "the lower bound points to: " << *ret1.first << '\n';
  std::cout << "the upper bound points to: " << *ret1.second << '\n';

  // set::get_allocator
  std::cout << std::endl << "*set::get_allocator*" << std::endl;

  ft::set<int> myset13;
  int * p;
  unsigned int j;

  p=myset13.get_allocator().allocate(5);

  for (j=0; j<5; j++) p[j]=(j+1)*10;

  std::cout << "The allocated array contains:";
  for (j=0; j<5; j++) std::cout << ' ' << p[j];
  std::cout << '\n';

  myset13.get_allocator().deallocate(p,5);

}
