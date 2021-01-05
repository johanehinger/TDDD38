#include <cassert>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>

template<typename Container>
class range
{
private:
    using value_type = typename Container::value_type;

    using iterator = decltype(std::begin(std::declval<Container&>()));
   
    Container container;

    iterator first;
    iterator last;


public:

    range(Container container, iterator first, iterator last) : container{container}, first{first}, last{last} {}

    iterator begin() const
    {
        return first;
    }

    iterator end() const
    {
        return last;
    }

    auto size() const
    {
        return std::distance(begin(), end());
    }

    range take(int n) const
    {
        auto it = first;
        std::advance(it, n);
        return range(container, first, it);
    }

    range skip(int n) const
    {
        auto it = first;
        std::advance(it, n);
        return range(container, it, last);
    }
};

template<typename Container>
auto make_range(Container&& container)
{
    return range(container, std::begin(container), std::end(container));
}

template<typename Container, typename Op>
range<Container>& map(range<Container>& r, Op op)
{
    std::transform(r.begin(), r.end(), r.begin(),
    [&](auto elem)
    {
        return op(elem);
    });
    return r;
}

template<typename Container, typename Predicate>
range<Container>& filter(range<Container>& r, Predicate pred)
{
    auto it = r.begin();
    while (it != r.end())
    {
        if (pred(*it))
        {
            std::rotate(it, std::next(it), r.end());
        }
        it = std::next(it);
    }
    it = r.begin();
    int i{};
    while (!pred(*it))
    {
        // std::cout<< i << std::endl;
        i++;
        it = std::next(it);
    }
    r = r.take(i);
    return r;
}

template<typename Container, typename value_type, typename Op>
value_type reduce(range<Container>& r, value_type initail, Op op)
{
    value_type sum{};
    sum = std::accumulate(r.begin(), r.end(), initail, 
        [&](auto elem1, auto elem2){
            return op(elem1, elem2);
        });
    return sum;
}

int main()
{
    { // test reduce, map, and filter
        std::list<int> v { 1, 2, 3, 4, 5, 6 };
        auto r {make_range(v)};
        // std::cout << r.size() << std::endl;
        assert(reduce(map(filter(r, [](int n)
                                 { return n % 2 == 0; }),
                          [](int n) { return 2 * n; }), 0.0,
                      [](int n, int m) { return n + m; }) == 18);
    }
    
    { // test size, filter and range-based for-loop
        std::vector<double> v { -2.6, 7.0, 1.3, 15.2 };
        auto r {make_range(v)};

        assert(r.size() == 4);
      
        filter(r, [](double x) { return x < 0.0; });

        assert(r.size() == 3);

        int i{0};
        for (double x : r)
        {
            assert(x == v[i++]);
        }
    }
    
    { // test take and skip
        std::forward_list<int> v { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto r {make_range(v)};

        int n{0};
        for (int x : r.take(3))
        {
            assert(x == n++);
        }

        for (int x : r.skip(3))
        {
            assert(x == n++);
        }
    }
    
}