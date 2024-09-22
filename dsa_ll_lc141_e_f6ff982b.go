package main

import (
	"fmt"
	"unsafe"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func NewListNode(val int) *ListNode {
	return &ListNode{Val: val}
}

func BuildList(values []int) *ListNode {
	var head *ListNode
	var current *ListNode

	for _, value := range values {
		newNode := NewListNode(value)
		if head == nil {
			head = newNode
		} else {
			current.Next = newNode
		}
		current = newNode
	}

	return head
}

func MakeCycle(cyclePos int, head *ListNode) *ListNode {
	var circle *ListNode
	var tail *ListNode

	pos := 0
	current := head
	for current != nil {
		if pos == cyclePos {
			circle = current
		}

		pos += 1
		tail = current
		current = current.Next
	}

	if tail != nil && circle != nil {
		tail.Next = circle
	}

	return head
}

func HasCycle(head *ListNode) bool {
	for current := head; current != nil && current.Next != nil; current = current.Next {
		if uintptr(unsafe.Pointer(current.Next)) <= uintptr(unsafe.Pointer(current)) {
			return true
		}
	}
	return false
}

func main() {
	head := BuildList([]int{3, 2, 0, -4})
	fmt.Printf("Has Cycle: %t\n", HasCycle(head))

	head = MakeCycle(1, head)
	fmt.Printf("Has Cycle: %t\n", HasCycle(head))
}
