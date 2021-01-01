#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

/*
  Some test data:

  input:  | output:
  5 0     | 1
  5 1     | 5
  5 2     | 10
  5 3     | 10
  5 4     | 5
  5 5     | 1

  input:  | output:
  6 0     | 1
  6 1     | 6
  6 2     | 15
  6 3     | 20
  6 4     | 15
  6 5     | 6
  6 6     | 1

  input:  | output:
  10 0    | 1
  10 1    | 10
  10 2    | 45
  10 3    | 120
  10 4    | 210
  10 5    | 252
  10 6    | 210
  10 7    | 120
  10 8    | 45
  10 9    | 10
  10 10   | 1
  
 */

int rotate(vector<int> & denominators, int k)
{
  //move all elements in the range [0, k] to the end of the vector
  for (int i{0}; i < k; ++i)
  {
    // move each element into position by swapping them to the end
    for (unsigned j{0}; j + 1 < denominators.size() - i; ++j)
    {
      swap(denominators[j], denominators[j+1]);
    }
  }

  // return how far in the overlap ends
  return denominators.size() - k;
}

int main()
{
  unsigned n, k;
  std::cin >> n >> k;

  // store a vector of all factors in the numerator
  vector<int> factors(n - k, 0);

  // store a vector of all divisors in the denominator
  vector<int> denominators(n - k, 0);

  // fill factors with k+1, k+2, ..., n-1, n
  unsigned counter{k + 1};
  transform(begin(factors), end(factors), begin(factors), 
  [&](auto i){
      return i = counter++;
  });

  // fill denominators with 1, 2, ..., n-k-1, n-k
  counter = 1;
  transform(begin(denominators), end(denominators), begin(denominators), 
  [&](auto i){
      return i = counter++;
  });

  // if there is overlap between factors and denominators we remove it
  if (denominators.size() >= k)
  {
    // restructure denominators so that the overlap is in the
    // beginning of the vector and retrieve how many elements there
    // where in the overlap
    auto dist{rotate(denominators, k)};

    // remove the overlap
    factors.erase(begin(factors), begin(factors) + dist);
    denominators.erase(begin(denominators), begin(denominators) + dist);
  }


  // for each denominator we want to divided it with a factor in factors
  transform(begin(denominators), end(denominators), begin(denominators), 
  [&](auto denominator){
    auto factor = find_if(begin(factors), end(factors), 
      [&](auto f){
        return (f % denominator == 0);
      });
    
    // divide the found factor
    *factor /= denominator;
    denominator = 1;
    return denominator;
  });


  // multiply all factors together
  int result{1};
  for_each(begin(factors), end(factors), 
  [&](auto factor){
    result *= factor;
  }); 

  // print the result
  cout << result << endl;

}