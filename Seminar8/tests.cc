#include <ostream>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <array>
#include <string>

namespace details
{
  /**
   * Works for simple prints like print(std::cout, 5);
   * or print(std::cout, 'e');
   */
  template<typename T>
  void print(std::ostream& ostr, T const& data) {
      ostr << data;
  }

  void print(std::ostream& ostr, std::string const &str) {
      ostr << str;
  }


  template<typename T, std::size_t N>
  void print(std::ostream& ostr, const T (&array)[N])
  {
    ostr << '{';
      for(unsigned i = 0; i < N; i++)
      {
        if(i<N-1) {
          print(ostr, array[i]);
        }
        else
        {
          print(ostr, array[i]);
        }
      }
    ostr << '}';
  }


  /**
   * Print any pair.
   */
  template<typename T1, typename T2>
  void print(std::ostream& ostr, std::pair<T1, T2> data) {
      ostr << '(' << data.first << ' ' << data.second << ')';
  }

  /**
   * print any container filled with any number of types like pair on simply just int
   */
  template<template <typename...> typename C, typename... Args>
  void print(std::ostream& ostr, C<Args...> const& data) {
    ostr << '{';
    for (auto const & e : data) {
          print(ostr, e);
          if (&e != &*data.rbegin())
              ostr << ' ';
    }
    ostr << '}';
  }

  template<typename T, std::size_t N>
  void print(std::ostream& ostr, std::array<T, N> const& data) {
    ostr << '{';
    for (unsigned i{}; i < N; i++) {
      print(ostr, data[i]);
      if (i != N -1) {
        ostr << ", ";
      }
    }
    ostr << '}';
  }


  // This is for tuple printing
  template<typename... T>
  void print(std::ostream& ostr, std::tuple<T...> t) {
    ostr << '(';
    std::apply([&](auto&&... args) {((ostr << args << ' '), ...);}, t);
    ostr << ')'; 
  }
}

template<typename T>
void print(std::ostream& ostr, T const& data) {
    details::print(ostr, data);
}

/* This should give the following output (or something similar at least):
5
{1, 2, 3}
{(1 1), (2 2), (3 3)}
(5 3.14)
{hello, world}
{{ab, c}, {def, g, hi}}
SFINAE
string literal
 */
int main()
{

  print(std::cout, 5);
  std::cout << std::endl;
  
  std::vector<int> v {1, 2, 3};
  print(std::cout, v);
  std::cout << std::endl;

  std::vector< std::vector< std::vector<int> > > hej { {{1, 2}, {3, 4} }, { {5, 6}} };
  print(std::cout, hej);
  std::cout << std::endl;

  std::map<int, int> m { {1, 1}, {2, 2}, {3, 3} };
  print(std::cout, m);
  std::cout << std::endl;

  std::tuple<int, double> t { 5, 3.14 };
  print(std::cout, t);
  std::cout << std::endl;

  int i[] = {1, 2, 3, 4};
  print(std::cout, i);
  std::cout << std::endl;

  std::string s[] { "hello", "world" };
  print(std::cout, s);
  std::cout << std::endl;

  std::array<std::vector<std::string>, 2> a {
    std::vector<std::string>{ "ab", "c" },
    std::vector<std::string>{"def", "g", "hi"}
  };

  print(std::cout, a);
  std::cout << std::endl;

  char const* str {"SFINAE"};
  print(std::cout, str);
  std::cout << std::endl;

  print(std::cout, "string literal");
  std::cout << std::endl;
  
}