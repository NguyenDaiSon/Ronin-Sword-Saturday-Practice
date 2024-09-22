#include <initializer_list>
#include <iostream>

// clang-format -i -style=google dsa_ll_lc876_e_8f3e04bf.cc
//
class List {
 public:
  struct Node;

  List(const std::initializer_list<int> &initValues);
  ~List();

  void Print() const;

  /////////////////////////////////////////////
  // LC: 876. Middle of the Linked List
  // //////////////////////////////////////////
  const Node *GetMiddleNode() const;

 private:
  Node *head_;

  // Deleting copy semantics also disables move semantics.
  List(const List &) = delete;
  List &operator=(const List &) = delete;
};

class List::Node {
 public:
  Node(int val, Node *next = nullptr);
  friend std::ostream &operator<<(std::ostream &stream, const Node *node);

 private:
  int val_;
  Node *next_;

  // Deleting copy semantics also disables move semantics.
  Node(const Node &) = delete;
  Node &operator=(const Node &) = delete;

  friend List;
};

List::Node::Node(int val, Node *next) : val_{val}, next_{next} {}

std::ostream &operator<<(std::ostream &stream, const List::Node *node) {
  if (node == nullptr) {
    return stream << "None";
  } else {
    return stream << "List::Node(val=" << node->val_ << ")";
  }
}

List::List(const std::initializer_list<int> &initValues) : head_{nullptr} {
  auto current = head_;
  for (const auto &value : initValues) {
    auto newNode = new Node(value);
    if (head_ == nullptr) {
      head_ = newNode;
    } else {
      current->next_ = newNode;
    }
    current = newNode;
  }
}

List::~List() {
  auto current = head_;
  while (current != nullptr) {
    auto delNode = current;
    current = current->next_;

    delNode->next_ = nullptr;
    delete delNode;
  }
  head_ = nullptr;
}

void List::Print() const {
  for (auto current = head_; current != nullptr; current = current->next_) {
    std::cout << current->val_ << ' ';
  }
  std::cout << std::endl;
}

const List::Node *List::GetMiddleNode() const {
  auto slow = head_;
  auto fast = head_;
  while (fast != nullptr && fast->next_ != nullptr) {
    slow = slow->next_;
    fast = fast->next_->next_;
  }
  return slow;
}

int main() {
  {
    List list{};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  {
    List list{1};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  {
    List list{1, 2};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  {
    List list{1, 2, 3};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  {
    List list{1, 2, 3, 4};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  {
    List list{1, 2, 3, 4, 5};
    list.Print();
    std::cout << "MiddleNode: " << list.GetMiddleNode() << std::endl;
  }

  return 0;
}
