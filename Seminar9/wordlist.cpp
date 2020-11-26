#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
    using namespace std;

int main() 
{   
    vector<string> text {istream_iterator<string>{cin}, istream_iterator<string>{}};
    vector<string> unique_words;
    unique_copy(begin(text), end(text), back_inserter(unique_words));

    transform(begin(unique_words), end(unique_words), ostream_iterator<string>{cout, "\n"}, 
        [&text](string const& str) {
            long int n{count(begin(text), end(text), str)};
            return str + ": " + to_string(n);
        }
    );
              
}