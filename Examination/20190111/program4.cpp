#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
class enumerate;

using namespace std;

template<class Policy = enumerate>
class print_list_iterator
{
private:
    ostream& os;
    Policy policy;
public:
    using value_type = void;
    using reference = void;
    using pointer = void;
    using difference_type = void;
    using iterator_category = std::output_iterator_tag;
    print_list_iterator(ostream& os, Policy policy = {}) : os{os}, policy{policy} {}
    // print_list_iterator(ostream& os) : os{os}, policy{} {}


    void operator++() {
        policy.increment();
    }
    
    print_list_iterator& operator*() 
    {
        return *this;
    }

    template<typename T>
    void operator=(T i)
    {
        auto data = policy.print_point();
        os << data ;
        os << i << endl;
    }
};


class enumerate
{
private:
    int start;
    int step;
    int current_entry;
public:
    enumerate(int start = 1, int step = 1) : start{start}, step{step}, current_entry{start} {
        
    }

    auto print_point() const {
        return to_string(current_entry) +". ";
    }

    void increment() {
        current_entry += step;
    }

};

template<typename Container>
class description
{
private:
    Container c;
    int list_point{};
public:
    description(Container c) : c{c} {}
    void increment() 
    {
        if (++list_point == c.size())
        {
            list_point = 0;
        }
        // else 
        // {
        //     list_point++;
        // }
    }
    auto print_point() const {
        return c[list_point] + ' ';
    }
};

// Must compile with c++17
// Example: g++ program4.cc -std=c++17
int main()
{
    
  {
    vector<string> list {"first", "second", "third", "fourth"};

    /*
      Should output:
      1. first
      2. second
      3. third
      4. fourth
    */
    ostringstream ss{};
    copy(begin(list), end(list), print_list_iterator{ss});
    cout << ss.str() << endl;
  
    /*
      Should output:
      5. first
      6. second
      7. third
      8. fourth
    */
    copy(begin(list), end(list), print_list_iterator{cout, enumerate{5}});
    cout << endl;
    
    /*
      Should output:
      10. first
      12. second
      14. third
      16. fourth
    */
    copy(begin(list), end(list), print_list_iterator{cout, enumerate{10, 2}});
    cout << endl;
  }

  {
    vector<int> list{1, 2, 3, 4};
    
    /*
      Should output:
      (a) 1
      (b) 2
      (c) 3
      (d) 4
    */
    {
      vector<string> points{"(a)", "(b)", "(c)", "(d)"};
      copy(begin(list), end(list), print_list_iterator{cout, description<vector<string>>{points}});
      cout << endl;
    }
    
    /*
      Should output:
      (a) 1
      (b) 2
      (a) 3
      (b) 4
    */
    {
      vector<string> points{"(a)", "(b)"};
      copy(begin(list), end(list), print_list_iterator{cout, description<vector<string>>{points}});
      cout << endl;
    }
  }
  
  print_list_iterator printer{cout, enumerate{}};

  /*
    Should output:
    1. 1
    1. second
    2. 3.4
    2. f
  */
  printer = 1;
  printer = "second";
  ++printer;
  printer = 3.4;
  printer = 'f';
}