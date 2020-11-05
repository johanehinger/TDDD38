#include <cassert>

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

  void push(int const& value)
  {
    head = new Node{value, head};
  }

  int pop()
  {
    int result{top()};
    Node* old {head};
    head = head->next;
    delete old;
    return result;
  }

  int& top()
  {
    return head->value;
  }

  int const& top() const
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
    int value;
    Node* next;
  };

  Node* head;

};

int main()
{
  Stack st {};
  assert(st.empty());

  st.push(1);
  assert(!st.empty());
  assert(st.top() == 1);

  st.push(2);
  assert(st.top() == 2);
  assert(st.pop() == 2);

  assert(st.pop() == 1);

  assert(st.empty());

  st.push(3);
  assert(st.pop() == 3);

  st.push(4);

  st.push(5);
  assert(st.pop() == 5);
}
