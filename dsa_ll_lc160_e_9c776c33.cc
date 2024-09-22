#include <iostream>
#include <initializer_list>

class List {
public:
	struct Node;

	List(const std::initializer_list<int>& initValues);
	~List();

	void Print() const;
	Node* MakeIntersectionWith(const List& otherList, int atOtherListPos);
	void ClearIntersection(Node *tail);


	/////////////////////////////////////////////
	// LC: 160. Intersection of Two Linked Lists
	// //////////////////////////////////////////
	Node* GetIntersectionNode(const List& other);
private:
	Node *head_;

	// Deleting copy semantics also disables move semantics.
	List(const List&) = delete;
	List& operator= (const List&) = delete;
};

class List::Node {
public:
	Node(int val, Node* next = nullptr);
	friend std::ostream& operator << (std::ostream& stream, const Node* node);

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

std::ostream& operator << (std::ostream& stream, const List::Node* node)
{
	if (node == nullptr) {
		return stream << "None";
	} else {
		return stream << "List::Node(val=" << node->val_ << ")";
	}
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

List::Node* List::MakeIntersectionWith(const List& otherList, int atOtherListPos)
{
	decltype(head_) tail = nullptr;
	for (auto current = head_; current != nullptr; current = current->next_) {
		tail = current;
	}

	int pos = 0;
	for (auto current = otherList.head_; current != nullptr; current = current->next_) {
		if (pos++ == atOtherListPos) {
			std::cout << "Creating IntersectionNode: " << current << std::endl;
			if (head_ == nullptr) {
				tail = current;
				head_ = tail;
			} else {
				tail->next_ = current;
			}
			
			break;
		}
	}

	return tail;
}

void List::ClearIntersection(Node* tail)
{
	if (tail != nullptr)
	{
		tail->next_ = nullptr;
	}

	if (head_ == tail) 
	{
		head_ = nullptr;
	}
}


List::Node* List::GetIntersectionNode(const List& other)
{
	auto nextNodeFn = [](Node* node, Node* head) -> Node* {
		return node != nullptr ? node->next_ : head;
	};

	auto current = head_;
	auto other_current = other.head_;
	while (current != other_current) {
		current = nextNodeFn(current, other.head_);
		other_current = nextNodeFn(other_current, head_);
	}

	return current;
}

int main() {
	List listA{4, 1};
	List listB{5, 6, 1, 8, 4, 5};
	listA.Print();
	listB.Print();

	std::cout << "IntersectionNode: " << std::boolalpha << listA.GetIntersectionNode(listB) << std::endl;
	const auto tailA = listA.MakeIntersectionWith(listB, 3);
	std::cout << "IntersectionNode: " << std::boolalpha << listA.GetIntersectionNode(listB) << std::endl;
	std::cout << "IntersectionNode: " << std::boolalpha << listB.GetIntersectionNode(listA) << std::endl;
	listA.ClearIntersection(tailA);


	return 0;

}
