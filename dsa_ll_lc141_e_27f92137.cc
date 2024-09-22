#include <iostream>
#include <initializer_list>

class List {
public:
	struct Node;

	List(const std::initializer_list<int>& initValues);
	~List();
	void Print() const;

	Node* MakeCycle(int cyclePos);
	void ClearCycle(Node *tail);


	/////////////////////////////////////////////
	// LC: 141. Linked List Cycle
	// //////////////////////////////////////////
	bool HasCycle() const;
private:
	Node *head_;

	// Deleting copy semantics also disables move semantics.
	List(const List&) = delete;
	List& operator= (const List&) = delete;
};

class List::Node {
public:
	Node(int val, Node* next = nullptr);

private:
	int val_;
	Node* next_;

	// Deleting copy semantics also disables move semantics.
	Node(const Node&) = delete;
	Node& operator = (const Node&) = delete;

	friend List;
};

List::Node::Node(int val, Node *next)
	: val_{val}
	, next_{next}
{

}

List::List(const std::initializer_list<int>& initValues)
	: head_{nullptr}
{
	auto current = head_;
	for (const auto& value : initValues) {
		auto newNode = new Node(value);
		if (head_ == nullptr) {
			head_ = newNode;
		} else {
			current->next_ = newNode;
		}
		current = newNode;
	}
}

List::~List() 
{
	if (HasCycle()) 
	{
		auto tail = MakeCycle(-1); 
		ClearCycle(tail);
	}
	
	auto current = head_;
	while (current != nullptr)
	{
		auto delNode = current;
		current = current->next_;

		delNode->next_ = nullptr;
		delete delNode;
	}
	head_ = nullptr;
}

void List::Print() const 
{
	for (auto current = head_; current != nullptr; current = current->next_)
	{
		std::cout << current->val_ << ' ';
	}
	std::cout << std::endl;
}

List::Node* List::MakeCycle(int cyclePos)
{
	auto current = head_;
	decltype(head_) circle = nullptr;
	decltype(head_) tail = nullptr;
	int pos = 0;

	while (current != nullptr)
	{
		if (pos == cyclePos)
		{
			circle = current;
		}

		tail = current;
		current = current->next_;
		++pos;
	}

	if (tail != nullptr && circle != nullptr) {
		tail->next_ = tail;
	}

	return tail;
}

void List::ClearCycle(Node* tail)
{
	if (tail != nullptr)
	{
		tail->next_ = nullptr;
	}
}

bool List::HasCycle() const 
{
	auto slow = head_;
	auto fast = head_;
	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;
		if (slow == fast)
		{
			return true;
		}
	}

	return false;
}

int main() {
	{
		List list{3, 2, 0, -4};
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		auto tail = list.MakeCycle(1);
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		list.ClearCycle(tail);
	}

	{
		List list{3};
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		auto tail = list.MakeCycle(1);
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		list.ClearCycle(tail);
	}
	
	{
		List list{3};
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		auto tail = list.MakeCycle(0);
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		list.ClearCycle(tail);
	}

	{
		List list{};
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		auto tail = list.MakeCycle(0);
		std::cout << "Has Cycle: "<< std::boolalpha << list.HasCycle() << std::endl;
		list.ClearCycle(tail);
	}
	return 0;
}
