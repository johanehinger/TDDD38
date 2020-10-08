#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

template <typename T>
T add(T const &val1, T const &val2)
{
    return val1 + val2;
}

template <typename T, size_t N>
T reduce(T const ( &array)[N], T initial = {}, T (*func)(T const &, T const &) = add<T> )
{
    T result{};
    result += func(array[0], initial);
    for (unsigned i{1}; i < N; i++)
    {
        result = func(result, array[i]);
    }
    return result;
}

double multiply(double const &lhs, double const &rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1, 2, 3, 4, 5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}