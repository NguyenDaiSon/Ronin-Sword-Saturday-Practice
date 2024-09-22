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

// Comparing object addresses to detect cycles is not a reliable approach
func HasCycle(head *ListNode) bool {
	for current := head; current != nil && current.Next != nil; current = current.Next {
		if uintptr(unsafe.Pointer(current.Next)) <= uintptr(unsafe.Pointer(current)) {
			return true
		}
	}
	return false
}

func HasCycleV2(head *ListNode) bool {
	slow, fast := head, head
	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
		if slow == fast {
			return true
		}
	}
	return false
}

func main() {
	head := BuildList([]int{3, 2, 0, -4})
	fmt.Printf("Has Cycle V1: %t\n", HasCycle(head))
	fmt.Printf("Has Cycle V2: %t\n", HasCycleV2(head))

	head = MakeCycle(1, head)
	fmt.Printf("Has Cycle V1: %t\n", HasCycle(head))
	fmt.Printf("Has Cycle V2: %t\n", HasCycleV2(head))
}
