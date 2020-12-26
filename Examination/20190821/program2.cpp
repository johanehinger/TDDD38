#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <typeinfo>

/* if implemented correctly this program
   should give the following output:

Rhea Deer recommends reading "The Lord of the Rings".
Rhea Deer recommends reading "Winnie the Pooh".
Rhea Deer recommends reading "The Da Vinci Code (best seller)".
Rhea Deer recommends reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Rhea Deer recommends reading "Course Literature".
Professor McProfessorsen does not recommend reading "The Lord of the Rings".
Professor McProfessorsen does not recommend reading "Winnie the Pooh".
Professor McProfessorsen does not recommend reading "The Da Vinci Code (best seller)".
Professor McProfessorsen does not recommend reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Professor McProfessorsen recommends reading "Course Literature".
Christopher Robin does not recommend reading "The Lord of the Rings".
Christopher Robin recommends reading "Winnie the Pooh".
Christopher Robin does not recommend reading "The Da Vinci Code (best seller)".
Christopher Robin recommends reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Christopher Robin does not recommend reading "Course Literature".
Sherlock Holmes recommends reading "The Lord of the Rings".
Sherlock Holmes recommends reading "Winnie the Pooh".
Sherlock Holmes does not recommend reading "The Da Vinci Code (best seller)".
Sherlock Holmes does not recommend reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Sherlock Holmes does not recommend reading "Course Literature".
*/

class Book
{
public:
   Book(std::string const& title) : title{title} {}
   Book() : title{} {}
   virtual bool for_children() const = 0;
   virtual ~Book() = default;
   
   std::string get_title() const
   {
      return title;
   }
private:
   std::string title;
};

class Non_Fiction : public Book
{
public:
   Non_Fiction(std::string title) : Book(title) {}
   Non_Fiction() : Book() {}
   bool for_children() const override
   {
      return false;
   }
};

class Fiction : public Book
{
private:
   bool is_childrens_book;
public:
   Fiction(std::string title, bool is_childrens_book = false) : 
      Book(title), is_childrens_book{is_childrens_book} {}
   bool for_children() const override
   {
      return is_childrens_book;
   }
};

class Crime_Fiction : public Book
{
private:
   bool is_childrens_book;
public:
   Crime_Fiction(std::string title, bool is_childrens_book = false) : 
      Book(title + " (best seller)"), is_childrens_book{is_childrens_book} {}
   bool for_children() const override
   {
      return is_childrens_book;
   }
};

class Reader
{
private:
   std::string name;
public:
   Reader(std::string name) : name{name} {}
   Reader() : name{} {}

   virtual ~Reader() = default;
   virtual bool likes(Book*) const
   {
      return true;
   }

   void read(Book* book) const
   {
      if (likes(book))
      {
         std::cout << name << " recommends reading " << book->get_title() << std::endl;
      }
      else
      {
         std::cout << name << " does not recommends reading " << book->get_title() << std::endl;
      }
   }
};

class Academic : public Reader
{
public:
   Academic(std::string name) : Reader(name) {}
   Academic() : Reader() {}

   bool likes(Book* book) const override 
   {
      return (dynamic_cast<Non_Fiction*>(book));
   }
};

class Child : public Reader
{
public:
   Child(std::string name) : Reader(name) {}
   Child() : Reader() {}

   bool likes(Book* book) const override 
   {
      return (book->for_children());
   }
};

class Detective : public Reader
{
public:
   Detective(std::string name) : Reader(name) {}
   Detective() : Reader() {}

   bool likes(Book* book) const override 
   {
      return (dynamic_cast<Fiction*>(book));

   }

};

int main()
{
  std::vector<Reader *> readers {
    new Reader{"Rhea Deer"},
    new Academic{"Professor McProfessorsen"},
    new Child{"Christopher Robin"},
    new Detective{"Sherlock Holmes"}
  };

  std::vector<Book*> books {
    new Fiction{"The Lord of the Rings"},
    new Fiction{"Winnie the Pooh", true},
    new Crime_Fiction{"The Da Vinci Code"},
    new Crime_Fiction{"Nancy Drew: The Secret of the Old Clock", true},
    new Non_Fiction{"Course Literature"}
  };

  for (auto reader : readers)
  {
    for (auto book : books)
    {
      reader->read(book);
    }
  }

  for (auto reader : readers) {
     delete reader;
  }
  
  for (auto book : books) {
     delete book;
  }
}