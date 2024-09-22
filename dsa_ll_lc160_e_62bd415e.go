package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func NewListNode(val int) *ListNode {
	return &ListNode{Val: val}
}

func (head *ListNode) Print() {
	for current := head; current != nil; current = current.Next {
		fmt.Printf("%d ", current.Val)
	}
	fmt.Println()
}

func MakeList(values []int) *ListNode {
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

func (headA *ListNode) CreateIntersectionWith(headB *ListNode, atBPos int) {
	var tailA *ListNode
	for currentA := headA; currentA != nil; currentA = currentA.Next {
		tailA = currentA
	}

	bPos := 0
	for currentB := headB; currentB != nil; currentB = currentB.Next {
		if bPos == atBPos {
			if headA != nil {
				tailA.Next = currentB
			} else {
				tailA = currentB
				headA = tailA
			}

			fmt.Printf("Creating Intersection-Node=%+v\n", currentB)
			break
		}

		bPos++
	}
}

// ///////////////////////////////////////////////////////////
// LC: 160. Intersection of Two Linked Lists
// ///////////////////////////////////////////////////////////
func (headA *ListNode) GetIntersectionNode(headB *ListNode) *ListNode {
	nextNodeFn := func(nodeListX, headListY *ListNode) *ListNode {
		if nodeListX != nil {
			nodeListX = nodeListX.Next
		} else {
			nodeListX = headListY
		}
		return nodeListX
	}

	currentA, currentB := headA, headB
	for currentA != currentB {
		currentA = nextNodeFn(currentA, headB)
		currentB = nextNodeFn(currentB, headA)
	}

	return currentA
}

func main() {
	listA := MakeList([]int{4, 1})
	listB := MakeList([]int{5, 6, 1, 8, 4, 5})
	listA.Print()
	listB.Print()

	fmt.Printf("Intersection-Node=%+v\n", listA.GetIntersectionNode(listB))
	fmt.Printf("Intersection-Node=%+v\n", listB.GetIntersectionNode(listA))
	listA.CreateIntersectionWith(listB, 3)
	fmt.Printf("Intersection-Node=%v\n", listA.GetIntersectionNode(listB))
	fmt.Printf("Intersection-Node=%v\n", listB.GetIntersectionNode(listA))
}
