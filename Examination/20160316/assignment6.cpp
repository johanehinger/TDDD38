#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Score_variant
{
public:
    virtual std::string name() const = 0;
    virtual int score(std::vector<int>) const = 0;

    virtual ~Score_variant() = default;
};

class Counted_Dice : public Score_variant
{
public:
    Counted_Dice(int nmbr) : number{std::move(nmbr)} {}
    int score(std::vector<int> scores) const override 
    {
        int sum{};
        for (auto const& n : scores) {
            if (n == number) {
                sum += n;
            }
        }
        return sum;
    }

    int get_number() {
        return number;
    }

private:
    int number;
};

class Ones : public Counted_Dice
{
    public:
    Ones() : Counted_Dice{1} {}
    std::string name() const override
    {
        return "Ones";
    }

};

class Twos : public Counted_Dice
{
    public: 
    Twos() : Counted_Dice{2} {}

    std::string name() const override
    {
        return "Twos";
    }

};

class Pair : public Score_variant
{
public:
    std::string name() const override
    {
        return "Pair";
    };

    int score(std::vector<int> scores) const override
    {
        std::sort(std::begin(scores), std::end(scores), std::greater<int>());

        auto it2 = std::begin(scores);

        for (auto it1 = std::begin(scores); it1 != std::end(scores); ++it1)
        {
            if (*it1 == *++it2)
            {
                return *it1 + *it2;
            }
        }
        return 0;
    }
};

int main()
{   
   std::vector<Score_variant*> score_variants = {new Pair, new Ones, new Twos};

   std::vector<int> dices = {3, 2, 2, 3, 5};

   for (auto && variant : score_variants) {
       auto points = variant->score(dices);
       std::cout << variant->name() << ": " << points << std::endl;
   }

   for (auto && variant : score_variants) {
       delete variant;
   }
}