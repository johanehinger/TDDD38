#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

struct Printable 
{
    virtual void print(std::ostream&) = 0;
};

struct Serializable
{
    virtual std::string serialize() = 0;
    virtual bool deserialize(std::string) = 0;
};

class Message : public Printable
{
public:
    Message(std::string const& msg) : msg{msg} {}
    void print(std::ostream& os) override 
    {
        os << msg;
    }

private:
    std::string msg;
};

class Integer : public Printable, public Serializable
{
public:
    Integer(int data) : data{data} {}

    void print(std::ostream& os) override 
    {
        os << data;
    }

    std::string serialize() override
    {
        return std::to_string(data);
    }

    bool deserialize(std::string str) override
    {
        return ((data = std::stoi(str)));
    }

private:
    int data;
};


using namespace std;

vector<string> serialize(vector<Printable *> const& v)
{
  vector<string> result{};
  for (Printable* obj : v)
  {
    if (auto p = dynamic_cast<Serializable*>(obj))
    { 
      result.push_back(p->serialize());
    }
  }
  return result;
}

void print(ostream& os, vector<Printable *> const& v)
{
  for (Printable* obj : v)
  {
    obj->print(os);
    os << endl;
  }
}

int main()
{
    
  vector<Printable* > v = {
    new Message{"Hello there"},
    new Integer{0},
    new Message{"This is a message"},
    new Integer{100053},
    new Integer{-5}
  };

  {
    vector<string> result {serialize(v)};
    assert((result == vector<string>{"0", "100053", "-5"}));
  }
  
  {
    ostringstream oss{};
    print(oss, v);
    assert(oss.str() == "Hello there\n0\nThis is a message\n100053\n-5\n");
  }

  {
    Integer i{0};
    assert(i.deserialize("15"));
    assert(i.serialize() == "15");
  }
  
}