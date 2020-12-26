#include <vector>
#include <cassert>
#include <forward_list>
#include <list>
#include <type_traits>
#include <iterator>

// binary search
template<typename It, typename T>
It binary_search(It first, It last, T const& value)
{
  It error{last};
  if (first != last)
  {
    while (first < last)
    {
      It pivot{first + (last - first) / 2};
      if (*pivot < value)
        first = pivot+1;
      else if (*pivot > value)
        last = pivot;
      else
        return pivot;
    }
  }
  return error;
}

// linear search
template<typename It, typename T>
It linear_search(It first, It last, T const& value)
{
  for (It pivot{first}; pivot != last; ++pivot)
  {
    if (*pivot == value)
      return pivot;
    else if (*pivot > value)
      break;
  }
  return last;
}

template<typename It, typename T>
auto search(It first, It last, T const& value)
{
    using category = typename std::iterator_traits<It>::iterator_category;
    if constexpr (std::is_same_v<category, 
                    std::random_access_iterator_tag>)
    {
        return binary_search(first, last, value);
    }
    else
    {
        return linear_search(first, last, value);
    }
}

int main()
{
  {
    std::vector<int> v {1,2,3,4,5};
    std::vector<int> e {};
    std::vector<int> o {1};
    assert((*search(o.begin(), o.end(), 1) == 1));
    for (auto i : v)
      assert((*search(v.begin(), v.end(), i) == i));
    assert((search(v.begin(), v.end(), 6) == v.end()));
    assert((search(e.begin(), e.end(), 0) == e.end()));
    assert((search(o.begin(), o.end(), 0) == o.end()));
  }
  {
    std::list<int> v {1,2,3,4,5};
    std::list<int> e {};
    std::list<int> o {1};
    assert((*search(o.begin(), o.end(), 1) == 1));
    for (auto i : v)
      assert((*search(v.begin(), v.end(), i) == i));
    assert((search(v.begin(), v.end(), 6) == v.end()));
    assert((search(e.begin(), e.end(), 0) == e.end()));
    assert((search(o.begin(), o.end(), 0) == o.end()));
  }
  {
    std::forward_list<int> v {1,2,3,4,5};
    std::forward_list<int> e {};
    std::forward_list<int> o {1};
    assert((*search(o.begin(), o.end(), 1) == 1));
    for (auto i : v)
      assert((*search(v.begin(), v.end(), i) == i));
    assert((search(v.begin(), v.end(), 6) == v.end()));
    assert((search(e.begin(), e.end(), 0) == e.end()));
    assert((search(o.begin(), o.end(), 0) == o.end()));
  }
}