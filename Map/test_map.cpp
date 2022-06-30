/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42roma.it>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:00:54 by mxu               #+#    #+#             */
/*   Updated: 2022/01/05 23:15:42 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <iostream>

// This is a collection of examples for each function of vector container defined at:
// https://cplusplus.com/reference/map/map/

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp 
{
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  // constructing maps
  std::cout << std::endl << "*constructing maps*" << std::endl;
  ft::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;
  
  std::cout << "first contains:\n";
  for (ft::map<char,int>::iterator it=first.begin(); it!=first.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  
  ft::map<char,int> second (first.begin(),first.end());

  std::cout << "second contains:\n";
  for (ft::map<char,int>::iterator it=second.begin(); it!=second.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  ft::map<char,int> third (second);

  std::cout << "third contains:\n";
  for (ft::map<char,int>::iterator it=third.begin(); it!=third.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  ft::map<char,int,classcomp> fourth;         // class as Compare

  ft::map<char,int,classcomp>::key_compare mycomp1 = fourth.key_comp();

  fourth['a']=100;
  fourth['b']=200;
  fourth['c']=300;

  std::cout << "fourth contains:\n";

  char highest2 = fourth.rbegin()->first;     

  ft::map<char,int>::iterator ith = fourth.begin();
  do {
    std::cout << ith->first << " => " << ith->second << '\n';
  } while ( mycomp1((*ith++).first, highest2) );

  bool(*fn_pt)(char,char) = fncomp;
  ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  fifth['a']=101;
  fifth['b']=201;
  fifth['c']=301;

  std::cout << "fifth contains:\n";

  ft::pair<char,int> highest3 = *fifth.rbegin();

  ft::map<char,int>::iterator itl = fifth.begin();
  do {
    std::cout << itl->first << " => " << itl->second << '\n';
  } while ( fifth.value_comp()(*itl++, highest3) );

  // map::begin/end
  std::cout << std::endl << "*map::begin/end*" << std::endl;
  ft::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // map::rbegin/rend
  std::cout << std::endl << "*map::rbegin/rend*" << std::endl;
  ft::map<char,int> mymap1;

  mymap1['x'] = 100;
  mymap1['y'] = 200;
  mymap1['z'] = 300;

  ft::map<char,int>::reverse_iterator rit;
  for (rit=mymap1.rbegin(); rit!=mymap1.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  // map::empty
  std::cout << std::endl << "*map::empty*" << std::endl;
  ft::map<char,int> mymap2;

  mymap2['a']=10;
  mymap2['b']=20;
  mymap2['c']=30;

  while (!mymap2.empty())
  {
    std::cout << mymap2.begin()->first << " => " << mymap2.begin()->second << '\n';
    mymap2.erase(mymap2.begin());
  }

  // map::size
  std::cout << std::endl << "*map::size*" << std::endl;
  ft::map<char,int> mymap3;
  mymap3['a']=101;
  mymap3['b']=202;
  mymap3['c']=302;

  std::cout << "mymap3.size() is " << mymap3.size() << '\n';

  // map::max_size
  std::cout << std::endl << "*map::max_size*" << std::endl;
  int i;
  ft::map<int,int> mymap4;

  if (mymap4.max_size()>1000)
  {
    for (i=0; i<1000; i++) mymap4[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else std::cout << "The map could not hold 1000 elements.\n";

  // map::key_comp
  std::cout << std::endl << "*map::key_comp*" << std::endl;
  ft::map<char,int> mymap5;

  ft::map<char,int>::key_compare mycomp = mymap5.key_comp();

  mymap5['a']=100;
  mymap5['b']=200;
  mymap5['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap5.rbegin()->first;     

  ft::map<char,int>::iterator it5 = mymap5.begin();
  do {
    std::cout << it5->first << " => " << it5->second << '\n';
  } while ( mycomp((*it5++).first, highest) );

  // map::value_comp
  std::cout << std::endl << "*map::value_comp*" << std::endl;
  ft::map<char,int> mymap6;

  mymap6['x']=1001;
  mymap6['y']=2002;
  mymap6['z']=3003;

  std::cout << "mymap contains:\n";

  ft::pair<char,int> highest1 = *mymap6.rbegin();          

  ft::map<char,int>::iterator it6 = mymap6.begin();
  do {
    std::cout << it6->first << " => " << it6->second << '\n';
  } while ( mymap6.value_comp()(*it6++, highest1) );

  // map::get_allocator
  std::cout << std::endl << "*map::get_allocator*" << std::endl;
  int psize;
  ft::map<char,int> mymap7;
  ft::pair<const char,int>* p;

  p=mymap7.get_allocator().allocate(5);

  psize = sizeof(ft::map<char,int>::value_type)*5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap7.get_allocator().deallocate(p,5);

  // map::insert (C++98)
  std::cout << std::endl << "*map::insert (C++98)*" << std::endl;
  ft::map<char,int> mymap8;

    // first insert function version (single parameter):
  mymap8.insert ( ft::pair<char,int>('a',100) );
  mymap8.insert ( ft::pair<char,int>('z',200) );

  ft::pair<ft::map<char,int>::iterator,bool> ret8;
  ret8 = mymap8.insert ( ft::pair<char,int>('z',500) );
  if (ret8.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret8.first->second << '\n';
  }
    // second insert function version (with hint position):
  ft::map<char,int>::iterator it8 = mymap8.begin();
  mymap8.insert (it8, ft::pair<char,int>('b',300));  // max efficiency inserting
  mymap8.insert (it8, ft::pair<char,int>('c',400));  // no max efficiency inserting

  mymap8.insert (ft::pair<char,int>('b',300));  // max efficiency inserting
  mymap8.insert (ft::pair<char,int>('c',400)); 

    // third insert function version (range insertion):
  ft::map<char,int> anothermap8;
  anothermap8.insert(mymap8.begin(),mymap8.find('c'));

    // showing contents:
  std::cout << "mymap contains:\n";
  for (ft::map<char,int>::iterator it=mymap8.begin(); it!=mymap8.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (ft::map<char,int>::iterator it=anothermap8.begin(); it!=anothermap8.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // erasing from map
  std::cout << std::endl << "*erasing from map*" << std::endl;
  ft::map<char,int> mymap9;
  ft::map<char,int>::iterator it9, itnew;

  mymap9['a']=10;
  mymap9['b']=20;
  mymap9['c']=30;
  mymap9['d']=40;
  mymap9['e']=50;
  mymap9['f']=60;

  it9=mymap9.find('b');
  mymap9.erase (it9);                   

  mymap9.erase ('c');                  

  itnew=mymap9.find ('e');
  
  mymap9.erase(itnew, mymap9.end());    

  for (ft::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // map::clear
  std::cout << std::endl << "*map::clear*" << std::endl;
  ft::map<char,int> mymap10;

  mymap10['x']=100;
  mymap10['y']=200;
  mymap10['z']=300;

  std::cout << "mymap contains:\n";
  for (ft::map<char,int>::iterator it10=mymap10.begin(); it10!=mymap10.end(); ++it10)
    std::cout << it10->first << " => " << it10->second << '\n';

  mymap10.clear();
  mymap10['a']=1101;
  mymap10['b']=2202;

  std::cout << "mymap contains:\n";
  for (ft::map<char,int>::iterator it10=mymap10.begin(); it10!=mymap10.end(); ++it10)
    std::cout << it10->first << " => " << it10->second << '\n';

  // swap maps
  std::cout << std::endl << "*swap maps*" << std::endl;
  ft::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // map::find
  std::cout << std::endl << "*map::find*" << std::endl;
  ft::map<char,int> mymap11;
  ft::map<char,int>::iterator it11;

  mymap11['a']=50;
  mymap11['b']=100;
  mymap11['c']=150;
  mymap11['d']=200;

  it11 = mymap11.find('b');
  if (it11 != mymap11.end())
    mymap11.erase (it11);

  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap11.find('a')->second << '\n';
  std::cout << "c => " << mymap11.find('c')->second << '\n';
  std::cout << "d => " << mymap11.find('d')->second << '\n';

  // map::count
  std::cout << std::endl << "*map::count*" << std::endl;
  ft::map<char,int> mymap12;
  char c;

  mymap12 ['a']=101;
  mymap12 ['c']=202;
  mymap12 ['f']=303;

  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap12.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }

  // map::lower_bound/upper_bound
  std::cout << std::endl << "*map::lower_bound/upper_bound*" << std::endl;
  ft::map<char,int> mymap13;
  ft::map<char,int>::iterator itlow,itup;

  mymap13['a']=20;
  mymap13['b']=40;
  mymap13['c']=60;
  mymap13['d']=80;
  mymap13['e']=100;

  itlow=mymap13.lower_bound ('b');  // itlow points to b
  
  itup=mymap13.upper_bound ('d');   // itup points to e (not d!)
  
  mymap13.erase(itlow,itup);        // erases [itlow,itup)
  
  for (ft::map<char,int>::iterator it=mymap13.begin(); it!=mymap13.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // map::equal_range
  std::cout << std::endl << "*map::equal_range*" << std::endl;
  ft::map<char,int> mymap14;

  mymap14['a']=10;
  mymap14['b']=20;
  mymap14['c']=30;

  ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
  ret = mymap14.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  // map comparisons
  std::cout << std::endl << "*map comparisons*" << std::endl;
  ft::map<int, char> alice;
  alice[1] = 'a';
  alice[2] = 'b';
  alice[3] = 'c';

  ft::map<int, char> bob;
  bob[7] = 'Z';
  bob[8] = 'Y';
  bob[9] = 'X';
  bob[10] = 'W';

  ft::map<int, char> eve;
  eve[1] = 'a';
  eve[2] = 'b';
  eve[3] = 'c';
 
  std::cout << std::boolalpha;
 
  // Compare non equal containers
  std::cout << "alice == bob returns " << (alice == bob) << '\n';
  std::cout << "alice != bob returns " << (alice != bob) << '\n';
  std::cout << "alice <  bob returns " << (alice < bob) << '\n';
  std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
  std::cout << "alice >  bob returns " << (alice > bob) << '\n';
  std::cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
  std::cout << '\n';
 
  // Compare equal containers
  std::cout << "alice == eve returns " << (alice == eve) << '\n';
  std::cout << "alice != eve returns " << (alice != eve) << '\n';
  std::cout << "alice <  eve returns " << (alice < eve) << '\n';
  std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
  std::cout << "alice >  eve returns " << (alice > eve) << '\n';
  std::cout << "alice >= eve returns " << (alice >= eve) << '\n';  

}
