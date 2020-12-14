#include <vector>
#include <algorithm>
#include <experimental/random>
#include <iostream>
#include <numeric>
#include <iterator>
using num_type = unsigned long long;

bool is_prime(num_type val, num_type divisor=2)
{
    if ( divisor*divisor > val )
    {
        return true;
    }
    if ( val % divisor == 0 )
    {
        return false;
    }
    return is_prime(val, ++divisor);
}

int main() {
    std::vector<num_type> rnd_values(10);

    std::transform(std::begin(rnd_values), std::end(rnd_values), std::begin(rnd_values), 
        [&](num_type){
            return std::experimental::randint(2, 75);
        });

    rnd_values.erase(std::remove_if(std::begin(rnd_values), std::end(rnd_values), [&](num_type number){return !is_prime(number);}), std::end(rnd_values));

    std::sort(std::begin(rnd_values), std::end(rnd_values));
    
    std::copy(std::begin(rnd_values), std::end(rnd_values), std::ostream_iterator<num_type>{std::cout, " "});

    num_type product = std::accumulate(std::begin(rnd_values), std::end(rnd_values), 1, std::multiplies<num_type>());

    std::cout << product << std::endl;
    
}