#include <iostream>
#include <string>
#include <vector>

class Sauna
{
public:
    friend std::ostream &operator<<(std::ostream &ostr, Sauna &s)
    {
        std::string heater{};
        if (s.heater)
        {
            heater = "ON";
        }
        else
        {
            heater = "OFF";
        }
        ostr << s.str() << " [" << heater << "] " << s.get_temperature();
        return ostr;
    };

    virtual void toggle_sauna()
    {
        if (heater)
        {
            set_temperature(22);
            heater = false;
        }
        else
        {
            heater = true;
            set_temperature(default_temperature);
        }
    }

    virtual std::string str() const = 0;

    int default_temperature{22};

    bool heater{false};

    int get_temperature() const
    {
        return temperature;
    }

    void set_temperature(int temp)
    {
        temperature = temp;
    }

    Sauna& get_clone() const {
        return clone();
    }

    virtual ~Sauna() = default;

private:
    virtual Sauna& clone() const = 0;
    int temperature{22};
};

class Steam_Heater : public Sauna
{
public:
    Steam_Heater()
    {
        default_temperature = 38;
    }

    std::string str() const override
    {
        return "Steam sauna";
    }
    private:
    Sauna& clone() const {
        return *(new Steam_Heater());
    }
};

class Electrical_Heater : public Sauna
{
public:
    Electrical_Heater()
    {
        default_temperature = 85;
    }

    std::string str() const override
    {
        return "Electrical heater";
    }
     private:
    Sauna& clone() const {
        return *(new Electrical_Heater());
    }
};

class Wood_Heater : public Sauna
{
public:
    Wood_Heater() {}
    std::string str() const override
    {
        return "Wood-burning sauna";
    }

    void toggle_sauna() override
    {
        if (heater)
        {
            set_temperature(22);
            heater = false;
        }
        else
        {
            heater = true;
            add_log(10);
        }
    }
    void add_log(int number_of_logs)
    {
        set_temperature(get_temperature() + 5*number_of_logs);
    }
     private:
    Sauna& clone() const {
        return *(new Electrical_Heater());
    }
};

int main()
{
    std::vector<Sauna *> saunas = {new Steam_Heater, new Electrical_Heater, new Wood_Heater};

    
    for (auto const &sauna : saunas)
    {
        std::cout << *sauna << std::endl;
    }

    for (auto const &sauna : saunas)
    {
        sauna->toggle_sauna();
    }

    for (auto const &sauna : saunas)
    {
        std::cout << *sauna << std::endl;
    }


    for (auto const sauna : saunas)
    {
        delete sauna;
    }
    return 0;
}