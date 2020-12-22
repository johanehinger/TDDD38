#include <iostream>
#include <string>
#include <vector>

class Celestial_Body
{
public:
    Celestial_Body(std::string name, double size) : name{name}, size{size} {}

    std::string get_name() const
    {
        return name;
    }
    double get_size() const
    {
        return size;
    }

private:
    std::string const name;
    double const size;
};

class Star : public Celestial_Body
{
public:
    Star(std::string name, double size, std::string galaxy) : Celestial_Body(name, size), galaxy_name{galaxy} {}

    std::string get_galaxy() const
    {
        return galaxy_name;
    }

private:
    std::string const galaxy_name;
};

class Planet : public Celestial_Body
{
public:
    Planet(std::string name, double size, Star *star, double orbit_time, bool inhabited = false) : Celestial_Body(name, size),
                                                                                                   host_star{star},
                                                                                                   orbit_time{orbit_time},
                                                                                                   inhabited{inhabited} {}

    Star *get_celestial_body() const
    {
        return host_star;
    }

    double get_orbit_time() const
    {
        return orbit_time;
    }

    bool is_populated() const
    {
        return inhabited;
    }

    void populated(bool p)
    {
        inhabited = p;
    }

private:
    Star *const host_star{};
    double const orbit_time;
    bool inhabited;
};

class Moon : public Planet
{
    Moon(std::string name, double size, Star *star, double orbit_time, bool inhabited = false) : 
        Planet(name, size, star, orbit_time, inhabited), host_planet{} {}
    
    private:
    Planet * const host_planet;
};

void print(const Celestial_Body &cb)
{
    // Depending on kind of celestial body, print its correspending data. Output
    // shall be as follows:
    // Helios: star, radius 696342.0 km, belongs to galaxy Milky Way
    // Earth: planet, radius 6371.0 km, belongs to star Helios, orbit time 365.2 days, populated
    // Moon: moon, radius 1737.1 km, belongs to planet Earth, orbit time 27.3 days, not populated
}

int main()
{
    // Declare statically one object of each of type Star, Planet, and Moon. Use
    // the following data to initialize the objects (use defaults when suitable):
    // Star: name Helios, radius 696342.0, belongs to galaxy Milky Way
    // Planet: name Earth, radius 6371.0, belongs to star Helios, orbit time 365.2 days, populated
    // Moon: name Moon, radius 1737.1, belongs to planet Earth, orbit time 27.3 days, not populated
    auto helios = Star("Helios", 696342.0, "Milky Way");
    auto earth = Planet("Earth", 6371.0, &helios, 365.2, true);
    auto moon = Moon("Moon", 1737.1,)
    // Call print() for each object above.



    return 0;
}