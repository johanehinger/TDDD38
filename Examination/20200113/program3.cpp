#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

int main()
{
    double const length {10.0};
    vector<double> road {};

    // double tmp{};
    // while (cin >> tmp)
    // {
    //     road.push_back(tmp);
    // }
    
    // NOTE: You need to press "Ctrl + d" to exit this.
    copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(road));

    vector<double> result(road);

    // for (unsigned i{1}; i < road.size(); ++i)
    // {
    //     std::swap(road[i-1], road[i]);
    // }

    auto prev_road = begin(road);
    transform(begin(road) + 1, end(road), begin(road) + 1, 
    [&] (auto road)
    {
        std::swap(*prev_road++, road);
        return road;
    });

    // for (unsigned i{0}; i < road.size(); ++i)
    // {
    //     double a {road[i]};
    //     double b {result[i]};
    //     result[i] = sqrt((a - b) * (a - b) + length * length);
    // }
    
    auto i = 0;
    transform(begin(result), end(result), begin(result), 
    [&](auto result)
    {
        double a {road[i++]};
        double b {result};
        return result = sqrt((a - b) * (a - b) + length * length);
    });
    

    // for (unsigned i{0}; i < result.size(); ++i)
    // {
    //     cout << result[i] << " m" << endl;
    // }

    copy(begin(result), end(result), ostream_iterator<double>(cout," m \n"));

    // double total {0.0};
    // for (unsigned i{0}; i < result.size(); ++i)
    // {
    //     total += result[i];
    // }
    double total = accumulate(begin(result), end(result), 0.0);

    cout << "Total distance: " << total << " m" << endl;
}