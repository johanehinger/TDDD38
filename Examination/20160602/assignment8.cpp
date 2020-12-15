#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Ascending
{
    template <typename T>
    static void sort(T begin, T end)
    {
        for (; next(begin) != end; ++begin)
        {
            auto min = begin;
            for (auto pos = next(begin); pos != end; ++pos)
                if (*pos < *min)
                    min = pos;
            std::iter_swap(begin, min);
        }
    }
};

struct Descending
{
    template <typename T>
    static void sort(T begin, T end)
    {
        for (; next(begin) != end; ++begin)
        {
            auto min = begin;
            for (auto pos = next(begin); pos != end; ++pos)
                if (*pos > *min)
                    min = pos;
            std::iter_swap(begin, min);
        }
    }
};
template <typename T, class Policy=Descending>
class Sort
{
public:
    template <typename Iter>
    static void sort(Iter begin, Iter end)
    {
        Policy::sort(begin, end);
    }
};

int main()
{
    vector<int> values{2, 3, 6, 8, 3};
    Sort<int, Ascending>::sort(begin(values), end(values));
    for (auto a : values)
    {
        cout << a << endl;
    }
    
    list<string> words {"hi", "hello", "all", "students"};
    Sort<string, Ascending>::sort(begin(words), end(words));

     for (auto a : words)
    {
        cout << a << endl;
    }
    
}