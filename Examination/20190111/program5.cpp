#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <deque>

using namespace std;
//* Good start but not quite what we want.
// template<typename T>
// void read(istream& iss, T& t)
// {
//     if constexpr (is_same_v<string, T>)
//     {
//         getline(iss, t);
//     }
//     else
//     {
//         t = {};
//     }
// }

template<typename T>
void read(istream& iss, T&& t);

namespace details
{
    void read(istream& iss, string& str, int)
    {
        cout<< "2" << endl;

        getline(iss, str);
    }

    template<typename... Ts>
    void read(istream& iss, tuple<Ts...>& tp, int)
    {
        cout<< "1" << endl;
        (::read(iss, get<Ts>(tp)), ...);
    }

    template<typename T>
    auto read(istream& iss, T&& t, int) -> decltype(iss >> t, declval<void>())
    {
        cout<< "4" << endl;
        iss >> t;
    }

    template<typename T>
    void read(istream& iss, T&& t, long long int)
    {
        t = {};
    }
}

template<typename T>
void read(istream& iss, T&& t)
{
    cout << "3" << endl;
    details::read(iss, t, 0);
}

int main()
{
  {
    istringstream iss{""};
    vector<int> data{1, 2, 3};
    read(iss, data);
    assert(data.empty());
  }
  {
    istringstream iss{"123"};
    int message{};
    read(iss, message);
    assert(message == 123);
  }
  {
    istringstream iss{"Hello Santa!"};
    string message{};
    read(iss, message);
    assert(message == "Hello Santa!");
  }
  {
    istringstream iss{"Pie is good!\n 3.1415"};
    tuple<string, double> message{};
    read(iss, message);
    assert((message == make_tuple("Pie is good!", 3.1415)));
  }
  {
    istringstream iss{"1 2.3 abc"};
    tuple<int, double, char, string> message{};
    read(iss, message);
    assert((message == make_tuple(1, 2.3, 'a', "bc")));
  }
}