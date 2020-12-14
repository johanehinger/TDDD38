#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T, numeric_limits<T>::min() start, int end>
class Modular {
public:
    Modular(T value) : value{setValue(value)} {}

    T setValue(T value) {
         if (value < start) {
            return start;
        }
        else {
            return value;
        }
    }

    friend ostream& operator<<(ostream& ostr, Modular m) {
        ostr << m.value;
        return ostr;
    }

    friend Modular operator+(Modular m_left, Modular m_right) {
        return m_left.value + m_right.value;
    }

    template<typename U, int s, int e>
    friend Modular operator+(Modular m_left, Modular<U, s, e> m_right) {
        return m_left.value + m_right.value;
    }

private:
    T value;
};

int main()
{
    Modular<int, 2, 10> m{3};
    
    
    cout << m << endl;
    
    try
    {
        m = 1;
    }
    catch ( std::domain_error const & e)
    {
        cout << e.what() << endl;
    }
    cout << m << endl;
    
    Modular<int, 2,10> m2 {5};
    m = m + m2;
    
    cout << m << endl;
        
    m = m + Modular<int,-11,-2>{-10};

    cout << "Should be 7: " << m << endl;
    /*
    cout << "Should print 7 9: " << m++ << " ";
    cout << ++m;
    Modular<char,'a','c'> mc{'b'};
    ++mc;
    cout << "\nShould print a: " << ++mc << endl;
    */
}