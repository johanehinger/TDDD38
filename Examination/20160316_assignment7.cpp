#include <iostream>
#include <iterator>
#include <list>
namespace assignment
{
    template<typename InputIterator, typename Functor>
    InputIterator find(InputIterator start, InputIterator end, const Functor& func)
    {
        while (start != end) {
            //if (*start == val) {
            if (func(*start)) {
                return start;
            }
            ++start;
        }
        return end;
        // for (auto it = start; it != end; ++it)
        // {
        //     if (*it == val)
        //         return it;
        // }
        // return end; // wasn't found
    }
} // namespace assignment

int main()
{
    /*
    int arr[] = {1, 2, 5, 2, 7, 8};
    auto pos = assignment::Find(std::begin(arr), std::end(arr), 2);
    if (pos != std::end(arr))
        std::cout << *pos << " found"; 
    else
        std::cout << "not found";
*/
    // After modifications:
    
    std::list<int> l{1,6,2,7,0,9};
    auto val = assignment::find(std::begin(l), std::end(l),
                                [](int i) { return i % 2 == 0; });
    if ( val != std::end(l) )
        std::cout << "First even number: " << *val << std::endl;
    
}