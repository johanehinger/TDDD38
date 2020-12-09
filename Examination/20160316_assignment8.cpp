#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
int main()
{
    // Task 1
    int N;
    int T;
    std::cin>>N>>T;

    // Task 2
    std::vector<int> input_values {};

    // Task 3
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(input_values));

    // Task 4
    std::vector<int> sum {};
 
    //std::copy(std::begin(input_values), std::begin(input_values) + T, std::back_inserter(sum));
    int index{};
    std::transform(std::begin(input_values), std::end(input_values), std::back_inserter(sum),
        [&index, input_values](int n) mutable{
            index++;
            return std::accumulate(std::begin(input_values), std::begin(input_values) + index, 0);

        }
        
    );
}