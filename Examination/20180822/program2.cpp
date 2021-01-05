#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

using namespace std;

class Food
{
private: 
    string name;
public:
    Food(string const& name) : name{name} {}
    virtual ~Food() = default;
    string get_name() const
    {
        return name;
    }  
    virtual bool is_vegetarian() const = 0;
};

class Pizza : public Food
{
private:
    bool is_vegetarian_pizza;

public:
    Pizza(string const& name, bool const& is_vegetarian_pizza) : 
        Food(name), is_vegetarian_pizza{is_vegetarian_pizza} {}

    bool is_vegetarian() const override 
    {
        return is_vegetarian_pizza;
    }
};

class Pizza_Roll : public Food
{
private:
    bool is_vegetarian_pizza_roll;

public:
    Pizza_Roll(string const& name, bool const& is_vegetarian_pizza_roll) : 
        Food(name + " roll"), is_vegetarian_pizza_roll{is_vegetarian_pizza_roll} {}
        
    bool is_vegetarian() const override 
    {
        return is_vegetarian_pizza_roll;
    }
};

class Salad : public Food
{
public:
    Salad(string const& name) : Food(name) {}
    bool is_vegetarian() const override
    {
        return true;
    }
};

class Guest
{
private:
    string name;

public:
    Guest(string const& name) : name{name} {}
    virtual ~Guest() = default;
    virtual bool prefer(Food&) const
    {
        return true;
    }
    void eat(Food& food) const
    {
        if (prefer(food))
        {
            cout << name << " eat " << food.get_name() << endl;
        }
        else
        {
            cout << name << "  does not want " << food.get_name() << endl;
        }
    }
};

class Salad_Lover : public Guest
{
public:
    Salad_Lover(string const& name) : Guest(name) {}
    bool prefer(Food& food) const
    {
        if (dynamic_cast<Salad*>(&food))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Pizza_Lover : public Guest
{
public:
    Pizza_Lover(string const& name) : Guest(name) {}
    bool prefer(Food& food) const
    {
        if (dynamic_cast<Pizza*>(&food))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Vegetarian : public Guest
{
public:
    Vegetarian(string const& name) : Guest(name) {}

    bool prefer(Food& food) const
    {
        if (food.is_vegetarian())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

/* if implemented correctly this program
   should give the following output:

Gus eat Vegetarian Pizza.
Gus eat Calzone.
Gus eat Ham Pizza roll.
Gus eat Vegetarian Pizza roll.
Gus eat Salad.
Sally does not want Vegetarian Pizza.
Sally does not want Calzone.
Sally does not want Ham Pizza roll.
Sally does not want Vegetarian Pizza roll.
Sally eat Salad.
Pete eat Vegetarian Pizza.
Pete eat Calzone.
Pete does not want Ham Pizza roll.
Pete does not want Vegetarian Pizza roll.
Pete does not want Salad.
Velma eat Vegetarian Pizza.
Velma does not want Calzone.
Velma does not want Ham Pizza roll.
Velma eat Vegetarian Pizza roll.
Velma eat Salad.
*/

int main()
{
   vector<Guest*> guests {
        new Guest {"Gus"},
        new Salad_Lover {"Sally"},
        new Pizza_Lover {"Pete"},
        new Vegetarian {"Velma"}
    };

    // the true and false parameters represents
    // wheter or not the pizza/pizza roll is vegetarian
    vector<Food*> foods {
        new Pizza {"Vegetarian Pizza", true},
        new Pizza {"Calzone", false},
        new Pizza_Roll {"Ham Pizza", false},
        new Pizza_Roll {"Vegetarian Pizza", true},
        new Salad {"Salad"}
    };
    
    for (auto guest : guests)
    {
        for (auto food : foods)
        {
            // guest.eat(food);
            // or
            guest->eat(*food);
        }
    }

    for (auto guest : guests)
    {
        delete guest;
    }
    for (auto food : foods)
    {
        delete food;
    }
}