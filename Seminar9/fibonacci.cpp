#include <vector>
#include <iostream>
#include <algorithm>


int main() 
{
    int size{};
    std::cin >> size;
    std::vector<unsigned long long int> fibonacci(size);

    unsigned long long int n1{0};
    unsigned long long int n2{1};
    unsigned long long int n3{};
    std::transform(fibonacci.begin(), fibonacci.end(), fibonacci.begin(), 
    [&](unsigned long long int n) {
            n3 = n1 + n2;
            n1=n2;    
            n2=n3;
            return n = n3;
    });

    for (auto const& number : fibonacci) {
        std::cout << number << std::endl;
    }
}