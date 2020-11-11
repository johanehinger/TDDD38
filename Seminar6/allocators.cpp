#include <cassert>
#include <string>
#include <iostream>

template<typename T>
struct New_allocator
{
  template<typename... Args>
  static T* create(Args&&... args)
  {
    return new T(std::forward<Args>(args)...);
  }

  static void destroy(T* object)
  {
    delete object;
  }
};

template<typename T>
struct Tracker_allocator
{
  template<typename... Args>
  static T* create(Args&&... args)
  {
    std::cout << "create" << std::endl;
    return new T(std::forward<Args>(args)...);
  }

  static void destroy(T* object)
  {
    std::cout << "delete" << std::endl;
    delete object;
  }
};

template<typename T, template <typename> typename allocator = New_allocator>
class Stack
{

  struct Node;

public:

  Stack()
    : head{nullptr} { }

  Stack(Stack const&) = delete;
  Stack(Stack&&) = delete;

  Stack& operator=(Stack const&) = delete;
  Stack& operator=(Stack&&) = delete;

  ~Stack()
  {
    while (!empty())
    {
      pop();
    }
  }

  void push(T const& value)
  {
    head = allocator<Node>::create(value, head);
  }

  T pop()
  {
    T result{top()};
    Node* old {head};
    head = head->next;
    //delete old;
    allocator<Node>::destroy(old);
    return result;
  }

  T& top()
  {
    return head->value;
  }

  T const& top() const
  {
    return head->value;
  }

  bool empty() const
  {
    return head == nullptr;
  }

private:

  struct Node
  {
    T value;
    Node* next;

    template<typename U>
    Node(U&& value, Node* next) : value{std::forward<U>(value)}, next{next} {}
  };

  Node* head;

};

int main()
{
  {
    Stack<std::string> st {};
    assert(st.empty());

    st.push("1");
    assert(!st.empty());
    assert(st.top() == "1");

    st.push("2");
    assert(st.top() == "2");
    assert(st.pop() == "2");

    assert(st.pop() == "1");

    assert(st.empty());

    st.push("3");
    assert(st.pop() == "3");

    st.push("4");

    st.push("5");
    assert(st.pop() == "5");
  }
  {
    Stack<std::string, Tracker_allocator> st {};
    assert(st.empty());

    st.push("1");
    assert(!st.empty());
    assert(st.top() == "1");

    st.push("2");
    assert(st.top() == "2");
    assert(st.pop() == "2");

    assert(st.pop() == "1");

    assert(st.empty());

    st.push("3");
    assert(st.pop() == "3");

    st.push("4");

    st.push("5");
    assert(st.pop() == "5");
  }
}
