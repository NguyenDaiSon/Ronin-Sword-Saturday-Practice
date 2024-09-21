#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <memory>

class List 
{
	struct Node;
	std::unique_ptr<Node> head_;

public:
	List(const std::initializer_list<int>& values);

	void Print() const;

	/////////////////////////////////////////////
	// LC: 83. Remove Duplicates from Sorted List
	// //////////////////////////////////////////
	void DeleteDuplicates();


	// Deleting copy semantics also disables move semantics.
	List(const List&) = delete;
	List& operator = (const List&) = delete;
};

struct List::Node 
{
	int val;
	std::unique_ptr<Node> next;


	Node(int val, std::unique_ptr<Node> next = nullptr);

	// Deleting copy semantics also disables move semantics.
	Node(const Node&) = delete;
	Node& operator= (const Node&) = delete;
};

List::Node::Node(int val, std::unique_ptr<Node> next)
	: val{val}
	, next{std::move(next)}
{
}

List::List(const std::initializer_list<int>& values)
	: head_{nullptr}
{
	std::vector<int> initValues{values.begin(), values.end()};
	std::sort(initValues.begin(), initValues.end());

	std::unique_ptr<Node> *current = &head_; 
	for (const auto& value : initValues)
	{
		*current = std::make_unique<Node>(value);
		current = &((*current)->next);
	}
}


void List::Print() const 
{
	for (auto current = head_.get(); current != nullptr; current = current->next.get())
	{
		std::cout << current->val << ' ';
	}
	std::cout << std::endl;
}

/////////////////////////////////////////////
// LC: 83. Remove Duplicates from Sorted List
// //////////////////////////////////////////
void List::DeleteDuplicates()
{
	auto current = head_.get();
	while (current != nullptr && current->next != nullptr) 
	{
		if (current->val == current->next->val) 
		{

			////////////////////////////////////////////////////////
			/// Handle potential memory leak without smart pointers
			////////////////////////////////////////////////////////

			current->next = std::move(current->next->next);
		} 
		else 
		{
			current = current->next.get();
		}
	}
}

int main() 
{
	List list{1, 1, 2, 3, 3};
	list.Print();
	list.DeleteDuplicates();
	list.Print();
}
