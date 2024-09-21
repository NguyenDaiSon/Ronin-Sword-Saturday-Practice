package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func NewListNode(value int) *ListNode {
	return &ListNode{Val: value}
}

func (head *ListNode) Dump() {
	for current := head; current != nil; current = current.Next {
		fmt.Printf("%d ", current.Val)
	}
	fmt.Println()
}

func buildSortedList(values []int) *ListNode {
	var head, current *ListNode
	for _, value := range values {
		node := NewListNode(value)
		if head == nil {
			head = node
		} else {
			current.Next = node
		}
		current = node
	}
	return head
}

// ///////////////////////////////////////////////////////////
// LC: 83. Remove Duplicates from Sorted List
// ///////////////////////////////////////////////////////////
func deleteDuplicatesInSortedList(head *ListNode) *ListNode {
	for current := head; current != nil && current.Next != nil; {
		if current.Val == current.Next.Val {
			current.Next = current.Next.Next
		} else {
			current = current.Next
		}
	}
	return head
}

func main() {
	head := buildSortedList([]int{1, 1, 2, 3, 3})
	head.Dump()
	deleteDuplicatesInSortedList(head)
	head.Dump()
}
