#include <cassert>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
class Attack;
class Defend;
class Damage_Multiplier;
class Defense_Multiplier;
class Named;

class Attack
{
public:
    Attack(double const& dmg) : dmg{dmg} {};
    Attack() : dmg{} {};

    double damage() const {
        return dmg;
    }
private:
    double dmg;
};

class Defend
{
public:
    Defend(double const& def) : def{def} {};
    Defend() : def{} {};

    double defense() const {
        return def;
    }
private:
    double def;
};

class Damage_Multiplier
{
public:
    Damage_Multiplier(double const& factor) : factor{factor} {};
    Damage_Multiplier() : factor{1.0} {};
    double damage(double current_damage) const {
        return current_damage*factor;
    }
private:
    double factor;
};

class Defense_Multiplier
{
public:
    Defense_Multiplier(double const& factor) : factor{factor} {};
    Defense_Multiplier() : factor{1.0} {};
    double defense(double current_defense) const {
        return current_defense * factor;
    }
private:
    double factor;
};

class Named
{
public:
    Named(std::string &&name) : name{std::move(name)} {};
    Named(std::string const& name) : name{name} {};
    Named() : name{"The Name of Default"} {};
    std::string name;
};

class Item_Base
{
public:
    virtual double damage() const = 0;
    virtual double defense() const = 0;
};

template<typename... Mixins>
class Item : public Item_Base, public Mixins...
{
public:
    template<typename... Args>
    Item(Args&&... m) : Mixins(std::forward<Args>(m))... {}

    template <typename T>
    auto damage_helper (T const* obj, double& total, int) const -> decltype(std::declval<T>().damage(total), void()) 
    {  
        total = obj -> damage(total);      
    }

    template <typename T>
    auto damage_helper (T const* obj, double& total, int) const -> decltype(std::declval<T>().damage(), void())
    {  
        total += obj -> damage();      
    }

    template <typename T>
    void damage_helper (T const*, double&, double) const {}

    double damage() const override
    {
        double total_damage{};
        (damage_helper(static_cast<Mixins const*>(this), total_damage, 0),...);
        return total_damage;
    }

    double defense() const override
    {
    double total_defense{};

        return 0.0;
    }
};



int main()
{
    using Weapon = Item<Attack>;
    using Armor = Item<Defend>;
    using Shield = Item<Defend, Attack, Defense_Multiplier>;
    using Sword = Item<Named, Attack, Damage_Multiplier>;
    
    std::vector<Item_Base *> items{
        new Weapon{
            Attack{5.0}},
        new Armor{
            Defend{10.0}},
        new Shield{
            Defend{2.0},
            Attack{2.5},
            Defense_Multiplier{2.5}},
        new Sword{
            Named{"Excalibur"},
            Attack{5.0},
            Damage_Multiplier{5.0}}};
    
    std::cout<< items[3]->damage() << std::endl;
    assert(items[0]->damage() == 5.0);

    //assert(items[1]->defense() == 10.0);

    assert(items[2]->damage() == 2.5);
    //assert(items[2]->defense() == 5.0);

    assert(static_cast<Sword *>(items[3])->name == "Excalibur");
    assert(items[3]->damage() == 25.0);

    
}