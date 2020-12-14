#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

struct format_container
{
    explicit format_container(char start_delimeter = '[') : start_delimeter{std::move(start_delimeter)} {
        if (start_delimeter == '{') {
            end_delimeter = '}';
        }
        else {
            end_delimeter = ']';
        }
    }
    std::ostream *ostr;
    char start_delimeter;
    char end_delimeter;

    friend format_container operator<<(std::ostream &ost, format_container fc)
    {
        fc.ostr = &ost;
        return fc;
    }
    
    friend std::ostream &operator<<(format_container fc, std::vector<int> vector)
    {
        *fc.ostr << fc.start_delimeter;
        for (auto it = vector.begin(); it != vector.end(); it++)
        {
            if (std::next(it) == vector.end())
                *fc.ostr << *it;
            else
                *fc.ostr << *it << ", ";
        }
        *fc.ostr << fc.end_delimeter;
        return *fc.ostr;
    }
    
    template<typename T, template<typename> typename Container>
    friend std::ostream &operator<<(format_container fc, Container<T> container)
    {
        *fc.ostr << fc.start_delimeter;
        for (auto it = container.begin(); it != container.end(); it++)
        {
            if (std::next(it) == std::end(container))
                *fc.ostr << *it;
            else
                *fc.ostr << *it << ", ";
        }
        *fc.ostr << fc.end_delimeter;
        return *fc.ostr;
    }

    ~format_container() = default;
};

using namespace std;
int main()
{
    // Part a
    vector<int> vec{2, 5, 1, 7, 10};

    cout << format_container() << vec << endl;
    cout << format_container('{') << vec << endl;

    // part b
    list<string> lst{"hi", "does", "this", "work?"};
    forward_list<int> fl{3,65,1,8};
    cout << format_container() << lst << "\n"
         << format_container() << fl << endl;
    
}